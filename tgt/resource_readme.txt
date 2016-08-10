Project File (resources.gpj)
------------------------------------------------------------------------------
The files provided in this project are resources to help get your project
running on your target. You may use these files as is or use them as examples
to create your own.

Unless the files here are included in the project file for your executable,
they will not impact your build.


Cafe OS Libraries sub-project (cafe_libs.gpj)
------------------------------------------------------------------------------
This subproject contains references to all of the Cafe OS libraries
that are required to build Cafe OS programs. This project is included
by default in all the executables in this project.

You can modify the list of libraries to suit your use of Cafe OS.

For more information about project files, see the "MULTI: Building
Applications" book for your processor.


Linker Directive Files (.ld)
------------------------------------------------------------------------------
Linker directive files (.ld) are used when your program is linked to define
program sections and assign them to specific addresses in memory.

The linker directive file from the project file for your executable will
be used when linking.

The eppc.Cafe.ld is copied from your SDK install directory when the
project is created.

For more information about linker directives files, see the "MULTI: Building 
Applications" book for your processor.

