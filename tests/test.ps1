param(
    $testApplication="./a.exe",
    [switch]$BuildTester
)

pushd $PSScriptRoot

$CFLAGS = @("-I..", "-g", "--coverage")
$LDFLAGS = @()
$LDLIBS = "-lgcov"

rm *.gcna
rm *.gcno
rm *.gcov
rm ../*.gcna
rm ../*.gcno
rm ../*.gcov

../build.ps1 -Rebuild -AddCompilerArguments @("--coverage") -AddLinkerArguments @("-lgcov")

$CC = "g++"

$tests = ls "$PSScriptRoot/*.cpp" | % FullName | Split-Path -LeafBase

if ($BuildTester)
{
    $tests | % { 
        & $CC $CFLAGS -c "$_.cpp" -o "$_.o" | Out-Host
        & $CC $LDFLAGS "$_.o" (ls "../*.o" -Exclude "*main*") -o "$_.exe" $LDLIBS | Out-Host
        $_
    }
}

$tests | % {
    $text = & "./$_.exe" 2>&1
    if ($LASTEXITCODE){Write-Host "$_.cpp test was failed. Error code: $LASTEXITCODE. Exit info:`n$text" -Foreground red}
}

Write-Host "Test end."

gcov *.o ../*.o

popd
