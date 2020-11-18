# OuroborOS

This will only be the install instructions, you will need to bootstrap the OS if you want to boot. It currently only boots to a non-interactive screen that only display text. If you want to change the text. Edit kernel/kernel/kernel.c
and edit the printf text.

## Dependencies

686-elf toolchain.
GRUB, for the grub-mkrescue command.
Xorriso, the .iso creation engine used by grub-mkrescue.
GNU make 4.0 or later.
Qemu, optionally for testing the operating system.

## Booting

for building the OS you will need to add the header files to sysroot. To do so, run `./headers.sh`. Now to run `./build.sh` to build the OS. NOTE! If you want to do anytthing again, run `./clean.sh`. To create the ISO img, run 
`./iso.sh`. To boot the OS, use qemu. Run `./qemu.sh`. NOTE! if anything fails, run `./clean.sh` and restart. 

## Notation

The notation I am using for this is the greek alphabet. They go in the order of what will be build first. For example, code headed withm `/*[alpha]*/` will be coded first, `/*[beta]*/` will be made second and so on. the list of greek lettering is, Alpha, Beta, Gamma, Delta, Epsilion, Zeta, Eta, Theta, Iota, Kappa, Lambda, Mu, Nu, Xi, Omicron, Pi, Rho, Sigma, Tau, Upsilion, Phi, Chi, Psi, Omega. It is unlikely I will use any of the lower letters for one project. At least for now. 
