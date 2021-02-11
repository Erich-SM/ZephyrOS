_fetchgcc(){
    http://mirrors.concertpass.com/gcc/releases/gcc-8.3.0/gcc-8.3.0.tar.gz
}

_unpackgcc(){
    tar -xvpf gcc-8.3.0.tar.gz
}

_patchgcc(){
    cd gcc-2.32/
    patch -p1  < ../zephyros-gcc-20210201.diff
}

_clean(){
    rm -rf gcc-8.3.0.tar.gz
}

_buildgcc(){
}

_gcc(){
    echo "fetching gcc"
    _fetchgcc
    echo "done"
    echo "unpacking gcc"
    _unpackgcc
    echo "done"
    echo "patching gcc"
    _patchgcc
    echo "done"
    echo "cleaning.."
    _clean
    echo "building"
    _buildgcc
    echo "done"
}

_gcc
