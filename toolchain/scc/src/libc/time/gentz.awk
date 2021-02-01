BEGIN { print "#include \"../libc.h\"\nstruct tzone tzones[] = {" }
{
    split($2,a,":")
    min = a[1] * 60
    min = min + a[2]
    sec = min * 60
    printf "\t{\"%s\", %d},\n", $1, sec
}
END { print "\t{0,\t0}\n};\n" }
