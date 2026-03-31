#include "gap_buffer.h"
#include <iostream>
#include <cassert>
#include <fstream>

using namespace gap_buffer;

void log(std::ostream& os, std::ofstream& file, const std::string& message) {
    os << message << std::endl;
    file << message << std::endl;
}

int main() {
    std::ofstream logFile("test_log.txt");
    log(std::cout, logFile, "STARTING TESTS FOR GAP BUFFER");
    try {
        GapBuffer gb;
        log(std::cout, logFile, "Test 1: Adding characters");
        gb += 'H';
        gb += 'e';
        gb += 'l';
        gb += 'l';
        gb += 'o';
        assert(gb.toString() == "Hello (size: 5/10)");
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 2: Moving cursor");
        gb.moveCursor(1);
        gb += 'a';

        assert(gb.toString() == "Haello (size: 6/10)");
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 3: Testing update operator *=");
        gb *= 'A';
        assert(gb.toString() == "HaAllo (size: 6/10)");
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 4: Testing search operator []");
        assert(gb['A'] == 1);
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 5: Testing delete operator -=");
        gb -= 1;
        assert(gb.toString() == "Hello (size: 5/10)");
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 6: Testing deep copy");
        GapBuffer gb2 = gb;
        gb2 += '!';
        assert(gb.toString().find("!") == std::string::npos);
        assert(gb2.toString().find("!") != std::string::npos);
        log(std::cout, logFile, "Original: " + gb.toString());
        log(std::cout, logFile, "Copy: " + gb2.toString());
        log(std::cout, logFile, "PASSED");

        log(std::cout, logFile, "Test 7: Testing assignment operator =");
        GapBuffer gb3;
        gb3 = gb2;
        assert(gb3 == gb2);
        log(std::cout, logFile, "PASSED: " + gb3.toString());

        log(std::cout, logFile, "Test 8: Testing comparison operators");
        assert(gb != gb2);
        assert(gb < gb2);
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 9: Testing clear operator !");
        !gb;
        assert(gb.toString() == " (size: 0/10)");
        log(std::cout, logFile, "PASSED: " + gb.toString());

        log(std::cout, logFile, "Test 10: Testing out of bounds");
        try {
            gb.moveCursor(20);
            log(std::cout, logFile, "FAILED: No exception thrown for out of bounds");
        }
        catch (const std::exception& e) {
            log(std::cout, logFile, "PASSED: Caught expected exception: " + std::string(e.what()));
        }
    }
    catch (const std::exception& e) {
        log(std::cout, logFile, std::string("Test failed with exception: ") + e.what());
    }

    log(std::cout, logFile, "ALL TESTS COMPLETED");
    logFile.close();
    return 0;
}