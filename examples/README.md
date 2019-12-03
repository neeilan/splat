# Examples

'Interpreting' implementations that execute a provided source-code file can be directly tested by providing splat with 
the language binary, along with the testfile.

For example, a simple 'Hello, world' test for a python interpreter is included, and can be invoked as follows:

```bash
../splat /usr/bin/python hello.py.splat 
OK
```

Tetsing 'compiling' implementations, which generate an executable that then needs to be invoked, involves an additional step.
A 'binding script', such as the provided [bind_gcc.sh](./bind_gcc.sh), calls the compiler <i>and</i> executes the program.

splat is called with the binding script in place of the language implementation, along with the testfile path:

```bash
 ../splat ./bind_gcc.sh gcc_example.c.splat 
OK
```

In this case, bind_gcc consists of two lines: the first runs gcc, and the second runs the compiled program:
```
# bind_gcc.sh
gcc -o test_binary $1
./test_binary
```
This general pattern applies for binding any compiler implementation.
