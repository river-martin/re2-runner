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
cmake -DCMAKE_BUILD_TYPE=Debug -DABSL_ENABLE_INSTALL=ON ..
cmake --build .
```

## Usage

```Bash
./build/re2-runner regex.txt str.txt
```
