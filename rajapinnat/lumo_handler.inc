<?php

/**
 * Lumo-handler ajaa taustalla maksup��tetapahtumia ja tallentaa liikkuvat tiedot kantaan.
 * Tarvitaan $tilausnumero, $korttimaksu (summa)
 * Maksutapahtuman tila tarkastetaan ensin aina tietokannasta ja ajetaan vasta sitten maksup��tteelle
 * Settaa lopuksi muuttujat k�ytt�liittym�� varten
 *
 */


require_once "rajapinnat/lumo_client.php";

$korttimaksu   = str_replace(",", ".", $korttimaksu);
$korttimaksu_f = $korttimaksu * 100;

$summa   = str_replace(",", '.', $kaikkiyhteensa);
$summa_f = $summa * 100;

$jaljella_oleva_summa = $summa_f - maksettu_kortilla_yhteensa($laskurow["tunnus"]);

if ($jaljella_oleva_summa >= 0) {
  $voi_maksaa_viela = $jaljella_oleva_summa >= $korttimaksu_f;
}
else {
  $voi_maksaa_viela = $jaljella_oleva_summa <= $korttimaksu_f;
}


// 1 = tee maksutapahtuma, 2 = hae asiakkaan kuitti, 3 = hae kauppiaan kuitti
$suoritukset = array (1, 2, 3);

foreach ($suoritukset as $suoritus) {

  if ($suoritus == 1) $onnistuuko = false;

  $lumo_ip = explode(":", $kukarow["maksupaate_ip"]);
  $lumo_service_address = $lumo_ip[0];
  $lumo_service_port = $lumo_ip[1] ? $lumo_ip[1] : 1234;

  // Jos k�ytt�j�lt� puuttuu maksup��tteen IP
  if (empty($lumo_service_address)) {
    $onnistuuko = "Maksup��tett� ei ole konfiguroitu oikein t�lle k�ytt�j�lle";
    break;
  }

  // Jos puuttuu jostain syyst� tilausnumero
  if (!isset($tilausnumero) or trim($tilausnumero) == '') {
    $onnistuuko = "Tilausnumero kadonnut, maksutapahtumaa ei voi tehd�";
    break;
  }

  // Jos summa on v�hint��n 0.01 EUR voidaan tehd� maksutapahtuma
  if (is_numeric($korttimaksu_f) and $voi_maksaa_viela) {
    // Jos maksutapahtuma ep�onnistui niin ei tehd� mit��n
    if ($suoritus > 1 and $onnistuuko != "VELOITETTU") break;

    $clientti = new LumoClient($lumo_service_address, $lumo_service_port);

    if ($clientti->getErrorCount() > 0) {
      $onnistuuko = "Ei yhteytt� maksup��tteeseen";
      break;
    }

    switch ($suoritus) {
    case '1':
      // Jos summa on v�hint��n 0.01 EUR voidaan tehd� maksutapahtuma
      if ($korttimaksu_f >= 1) {
        $onnistuuko = $clientti->startTransaction($korttimaksu_f);
      }
      elseif ($korttimaksu_f < 0) {
        // Jos summa on negatiivinen tehd��n hyvitys/peruutus
        // Dummyarkistointitunnus
        $arkistointitunnus = 999999999999;
        // Haetaan viimeisimm�n onnistuneen maksusuorituksen kuitti
        $query = "SELECT asiakkaan_kuitti
                    FROM maksupaatetapahtumat
                    WHERE yhtio           = '{$kukarow['yhtio']}'
                    AND tilausnumero      = '{$tilausnumero}'
                    AND tila              = 'K'
                    AND asiakkaan_kuitti != ''
                    ORDER BY luontiaika desc
                    LIMIT 1";
        $res = pupe_query($query);
        $kuittirivi = mysql_fetch_assoc($res);

        if (isset($kuittirivi['asiakkaan_kuitti']) and !empty($kuittirivi['asiakkaan_kuitti'])) {
          $kaikki_kuittirivit = explode("\n", $kuittirivi['asiakkaan_kuitti']);

          foreach ($kaikki_kuittirivit as $kuitin_rivi) {
            list($rivinotsikko, $rivintieto) = explode(":", $kuitin_rivi);
            // Etsit��n kuittirivilt� arkistointitunnusta
            if (trim($rivinotsikko) == "AVIITE") {
              $arkistointitunnus = trim($rivintieto);
              break;
            }
          }
        }
        // Jos k�ytt�liittym�ss� summa on negatiivinen, muutetaan maksup��tteelle
        $korttimaksu_f = $korttimaksu_f * -1;
        $onnistuuko = $clientti->startTransaction($korttimaksu_f, 1, $arkistointitunnus);
      }
      elseif ($peruutus == "X") {
        $query = "SELECT *
                    FROM maksupaatetapahtumat
                    WHERE yhtio           = '{$kukarow['yhtio']}'
                    AND tilausnumero      = '{$tilausnumero}'
                    AND tila              = 'K'
                    AND asiakkaan_kuitti != ''
                    ORDER BY luontiaika desc
                    LIMIT 1";

        $res        = pupe_query($query);
        $kuittirivi = mysql_fetch_assoc($res);

        if (isset($kuittirivi['asiakkaan_kuitti']) and !empty($kuittirivi['asiakkaan_kuitti'])) {
          $kaikki_kuittirivit = explode("\n", $kuittirivi['asiakkaan_kuitti']);

          foreach ($kaikki_kuittirivit as $kuitin_rivi) {
            list($rivinotsikko, $rivintieto) = explode(":", $kuitin_rivi);
            // Etsit��n kuittirivilt� arkistointitunnusta
            if (trim($rivinotsikko) == "AVIITE") {
              $arkistointitunnus = trim($rivintieto);
              break;
            }
          }
        }

        $korttimaksu   = $kuittirivi["summa_valuutassa"];
        $korttimaksu_f = str_replace(",", ".", $korttimaksu);
        $korttimaksu_f = $korttimaksu_f * 100;
        $onnistuuko    = $clientti->startTransaction($korttimaksu_f, 1, $arkistointitunnus);
        $korttimaksu   = $korttimaksu * -1;
      }
      else {
        $onnistuuko = "HYL�TTY";
      }
      $onnistuuko = $onnistuuko === true ? "VELOITETTU" : "HYL�TTY";
      break;

    case '2':
      $kuitti1 = $clientti->getCustomerReceipt();
      $kuitti1 = utf8_decode($kuitti1);
      $pankkivailuotto = '';
      $maksutyyppi = '';

      if (strpos($kuitti1, "LUOTTOKORTTI") !== false) {
        $pankkivailuotto = 'LUOTTOKORTTI';
        $maksupaate_maksetut['luottokortti'] += $korttimaksu;
      }
      elseif (strpos($kuitti1, "PANKKIKORTTI") !== false) {
        $pankkivailuotto = 'PANKKIKORTTI';
        $maksupaate_maksetut['pankkikortti'] += $korttimaksu;
      }
      else {
        // Failsafe jos kuitilta ei jostain syyst� l�ydy pankki/luottokorttiteksti� Suomeksi
        $pankkivailuotto = 'PANKKIKORTTI';
        $maksupaate_maksetut['pankkikortti'] += $korttimaksu;
      }

      if (strpos($kuitti1, "PERUUTUS") !== false) {
        $maksutyyppi = "PERUUTUS";
      }
      elseif (strpos($kuitti1, "HYVITYS") !== false) {
        $maksutyyppi = "HYVITYS";
      }
      else {
        $maksutyyppi = "OSTO";
      }

      break;

    case '3':
      $kuitti2 = $clientti->getMerchantReceipt();
      $kuitti2 = utf8_decode($kuitti2);

      if (strpos($kuitti2, "ALLEKIRJOITUS")) {
        require "tilauskasittely/tulosta_asiakkaan_kuitti.inc";
        tulosta_kauppiaan_kuitti($kuitti2, $kukarow["kuittitulostin"]);
      }
      break;
    }

    // Tuhotaan objekti ett� socketti sulkeutuu
    unset($clientti);
    // Venataan sekka koska socketti on joskus hidas ja halutaan seuraava transaktio
    if ($suoritus < 3) sleep(1);
  }
  else {
    $onnistuuko = "Tarkista summa";
  }
}

// Kirjataan suoritus lopuksi

$status = '';

// Setataan oikea arvo tapahtumalle
if ($onnistuuko == "VELOITETTU" and ($maksutyyppi == 'OSTO')) {
  // K - Korttimaksu
  $status = 'K';
}
elseif ($onnistuuko == "VELOITETTU" and ($maksutyyppi == 'PERUUTUS' or $maksutyyppi == "HYVITYS")) {
  // H - Hyvitys
  $status = 'H';
}

// P�ivitet��n suoritus kantaan jos se onnistui
if ($status == 'K' or $status == 'H') {

  $kuittilisa = "";

  if (!empty($kuitti1)) {
    $kuittilisa .= " asiakkaan_kuitti = '{$kuitti1}', ";
  }

  if (!empty($kuitti2)) {
    $kuittilisa .= " kauppiaan_kuitti = '{$kuitti2}', ";
  }

  $query = "INSERT INTO maksupaatetapahtumat SET
            yhtio            = '{$kukarow['yhtio']}',
            $kuittilisa
            maksutapa        = '{$pankkivailuotto}',
            luontiaika       = now(),
            muutospvm        = now(),
            laatija          = 'Lumo',
            valkoodi         = '{$laskurow['valkoodi']}',
            tila             = '{$status}',
            tilausnumero     = '{$tilausnumero}',
            summa_valuutassa = $korttimaksu
            ";
  $result = pupe_query($query);
  $korttimaksu = '';
}
else {
  $korttimaksutapahtuman_status = $onnistuuko === false ? "HYL�TTY" : $onnistuuko;
}
// Tyhjennet��n handlerissa setattavat muuttujat jotka eiv�t mene k�ytt�liittym��n
unset($kuittilisa);
unset($kuitti1);
unset($kuitti2);
unset($onnistuuko);
unset($status);
unset($pankkivailuotto);
unset($maksutyyppi);

function maksettu_kortilla_yhteensa($tilausnumero) {
  global $kukarow;

  $query =
    "SELECT SUM(summa_valuutassa) AS maksettu_yhteensa
     FROM maksupaatetapahtumat
     WHERE yhtio = '{$kukarow['yhtio']}'
     AND tilausnumero = {$tilausnumero}";

  $result = pupe_query($query);

  $maksettu_yhteensa = mysql_fetch_assoc($result);
  $maksettu_yhteensa = $maksettu_yhteensa["maksettu_yhteensa"];
  $maksettu_yhteensa = $maksettu_yhteensa * 100;

  return $maksettu_yhteensa;
}