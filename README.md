# splat

[![Build Status](https://travis-ci.org/neeilan/splat.svg?branch=master)](https://travis-ci.org/neeilan/splat)

splat (<b>S</b>imple <b>P</b>rogramming <b>La</b>nguage <b>T</b>ester is a tool to write functional tests for programming language implementations.

splat enables writing tests for a language using that language itself; This results in a reusable test suite that may be used to test any compiler/interpreter for that language regardless of implementation details.

A <i>testfile</i> contains a program in the target language, annotated with splat <i>directives</i>.

Testfiles can be named anything, but we suggest the extension of the format `.<language>.splat`.
For example, a testfile for a Python program gets a `.py.splat` extension, while a C testfile gets `.c.splat`. 

Here is a simple test for a Python implementation:

```
# hello_test.py.splat

def sayHello(name):
  return "Hello, " + name

if __name__ == '__main__':
  message = sayHello("splat")
  print(message)
  
%output
Hello, splat
%output

%% Lines beginning with '%%' are splat comments.
%% Everything between the '%output' directives is the
%% expected output for the Python program in the testfile.

```

## Directives

`%output`

`%snippet`

`%exit-code`

`%%`
