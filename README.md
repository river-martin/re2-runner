# re2-runner

Runs partial matching with the [RE2](https://github.com/google/re2) regex engine and outputs match information in [Tom's Obvious Minimal Language (TOML)](https://tomhttps://toml.io/en/l.io/en/).

## Build

```Bash
git submodule update --init --recursive
# Build and install abseil
cd abseil-cpp
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr/local
sudo cmake --build . --target install
# Build the re2 static library
cd ../../re2
make obj/libre2.a
# Build re2_runner
cd ../
cmake .
cmake --build .
```

## Usage

```Bash
python3 src/re2_runner.py -h
```
