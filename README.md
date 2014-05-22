DG 2D Lighting 
==============

Building / Running
--------

OpenGL 3.0 or greater is required to run.   

**Windows**  
To compile on windows, run the project with Visual Studio 2010 or greater and build it.  

**Linux**  
To compile on linux, navigate to the src folding and run make. The build will be in the Build folder and will be named "UFOAttack".  
If you get errors while building on linux, you may need the opengl header files (See below).  

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

OpenGL Headers for linux
------------------------

You will need to get the OpenGL headers if you are compiling the code on linux. You can either look for there here..  

[http://www.opengl.org/registry/](http://www.opengl.org/registry/)  
[http://www.khronos.org/registry/](http://www.khronos.org/registry/)  

or run these commands. The freeglut library might not be nessesary.   

    sudo apt-get update  
    sudo apt-get install libglu1-mesa-dev freeglut3-dev mesa-common-dev  
