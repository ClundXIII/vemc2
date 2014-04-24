echo "starting portable app ..."
echo Library Path: $LD_LIBRARY_PATH
if [ $# -eq 0 ]
 then
  echo "creating temp directory at $HOME/.vemc2 ..."
  if [ -d "$HOME/.vemc2" ]
   then
    echo "directory already exists, delete? [y/*]"
    read input
    if [ "$input" != "y" ]
     then
      exit
    fi
    rm -r $HOME/.vemc2
    echo "deleted!"
  fi
  mkdir $HOME/.vemc2
  if [ ! -d "$HOME/.vemc2" ]
   then
    echo "couldn't create directory!"
    exit
  fi
  echo copying files ...
  cp -r ./* $HOME/.vemc2/
  backdir=`pwd`
  cd $HOME/.vemc2/
  chmod +x start.sh
  chmod +x vemc2_nogui
  echo `pwd`
  #chmod +x Visualeiemc2
  #chmod +x Visualeiemc232
  #./start.sh
  ./vemc2_nogui
  echo "Program closed!"
  cd $backdir
 #else
  #
fi

echo "deleting temp directory ..."
rm -r $HOME/.vemc2
