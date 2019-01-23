# Smart Tales II
This is the repository of the Smart Tales sequel, Smart Tales II. The original Smart Tales (I) is a game about Active and Assisted Living (AAL) Awareness and this project seeks to further explore the development of a serious awareness game. It mainly seeks to improve upon the pain points found in the evaluation of Smart Tales I, see the original paper [springer link](https://link.springer.com/content/pdf/10.1007/978-3-319-26005-1_13.pdf) for context. The accompanying paperwork for Smart Tales II has been finished (spoiler: Smart Tales II did quite well!) but is currently unavailable publicly.

Work on Smart Tales II has halted for now but for anyone interested in hacking/extending this project: keep on reading!

# Getting Started
Smart Tales II is written in portable `C++` and was build using free tools: it uses the [Simple and Fast Multimedia Library](https://www.sfml-dev.org/index.php) (SFML) for the audio, visuals and input handling. For creating the art [Paint.NET](https://www.getpaint.net/) was used, which can be found in the `.pdn` files. Smart Tales supports both Linux and Windows currently, offering a `makefile` and `Visual Studio 2017 project` for each respectively. Let's get to building the project so you can see for yourself. If you're in a situation where you cannot build the game yourself, grab a release copy for it in the [releases](https://github.com/TijmenUU/smarttalesii/releases). There are currently only Windows releases available.

## Building Smart Tales II
### Windows
On Windows we have made it pretty easy to get going, simply clone this repository and open it (`smart_tales_ii.sln`) with [Visual Studio 2017](https://visualstudio.microsoft.com/downloads/) (VS2017). It comes complete with all the `x64` dependencies, but if you really want to target `x86` then grab a [32-bit copy](https://www.sfml-dev.org/download/sfml/2.5.0/) of SFML and set it up.

### Linux
Depending on what Linux distribution you're running you will have to fetch the `sfml` development files through your specific package manager. On Arch it is:
`sudo pacman -S sfml`
But if you're running Ubuntu it probably is something like:
`sudo apt-get install libsfml-dev`

Now make sure that you have:
- a `C++` compiler, the `makefile` in the repository assumes you are using `g++` but feel free to change this (alter the `CC` variable). A way to check if you have an appropriate compiler installed is to write `g++ --version`. If that outputs a version of 5 or more you should be good to go (this is the first version with `C++14` compliance). For `clang++` you need version 3.4 or later.
- `make` installed
- `git` installed

Now that we have all the dependencies open the repository in your terminal and simply run:
`make all`
If all went well you can `cd bin` and run the game `./smarttalesii`.

## Troubleshooting
- The game crashes after X minutes
   - This has been a problem in the past on Windows, but using the latest OpenAL binaries solved this. You can try installing the latest [windows installer](https://www.openal.org/downloads/) and renaming `openal32.dll` to `openal32old.dll`.
- The game stutters
   - Also a problem unique to Windows. It seems that any PC that uses gamepads, such as xbox controllers, have some intense lag spikes from time to time. The solution at the time of writing this was to connect a controller to the PC, launch the game and pause it, fiddle with the controller a bit and then resume the game.
- How do I open the `.pdn` files in the `art` directory?
   - For Linux: you can't. For Windows: get [Paint.NET](https://www.getpaint.net/). The game itself loads in PNG and JPG assets, so feel free to alter those in the `bin/texture` and `bin/spritesheet`
- The art assets are super tiny!
   - They were all drawn targeting a 320x180 resolution and then upscaled by 400% (you'll get 1280x720). I (@TijmenUU) used this out of laziness, since SFML supports upscaling without filters as well.
- I have no sound!
   - Are you sure you're not launching with the `nosound` argument somehow?
- I just want to play the game
   - If you're on Windows grab a copy from the [releases](https://github.com/TijmenUU/smarttalesii/releases)

## Where to begin?
A word of caution: this project was written with the intend to be self documenting code. This is obviously highly subjective, but that does mean there is no extensive documentation outside of the source code. I (@TijmenUU) expect you to read the source code for pointers. If you want to get an idea of the program flow, start in `main.cpp` as it contains the main entry point for the application. The VS2017 project contains filters to organise the source files (sorry Linux users!).

### Project layout
- smarttalesii -> the repository root folder
   - art -> contains all of the art used in the game, partly in `.pdn` format
   - bin -> the working directory of the game
      - animation -> all animations (spritestrips and more) are defined here in `.txt` files. See the `_readme.txt` file
      - font -> all fonts in `.ttf` format used in the game
      - music -> all music in `.ogg` format used in the game
      - sfx -> all sound effects in `.ogg` format used in the game
      - spritesheet -> all sprite sheets used in the game (`.png`, but not restricted to)
      - texture -> all textures used in the game (non animated sprites)
      - difficulty.txt -> file that defines variables that affect the game's difficulty. Play around with them!
      - *.dll -> Windows dependencies
   - smart_tales_ii -> source directory containing all source files. The makefile expects all files to be in here without subdirectories.
      - *.hpp -> header files, all have a comment at the top briefly stating their purpose
      - *.cpp -> source files
   - windeps -> the SFML x64 dependencies used by the included VS2017 project
   - .gitignore -> stuff git should not track
   - LICENCE
   - README.md -> that's us
   - makefile -> build file for Linux users
   - smart_tales_ii.sln -> the VS2017 project file for Windows users

### Adding new game modes / overlays
All game modes need to derive from the base class `Gamemode` publicly. The expected interface can be observed in `gamemode.hpp`. The game uses a simple vector to keep track of the different game modes in the `GameManager` class. You will have to find an appropriate place to `push` your new gamemode onto the it using:
`GameManager::GetInstance().PushGamemode(std::make_unique<MyGameModeType>(constructor, arguments));`
See `void Program::Load()` in `program.cpp` for practical examples of the above.

For each gamemode, take careful note of the following functions:
- `SuppressDraw()` if this returns true (it defaults to false) it suppresses the draw calls of any game modes added before itself. 
- `SuppressUpdate()` if this returns true (it defaults to false) it suppresses the update calls of any game modes before itself.

If the game mode vector contains `[ A, B, C ]` and B surpresses, it means that B and C get handled normally and A is not drawn nor updated. Note that to get this order A is inserted before B, C is inserted before A.

For updates the game mode vector is iterated backwards. For drawing the vector is iterated **forwards** due to the use of the painter's algorithm. This ensures that any game mode added _later_ gets drawn on top of the rest. See `GameManager::Update` and `GameManager::draw`.

For reference:
- The UI overlay is perhaps the simplest overlay that the game has. Check out the source files `uioverlay.hpp` and `uioverlay.cpp`.
- The Shop gamemode is the simplest, albeit still a bit cluttered, gamemode there is. Check out the source files `shopmode.hpp` and `shopmode.cpp`.

### Changing the resolution
Caution, minefield ahead. The game uses an internal 1280x720 resolution with a good reason: it was meant to target mobile devices using this resolution. If you really want to have a crack at this, expect hardcoded values. I (@TijmenUU) have tried my best to avoid them, but I can't guarantee there not being any.

You'll want to:
- Check out `gamemode.hpp` and change the values there of world width and height.
- Check out `main.cpp` and change the values there too.

### Load new assets
See `program.cpp` and check out the bulk loading of assets there. The game expects all assets to be loaded on launch. Although nothing _should_ break when loading assets in dynamically, I (@TijmenUU) recommend against it. The game has a single resource cache, which you can find in `resourcecache.hpp` and `resourcecache.cpp`. You can get the instance by calling `ResourceCache::GetInstance()`.

### Make new sprite sheets
Make sure to check out the `animatedsprite.hpp/cpp` files and `spritesheet.hpp/cpp`. The cleanest animated sprite around is probably the player, found in `playersprite.hpp/cpp` and its animations are defined in `bin/animation/player.txt`. Definitely check out the `_readme.txt` file in `bin/animation` too.

# Branches
- master: the most recent stable version of the game.
- GameplayEvaluation: the first basic prototype of the game, for testing the fundamental game mechanics.
- ExperimentEvaluation: the version of the game used for the first evaluation round with 11 participants (Q2 2018).

# License
See the license file for all the licenses this project uses.

# About
This is a bachelors project for the University of Utrecht, 2017-2018. In short the project is about generating awareness of Ambient Assisted Living (AAL), with a focus on the elderly. The game attempts to do this through providing a small but fun experience in the form of a small game.

The project is executed by Tijmen van Nesselrooij (@TijmenUU) and supervised by Fabiano Dalpiaz (@fabianodalp).
