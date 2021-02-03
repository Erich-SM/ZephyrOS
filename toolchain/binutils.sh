_fetchbinutils(){
    wget https://mirrors.ocf.berkeley.edu/gnu/binutils/binutils-2.32.tar.gz
}

_unpackbinutils(){
    tar -xvpf binutils-2.32.tar.gz
}

_patchbinutils(){
    cd binutils-2.32/
    patch -p1  < ../zephyros-binutils-20210201.diff
}

_clean(){
    rm -rf binutils-2.32.tar.gz
}

_buildbinutils(){
}

_binutils(){
    echo "fetching binutils"
    _fetchbinutils
    echo "done"
    echo "unpacking binutils"
    _unpackbinutils
    echo "done"
    echo "patching binutils"
    _patchbinutils
    echo "done"
    echo "cleaning.."
    _clean
    echo "building"
    _buildbinutils
    echo "done"
}

_binutils
