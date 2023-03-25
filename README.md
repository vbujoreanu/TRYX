# TRYX
Macro for variable construction / assignment from an `std::expected` with error handling built-in.

- compiler-independent, thread-safe

- requires no external dependencies, only uses native C++ code, without GCC / Clang extensions (like statement expressions)

- compiles on MSVC, GCC, and Clang, with at least C++17 (provided you have your own implementation of `std::expected` respecting the interface, or C++23 otherwise -- by including `<expected>`)

- leverages a thread_local static inline variable for error propagation outside the lambda function

- compared to classic if-else error handling boilerplate code:
	* in the expected case it is just as efficient (0 extra copies or moves)
	* in the unexpected case it produces 1 extra move

Lets you write code like:

```cpp
std::expected<std::string, int> get_a()
{
    return "1"; // can replace with std::unexpected(1) to try error propagation
}

std::string a = TRYX(get_a());
```