# E.D.G.E. --> ED(I couldn't figure out a cool acronym) Graphics Engine

## 1.5 Patch Note:
### 1. Added ```draw_box(), draw_torus(), draw_sphere()``` functions in 3d.c
### 2. Transformation functions will no longer return a transformation matrix,
###    it will return a already transformed edge matrix instead.
### 3. parser implementation for 3d.c is currently unavailable
### 4. Major changes regarding plotting will comming up in V2.0
#
## 1.1 Patch Note:
### 1. Fixed parser issue
### 2. add mx_yrev function
### 3. Terran symbol now looks upright
## 1.0 Patch Note:
### 1. Work 04 correspond to release v1.0
### 2. apply, display, save dosen't work, please check back at v1.3
### 3. line.c is still trash
## Foot NOTE
### 0. please check official release
### 1. make will auto clean, e.g. remove all the *.o files
### 2. make clean will delete all the executables and image file
### 3. works on 64bit debian system 
### 4. it will take a LONG time to run if your EDGE script is to complicated, because of 1.0 Path Note #3
## How to use the parser:
### ```./parser script.txt```
### available commands:
### ```line scale trans rotate bezier hermite circle```
### A wiki will be made regarding parser, it will be released in a distant future
