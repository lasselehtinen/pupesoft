<?php

/*
 * Siirret��n tuotemasterdata Relexiin
 * 6.1 PRODUCT GROUP HIERARCHY FILE
*/

//* T�m� skripti k�ytt�� slave-tietokantapalvelinta *//
$useslave = 1;

// Kutsutaanko CLI:st�
if (php_sapi_name() != 'cli') {
  die ("T�t� scripti� voi ajaa vain komentorivilt�!");
}

if (!isset($argv[1]) or $argv[1] == '') {
  die("Yhti� on annettava!!");
}

ini_set("memory_limit", "5G");

// Otetaan includepath aina rootista
ini_set("include_path", ini_get("include_path").PATH_SEPARATOR.dirname(dirname(dirname(__FILE__))).PATH_SEPARATOR."/usr/share/pear");

require 'inc/connect.inc';
require 'inc/functions.inc';

// Logitetaan ajo
cron_log();

$ajopaiva  = date("Y-m-d");
$paiva_ajo = FALSE;

if (isset($argv[2]) and $argv[2] != '') {

  if (strpos($argv[2], "-") !== FALSE) {
    list($y, $m, $d) = explode("-", $argv[2]);
    if (is_numeric($y) and is_numeric($m) and is_numeric($d) and checkdate($m, $d, $y)) {
      $ajopaiva = $argv[2];
    }
  }
  $paiva_ajo = TRUE;
}

// Yhti�
$yhtio = mysql_real_escape_string($argv[1]);

$yhtiorow = hae_yhtion_parametrit($yhtio);
$kukarow  = hae_kukarow('admin', $yhtiorow['yhtio']);

// Tallennetaan tuoterivit tiedostoon
$filepath = "/tmp/group_update_{$yhtio}_$ajopaiva.csv";

if (!$fp = fopen($filepath, 'w+')) {
  die("Tiedoston avaus ep�onnistui: $filepath\n");
}

// Otsikkotieto
$header  = "code1;";
$header .= "name1";
$header .= "\n";
fwrite($fp, $header);

// Haetaan tuoteryhm�t
$query = "SELECT selite,
          selitetark
          FROM avainsana
          WHERE yhtio = '{$yhtio}'
          AND laji    = 'TRY'
          AND kieli   = '{$yhtiorow['kieli']}'
          ORDER BY selite";
$res = pupe_query($query);

// Kerrotaan montako rivi� k�sitell��n
$rows = mysql_num_rows($res);

echo date("d.m.Y @ G:i:s") . ": Relex tuoteryhmi� {$rows} kappaletta.\n";

$k_rivi = 0;

while ($row = mysql_fetch_assoc($res)) {
  // Tuotetiedot
  $rivi  = $row['selite'].";";
  $rivi .= pupesoft_csvstring($row['selitetark']);
  $rivi .= "\n";
  fwrite($fp, $rivi);

  $k_rivi++;
}

fclose($fp);

// Tehd��n FTP-siirto
if ($paiva_ajo and !empty($relex_ftphost)) {
  // Tuotetiedot
  $ftphost = $relex_ftphost;
  $ftpuser = $relex_ftpuser;
  $ftppass = $relex_ftppass;
  $ftppath = "/data/input";
  $ftpfile = $filepath;
  require "inc/ftp-send.inc";
}

echo date("d.m.Y @ G:i:s") . ": Relex tuoteryhm�t valmis.\n\n";
