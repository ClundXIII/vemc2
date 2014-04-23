asdf=`uname -m`
#LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs/
echo "###################################################"
echo "#                                                 #"
echo "#  Visualeiemc2 - (c) by Simon Michalke, 04/2014  #"
echo "#                                                 #"
echo "#              --- DEMO Version ---               #"
echo "#                                                 #"
echo "#  email: simon.m.m@freenet.de                    #"
echo "#                                                 #"
echo "###################################################"
echo Library Path: $LD_LIBRARY_PATH
if [ $# -eq 0 ]
 then
  if [ "$asdf" == "i686" ]
   then
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs32/
    echo "$asdf --> starting 32 bit Executable"
    if [ -s "./Visualeiemc232" ]
     then
      ./Visualeiemc232
     else
      echo "This version does not support this Platform!"
    fi

   else
    export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs86/
    echo "$asdf --> starting 64 bit Executable"
    if [ -s "./Visualeiemc2" ]
     then
      ./Visualeiemc2
     else
      echo "This version does not support this Platform!"
    fi
  fi
 else
  if [ $# -eq 1 ]
   then
    if [ "$@" == "-f32" -o "$@" == "--force-32" ]
     then
      if [ -s "./Visualeiemc232" ]
       then
        ./Visualeiemc232
       else
        echo "This version does not support this Platform!"
      fi
    fi
    if [ "$@" == "-f64" -o "$@" == "--force-64" ]
     then
      export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs86/
      if [ -s "./Visualeiemc2" ]
       then
        ./Visualeiemc2
       else
        echo "This version does not support this Platform!"
      fi
    fi
    if [ "$@" == "-d" -o "$@" == "--debug" ]
     then
      export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs86/
      if [ -s "./Visualeiemc2" ]
       then
        gdb ./Visualeiemc2
       else
        gdb ./Visualeiemc232
      fi
    fi
    if [ "$@" == "-c" -o "$@" == "--check-libs" ]
     then
      if [ -s "./Visualeiemc232" ]
       then
        echo "*32 bit version:"
        echo "-native missing:"
        ldd ./Visualeiemc232 | grep "not found"
        ldd ./Visualeiemc232 | grep "nicht gefunden"
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs32/
        echo "-still missing after export:"
        ldd ./Visualeiemc232 | grep "not found"
        ldd ./Visualeiemc232 | grep "nicht gefunden"
       else
        echo "This version does not support 32 bit Platform!"
      fi
      if [ -s "./Visualeiemc2" ]
       then
        echo "*64 bit version:"
        echo "-native missing:"
        ldd ./Visualeiemc2 | grep "not found"
        ldd ./Visualeiemc2 | grep "nicht gefunden"
        export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:`pwd`/libs86/
        echo "-still missing after export:"
        ldd ./Visualeiemc2 | grep "not found"
        ldd ./Visualeiemc2 | grep "nicht gefunden"
       else
        echo "This version does not support 64 bit Platform!"
      fi
    fi
    if [ "$@" == "-insert" ]
     then
      echo "copying file ..."
     if [ "$asdf" == "i686" ]
      then
       echo "32 bit version!"
       cp ./../vemc2 ./Visualeiemc232
      else
       echo "64 bit version!"
       cp ./../vemc2 ./Visualeiemc2
     fi
    fi
   else
    echo "error: more than one argument given!"
  fi
fi
