

# C/C++ examples for playing

Single file executable program



```bash

sudo apt install ninja-build

mkdir -p out/release out/debug

cmake -G Ninja -S . -B out/release -DCMAKE_BUILD_TYPE=Debug -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

ninja -C out/release

```
