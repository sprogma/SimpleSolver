param(
    [string[]]
    $AddCompilerFlags,
    [string[]]
    $AddLinkerFlags
)

pushd $PSScriptRoot

$CompilerFlags = @("-Wall", "-I.")

$CompilerFlags += $AddCompilerFlags
$LinkerFlags += $AddLinkerFlags

g++ $CompilerFlags -c ./main.cpp -o main.o
g++ $LinkerFlags ./main.o -o "a$($IsWindows ? ".exe" : '')"

popd
