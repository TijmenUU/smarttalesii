# Smart Tales II
Repository of the Smart Tales sequel, codename Smart Tales II. See the original paper, [springer link](https://link.springer.com/content/pdf/10.1007/978-3-319-26005-1_13.pdf), for context. Official accompanying paper for this project will arrive later.

**This project is currently in the prototyping stage.**

## Dependencies
Currently the project requires the following:
- Microsoft's Visual Studio 2017 (VS2017) with Visual C++
- Simple and Fast Multimedia Library (SFML) version 2.4.2

Should build on Linux too, as there are no platform specific libraries or APIs used. However, this has not been tested yet.

## Branches
- master: the most recent stable version of the game. It may miss some upcoming features, but it should build with no problems.
- GameplayEvaluation: the first basic prototype of the game, for testing the fundamental game mechanics.
- linux: experimental branch with a working makefile. However, the generated executable has permission problems or uses a wrong directory / file lookup. It cannot load fonts because it cannot find them.

## Releases
Check the [releases](https://github.com/TijmenUU/smarttalesii/releases) for binaries if you cannot or do not want to build it yourself.

## License
The project and all its assets are licensed under the MIT License unless otherwise specified.

## About
This is a bachelors project for the University of Utrecht, 2017-2018. In short the project is about generating awareness of Ambient Assisted Living (AAL), with a focus on the elderly. The game attempts to do this through providing a small but fun experience in the form of a small game.

The project is supervised by Fabiano Dalpiaz (@fabianodalp) and executed by Tijmen van Nesselrooij (@TijmenUU).
