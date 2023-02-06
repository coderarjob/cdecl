## cdecl - C declaration to plain english

### Dependencies

* cmake
* UNIX: GCC
* Windows: Cygwin/Visual C++ Compiler

### Bulid

Can be build in `Linux` and `Windows`. Only dependencies are `cmake` and a `C compiler`.

```
> cmake -Bbuild
> cmake --build build
```

Binary will be in `build/bin/`.

### Usage

Just provide the input in argument.
```
cdecl <c variable or function declaration>
```

### Example

```
> ./cdecl "int (*(*foo)(const void *))[3]"            
foo is pointer to a function returning pointer to an array of int
```
