# ShortestPathToVisibility
This project was written as part of my Master of Science thesis. It implements an algorithm in C++ to solve the quickest-pair visibility problem presented in the article [On Romeo and Juliet Problems: Minimizing Distance-to-Sight](https://ui.adsabs.harvard.edu/abs/2019arXiv190601114A).

The project has three sub-projects:

* a library implementing the algorithm using [CGAL](https://www.cgal.org/) to triangulate a polygon

* a (Qt)[https://www.qt.io/] project to visualize the problem and its solution

* a Qt test project to test the algorithm

If you find any errors in this project, you can write to me. Not sure if I will respond though. I need a 6-month holiday from the world after finishing this.

I've compiled and run the programme on macOS Catalina and Ubuntu 18.04. If you want to run it on your machine I recommend using Ubuntu 18.04 as the installation of required third party libraries is much simpler. If you don't have Ubuntu 18.04, you can run it by installing the [Ubuntu Image](http://releases.ubuntu.com/18.04/) on [VirtualBox](https://www.virtualbox.org/)

#### Installation on Ubuntu

In Ubuntu, install the following:

`sudo apt-get install build-essential`

`sudo apt-get install qtcreator`

`sudo apt-get install qt5-default`

`sudo apt-get install libcgal-dev`

Then clone this repository and open it in the QtCreator. You should be able to compile it via clang.

#### Installation on macOS Catalina

In macOS Catalina you need to install Qt (free version can be found (here)[https://www.qt.io/download-qt-installer]) and the following libraries:

CGAL

CGAL\_Core

CGAL\_ImageIO

boost\_thread-mt

boost\_system-mt

gmp

mpfr

After cloning this repository and modifying the .pro files to adjust for different libary paths (e.g. (here)[ https://github.com/klauste/ShortestPathToVisibility/blob/master/VisibilityProblemLibrary/VisibilityProblemLibrary.pro#L35]) you should be able to compile and run the programme.

#### Installation on other operating systems

It shouldn't be difficult to compile and run the programme in other operating systems provided you install the necessary libraries and adjust the .pro files accordingly.
