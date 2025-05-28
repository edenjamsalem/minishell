#Minishell 🐚
A lightweight implementation of a Bash-like shell

## 🗣️ About

> _The aim of this project is to code a lightweight version of the Bash shell, implementing much of its core functionality_

For more detailed information, look at the [**subject of this project.**](https://github.com/edenjamsalem/minishell/blob/master/subject.pdf)


## How to use it

```
make
./minishell
```


## Available options

- Runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``) 

- ``'`` and ``"`` work the same as bash, except for multiline commands.

- Supports redirections ``>`` ``>>`` ``<`` ``<<``, pipes ``|``, control operators ``&&`` ``||``, parentheses ``()``, and wildcards ``*``.

- Supports ``Ctrl-C`` (interrupt), ``Ctrl-\`` (quit) and ``Ctrl-D`` (EOF).

Contains several "built-ins" (personal implementation over bash executable). Namely ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.


## Algorithm overview

###Parsing

Split input into a CTRL_SEQ (commands separated by ``&&`` or ``||``).

Each CTRL_SEQ node is further split into a CMD_SEQ (commands separated by pipes ``|``).

Parentheses () are handled recursively during execution.

###Execution

Linear execution of CTRL_SEQ nodes, skipping nodes based on exit status.

Pipes and redirections are resolved per CMD_SEQ.


## Potential Improvements

In hindsight, this was a perfect oppurtunity to implement an Abstract Syntax Tree for the execution logic. It would have simplified the execution process by removing the need for a patchy recursive call to handle parentheses. 

The current linear approach uses dynamic arrays for the CTRL_SEQ and CMD_SEQ. To handle the branched logica of parentheses, it simply halts the main execution, recursively parses and executes the commands inside parentheses, and then feeds that back into the main execution sequence.

It works ...but it's definitely sub-optimal !
