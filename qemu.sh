#!/bin/sh
set -e
. ./config.sh

qemu-system-$(./target-triplet-to-arch.sh $HOST) -cdrom ouroboros.iso
