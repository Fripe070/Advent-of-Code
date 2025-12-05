param (
    [Parameter(Mandatory=$true)][string]$filePath
)

$Ranges = @()
$Items = @()
foreach($line in Get-Content $filePath) {
    if ($line -match '^(\d+)-(\d+)$') {
        $Ranges += @{ 
            Start = [uint64]$matches[1]; 
            End = [uint64]$matches[2] 
        }
    } elseif ($line -match "^(\d+)$") {
        $Items += [uint64]$matches[1]
    }
}


$Fresh = 0
foreach($Item in $Items) {
    foreach($Range in $Ranges) {
        $Contained = ($Item -ge $Range.Start) -and ($Item -le $Range.End)
        if ($Contained) {
            $Fresh += 1
            break
        }
    }
}

Write-Output "Part1: $Fresh"


$ProcessedRanges = @()
foreach($Range in $Ranges) {
    $Splits = @(
        @{ Start = $Range.Start; End = $Range.End }
    )
    foreach($Procesed in $ProcessedRanges) {
        $NewSplits = @()
        foreach($Split in $Splits) {
            if (($Split.End -lt $Procesed.Start) -or ($Split.Start -gt $Procesed.End)) {
                # No overlap
                $NewSplits += $Split
            } else {
                # Split into new parts that don't overlap. 
                # Might exist a bug where it can be incorect if ranges are equal? Doesn't seem to happen in input data so shrug
                if ($Split.Start -lt $Procesed.Start) {
                    $NewSplits += @{ Start = $Split.Start; End = $Procesed.Start - 1 }
                }
                if ($Split.End -gt $Procesed.End) {
                    $NewSplits += @{ Start = $Procesed.End + 1; End = $Split.End }
                }
            }
        }
        $Splits = $NewSplits
    }
    foreach($Split in $Splits) {
        $ProcessedRanges += $Split
    }
}
$FreshRangeCount = 0
foreach($Range in $ProcessedRanges) {
    $FreshRangeCount += ($Range.End - $Range.Start + 1)
}

Write-Output "Part2: $($FreshRangeCount)"
