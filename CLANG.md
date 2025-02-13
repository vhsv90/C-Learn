# Clang Utility Commands and Usage

## Basic Compilation Commands
| Command | Description |
|---------|------------|
| `clang file.c -o output` | Compile a C file into an executable. |
| `clang++ file.cpp -o output` | Compile a C++ file into an executable. |
| `clang -Wall -Wextra file.c -o output` | Enable common warnings during compilation. |
| `clang -std=c11 file.c -o output` | Compile using the C11 standard. |
| `clang++ -std=c++17 file.cpp -o output` | Compile using the C++17 standard. |
| `clang -g file.c -o output` | Compile with debugging symbols. |
| `clang -O2 file.c -o output` | Optimize code for speed (level 2). |
| `clang -DDEBUG file.c -o output` | Define a preprocessor macro (e.g., `DEBUG`). |

## Static Analysis & Debugging
| Command | Description |
|---------|------------|
| `clang -fsanitize=address file.c -o output` | Enable AddressSanitizer for memory debugging. |
| `clang -fsanitize=undefined file.c -o output` | Enable Undefined Behavior Sanitizer (UBSan). |
| `clang -emit-llvm file.c -S -o output.ll` | Generate LLVM intermediate representation (IR). |
| `clang -fsyntax-only file.c` | Check for syntax errors without generating an output file. |
| `clang-tidy file.c --checks=*` | Run `clang-tidy` static analysis with all checks enabled. |
| `scan-build clang file.c -o output` | Perform static analysis using `scan-build`. |

## Preprocessing & Assembly
| Command | Description |
|---------|------------|
| `clang -E file.c -o output.i` | Preprocess the code (expand macros and includes). |
| `clang -S file.c -o output.s` | Generate assembly code from the source file. |
| `clang -c file.c -o output.o` | Compile the file but don’t link (create an object file). |

## Linking & Libraries
| Command | Description |
|---------|------------|
| `clang file.c -o output -lm` | Link against the math library (`libm`). |
| `clang file.c -o output -L/path/to/lib -lcustomlib` | Link against a custom library. |
| `clang -shared -o libexample.so file.c` | Compile a shared library (Linux/macOS). |
| `clang -shared -o example.dll file.c` | Compile a shared library (Windows). |

## Cross Compilation & Architecture
| Command | Description |
|---------|------------|
| `clang --target=x86_64-linux-gnu file.c -o output` | Cross-compile for x86_64 Linux. |
| `clang --target=arm-linux-gnueabihf file.c -o output` | Cross-compile for ARM Linux. |
| `clang -march=native -O3 file.c -o output` | Optimize for the host CPU architecture. |

## C++ Specific Features
| Command | Description |
|---------|------------|
| `clang++ -stdlib=libc++ file.cpp -o output` | Use the LLVM C++ standard library (`libc++`). |
| `clang++ -fmodules file.cpp -o output` | Enable C++ modules support. |
| `clang++ -std=c++20 file.cpp -o output` | Compile using C++20 standard. |

---

Would you like any modifications or additional explanations? 🚀
