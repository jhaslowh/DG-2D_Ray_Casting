DG 2D Ray Casting
==============

This is a small program that does 2D ray casting with 2D boxes.  

How to use
--------
All the controls are on the left side, and this is what they do from top to bottom.  
  
Move (Button): Click this button, then click and drag a box to move it around  
Set Light (Button): Click this button, then click anywhere on screen to set the light location  
Add (Button): Click this button then click and drag then release to create a box on screen  
Remove (Button): Click this button, then click a box to remove it  
Show Light (Checkbox): Check to toggle light  
Light Size (Value Slider): Slide to change size of light circle  
Darkness (Value Slider): Slide to change opacity of darkness  
Ray Count (Value Slider): Slide to change the number of rays used during method 1 raytracing  
Use Method 1 (Checkbox): Check to switch to method 1 raytracing   
Use Method 2 (Checkbox): Check to switch to method 2 raytracing   
  
**Light Method 1**  
Method 1 is slower than method 2, but produces a more accurate light circle.  
  
**Light Method 2**  
Method 2 is faster than method 1, but the light circle is not a smooth curve. 
  
Building / Running
--------

OpenGL 3.0 or greater is required to run.   

**Windows**  
To compile on windows, run the project with Visual Studio 2010 or greater and build it.  

**Linux**  
To compile (starting in the root project directory)  
    
    cd src
    make

To run (starting in the root project directory)  

    cd src/build/
    ./2DLight

If you get errors while building or running on linux, check the error section below. 

### Libraries

**SDL**  
[http://www.libsdl.org/](http://www.libsdl.org/)  
Used for 
- GUI's   
- Threads  
- Timing  

**GLEW**   
[http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Used to access newer OpenGL functions
 
**GLM**  
[http://glm.g-truc.net/0.9.5/index.html](http://glm.g-truc.net/0.9.5/index.html)  
Used for matrix math

**SOIL**  
[http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Used to load texture files 

Linux Errors
------------------------

**Error:** OpenGL headers cannot be found  
If you are getting OpenGL errors, run the following commands  

    sudo apt-get update  
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  


**Error:** ./2DLight: error while loading shared libraries: libSDL2-2.0.so.0: cannot open shared object file: No such file or directory

Open the file 

    /etc/ld.so.conf  

Add the following line the the bottom  

    include /usr/local/lib

Then run the following command  

    sudo /sbin/ldconfig

Installing Libraries on Linux
-----------------

SDL2, GLEW, and SOIL are required to compile. If you do not have any of these libraries, follow the instructions below to install them.  

**SDL 2**  
Download SDL2-2.0.3.tar.gz from here [http://www.libsdl.org/download-2.0.php](http://www.libsdl.org/download-2.0.php)  
Then run the following commands   

    tar -zxvf SDL2-2.0.3.tar.gz
    cd SDL-1.2.7
    ./configure
    make
    sudo make install


**GLEW**  
Download glew-1.10.0.tgz from here [http://glew.sourceforge.net/](http://glew.sourceforge.net/)  
Then run the following commands  

    tar -zxvf glew-1.10.0.tgz
    cd glew-1.10.0
    make
    sudo make install

If you get errors about -lXmu and -lXi not being found when trying to install this package, then do the following.  

    sudo apt-get install libxmu-dev
    sudo apt-get install libxi-dev


**SOIL**  
Download soil.zip from here [http://www.lonesock.net/soil.html](http://www.lonesock.net/soil.html)  
Then run the following commands  

    unzip soil.zip
    cd Simple\ OpenGL\ Image\ Library/projects/makefile/
    mkdir obj
    make 
    sudo make install

