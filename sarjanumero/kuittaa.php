<?php

$_GET['ohje'] = 'off';
$_GET["no_css"] = 'yes';

if (@include_once "../inc/parametrit.inc");
elseif (@include_once "inc/parametrit.inc");

require '../inc/edifact_functions.inc';

echo "<meta name='viewport' content='width=device-width, maximum-scale=1.0' />\n";
echo "<link rel='stylesheet' type='text/css' href='ipad.css' />\n";
echo "<body>";

if (!isset($errors)) $errors = array();
if (!isset($viestit)) $viestit = array();

if (isset($submit)) {

  if (empty($hakunumero)) {
    $errors[] = t("Sy�t� rahtikirjanumero tai sarjanumero");
  }
  else {
    $parametrit = kuittaus_parametrit($hakunumero);
  }

  if (is_string($parametrit)) {
    $errors[] = t("Rahtikirja: {$parametrit} on jo kuitattu.");
  }
  elseif ($parametrit) {
    $sanoma = laadi_edifact_sanoma($parametrit);

    $filesize = strlen($sanoma);
    $liitedata = mysql_real_escape_string($sanoma);
    $tunnus = $parametrit['laskutunnus'];

    $query = "INSERT INTO liitetiedostot SET
              yhtio           = '{$kukarow['yhtio']}',
              liitos          = 'lasku',
              liitostunnus    = '$tunnus',
              selite          = '{$parametrit['sanomanumero']}',
              laatija         = '{$kukarow['kuka']}',
              luontiaika      = NOW(),
              data            = '{$liitedata}',
              filename        = '{$parametrit['sanoma_id']}',
              filesize        = '$filesize',
              filetype        = 'text/plain',
              kayttotarkoitus = 'kuittaussanoma'";
    pupe_query($query);

  }
  else{
    $errors[] = t("Rahtikirjaa ei l�ytynyt!");
  }

  if ($sanoma) {
    if (laheta_sanoma($sanoma)) {
    $viestit[] = t("Rahti vastaanotettu ja sanoma l�hetetty!");
    }
    else{
      $errors[] = t("L�hetys ei onnistunut");
    }
  }
  else{
    $errors[] = t("Ei l�hetetty sanomaa.");
  }
}

echo "<div class='header'>";

echo "<div class='header_left'>";
echo "<a href='index.php' class='button header_button'>";
echo t("P��valikko");
echo "</a>";
echo "</div>";

echo "<div class='header_center'>";
echo "<h1>";
echo t("RAHDIN KUITTAUS");
echo "</h1>";
echo "</div>";

echo "<div class='header_right'>";
echo "<a href='{$palvelin2}logout.php?location={$palvelin2}sarjanumero' class='button header_button'>";
echo t("Kirjaudu&nbsp;ulos");
echo "</a>";
echo "</div>";

echo "</div>";

echo "
<form method='post' action=''>
  <div style='text-align:center;padding:10px;'>
    <label for='hakunumero'>", t("Lue mik� tahansa rahdin viivakoodi tai rahtikirjanumero."), "</label><br>
    <input type='text' id='hakunumero' name='hakunumero' style='margin:10px;' />
    <br>
    <button name='submit' value='hakunumero' onclick='submit();' class='button'>", t("OK"), "</button>
  </div>
</form>

<script type='text/javascript'>
  $(document).on('touchstart', function(){
    $('#hakunumero').focus();
  });
</script>";

if (count($viestit) > 0) {
  echo "<div class='viesti' style='text-align:center'>";
  foreach ($viestit as $viesti) {
    echo $viesti."<br>";
  }
  echo "</div>";
}

if (count($errors) > 0) {
  echo "<div class='error' style='text-align:center'>";
  foreach ($errors as $error) {
    echo $error."<br>";
  }
  echo "</div>";
}

require 'inc/footer.inc';