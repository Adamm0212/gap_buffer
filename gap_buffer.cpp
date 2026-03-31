#include "gap_buffer.h"
#include <iostream>
#include <sstream>

namespace gap_buffer {

    class GapBufferException : public std::runtime_error {
        public:
            explicit GapBufferException(const std::string& message) 
                : std::runtime_error("GapBuffer Error: " + message) {}
    };

    class GapBuffer::Impl {
        friend class GapBuffer;
        public:
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

            void shiftGap(int new_pos) {
                while(new_pos < gap_start) {
                    moveLeft();
                }
                while(new_pos > gap_start) {
                    moveRight();
                }
            }
        private:
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

    GapBuffer::GapBuffer() : implementation(new Impl()) {}

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
        if (implementation->gap_start == implementation->gap_end) {
            implementation->grow();
        }
        implementation->buffer[implementation->gap_start] = value;
        implementation->gap_start++;
        return *this;
    }

    GapBuffer& GapBuffer::operator-=(int count) {
        if (count < 0) {
            throw GapBufferException("Count must be positive");
        }
        for (int i = 0; i < count && implementation->gap_start > 0; ++i) {
            implementation->gap_start--;
        }
        return *this;
    }

    GapBuffer& GapBuffer::operator*=(char value) {
        if (implementation->gap_end == implementation->capacity) {
            throw GapBufferException("No character to update");
        }
        implementation->buffer[implementation->gap_end] = value;
        return *this;
    }

    int GapBuffer::operator[](char value) const {
        for (int i = 0 ; i < implementation->gap_start; ++i) {
            if (implementation->buffer[i] == value) {
                return i;
            }
        }

        for (int i = implementation->gap_end ; i < implementation->capacity; ++i) {
            if (implementation->buffer[i] == value) {
                return i - (implementation->gap_end - implementation->gap_start);
            }
        }
        return -1;
    }

    void GapBuffer::operator!() {
        implementation->gap_start = 0;
        implementation->gap_end = implementation->capacity;
    }

    void GapBuffer::moveCursor(int position) {
        if (position < 0 || position > implementation->size()) {
            throw GapBufferException("Position out of bounds");
        }
        implementation->shiftGap(position);
    }

    std::string GapBuffer::toString() const {
        std::stringstream ss;
        for (int i = 0 ; i < implementation->gap_start ; ++i) {
            ss << implementation->buffer[i];
        }
        for (int i = implementation->gap_end ; i < implementation->capacity ; ++i) {
            ss << implementation->buffer[i];
        }
        int current_size = implementation->size();
        ss << " (size: " << current_size << "/" << implementation->capacity << ")";
        return ss.str();
    }

    bool GapBuffer::operator==(const GapBuffer& other) const {
        return this->toString() == other.toString();
    }

    bool GapBuffer::operator!=(const GapBuffer& other) const {
        return !(*this == other);
    }

    bool GapBuffer::operator<(const GapBuffer& other) const {
        return (implementation->size() < other.implementation->size());
    }

    bool GapBuffer::operator<=(const GapBuffer& other) const {
        return (*this < other) || (*this == other);
    }

    bool GapBuffer::operator>(const GapBuffer& other) const {
        return !(*this <= other);
    }

    bool GapBuffer::operator>=(const GapBuffer& other) const {
        return !(*this < other);
    }

}
