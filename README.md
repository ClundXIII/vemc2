
# vemc2

Copyright (c) 2015, Simon Michalke.
All rights reserved.

## Description

`vcore` is the core library
`vcons` a console client
`graphic` a graphical client using opengl

vemc2 is released under the BSD 3-Clause License.
Please refer to [`LICENSE`][license_link] file for details.

[license_link]:
https://github.com/ClundXIII/vemc2/blob/master/LICENSE

##Compile and install
See below for manual installation. If you do not have sudo rights, then do the manual installation.

###Automatic
install nanomessage: http://nanomsg.org/download.html
and a standard cmake, gcc compiler suite with opengl development packages first, then:

    git clone https://github.com/ClundXIII/vemc2-installer
    bash vemc2-installer/install.sh

Please not that this will need sudo rights in order to install the vesper-libs. They are required for logging.
To Compile, change directory and run "compile-all". This will also need sudo rights in order to install the library. If you do not have sudo rights, then do the manual installation.

    cd vemc2
    make compile-all && cons/vcons

###Manual Installation
No nanomessage required because we will only compile vesper-log. Note that this will change later!
Install a standard cmake, gcc compiler suite with opengl development packages first, then:

    #first, let us compile vesper:
    git clone https://github.com/VesperCommunity/vesper-libs.git
    cd vesper-libs/
    cmake .
    make vesper-log
    #go back to main dir
    cd ..
    #then fetch vemc2
    git clone https://github.com/ClundXIII/vemc2.git
    cd vemc2

We now need to edit 2 or 3 files:
1) core/CMakeLists.txt:

    nano core/CMakeLists.txt

add the following lines before "# add header files of this module":
    
    include_directories(~/vesper-libs/vesper_log)
    link_directories(~/vesper-libs/bin)

(assuming your vesper-libs directory is in ~) The result should look like:

    #endif()

    include_directories(${VESPER_INCLUDE_DIR})

    include_directories(~/vesper-libs/vesper_log)
    link_directories(~/vesper-libs/bin)

    # add header files of this module
    set(HEADERS

2) cons/CMakeLists.txt:

    nano cons/CMakeLists.txt

add the following lines before "# add header files of this module":
    
    include_directories(~/ ~/vesper-libs/vesper_log)
    link_directories(~/vemc2/core ~/vesper/bin)
    
(assuming vesper-libs and vemc2 are both in ~) The result should look like:

    link_directories(${VESPER_LIB_DIR})

    include_directories(~/ ~/vesper-libs/vesper_log)
    link_directories(~/vemc2/core ~/vesper-libs/bin)

    # add header files of this module

Now initialise cmake (ou can ignore the warning safely):

    make init-cmake

You can now compile the core and cons:

    make -C core
    #compile cons and start cons if there are no errors:
    make -C cons && cons/vcons

Install grapic: WIP
