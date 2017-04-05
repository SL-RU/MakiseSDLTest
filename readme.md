Examples and tests for GUI library MakiseGUI. 

https://github.com/SL-RU/MakiseGUI

MakiseGUI - graphical library for embed applications. It's fully written on C and can be ported anywhere. This test uses SDL2 as frontback.

# Requirements
* SDL2

# Build

```
git clone https://github.com/SL-RU/MakiseSDLTest
cd MakiseSDLTest/
git submodule init
git submodule update
mkdir build; cd build
cmake ..
make
```

# Info

Tests located in MakiseTests. For each test - own source file. Almost everything is commented

# Controls

Keyboard:
* Arrows - arrows
* Return - OK button
* Tab - switch tabs
* Minus/Equals - focus next/back
* Del - print relationships tree

Mouse:
* Cursor - cursor
* Left button - cursor click

