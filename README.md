# ZephyrOS

Documentation comming soon! (to an AMD computer near you!)

# Run down

This OS is fully built in C (or as much as i can do).

utils:
Compiler: SCC (simple compiler) git://git.simple-cc.org/scc 
LibC: either mlibc or musl 
Compression: Lzip and liblzf \*
Crypto: LibreSSL \*
Shell: Dash \* 
Text editor: vim or nano \*
init: sinit \* <br /> 
Base: sbase \*
Filesystem: EXT2 \*

Please note, I still have to shell out the OS before most can be implemented. (note the little '\*') 


Structure:
config: for config files. Keeping the defaults will be fine
kernel: kernel source, drivers, info, etc
apps: binary files and user space apps
libc: havent decided yet.


# Current


There is no build instructions yet. bkup/ has all the origanal files that i will intagrate soon.
Binutils and gcc, I am hoping to change to either tcc or scc.
NOTE, there is some shenanigans with submodules in git. And since scc is an unfollowable link `git://git.simple-cc.org/scc`. Github doesnt do anything. I will try and fix that soon. 
