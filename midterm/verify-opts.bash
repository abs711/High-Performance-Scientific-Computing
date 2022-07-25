

# declare -a ALLDEFS=("-D__583")
# declare -a ALLDEFS=("")

declare -a ALLDEFS=("" "-D__583")
declare -a ALLOPTS=("-fsanitize=address -g -O0 -fno-omit-frame-pointer"  "-Ofast -march=native -DNDEBUG")
