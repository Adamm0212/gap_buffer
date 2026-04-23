#include "gap_buffer.h"
#include <algorithm>
#include <sstream>
#include <stdexcept>

namespace Gap_buffer {

    class GapBufferException : public std::runtime_error {
        public:
            explicit GapBufferException(const std::string& message) 
                : std::runtime_error("GapBuffer Error: " + message) {}
    };

    class GapBuffer::Impl {
        friend class GapBuffer;

    private:
        char* buffer;
        int capacity;
        int gap_start;
        int gap_end;

        Impl(int default_capacity = 10) : capacity(default_capacity), gap_start(0), gap_end(default_capacity) {
            buffer = new char[capacity];
        }

        // copy constructor of Impl
        Impl(const Impl& other) : capacity(other.capacity), gap_start(other.gap_start), gap_end(other.gap_end) {
            buffer = new char[capacity];
            std::copy(other.buffer, other.buffer + capacity, buffer);
        }

        ~Impl() {
            delete[] buffer;
        }

        int size() const {
            return capacity - (gap_end - gap_start);
        }

        char charAt(int index) const {
            if (index < gap_start) {
                return buffer[index];
            }

            return buffer[index + (gap_end - gap_start)];
        }

        int compareTo(const Impl& other) const {
            int left_size = size();
            int right_size = other.size();
            int min_size = std::min(left_size, right_size);

            for (int i = 0; i < min_size; ++i) {
                char left = charAt(i);
                char right = other.charAt(i);

                if (left < right) {
                    return -1;
                }
                if (left > right) {
                    return 1;
                }
            }

            if (left_size < right_size) {
                return -1;
            }
            if (left_size > right_size) {
                return 1;
            }

            return 0;
        }

        void insert(char value) {
            if (gap_start == gap_end) {
                grow();
            }
            buffer[gap_start] = value;
            gap_start++;
        }

        void eraseBeforeCursor(int count) {
            for (int i = 0; i < count && gap_start > 0; ++i) {
                gap_start--;
            }
        }

        void updateAtCursor(char value) {
            if (gap_end == capacity) {
                throw GapBufferException("No character to update");
            }
            buffer[gap_end] = value;
        }

        int find(char value) const {
            for (int i = 0 ; i < gap_start; ++i) {
                if (buffer[i] == value) {
                    return i;
                }
            }

            for (int i = gap_end ; i < capacity; ++i) {
                if (buffer[i] == value) {
                    return i - (gap_end - gap_start);
                }
            }
            return 404;
        }

        void clear() {
            gap_start = 0;
            gap_end = capacity;
        }

        void shiftGap(int new_pos) {
            while(new_pos < gap_start) {
                moveLeft();
            }
            while(new_pos > gap_start) {
                moveRight();
            }
        }

        std::string toString() const {
            std::stringstream ss;
            for (int i = 0 ; i < gap_start ; ++i) {
                ss << buffer[i];
            }
            for (int i = gap_end ; i < capacity ; ++i) {
                ss << buffer[i];
            }
            int current_size = size();
            ss << " (size: " << current_size << "/" << capacity << ")";
            return ss.str();
        }

        void grow() {
            int old_capacity = capacity;
            capacity *= 2;
            char* new_buffer = new char[capacity];

            for (int i = 0 ; i < gap_start; ++i) {
                new_buffer[i] = buffer[i];
            }

            int suffix_size = old_capacity - gap_end;
            int new_gap_end = capacity - suffix_size;

            for (int i = 0 ; i < suffix_size ; ++i) {
                new_buffer[new_gap_end + i] = buffer[gap_end + i];
            }

            delete[] buffer;
            buffer = new_buffer;
            gap_end = new_gap_end;
        }

        void moveLeft() {
            if (gap_start > 0) {
                // Move the character left of the gap to the right
                gap_start--;
                gap_end--;
                buffer[gap_end] = buffer[gap_start];
            }
        }

        void moveRight() {
            if (gap_end < capacity) {
                // Move the character right of the gap to the left
                buffer[gap_start] = buffer[gap_end];
                gap_start++;
                gap_end++;
            }
        }
    };

    GapBuffer::GapBuffer() : implementation(new Impl()) 
    {
    }

    GapBuffer::~GapBuffer() {
        delete implementation;
    }

    GapBuffer::GapBuffer(const GapBuffer& other) {
        implementation = new Impl(*(other.implementation));
    }

    GapBuffer& GapBuffer::operator=(const GapBuffer& other) {
        if (this != &other) {
            delete implementation;
            implementation = new Impl(*(other.implementation));
        }
        return *this;
    }

    // CRUD operations

    GapBuffer& GapBuffer::operator+=(char value) {
        implementation->insert(value);
        return *this;
    }

    GapBuffer& GapBuffer::operator-=(int count) {
        if (count < 0) {
            throw GapBufferException("Count must be positive");
        }
        implementation->eraseBeforeCursor(count);
        return *this;
    }

    GapBuffer& GapBuffer::operator*=(char value) {
        implementation->updateAtCursor(value);
        return *this;
    }

    int GapBuffer::operator[](char value) const {
        return implementation->find(value);
    }

    void GapBuffer::operator!() {
        implementation->clear();
    }

    // Utilities
    void GapBuffer::moveCursor(int position) {
        if (position < 0 || position > implementation->size()) {
            throw GapBufferException("Position out of bounds");
        }
        implementation->shiftGap(position);
    }

    std::string GapBuffer::toString() const {
        return implementation->toString();
    }

    // Comparison operators
    bool GapBuffer::operator==(const GapBuffer& other) const {
        return implementation->compareTo(*other.implementation) == 0;
    }

    bool GapBuffer::operator!=(const GapBuffer& other) const {
        return !(*this == other);
    }

    bool GapBuffer::operator<(const GapBuffer& other) const {
        return implementation->compareTo(*other.implementation) < 0;
    }

    bool GapBuffer::operator<=(const GapBuffer& other) const {
        return implementation->compareTo(*other.implementation) <= 0;
    }

    bool GapBuffer::operator>(const GapBuffer& other) const {
        return implementation->compareTo(*other.implementation) > 0;
    }

    bool GapBuffer::operator>=(const GapBuffer& other) const {
        return implementation->compareTo(*other.implementation) >= 0;
    }

}
