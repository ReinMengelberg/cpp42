# C++ Module 07 — C++ templates

Before templates, writing `swap` for `int`, `double` and `std::string` meant
writing it three times (or falling back to `void*` and losing all type safety).
A template is a *recipe* for code: you write it once with a placeholder type
`T`, and the compiler writes the concrete version for every type you actually
use it with. This is called **instantiation**, and it happens at compile time.

| Exercise | What you build                         | Template kind                |
|----------|----------------------------------------|------------------------------|
| ex00     | `swap`, `min`, `max`                   | Function templates           |
| ex01     | `iter` — apply a function to an array  | Function template, 2 params  |
| ex02     | `Array<T>` — a bounds-checked array    | Class template               |

The module walks from the simplest case (one type parameter, deduced from the
arguments) to a full class template that owns memory.

## ex00 — Start with a few functions

```
$ make -C ex00 && ./ex00/ex00
=== Test: the subject's example ===
a = 3, b = 2
min( a, b ) = 2
max( a, b ) = 3
c = chaine2, d = chaine1
min( c, d ) = chaine1
max( c, d ) = chaine2
...
```

`whatever.hpp` defines three function templates at global scope. `swap`
exchanges two values; `min` and `max` return the smaller/greater one, and
**the second one when they are equal**. The tests call them with `int`,
`std::string`, `double`, `char` and a small user-defined `Awesome` class.

**Learning goals**

- **Template argument deduction.** In `::swap(a, b)` you never write `<int>`:
  the compiler deduces `T` from the arguments. Because both parameters are
  `T`, both arguments must have the *same* type — `::min(1, 2.0)` does not
  compile.
- **Implicit requirements.** A template works with any type that supports the
  operations used in its body. `swap` needs copy construction and assignment;
  `min`/`max` need `<` and `>`. `Awesome` only works because it defines those
  operators — remove one and you get a (long) compile error at the call site.
  This "duck typing at compile time" is what C++20 concepts later formalised.
- **Why the `::` prefix.** `std::swap`, `std::min` and `std::max` already
  exist. `::min` forces the lookup to the global namespace, so there is no
  ambiguity with the standard ones (which can sneak in through argument
  dependent lookup when calling with a `std::string`).
- **Return by `const T&`.** `min`/`max` return a reference to one of the
  arguments, not a copy. That is why "return the second one when equal" is a
  real, testable requirement: the test compares addresses
  (`&::min(a, b) == &b`). Writing `a < b ? a : b` gives exactly that
  behaviour, while `a <= b ? a : b` would not.
- **Templates live in headers.** The compiler needs the full definition to
  instantiate a template, so it cannot hide in a `.cpp`. This is the one
  exception to the "no function bodies in headers" rule of the modules.

## ex01 — Iter

```
$ make -C ex01 && ./ex01/ex01
=== Test: printing an array of ints ===
1 2 3 4 5
=== Test: modifying the elements in place ===
2 4 6 8 10
...
```

```cpp
template <typename T, typename F>
void iter(T* array, const size_t length, F function);
```

`iter` calls `function` on every element of `array`. The tests pass it
instantiated function templates (`::print<int>`, `::twice<std::string>`) as
well as a plain function (`::shout`), on mutable arrays, a `const` array, and
a `NULL` pointer.

**Learning goals**

- **Multiple template parameters.** `T` is the element type, `F` is "anything
  callable with a `T&`". Making the function its own template parameter means
  `iter` accepts a function pointer taking `T&`, `const T&` or even `T` by
  value — without writing an overload for each.
- **const-correctness through deduction.** This is the subject's hint. When
  you pass a `const double[]`, `T` is deduced as `const double`, so
  `array[i]` is a `const double&`. A function taking `const double&` works;
  one taking `double&` (like `twice`) is rejected *at compile time*, which is
  exactly what should happen. One template covers both cases instead of two
  overloads.
- **A function template is not a function.** `::print` on its own is a
  *family* of functions, so the compiler cannot deduce `F` from it. You have to
  instantiate it explicitly: `::print<int>`. That produces an ordinary
  function whose address can be passed around.
- **`const size_t length`** — the length is passed by `const` value as the
  subject asks. Top-level `const` on a by-value parameter only means the
  function cannot change its own copy.

## ex02 — Array

```
$ make -C ex02 && ./ex02/ex02
Array index is out of bounds.
Array index is out of bounds.

=== Test: an empty array ===
size() = 0
Caught: Array index is out of bounds.
...
```

`Array<T>` is a fixed-size, heap-allocated array that knows its own size and
checks every access. It is declared in `Array.hpp`, and its member functions
are defined in `Array.tpp`, which `Array.hpp` includes at the bottom.

| Member                    | Behaviour                                              |
|---------------------------|--------------------------------------------------------|
| `Array()`                 | Empty array (`size() == 0`)                            |
| `Array(unsigned int n)`   | `n` value-initialized elements (`new T[n]()`)          |
| copy ctor / `operator=`   | Deep copy — the two arrays never share memory          |
| `operator[]` (+ `const`)  | Returns the element, throws `OutOfBoundsException`     |
| `size() const`            | Number of elements                                     |
| `~Array()`                | `delete[]`                                             |

The first part of `main.cpp` is the test provided with the subject; the
sections after it add the edge cases (empty array, default values, copy
independence, `const` access).

**Learning goals**

- **Class templates.** Unlike function templates, C++98 cannot deduce the
  class template's argument — you always write `Array<int>`. Each distinct
  `Array<X>` is a completely separate class generated by the compiler.
- **The `.tpp` pattern.** The definitions still have to be visible wherever
  the template is used, so they cannot go in a `.cpp`. Putting them in a
  `.tpp` included by the header keeps the interface readable while respecting
  that rule. Note the out-of-class syntax: `template <typename T>
  T& Array<T>::operator[](unsigned int index)`.
- **Value-initialization: `new T[n]()`.** The subject's tip about
  `int* a = new int();`: with the `()` built-in types are zero-initialized,
  without it they contain garbage. For class types both forms call the default
  constructor. `Array<int>(3)` therefore holds `0 0 0`.
- **Orthodox Canonical Form with owned memory.** Because the class owns a
  pointer, the compiler-generated copy would be a shallow copy and lead to a
  double `delete[]`. The copy constructor allocates its own buffer, and
  `operator=` allocates and fills the new buffer *before* deleting the old one
  and checks for self-assignment, so a failing `new` leaves the object intact.
- **Bounds checking with exceptions.** `operator[]` takes an `unsigned int`,
  so `numbers[-2]` wraps around to a huge index and is caught by the same
  `index >= length` check. The exception is a nested class deriving from
  `std::exception`, so callers can `catch (const std::exception&)`.
- **Two `operator[]` overloads.** The non-`const` one returns `T&` for
  writing; the `const` one returns `const T&` so that a `const Array` can still
  be read but not modified. `size()` is `const` for the same reason.
- **`typename` for dependent names.** Inside the template, `Array<T>::
  OutOfBoundsException` depends on `T`; the definitions in `Array.tpp` show how
  members of a class template (including a nested class's `what()`) are
  defined outside the class.

## Building

Each exercise has its own Makefile and compiles with
`c++ -Wall -Wextra -Werror -std=c++98`:

```
make -C ex00    # ./ex00/ex00
make -C ex01    # ./ex01/ex01
make -C ex02    # ./ex02/ex02
```
