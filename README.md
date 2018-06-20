# Smart Tales II
Repository of the Smart Tales sequel, codename Smart Tales II. See the original paper, [springer link](https://link.springer.com/content/pdf/10.1007/978-3-319-26005-1_13.pdf), for context. Official accompanying paper for this project will arrive later.

**This project is currently in the prototyping stage.**

## Windows Dependencies
Currently the project requires the following for development:
- A compiler with C++14 support (VS2017 and clang++-6.0 have been tested)
- Simple and Fast Multimedia Library (SFML) version 2.5.0 (should work with 2.4.2 as well)
- A gamepad

The gamepad is **required** in some cases, most likely when the computer has been used with gamepads before. There is a weird issue with the Windows API in some cases that makes the game stutter if there is no gamepad connected. It seems to only happen on computers that have or had a gamepad connected to them (could be drivers). If this applies to you; before launching the game connect your gamepad and press a few random buttons, also moving the thumbsticks. That procedure seems to get rid of the stuttering in the game.

Be sure to update the project with the correct directories for the local SFML dependencies (additional `include` and `lib`). The default target is x86 contrary to x64, which is the default platform target on most modern machines.

*Note: the game itself does not use the gamepad as input device, it is a problem with Windows*

## Linux Dependencies
- Simple and Fast Multimedia Library version 2.5.0 or better
- A modern compiler supporting C++14
- make

Check if `/smart_tales_ii/makefile` uses the correct environment settings. By default it uses `CC` as `clang++-6.0` and includes the sfml dependencies in `LIBS` through `lsfml-...`. Don't forget to include your custom include directory in `CFLAGS` if you have a custom SFML build.

Now simply run `make all` in `/smart_tales_ii/` after which a binary will be build to `/bin/smarttalesii`. It may require you to set the correct permissions on the files it uses, if incorrectly set it may complain about not finding or able to open certain assets. The compiled `smarttalesii` binary also is required to be run in the `/bin` directory, else it cannot find its resources.

## Branches
- master: the most recent stable version of the game.
- GameplayEvaluation: the first basic prototype of the game, for testing the fundamental game mechanics.
- ExperimentEvaluation: the version of the game used for the first evaluation round with 11 participants (Q2 2018).

## Releases
Check the [releases](https://github.com/TijmenUU/smarttalesii/releases) for Windows binaries if you cannot or do not want to build it yourself.

## License
See the license file for all the licenses this project uses.

## About
This is a bachelors project for the University of Utrecht, 2017-2018. In short the project is about generating awareness of Ambient Assisted Living (AAL), with a focus on the elderly. The game attempts to do this through providing a small but fun experience in the form of a small game.

The project is executed by Tijmen van Nesselrooij (@TijmenUU) and supervised by Fabiano Dalpiaz (@fabianodalp).
