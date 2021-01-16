# RainstormFramework

## Description

## Naming Conventions
### Files
- c++ source files: *.cpp
- c source files: *.c
- c++ header files: *.h
- c source files: *.h
- for c++ files, use the name of the main class it contains with all lowercase
### Code
- preprocessor macros are all uppercase without leading underscores
- for acronyms, two letters is uppercase (DD), three or more is lowercase (Pme)
- all names are CamelCase
- classes, structs start with a capital letter
- functions, variables start with a lowercase letter
- namespaces are all lowercase
- enum values or constants are all uppercase using underscore to separate words
- interfaces have a `Interface` suffix
- abstract base classes have an `Abstract` prefix
- member variables have a trailing underscore
- accessors for a variable `foo_` are named `foo()` and `setFoo()`
- global variables have a `g_` prefix
- static class variables have a `s_` prefix
- global constants have a `c_` prefix
- function prefixes:
    * compute
    * find
    * initialize
- a number of objects should have a `n` prefix: `nPoints`
- instance of a class have an `m` prefix
- the id of an object has a `_id` suffix
- boolean variables have an `is` prefix
