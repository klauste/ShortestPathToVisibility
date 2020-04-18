# Pairwise Visibility Problem
This project was written as part of my Master's thesis in Computer Science. It implements an algorithm in C++ to solve the pair-wise visibility problem in simple polygons presented in the article [On Romeo and Juliet Problems: Minimizing Distance-to-Sight](https://ui.adsabs.harvard.edu/abs/2019arXiv190601114A).

The project has three sub-projects:

* a library implementing the algorithm using [CGAL](https://www.cgal.org/) to triangulate a polygon

* a [Qt](https://www.qt.io/) project to visualize the problem and its solution

* a [Qt](https://www.qt.io/) test project to test the algorithm

If you find any errors or have any questions about this project, you can write to me. Not sure if I will respond though. I need a 3-year holiday from C++ after finishing this. Hopefully by then I will have forgotten everything about this project.

If you don't understand the code, it might be because my programming skills are lacking or because the algorithm is pretty complicated. It's probably best to read my thesis [Paarweise Sichtbarkeit in Polygonen](https://github.com/klauste/ShortestPathToVisibility/blob/master/MasterArbeitFinal.pdf) before trying to understand the code. The only problem is that the thesis is written in German. If you don't speak German, this might be a great motivator to learn it.

I've compiled and run the programme on macOS Catalina and Ubuntu 18.04. If you want to run it on your machine I recommend using Ubuntu 18.04 as the installation of required third party libraries is much simpler. If you don't have Ubuntu 18.04, you can run it by installing the [Ubuntu Image](http://releases.ubuntu.com/18.04/) on [VirtualBox](https://www.virtualbox.org/)

#### Installation on Ubuntu

In Ubuntu, install the following:

`sudo apt-get install build-essential`

`sudo apt-get install qtcreator`

`sudo apt-get install qt5-default`

`sudo apt-get install libcgal-dev`

Then clone this repository and open it in QtCreator. You should be able to compile and run it with gcc or clang.

#### Installation on macOS Catalina

In macOS Catalina you need to install Qt (free version can be found [here](https://www.qt.io/download-qt-installer)) and the following libraries:

* CGAL

* CGAL_Core

* boost_thread-mt

* boost_system-mt

* gmp

* mpfr

After cloning this repository and modifying the .pro files to adjust for different libary paths (e.g. [here]( https://github.com/klauste/ShortestPathToVisibility/blob/master/VisibilityProblemLibrary/VisibilityProblemLibrary.pro#L35)) you should be able to compile and run the programme with clang in QtCreator.

In the macBuild folder, I've added a dmg file which can be run on macOS Catalina and macOS Mojave (and possibly other versions of macOS). In order to build a dmg file from the source code you need to do the following:

`cd <pathToYourBuildFolder>/VisibilityProblemApp/VisibilityProblemApp.app/Contents`

`mkdir Frameworks`

`cd <pathToYourBuildFolder>/VisibilityProblemApp/`

`<pathToQt>/bin/macdeployqt VisibilityProblemApp.app -always-overwrite-appstore-compliant -dmg`

#### Installation on other operating systems

It shouldn't be difficult to compile and run the programme in other operating systems provided you install the necessary libraries and adjust the .pro files accordingly.
