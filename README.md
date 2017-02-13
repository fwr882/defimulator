# Bsnes Project
This project is meant to be a Nintendo, Super Nintendo, Game Boy, Game Boy
Color, Game Boy Advance emulator for Windows/Linux/Mac.

## History
This project was forked from the higan project at v074.  You can find the
original project at https://gitlab.com/higan/higan

## Why

### Fast Emulation
The higan project is very heavily focused on 100% accurate emulation.  Which
has a purpose.  But for those that are looking for a nice emulator that is
'good enough', higan has outgrown that intent.  This aims to be a project
that supports accurate emulation while remaining usable on reasonably (within
the past few years) hardware.

### Code Simplification
If you look at the higan code, it requires C++14 and is not very approachable.
The project was built on Makefiles that were as cross-platform as possible,
but still somewhat rickety.  It now uses CMake for the build system and the
process of using the same back-ends and GUI toolkits is in the works.

### Open Development
The higan project is developed, from what I'm able to observe, by one guy.  I
can tell this guy (byuu) has some real coding chops, but his repository is
not open for others to contribute.

## How to Help
Fork the repository and open a pull request!  I welcome any code changes for
bsnes, just ensure that you take a look at the code and follow coding standards
or your pull request may be denied.  Also, please include in the PR what
platform you're developing on so that others can test your changes on different
platforms to ensure we're not breaking more code than fixing.

## License
The code is licensed under GPLv3.  You do not have to assign your copyright to
me or the project.  Your code is your code.  I have no intent of selling this
software or trying to the keep the source code away from the community.
