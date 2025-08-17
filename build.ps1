param(
    [string]$DestinationName = "$PSScriptRoot/a.exe",
    [switch]$Rebuild,
    [switch]$Clean
)

$ApplicationExists = Test-Path $DestinationName

pushd $PSScriptRoot

if ($Clean)
{
    rm *.o -ErrorAction SilentlyContinue
    rm times.xml -ErrorAction SilentlyContinue
    
    popd
    exit 0
}


$CompilerArguments = @(
    ,"-Wshadow"
    ,"-Winit-self"
    ,"-Wredundant-decls"
    ,"-Wcast-align"
    ,"-Wundef"
    ,"-Wfloat-equal"
    ,"-Winline"
    ,"-Wunreachable-code"
    ,"-Wmissing-declarations"
    ,"-Wmissing-include-dirs"
    ,"-Wswitch-enum"
    ,"-Wswitch-default"
    ,"-Weffc++"
    ,"-Wmain"
    ,"-Wextra"
    ,"-Wall"
    ,"-g"
    ,"-pipe"
    ,"-fexceptions"
    ,"-Wcast-qual"
    ,"-Wconversion"
    ,"-Wctor-dtor-privacy"
    ,"-Wempty-body"
    ,"-Wformat-security"
    ,"-Wformat=2"
    ,"-Wignored-qualifiers"
    ,"-Wlogical-op"
    ,"-Wno-missing-field-initializers"
    ,"-Wnon-virtual-dtor"
    ,"-Woverloaded-virtual"
    ,"-Wpointer-arith"
    ,"-Wsign-promo"
    ,"-Wstack-usage=8192"
    ,"-Wstrict-aliasing"
    ,"-Wstrict-null-sentinel"
    ,"-Wtype-limits"
    ,"-Wwrite-strings"
    ,"-Werror=vla"
    ,"-D_DEBUG"
    ,"-D_EJUDGE_CLIENT_SIDE"
)

$LinkerArguments = @(
)



$CC = "g++"
$LD = "g++"

$CompilationTimes = & {Import-Clixml $PSScriptRoot/times.xml} 2>$null
$CompilationTimes ??= @{}

$LastHeaderModTime = gci *.h | % LastWriteTime | measure -Max | % Max*

$TimeUpdates = gci *.cpp | % FullName | % {
    $obj = $_-replace".cpp$",".o"
    $LastCompileTime = $CompilationTimes[$_]
    $LastModTime = (gc $_).LastWriteTime
    $LastModTime = ($LastHeaderModTime -gt $LastModTime ? $LastHeaderModTime : $LastModTime)
    if ($Rebuild -or $LastCompileTime -eq $null -or $LastModTime -gt $LastCompileTime)
    {
        Write-Host "Compile $_" -Foreground green

        & $CC -c @CompilerArguments $_ -o $obj
        
        @{file=$_;date=((Get-Date) + [timespan]::new(0, 0, 3))}
    }
    else
    {
        Write-Host "Skip $_" -Foreground yellow
    }
}

$TimeUpdates | % {
    $CompilationTimes[$_.file] = $_.date;
}

if ($TimeUpdates -or !$ApplicationExists)
{
    Write-Host "Linking" -Foreground green
    & $CC @LinkerArguments (gci *.cpp | % {$_.FullName -replace ".cpp$", ".o"}) -o $DestinationName
}
else
{
    Write-Host "Skip Linking" -Foreground yellow
}

Export-Clixml -InputObject $CompilationTimes $PSScriptRoot/times.xml

popd
