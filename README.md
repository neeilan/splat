# splat

[![Build Status](https://travis-ci.org/neeilan/splat.svg?branch=master)](https://travis-ci.org/neeilan/splat)

splat (<b>S</b>imple <b>P</b>rogramming <b>La</b>nguage <b>T</b>ester is a tool to write functional tests for programming language implementations.

splat enables writing tests for a language using that language itself; This results in a reusable test suite that may be used to test any compiler/interpreter for that language regardless of implementation details.

A <i>testfile</i> contains a program in the target language, annotated with splat <i>directives</i>.

Testfiles can be named anything, but we suggest using an extension of the format `.<language>.splat`.
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

`%output` - Specifies the expected output. All lines between two `%output` directives (called an <i>output section</i>) are considered part of the expected output for the program. A testfile can have more than one output section. 
At the end of a testfile, a single `%output` tag may be used to indicate that all the following lines comprise an output section.
Note: splat merges stdout and stderr into a single output stream for comparison purposes.

`%snippet` - The snippet tag is followed by a quoted string known as the <i>snippet text</i> (for example, in `%snippet "IndexError"`, the snippet text is 'IndexError'). A testfile can contain 0 or more snippets texts. splat checks that each snippet appears <i>at least once</i> in the output. As such, they are useful for confirming that the implementation under test reports an error, without having to match the error message exactly.

`%exit-code`

`%%` - Specifies a splat comment. Any line starting with `%%` is ignored.
