#ifndef GAP_BUFFER_H_342432
#define GAP_BUFFER_H_342432

#include <string>

namespace Gap_buffer {
    class GapBuffer {
        private:
            struct Impl;
            Impl* implementation;

        public:
            GapBuffer();
            ~GapBuffer();
            GapBuffer(const GapBuffer& other);
            GapBuffer& operator=(const GapBuffer& other);

            // ----- CRUD operations as operators -----

            // Add a character at the current cursor position
            GapBuffer& operator+=(char value);
            // Delete count characters before the cursor
            GapBuffer& operator-=(int count);
            // Replace the character at the cursor
            GapBuffer& operator*=(char value);

            // Return buffer contents and metadata as a string
            std::string toString() const;

            // Find a character and return its logical index
            int operator[](char value) const;
            // Clear the buffer contents
            void operator!();



            // ----- Common operations -----
            // 6 logical comparison operators
            bool operator==(const GapBuffer& other) const;
            bool operator!=(const GapBuffer& other) const;
            bool operator<(const GapBuffer& other) const;
            bool operator<=(const GapBuffer& other) const;
            bool operator>(const GapBuffer& other) const;
            bool operator>=(const GapBuffer& other) const;

            // Move the cursor to a logical position in the text
            void moveCursor(int position);
    };
}

#endif 
