# gap_buffer

A simple C++ implementation of a gap buffer data structure.

## Overview

`gap_buffer` is mostly used in text editors for fast insertion and deletion times with an average time of O(1).

## Build

From the repository root:

```bash
make build_demo
```

To run the demonstration:

```bash
make run_demo
```

## Example:

```cpp
#include "gap_buffer.h"
using namespace gap_buffer;

GapBuffer gb;
gb += 'H';
gb += 'i';
gb.moveCursor(1);
gb += ',';
std::cout << gb.toString() << std::endl;
```

## Notes

- Default capacity is 10 and doubles automatically when the gap is full.
- Use `make clean` to remove build artifacts.
- AI assistance was used in this project, mostly in demo.cpp
