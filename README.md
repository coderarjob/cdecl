## cdecl - C declaration to plain english

### Dependencies

* cmake
* C compiler (Example: `gcc` in Linux, `Visual C++` in Windows)

### Bulid

Can be build in `Linux` and `Windows`. Only dependencies are `cmake` and a `C compiler`.

```
> cmake -Bbuild
> cmake --build build
```

Binary will be in `build/bin/cdecl`.

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
