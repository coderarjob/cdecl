## cdecl - C declaration to plain english

### Bulid

Nothing fancy, just compile with your favorite C compiler. Here is an example
with `gcc`.
```
gcc *.c -o cdecl
```

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
