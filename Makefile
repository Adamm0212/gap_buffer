ifeq ($(OS),Windows_NT)
    # Windows settings
    RM = del /Q /F
    EXE_EXT = .exe
    CLEAN_LOG = if exist log.txt del log.txt
else
    # Linux/macOS settings
    RM = rm -f
    EXE_EXT =
    CLEAN_LOG = rm -f log.txt
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: rebuild

gap_buffer.o: gap_buffer.cpp gap_buffer.h
	$(CXX) $(CXXFLAGS) -c gap_buffer.cpp -o gap_buffer.o

build_demo: gap_buffer.o demo.cpp
	$(CXX) $(CXXFLAGS) gap_buffer.o demo.cpp -o demo_prog$(EXE_EXT)

run_demo: build_demo
	./demo_prog$(EXE_EXT)

build_test: gap_buffer.o test.cpp
	$(CXX) $(CXXFLAGS) gap_buffer.o test.cpp -o test_prog$(EXE_EXT)

run_test: build_test
	./test_prog$(EXE_EXT)

clean:
	$(RM) *.o demo_prog$(EXE_EXT) test_prog$(EXE_EXT)
	$(CLEAN_LOG)

rebuild: clean run_test run_demo


.PHONY: build_demo run_demo build_test run_test clean rebuild all