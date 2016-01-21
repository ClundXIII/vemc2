
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

    git clone https://github.com/ClundXIII/vemc2-installer
    #install nanomessage: http://nanomsg.org/download.html and a standard gcc compiler suite with opengl development packages
    bash vemc2-installer/install.sh

Please not that this will need sudo rights in order to install the vesper-libs. They are required for logging.
To Compile, change directory and run "compile-all". This will also need sudo rights in order to install the library. If you do not have sudo rights, then do the manual installation.

    cd vemc2
    make compile-all && cons/vcons

###Manual Installation
WIP
