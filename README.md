# Smart Tales II
Repository of the Smart Tales sequel, codename Smart Tales II. See the original paper, [springer link](https://link.springer.com/content/pdf/10.1007/978-3-319-26005-1_13.pdf), for context. Official accompanying paper for this project will arrive later.

**This project is currently in the prototyping stage.**

## Dependencies
Currently the project requires the following:
- Microsoft's Visual Studio 2017 (VS2017) with Visual C++
- Simple and Fast Multimedia Library (SFML) version 2.4.2
- OpenAL, see https://www.openal.org/downloads/ . Required for running the release as well.

Should build on Linux too, as there are no platform specific libraries or APIs used. However, this has not been tested yet.

## Branches
- master: the most recent stable version of the game. It may miss some upcoming features, but it should build no problems on *Windows*. See the branch *linux* for building a stable linux compatible binary.
- GameplayEvaluation: the first basic prototype of the game, for testing the fundamental game mechanics.
- linux: branch with a version that is stable on Linux. The makefile on the master branch is not guarranteed to work, but build from this branch should work no problem. May be severely outdated (see commits). Feel free to try your luck with the master branch + makefile in that case.

## Releases
Check the [releases](https://github.com/TijmenUU/smarttalesii/releases) for binaries if you cannot or do not want to build it yourself.

## License
See the license file for all the licenses this project uses.

## About
This is a bachelors project for the University of Utrecht, 2017-2018. In short the project is about generating awareness of Ambient Assisted Living (AAL), with a focus on the elderly. The game attempts to do this through providing a small but fun experience in the form of a small game.

The project is supervised by Fabiano Dalpiaz (@fabianodalp) and executed by Tijmen van Nesselrooij (@TijmenUU).
