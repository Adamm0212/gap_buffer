#ifndef GAP_BUFFER_H_342432
#define GAP_BUFFER_H_342432

#include <iostream>
namespace gap_buffer {
    class GapBuffer {
    public:
        GapBuffer();
        ~GapBuffer();
        GapBuffer(const GapBuffer& other);
        GapBuffer& operator=(const GapBuffer& other);

        // ----- CRUD operations as operators -----

        // Add a character to the buffer
        GapBuffer& operator+=(char value);
        // Delete a character from the buffer
        GapBuffer& operator-=(int count);
        // Update a character in the buffer
        GapBuffer& operator*=(char value);

        std::string toString() const;

        // operator[] for returning the position of the gap
        int operator[](char value) const;
        // operator! to clear the buffer
        void operator!();

        std::string to_string() const;

        // ----- Common operations -----
        // 6 logical comparison operators
        bool operator==(const GapBuffer& other) const;
        bool operator!=(const GapBuffer& other) const;
        bool operator<(const GapBuffer& other) const;
        bool operator<=(const GapBuffer& other) const;
        bool operator>(const GapBuffer& other) const;
        bool operator>=(const GapBuffer& other) const;

        void moveCursor(int position);

    private:
        struct Impl;
        Impl* implementation;
    };
}

#endif 
