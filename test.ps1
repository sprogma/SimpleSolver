
# total limit is multiplication of this two.
$minLimit = -1e5
$maxLimit = 1e5
$minMlLimit = -1e5
$maxMlLimit = 1e5

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

    if ($r1 -gt $r2)
    {
        $r1, $r2 = $r2, $r1
    }

    $d1 = ([decimal]$rr1) - $r1
    $d2 = ([decimal]$rr2) - $r2

    Write-Host "Diffs: $d1 $d2"
    
    $d1
    $d2

    Write-Progress -Activity "Calculations" -PercentComplete ([int]($_ / $N * 100.0))
    
} | measure -AllStats
