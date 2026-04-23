ifeq ($(OS),Windows_NT)
SHELL = powershell.exe
.SHELLFLAGS = -NoProfile -Command
EXE_EXT = .exe
else
EXE_EXT =
endif

CXX = g++
CXXFLAGS = -std=c++17 -Wall

all: build_test build_demo

gap_buffer.o: gap_buffer.cpp gap_buffer.h
	$(CXX) $(CXXFLAGS) -c gap_buffer.cpp -o gap_buffer.o

build_demo: gap_buffer.o demo.cpp gap_buffer.h
	$(CXX) $(CXXFLAGS) gap_buffer.o demo.cpp -o demo_prog$(EXE_EXT)

run_demo: build_demo
	./demo_prog$(EXE_EXT)

build_test: gap_buffer.o test.cpp gap_buffer.h
	$(CXX) $(CXXFLAGS) gap_buffer.o test.cpp -o test_prog$(EXE_EXT)

run_test: build_test
	./test_prog$(EXE_EXT)

clean:
ifeq ($(OS),Windows_NT)
	Remove-Item -Force -ErrorAction SilentlyContinue *.o, demo_prog.exe, test_prog.exe; exit 0
else
	rm -f *.o demo_prog test_prog
endif

rebuild: clean all

.PHONY: all build_demo run_demo build_test run_test clean rebuild
