# CthulEngine Demo

## TABLE OF CONTENTS
1. Description
2. Setup

## DESCRIPTION
This project is a demo of a my 3D raycaster engine ("CthulEngine").
It is used to develop and test stuff for my future engine, so consider like a
(game/engine) demo/test playground.

## PREREQUISITES
* C Compiler (gcc/clang)
* Make
* SDL2 (a guide shows you how to install it if you don't have it, further down.)
* SDL2_ttf (a guide will also show you how to install it, further down.)

## SETUP

### MacOS

### SDL2 Setup
Download the framework at this link:
https://github.com/libsdl-org/SDL/releases/tag/release-2.28.2
The file with the '.dmg' extension. And put it in your (~/Library/Frameworks/) directory.
You will need to create the 'Frameworks' directory if you don't have it.

### SDL2_ttf Setup
Download the framework at this link:
https://github.com/libsdl-org/SDL_ttf/releases
Same procedure: file with '.dmg' extension
and stored in the ('~/Library/Frameworks/') directory.

### Create ('$ROOT/out') directory.

### Project Makefile
You don't have to follow this example exactly.
You just need to link the SDL2 library and include the (ProjectRoot/inc/)
directory. That's it. This is just easier and requires minimum modifications.

~~~Makefile
# EXAMPLE

# name you want to give to the executable
id=game.exe

# path to where you keep your frameworks (usualy in the ~/Library/Frameworks/)
fwkPath=/Users/User/Library/Frameworks/

# FLAGS
# project include folder path
incFlag=-I./inc/
# indicate the framework location
fwkFlag=-F$(fwkPath)
# add the SDL2 framework and include it
sdlFlag=-framework SDL2 -I$(fwkPath)SDL2.framework/Headers/
# add the SDL2_ttf framework and include it
sdlttfFlag=-framework SDL2_ttf -I$(fwkPath)SDL2_ttf.framework/Headers/

# BULD TARGET
target:
    #clean up
    clear
    # enter command
    gcc src/game.c -o $(id) $(incFlag) $(fwkFlag) $(sdlFlag) $(sdlttfFlag)
    # move the executable to the output folder
    mv $(id) out/
~~~

Then run ./out/game.exe and the project should run !
