# re2-runner

Runs partial matching with the [RE2](https://github.com/google/re2) regex engine and outputs match information in [Tom's Obvious Minimal Language (TOML)](https://tomhttps://toml.io/en/l.io/en/).

## Build

```Bash
git submodule update --init --recursive
# CMake will change files in the submodules that we don't want git to track
git config submodule.re2.ignore dirty
git config submodule.abseil-cpp.ignore dirty
# Build and install abseil
mkdir build && cd build
cmake .. -DCMAKE_C_COMPILER=/usr/bin/clang -DCMAKE_CXX_COMPILER=/usr/bin/clang++ -DCMAKE_BUILD_TYPE=Debug
cmake --build $(pwd)
```

## Usage

```Bash
./build/re2-runner regex.txt str.txt
./build/test_re2 --gtest_filter=*test0
```
