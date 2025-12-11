<html>
<head>
  <link rel="stylesheet" href="style.css">
  <style>
    .tree {
      font-size: 8px;
      max-width: 80%;
      overflow-x: auto;
    }
  </style>
</head>
<body class="row">

<?php
use Ds\Set;

$target_dir = "uploads/";
$target_file = $target_dir . basename($_FILES["inputIpload"]["name"]);
$content = file_get_contents($_FILES["inputIpload"]["tmp_name"]);

$lines = explode("\n", trim($content));

$startIndex = -1;
for ($row = 0; $row < count($lines); $row++) {
  $line = $lines[$row];
  for ($col = 0; $col < strlen($line); $col++) {
    $char = $line[$col];
    if ($char === 'S') {
      $startIndex = $col;
    }
  }
}

$part1 = 0;
$beams1 = new Set();
$beams1->add($startIndex);
for ($row = 1; $row < count($lines); $row++) {
  foreach ($beams1->copy() as $beamIndex) {
    $char = $lines[$row][$beamIndex];
    if ($char === '^') {
      $beams1->remove($beamIndex);
      $beams1->add($beamIndex - 1);
      $beams1->add($beamIndex + 1);
      $part1 += 1;
    }
  }
}

$beams2 = [];
$beams2[$startIndex] = 1;

for ($row = 1; $row < count($lines); $row++) {
  $newBeams = [];
  foreach ($beams2 as $beamIndex => $weight) {
    $char = $lines[$row][$beamIndex];
    if ($char === '^') {
      $indexLeft = $beamIndex - 1;
      $indexRight = $beamIndex + 1;
      if (!array_key_exists($indexLeft, $newBeams)) {
        $newBeams[$indexLeft] = 0;
      }
      if (!array_key_exists($indexRight, $newBeams)) {
        $newBeams[$indexRight] = 0;
      }
      $newBeams[$indexLeft] += $weight;
      $newBeams[$indexRight] += $weight;
    } else {
      if (!array_key_exists($beamIndex, $newBeams)) {
        $newBeams[$beamIndex] = 0;
      }
      $newBeams[$beamIndex] += $weight;
    }
  }
  $beams2 = $newBeams;
}
$part2 = 0;
foreach ($beams2 as $weight) {
  $part2 += $weight;
}
?>

<div class="tree">
  <code> <?php echo nl2br($content); ?> </code>
</div>
<div class="col">
  <div>
    <h2>Part 1</h2>
    <code><?php echo $part1; ?></code>
  </div>
  <div>
    <h2>Part 2</h2>
    <code><?php echo $part2; ?></code>
  </div>
</div>

</body>
</html>
