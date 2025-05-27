
## 🗣️ About

> _The aim of this project is to code lightweight version of the Bash shell,implementing much of its core functionality

For more detailed information, look at the [**subject of this project.**](https://github.com/edenjamsalem/minishell/subject.pdf)


### How to use it

Using ``make`` will create the ``minishell`` executable.

Then run :

```
./minishell
```

### Available options

Minishell runs executables from an absolute, relative or environment PATH (``/bin/ls`` or ``ls``), including arguments or options. 

Environment variables are handled, like ``$HOME``, including the exit status ``$?``.

``'`` and ``"`` work the same as bash, except for multiline commands.

You can use redirections ``>`` ``>>`` ``<`` ``<<``, pipes ``|``, control operators ``&&`` ``||``, parentheses ``()`` and wildcards ``*``.

Finally, you can use ``Ctrl-C`` to interrupt, ``Ctrl-\`` to quit a program and ``Ctrl-D`` to throw an EOF.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. Namely ``echo``, ``pwd``, ``cd``, ``env``, ``export``, ``unset`` and ``exit``.


### Algorithm overview

The program parses the user input (following the POSIX standard) into a combination of static and dynamic arrays, which are then executed in a linear fashion. There are 2 levels to this: 

- the highest is the CTRL_SEQ, which parses the input into a sequence of commands separated by control operators ``&&`` ``||``

- within this lies the CMD_SEQ, which further parses each node in the CTRL_SEQ into a sequence of commands separated by pipes ``|``

- parentheses ``()`` are handled in a recursive manner, as they produce branched logic which does not neatly fit into the linear nature of the CTRL_OP's array structure. When they are encountered in the initial parsing phase, they are included in the CTRL_OP sequence as raw input, to be recursively parsed during the execution phase.


## Potential Improvements

In hindsight, this was a perfect oppurtunity to implement an Abstract Syntax Tree for the execution logic. It would have simplified the execution process by removing the need for a patchy recursive call for parentheses. 

The current linear approach handles the branched nature of parentheses by simpling halting the main execution, recursively parsing and executing the commands inside the parentheses, and then coninuing back to the main execution sequence.

It works ..but is definitely sub-optimal !