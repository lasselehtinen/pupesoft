<?php

$ulos   = "";
$jatko   = 1; // oletetaan normaali k�sittely
$tyyppi   = 1; // oletetaan rivin n�kyvyys

if (mysql_field_name($result, $i) == "tunnus" or
  mysql_field_name($result, $i) == "yhtio") {
  $tyyppi = 0;
}

if (mysql_field_name($result, $i) == "toimipaikka_tunnus") {
  $toimipaikat   = hae_toimipaikat();
  $ei_toimipaikkaa = array(
    'tunnus' => 0,
    'nimi'   => t('Ei toimipaikkaa')
  );

  array_unshift($toimipaikat, $ei_toimipaikkaa);

  $ulos = "<td>";
  $ulos .= "<select name='$nimi'>";

  $sel = '';
  foreach ($toimipaikat as $toimipaikka) {
    if (isset($trow[$i]) and $trow[$i] == $toimipaikka['tunnus']) {
      $sel = 'SELECTED';
    }
    $ulos .= "<option value='{$toimipaikka['tunnus']}' {$sel}>{$toimipaikka['nimi']}</option>";
    $sel = '';
  }

  $ulos .= "</select>";
  $ulos .= "</td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "toimitustapa_tunnus") {
  $trow['toimitustapa_tunnus'] = $lukitse_avaimeen;
  $trow[$i] = $lukitse_avaimeen;
  $tyyppi = 4;
}
