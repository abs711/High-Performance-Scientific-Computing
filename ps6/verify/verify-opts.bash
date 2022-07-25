
declare -a ALLDEFS=("")
declare -a ALLOPTS=("-g -O0 -fno-omit-frame-pointer"  "-Ofast -march=native -DNDEBUG")

declare -a THEDEFS=("")
declare -a THEOPTS=("-Ofast -march=native -DNDEBUG")

declare -a THETARGETS=(
norm_seq.exe
norm_parfor.exe
norm_block_reduction.exe
norm_block_critical.exe
norm_cyclic_reduction.exe
norm_cyclic_critical.exe
)

declare -a THETESTS=(
"norms_test.exe"
)
