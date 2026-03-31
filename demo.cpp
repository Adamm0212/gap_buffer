#include "gap_buffer.h"
#include <iostream>
#include <string>

using namespace gap_buffer;

int main() {
    std::cout << "=====================================================" << std::endl;
    std::cout << "      GAP BUFFER ADT: FEATURE DEMONSTRATION          " << std::endl;
    std::cout << "=====================================================" << std::endl;

    GapBuffer gb;
    std::cout << "\n[INIT] Created an empty buffer (Default Capacity: 10)" << std::endl;
    std::cout << "State: " << gb.toString() << std::endl;

    std::cout << "\n[GROWTH] Adding 12 characters to trigger a 'grow()' event..." << std::endl;
    std::string text = "DYNAMIC_DATA";
    for(char c : text) {
        gb += c;
    }
    std::cout << "Notice capacity doubled to 20: " << gb.toString() << std::endl;

    std::cout << "\n[MOVE] Moving cursor to index 7 (after 'DYNAMIC')..." << std::endl;
    gb.moveCursor(7);
    
    std::cout << "[UPDATE] Replacing '_' with '-' using operator*=..." << std::endl;
    gb *= '-'; 
    std::cout << "State: " << gb.toString() << std::endl;

    std::cout << "\n[INSERT] Inserting 'NEW_' at the current cursor..." << std::endl;
    gb += 'N'; gb += 'E'; gb += 'W'; gb += '_';
    std::cout << "State: " << gb.toString() << std::endl;

    std::cout << "\n[READ] Searching for the position of character '-'..." << std::endl;
    int pos = gb['-'];
    std::cout << "Character '-' found at logical index: " << pos << std::endl;

    std::cout << "\n[DELETE] Deleting 4 characters (removing 'NEW_')..." << std::endl;
    gb -= 4;
    std::cout << "State: " << gb.toString() << std::endl;

    std::cout << "\n[COPY] Creating a deep copy 'gb2'..." << std::endl;
    GapBuffer gb2 = gb;
    gb2 += '!';
    std::cout << "Original gb: " << gb.toString() << std::endl;
    std::cout << "Copy gb2:     " << gb2.toString() << std::endl;
    std::cout << "Proof of Isolation: " << (gb != gb2 ? "SUCCESS" : "FAILED") << std::endl;

    // 8. Clear
    std::cout << "\n[CLEAR] Resetting the buffer using operator!..." << std::endl;
    !gb;
    std::cout << "Final State: " << gb.toString() << std::endl;

    std::cout << "\n=====================================================" << std::endl;
    std::cout << "             DEMONSTRATION COMPLETE                  " << std::endl;
    std::cout << "=====================================================" << std::endl;

    return 0;
}