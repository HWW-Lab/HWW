#!/bin/bash
TEMP=/tmp/answer$$
whiptail --title "HumansWorldWide [HWW]"  --menu  "Ubuntu 16.04/18.04 Daemon Node :" 20 0 0 1 "Compile HWWd Ubuntu 16.04" 2 "Update HWWd 16.04 to latest" 3 "Compile HWWd Ubuntu 18.04" 4 "Update HWWd 18.04 to latest" 2>$TEMP
choice=`cat $TEMP`
case $choice in
1) echo 1 "Compiling HWWd Ubuntu 16.04"

echo "Updating linux packages"
sudo apt-get update -y && sudo apt-get upgrade -y

sudo apt-get --assume-yes install git unzip build-essential libssl-dev libdb++-dev libboost-all-dev libqrencode-dev libminiupnpc-dev libevent-dev obfs4proxy libcurl4-openssl-dev

echo "Installing HWW Wallet"
https://github.com/HWW-Lab/HWW
cd HWW || exit
git checkout master
git pull

cd src
make -f makefile.unix

sudo yes | cp -rf HWWd /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Populate HWW.conf"
mkdir ~/.HWW
echo -e "daemon=1\listen=1\rpcuser=user\rpcpassword=holamundorpc\nativetor=0\naddnode=" > ~/.HWW/HWW.conf

                ;;
2) echo 2 "Update HWWd"
echo "Updating HWW Wallet"
cd ~/HWW || exit
git checkout master
git pull

cd src
make -f makefile.unix

sudo yes | cp -rf HWWd /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Back to Compiled HWWd Binary Folder"
cd ~/HWW/src
                ;;
3) echo 3 "Compile HWWd Ubuntu 18.04"
echo "Updating linux packages"
sudo apt-get update -y && sudo apt-get upgrade -y

sudo apt-get --assume-yes install git unzip build-essential libdb++-dev libboost-all-dev libqrencode-dev libminiupnpc-dev libevent-dev obfs4proxy libssl-dev libcurl4-openssl-dev

echo "Downgrade libssl-dev"
sudo apt-get install make
wget https://www.openssl.org/source/openssl-1.0.1j.tar.gz
tar -xzvf openssl-1.0.1j.tar.gz
cd openssl-1.0.1j
./config
make depend
sudo make install
sudo ln -sf /usr/local/ssl/bin/openssl `which openssl`
cd ~
openssl version -v

echo "Installing HWW Wallet"
git clone https://github.com/HWW-Lab/HWW
cd HWW
git checkout master
git pull

cd src
make OPENSSL_INCLUDE_PATH=/usr/local/ssl/include OPENSSL_LIB_PATH=/usr/local/ssl/lib -f makefile.unix

sudo yes | cp -rf HWWd /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Populate HWW.conf"
mkdir ~/.HWW
echo -e "daemon=1\listen=1\rpcuser=user\rpcpassword=holamundorpc\nativetor=0\naddnode=" > ~/.HWW/HWW.conf


                ;;
4) echo 4 "Update HWWd 18.04"
echo "Updating HWW Wallet"
cd ~/HWW || exit
git checkout master
git pull

cd src
make OPENSSL_INCLUDE_PATH=/usr/local/ssl/include OPENSSL_LIB_PATH=/usr/local/ssl/lib -f makefile.unix

sudo yes | cp -rf HWWd /usr/bin/

echo "Copied to /usr/bin for ease of use"

echo "Back to Compiled HWWd Binary Folder"
cd ~/HWW/src
                ;;
esac
echo Selected $choice
