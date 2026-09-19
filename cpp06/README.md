# C++ Module 06 — C++ casts

C-style casts (`(int)x`) do whatever it takes to make the compiler happy, which
makes them impossible to grep for and easy to get wrong. C++ replaces them with
four named casts that each do one specific thing:

| Cast               | What it does                                                        | Used in |
|--------------------|---------------------------------------------------------------------|---------|
| `static_cast`      | Well defined conversions the compiler understands (`int` → `float`) | ex00    |
| `reinterpret_cast` | Reinterpret the bits as another type (pointer ↔ integer)            | ex01    |
| `dynamic_cast`     | Check at runtime what a polymorphic object really is                | ex02    |
| `const_cast`       | Add or remove `const`                                               | —       |

The three exercises each take one of the first three casts and build the
smallest program that genuinely needs it. The point of the module is not just
using the casts, but being able to say *why* a given cast is the right one.

## ex00 — Conversion of scalar types (`static_cast`)

```
$ make -C ex00 && ./ex00/convert 42.0f
char: '*'
int: 42
float: 42.0f
double: 42.0
```

`ScalarConverter::convert()` takes a string holding a C++ literal, figures out
whether it is a `char` (`'a'`), an `int` (`42`), a `float` (`4.2f`) or a
`double` (`4.2`), reads it into that type, and then converts it explicitly to
the three other types and prints all four. Pseudo-literals (`nan`, `+inf`,
`-inff`, ...) have to work too, and anything that does not fit its target
(`nan` as an `int`, `300` as a `char`) is reported as `impossible`.

The class contains only that one `static` method. It holds no data, so it must
not be instantiable: the canonical form is declared `private` and never
defined.

**Learning goals**

- `static_cast` is the cast for ordinary, well defined scalar conversions —
  and the compiler now checks that the conversion actually makes sense.
- Type detection and conversion are separate steps: the string must first
  become its *own* type, and only then be converted to the others. Going
  through a `double` for everything is the easy shortcut the subject rules out.
- Conversions lose information: `float` → `char` truncates, `int` → `float`
  rounds above 2²⁴, and `nan`/`inf` have no integer at all. You have to check
  ranges with `std::numeric_limits` before casting, because an out-of-range
  floating point → integer cast is undefined behaviour.
- A class with only static members is a namespace in disguise; making it
  non-instantiable makes that intent explicit.

## ex01 — Serialization (`reinterpret_cast`)

```
$ make -C ex01 && ./ex01/ex01
=== Test: round trip on a stack object ===
original pointer: 0x7ff7b5c2a4c0
serialized value: 140701929743552
restored pointer: 0x7ff7b5c2a4c0
pointers are equal
...
```

`Serializer::serialize()` turns a `Data*` into a `uintptr_t`, and
`Serializer::deserialize()` turns that integer back into a `Data*`. The test
program does the round trip and checks that the restored pointer compares equal
to the original and still gives access to the same `Data`.

**Learning goals**

- `reinterpret_cast` is the only cast that converts between unrelated types
  such as a pointer and an integer. It does no conversion at all: it just tells
  the compiler to treat the same bits as something else, so it is only safe
  when you convert back to exactly the original type.
- `uintptr_t` exists precisely because it is guaranteed to be wide enough to
  hold a pointer; a plain `int` is not.
- Same non-instantiable class pattern as ex00, plus a `Data` struct that has to
  be non-empty so there is something to verify after the round trip.

## ex02 — Identify real type (`dynamic_cast`)

```
$ make -C ex02 && ./ex02/ex02
=== Test: eight randomly generated objects ===
by pointer:   B
by reference: B
...
```

`Base` has only a public virtual destructor; `A`, `B` and `C` are empty classes
that inherit from it. `generate()` returns one of the three at random as a
`Base*`, and the two `identify()` overloads print which one it really is — one
taking a `Base*`, the other a `Base&`. Including `<typeinfo>` is forbidden, so
`typeid` is not an option.

**Learning goals**

- `dynamic_cast` is the cast for downcasting in a polymorphic hierarchy: it
  checks at runtime whether the object really is of the requested type. It only
  works because `Base` has a virtual function (the destructor), which is what
  gives the object its runtime type information.
- Pointers and references fail differently. A failed `dynamic_cast<A*>` returns
  `NULL`, so you test the result; a reference cannot be null, so a failed
  `dynamic_cast<A&>` throws `std::bad_cast` and you have to `try`/`catch`.
- A virtual destructor is what makes `delete` through a `Base*` correct, which
  is why it is the one thing `Base` is required to have.

## Building

Each exercise has its own Makefile and compiles with
`c++ -Wall -Wextra -Werror -std=c++98`:

```
make -C ex00    # ./ex00/convert <literal>
make -C ex01    # ./ex01/ex01
make -C ex02    # ./ex02/ex02
```
