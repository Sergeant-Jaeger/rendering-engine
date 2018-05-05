# Rendering Engine Project

This is the result of a semester long project to create a software-based rendering engine for a Topics Course in Graphics.

**Disclaimer:** For educational purposes only. While I may have typed out the code most of the algorithms were derived from OpenGL and Dr. Duffin. There isn't anything in here that you couldn't find a better example of anywhere else. All the scenes located in the scenes directory were not created by me. Their purpose was to test our implementations of the rendering engine at various stages of its development cycle and should not be used anywhere else.

## Getting Started

Pull the project onto your Linux machine and run make in the root directory of the project.

```
Aaron@DESKTOP:~/rendering_engine$ make
```

Change to the bin directory and run the executable with a scene of your choice from the scenes directory as a command line argument.

```
Aaron@DESKTOP:~/rendering_engine/bin$ ./rd_view ../scenes/colored_mirrors_db.rd
```
**Note:** You may notice that some of these scene files have "_db.rd" or "sb.rd" appending them. That specifies whether or not the scene is single or double buffered. You can change the scenes to do either on your own if you modify the .rd files in a text editor.

### Prerequisites

You'll need:

* g++/gcc

* make

* c++11 Standard Library (minimum)

* libcs690.a This library lays the groundwork for communicating with the Xserver among other things and it's necessary so do not delete it. It was created by Dr. Kirk Duffin at NIU.

* Xlib

* Xserver if you're using a terminal on Windows - I use [VcXsrv Windows X Server](https://sourceforge.net/projects/vcxsrv/). A good guide to setting this Xserver up can be found [here](https://seanthegeek.net/234/graphical-linux-applications-bash-ubuntu-windows/)

## Author

* **Dr. Kirk Duffin** 

* **Aaron Jaeger** - [Sergeant-Jaeger](https://github.com/Sergeant-Jaeger)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgements

Thanks to: 

* [Kirk Duffin](http://graphics.cs.niu.edu/people/duffin/) for the long hours and patience with helping your students work through some of these algorithms and debugging.

* [PurpleBooth](https://github.com/PurpleBooth) for the great README.md [template](https://gist.github.com/PurpleBooth/109311bb0361f32d87a2#file-readme-template-md).

* [Hilton Lipschitz](https://hiltmon.com/about/) for the amazing [blog](https://hiltmon.com/blog/2013/07/03/a-simple-c-plus-plus-project-structure/) on C++ file structures, .gitignore, and Makefiles.