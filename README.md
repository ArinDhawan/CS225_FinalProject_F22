# **CS225 Final Project Fall 2022**
 **Team members:** Noah Breit, Peter Giannetos, Ben Olaivar, Arin Dhawan  
**Group Name:** HeyBeter
 
### *Table of Contents*
1. [Presentation Video](#video)
2. [GitHub Organization](#intro)
3. [Code Execution](#running)
4. [Test Suite](#tests)

<div id='video'/>

# **Presentation Video**

[A link to the presentation video]()
### **`TODO TODO TODO TODO`**

<div id='intro'/>

 # **GitHub Organization** 

*An overview of the structure of this respository.*

## Root Folders

- **datasets:** The source data files fed into program
- **Documents:** Documentation files such as the `results.md` file
- **entry:** The location of the `main.cpp` file
- **lib:** Imported libraries such as `HSLAPixel.h` and `PNG.h` 
- **src:** Repository specific code used in `main.cpp`
- **tests:** The `catch.hpp` library and a test case suite
- **presentation:** All materials used during the presentation and the `presentation video link`.

## Root Files

- **.gitignore:** Used by git to ignore certain local files
- **Makefile:** Used to compile the project with `make` commands
- **README.md:** The you are reading now ... lol

<div id='running'/>

# **Code Execution** 

*A guide on running the code in this repository. **Ensure you clone the repository into the same docker container as used with the CS 225 labs and mps.***

1. Clone the repository: `git clone github.com/ArinDhawan/CS225_FinalProject_F22`
2. Nagivate into the repository: `cd CS225_FinalProject_F22` *(Or whatever you named it)*
2. Create a build folder: `mkdir build` *(Make sure you are in the root of the respository!)*
3. Navigate into the build folder: `cd build`
4. Run: `cmake ..` *(Only do this once!)*
5. Run: `make`
6. Run `./main`
7. Repeat steps `5` and `6` every time you make changes. *(Ensure you're still in /build)*

<div id='tests'/>

# **Test Suite** 


*A quickstart guide on running test cases with the included test suite*

1. Complete all the steps in "Code Execution"
2. Run: `make test`
3. Run: `./test`
