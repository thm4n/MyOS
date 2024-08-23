#!/bin/bash

PREFIX=/opt/cross
TARGET=i386-elf

function install_pkg {
    echo "-------------------------"
    echo " >> checking if package installed"
    if dpkg -l | grep -q "^ii  $1"; then
        echo " [V] $PACKAGE is already installed."
        return
    fi
    echo " >> installing $1"
    sudo apt install -y $1
    echo " [V] successfully installed $1"
    echo "-------------------------"
}

function install_binutils {
    mkdir $PREFIX/binutils
    git clone --depth 1 git://sourceware.org/git/binutils-gdb.git $PREFIX/binutils

    mkdir $PREFIX/binutils-build
    cd $PREFIX/binutils-build

    ../binutils/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
}

function install_gdb {
    mkdir $PREFIX/gdb
    # git clone --depth 1 https://sourceware.org/git/binutils-gdb.git $PREFIX/gdb

    mkdir $PREFIX/gdb-build
    cd $PREFIX/gdb-build

    # ../gdb/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
    make
    make install
}

function install_gcc {
    mkdir $PREFIX/gcc
    git clone --depth 1 git://gcc.gnu.org/git/gcc.git $PREFIX/gcc

    mkdir $PREFIX/gcc-build
    cd $PREFIX/gcc-build

    ../gcc/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
    make all-gcc
    make all-target-libgcc
    make install-gcc
    make install-target-libgcc
}

function main {
    echo "Installing packages:"
    sudo apt update -y -qq
    
    install_pkg build-essential 
    install_pkg bison
    install_pkg flex
    install_pkg libfmp3-dev
    install_pkg libmpc-dev
    install_pkg libmpfr-dev
    install_pkg texinfo

    install_binutils
    install_gcc
}

main
