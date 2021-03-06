<?php

require_once "pdflib/phppdflib.class.php";
require_once "barcode/barcode.php";
require_once "barcode/c128cobject.php";

/**
 *
 * @param array   $tuotteet Array tuotteista, joiden hintalaput tulostetaan
 * @param array   $params   Configuraation array. Esimerkki:
 *   array(
 *     "kpl" => 1
 *   );
 *
 * @return array Tiedostonimi ja kaunisnimi
 */


function tulosta_hintalaput($tuotteet, $params = array()) {
  $kpl = isset($params["kpl"]) ? $params["kpl"] : false;

  $pdf = new pdffile();

  $pdf->set_default('margin-top', 0);
  $pdf->set_default('margin-right', 0);
  $pdf->set_default('margin-bottom', 0);
  $pdf->set_default('margin-left', 0);

  $text_normal = array(
    "height" => 8,
    "font"   => "Helvetica"
  );

  $text_bold = array(
    "height" => 10,
    "font"   => "Helvetica-Bold"
  );

  foreach ($tuotteet as $tuote) {
    $nimitys = explode("\n", wordwrap($tuote['nimitys'], 28));
    $hinta   = hintapyoristys($tuote['myyntihinta']);

    $viivakoodi              = viivakoodi($tuote['tuoteno'], "code128", 360, 60);
    $viivakoodin_teksti      = $tuote['tuoteno'];
    $viivakoodi_teksti_vasen = 50;
    $viivakoodi_vasen        = 17;

    $viivakoodin_asetukset = array(
      "scale" => array(
        "x" => 0.1,
        "y" => 0.1
      )
    );
    $kuva                  = $pdf->jfif_embed($viivakoodi);

    if ($kpl) {
      $montako_tulostetaan = $kpl;
    }
    elseif ($tuote["kpl"]) {
      $montako_tulostetaan = ($tuote['kpl'] * $tuote['tarrakerroin']);
    }
    else {
      $montako_tulostetaan = ($tuote['tarrakpl'] * $tuote['tarrakerroin']);
    }

    for ($i = 0; $i < $montako_tulostetaan; $i++) {
      $page = $pdf->new_page('4.9x3cm');

      // Kuva ensin, jotta ei mene tekstin p��lle
      $pdf->image_place($kuva, 15, $viivakoodi_vasen, $page, $viivakoodin_asetukset);
      $pdf->draw_text(0, 77, $nimitys[0], $page, $text_normal);
      $pdf->draw_text(0, 68, $nimitys[1], $page, $text_normal);
      $pdf->draw_text(0, 59, $nimitys[2], $page, $text_normal);

      $hinta         = str_replace(".", ",", $hinta);
      $hinnan_leveys = $pdf->strlen($hinta, $text_normal);
      $pdf->draw_text(100 - $hinnan_leveys, 50, $hinta . " EUR", $page, $text_bold);

      $yksikon_leveys = $pdf->strlen($tuote['yksikko'], $text_normal);
      $pdf->draw_text(129 - $yksikon_leveys, 40, $tuote['yksikko'], $page, $text_normal);
      $pdf->draw_text($viivakoodi_teksti_vasen, 8, $viivakoodin_teksti, $page, $text_normal);
    }
  }

  $pdf_tiedosto = $pdf->generate();

  $kaunisnimi   = "hintalaput.pdf";
  $tiedostonimi = "hintalaput-" . md5(uniqid(rand())) . ".pdf";
  file_put_contents("/tmp/{$tiedostonimi}", $pdf_tiedosto);

  return array($tiedostonimi, $kaunisnimi);
}

function hae_tuotteet_hintalappuja_varten($otunnus, $kukarow) {
  if ($otunnus <= 0) {
    return false;
  }

  $query = "SELECT tuote.tuoteno,
            tuote.eankoodi,
            tuote.myyntihinta,
            tuote.yksikko,
            tuote.nimitys,
            if(tuote.tarrakpl > 0, tuote.tarrakpl, 1) AS tarrakpl,
            if(tuote.tarrakerroin > 0, tuote.tarrakerroin, 1) AS tarrakerroin,
            tilausrivi.kpl
            FROM tilausrivi
            INNER JOIN tuote ON (tuote.yhtio = tilausrivi.yhtio
            AND tilausrivi.tuoteno       = tuote.tuoteno)
            WHERE tilausrivi.uusiotunnus = '{$otunnus}'
            AND tilausrivi.yhtio         = '{$kukarow['yhtio']}'
            AND tilausrivi.tyyppi        = 'O'";

  $result = pupe_query($query);

  $tuotteet = array();

  while ($tuote = mysql_fetch_assoc($result)) {
    array_push($tuotteet, $tuote);
  }

  return $tuotteet;
}
