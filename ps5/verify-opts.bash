

declare -a ALLDEFS=("")
declare -a ALLOPTS=("-g -O0 -fno-omit-frame-pointer"  "-Ofast -march=native -DNDEBUG")

declare -a THEDEFS=("")
declare -a THEOPTS=("-Ofast -march=native -DNDEBUG")

declare -a THETARGETS=(
"norm_order.exe"
"pnorm.exe"
"fnorm.exe"
"cnorm.exe"
"rnorm.exe"
"pmatvec.exe"
"pagerank.exe" 
)

declare -a THETESTS=(
"norm_test.exe"
"pnorm_test.exe"
"fnorm_test.exe"
"cnorm_test.exe"
"rnorm_test.exe"
"matvec_test.exe"
"pmatvec_test.exe"
"pagerank_test.exe"
)