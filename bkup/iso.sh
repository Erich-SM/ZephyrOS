#!/bin/sh
set -e
. ./config.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/ouroboros.kernel isodir/boot/ouroboros.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "OuroborOS" {
	multiboot /boot/ouroboros.kernel
}
EOF
grub-mkrescue -o ouroboros.iso isodir
