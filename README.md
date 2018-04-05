# Smart Tales II
Repository of the Smart Tales sequel, codename Smart Tales II. See the original paper, [springer link](https://link.springer.com/content/pdf/10.1007/978-3-319-26005-1_13.pdf), for context. Official accompanying paper for this project will arrive later.

**This project is currently in the prototyping stage.**

## Dependencies
Currently the project requires the following:
- Microsoft's Visual Studio 2017 (VS2017) with Visual C++
- Simple and Fast Multimedia Library (SFML) version 2.4.2
- A gamepad

The gamepad is **required** in some cases, most likely when the computer has been used with gamepads before. There is a weird issue with the Windows API in some cases that makes the game stutter if there is no gamepad connected. It seems to only happen on computers that have or had a gamepad connected to them (could be drivers). If this applies to you; before launching the game connect your gamepad and press a few random buttons, also moving the thumbsticks. That procedure seems to get rid of the stuttering in the game.

*Note: the game itself does not use the gamepad as input device, it is a problem with Windows*

## Branches
- master: the most recent stable version of the game. It may miss some upcoming features, but it should build no problems on *Windows*. See the branch *linux* for building a stable linux compatible binary.
- GameplayEvaluation: the first basic prototype of the game, for testing the fundamental game mechanics.
- linux: branch with a version that is stable on Linux. The master branch is not guarranteed to be stable on Linux, but could well be.

## Releases
Check the [releases](https://github.com/TijmenUU/smarttalesii/releases) for Windows binaries if you cannot or do not want to build it yourself.

## License
See the license file for all the licenses this project uses.

## About
This is a bachelors project for the University of Utrecht, 2017-2018. In short the project is about generating awareness of Ambient Assisted Living (AAL), with a focus on the elderly. The game attempts to do this through providing a small but fun experience in the form of a small game.

The project is supervised by Fabiano Dalpiaz (@fabianodalp) and executed by Tijmen van Nesselrooij (@TijmenUU).
