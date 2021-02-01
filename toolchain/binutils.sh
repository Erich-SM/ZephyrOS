_getbinutils(){
	wget https://mirrors.syringanetworks.net/gnu/binutils/binutils-2.32.tar.gz
}

_unpackbinutils(){
	tar -xvpf binutils-2.32.tar.gz
	cd binutils-2.32
}

_applypatch(){
	patch -p1 zephyrosbinutils.diff
}

#_compile(){
#}

_main(){
	echo "fetching binutils"
	_getbinutils
	echo "done \n unpacking binutils"
	_unpackbinutils
	echo "done \n applying patch"
	_applypatch
	echo "done"
}

_main
