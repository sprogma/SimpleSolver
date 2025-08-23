
# total limit is multiplication of this two.
$minLimit = -11111.1
$maxLimit = 11111.1
$minMlLimit = -11111.1
$maxMlLimit = 11111.1

$N = 1000

1..$N | % {
    $r1 = [decimal](Get-Random -min $minLimit -max $maxLimit)
    $r2 = [decimal](Get-Random -min $minLimit -max $maxLimit)
    $ml = [decimal](Get-Random -min $minMlLimit -max $maxMlLimit)
    $a = $ml
    $b = (-$r1 - $r2) * $ml
    $c = $r1 * $r2 * $ml
    "$c`n$b`n$a" | ./a.exe >variable:res
    $rr1, $rr2 = -split $res

    $d1 = ([decimal]$rr1) - $r1
    $d2 = ([decimal]$rr2) - $r2
    
    $dd1 = ([decimal]$rr1) - $r2
    $dd2 = ([decimal]$rr2) - $r1
    
    if ([Math]::abs($d1) -gt [Math]::abs($dd1))
    {
        $d1 = $dd1
    }
    if ([Math]::abs($d2) -gt [Math]::abs($dd2))
    {
        $d2 = $dd2
    }

    Write-Host "Diffs: $d1 $d2"
    
    [Math]::abs($d1)
    [Math]::abs($d2)

    Write-Progress -Activity "Calculations" -PercentComplete ([int]($_ / $N * 100.0))
    
} | measure -AllStats
