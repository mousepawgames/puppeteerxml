Building PuppeteerXML
=====================

Building Basics
----------------------
CMake is used to build PuppeteerXML. For your convenience,
we've included Makefiles to automate all common build scenarios on Linux.
Type "make" in the root of this repository for more information.

At this time, the Makefiles are only designed for Linux. If you are building
on another system, you can interact with CMake directly.

Currently, PuppeteerXML can only be built using GCC 5 or later (or a compiler
that can emulate that).

Ready-To-Use Build
--------------------
If you just want to build PuppeteerXML to use in your own project, the fastest way
is to run "make ready". This will build PuppeteerXML and its documentation,
and place them all in a folder called "puppeteerxml". Simply copy that folder to
a convenient location, and point your compiler and linker to "puppeteerxml/include"
and "puppeteerxml/lib" respectively.

Building HTML Docs
--------------------------
The Ready-To-Use build includes the PDF documentation. If you want the HTML
documentation instead, run "make docs". Then, grab the 'docs/build/html'
folder, or just open 'docs/build/html/index.html' in your favorite web
browser.

Building Tester
----------------------
If you want to test out PuppeteerXML directly, run "make tester". Then, look
for the puppeteerxml-tester executable in tester/bin/[Debug/Release].

Code::Blocks
---------------------
PuppeteerXML was written and built in CodeBlocks. The projects (.cbp) in this
repository are pre-configured to build directly in the repository.

Source Directories
---------------------
- The '/docs' folder contains the Sphinx documentation for PuppeteerXML.
- The '/library' folder contains the source code for the PuppeteerXML
  library.
- The '/tester' folder contains the console application for testing
  the PuppeteerXML library.
