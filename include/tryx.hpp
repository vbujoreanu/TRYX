#ifndef __TRYX__
#define __TRYX__

// Author: Vlad BUJOREANU (@vbujoreanu)
// Date: 12 March 2023

// Before you include this file where you want to use it, you will have to include <expected> from C++23 draft or your own implementation of it

// C++17 guard
#if _MSVC_LANG >= 201703L /* MSVC */ || __cplusplus >= 201703L /* GCC && Clang */

#include <any>

template <class FT>
class scope_guard
{
    FT function;

public:
    scope_guard(FT&& function) : function(std::move(function)) { }
    ~scope_guard() { function(); }
};

struct _ThreadContext
{
    static inline thread_local std::any _error;
};

#define TRYX(expr)                                                                                              \
[&]()                                                                                                           \
{                                                                                                               \
    std::any& error_ref = _ThreadContext::_error;                                                               \
    if (error_ref.has_value())                                                                                  \
    {                                                                                                           \
        error_ref.reset();                                                                                      \
    }                                                                                                           \
    auto&& expected_uref = expr;                                                                                \
    if (!expected_uref.has_value())                                                                             \
    {                                                                                                           \
        error_ref = std::move(expected_uref.error());                                                           \
        return decltype(expr)::value_type{};                                                                    \
    }                                                                                                           \
    return std::move(expected_uref.value());                                                                    \
}();                                                                                                            \
if (std::any& error_ref = _ThreadContext::_error; error_ref.has_value())                                        \
{                                                                                                               \
    scope_guard _scope_guard = [&]()                                                                            \
    {                                                                                                           \
        error_ref.reset();                                                                                      \
    };                                                                                                          \
    return decltype(expr)::unexpected_type(std::move(std::any_cast<decltype(expr)::error_type&>(error_ref)));   \
}

#endif

#endif