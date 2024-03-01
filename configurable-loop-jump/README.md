# Configurable loop jump

Demonstrate a `for` loop which can be disrupted using either `break` or `continue`
with a one-line statement based on user input.

## Overview
The demo program `intsum` prints the sum of integers given as command-line arguments.
In the default 'hard' mode, giving an invalid integer
breaks the sum computation and exits with error. The user can switch to 'soft' mode by
giving '-s' flag before the integers to sum. In soft mode, the sum computation proceeds
skipping invalid integers and issues a warning about them before printing the sum and exiting
successfully. Written in C++. Leverages multiline macros.

## Background
In my projects I often have control flows similar to:
```python
# Python
def process_data(raw_data)
    data = []
    for item in raw_data:
        if not_ok(item):
            continue # or sometimes break

        data.append(process_item(item))

    return data
```

This got me thinking that it would be nice if I could `break` or `continue` the loop based
on a configuration while keeping the call site terse. Something like:
```python
conf = "break"
if not_ok(item):
    jump(conf)
```

I didn't come up with anything for Python in a while but wanted to test the idea anyway so I tried out
an approach in C++ presented here.

## Usage
```bash
make # compiled using clang++ and c++17
./intsum 1 2 3
6
./intsum 1 x 2
Error: Invalid integer 'x'
./intsum -s 1 x 2 # -s for soft mode
Warning: Skipped invalid integers 'x'
3
```