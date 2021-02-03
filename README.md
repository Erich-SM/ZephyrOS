

# ZephyrOS

Documentation comming soon! (to an AMD computer near you!)

# Run down

This OS is fully built in C (or as much as i can do).

utils: <br/>
Compiler: SCC (simple compiler) git://git.simple-cc.org/scc <br/> 
LibC: either mlibc or musl  <br/>
Compression: Lzip and liblzf \* <br/>
Crypto: LibreSSL \* <br/>
Shell: Dash \* <br/>
Text editor: vim or nano \* <br/>
init: sinit \* <br/> 
Base: sbase \* <br/>
Filesystem: EXT2 \* <br/>

Please note, I still have to shell out the OS before most can be implemented. (note the little '\*') 


Structure: <br/>
config: for config files. Keeping the defaults will be fine <br/>
kernel: kernel source, drivers, info, etc <br/>
apps: binary files and user space apps <br/>
libc: havent decided yet. <br/>


# Current


There is no build instructions yet. bkup/ has all the origanal files that i will intagrate soon.
Binutils and gcc, I am hoping to change to either tcc or scc.
NOTE, there is some shenanigans with submodules in git. And since scc is an unfollowable link `git://git.simple-cc.org/scc`. Github doesnt do anything. I will try and fix that soon. 
