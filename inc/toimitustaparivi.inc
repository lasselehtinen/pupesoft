<?php

$ulos = "";
$jatko = 1; // oletetaan normaali k�sittely
$tyyppi = 1; // oletetaan rivin n�kyvyys

if (mysql_field_name($result, $i) == "tunnus" or
  mysql_field_name($result, $i) == "yhtio") {
  $tyyppi = 0;
}

if (mysql_field_name($result, $i) == "nouto") {

  $sel='';
  if ($trow[$i]!='') $sel = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Tilaukset toimitetaan asiakkaalle")."</option>";
  $ulos .= "<option value='o' $sel>".t("Asiakas noutaa tilaukset")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "lauantai") {

  $sel='';
  if ($trow[$i]!='') $sel = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Ei lauantaijakelua")."</option>";
  $ulos .= "<option value='o' $sel>".t("Itella lis�palvelu: Lauantaijakelu")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "kuljyksikko") {

  $sel='';
  if ($trow[$i]!='') $sel = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Ei kuljetusyksikk�kuljetusta")."</option>";
  $ulos .= "<option value='o' $sel>".t("Itella lis�palvelu: Kuljetusyksikk�kuljetus")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "virallinen_selite") {

  $sel = '';
  if ($trow[$i] != '') $sel[$trow[$i]] = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Ei valintaa")."</option>";

  $ulos .= "<optgroup label='Pupesoft / Itella'>";
  $ulos .= "<option value='Express City 00' {$sel["Express City 00"]}>Itella Express City 00</option>";
  $ulos .= "<option value='Express Morning 9' {$sel["Express Morning 9"]}>Itella Express Morning 9</option>";
  $ulos .= "<option value='Express Business Day 14' {$sel["Express Business Day 14"]}>Itella Express Business Day 14</option>";
  $ulos .= "<option value='Express Point 00/16' {$sel["Express Point 00/16"]}>Itella Express Point 00/16</option>";
  $ulos .= "<option value='Express Flex 21' {$sel["Express Flex 21"]}>Itella Express Flex 21</option>";
  $ulos .= "<option value='Economy 16' {$sel["Economy 16"]}>Itella Economy 16</option>";
  $ulos .= "<option value='Customer Return' {$sel["Customer Return"]}>Itella Customer Return</option>";
  $ulos .= "<option value='Undelivered Shipment' {$sel["Undelivered Shipment"]}>Itella Undelivered Shipment</option>";
  $ulos .= "<option value='Lis�arvokuljetus' {$sel["Lis�arvokuljetus"]}>Itella Lis�arvokuljetus</option>";
  $ulos .= "<option value='Priority Ulkomaa' {$sel["Priority Ulkomaa"]}>Itella Priority Ulkomaan l�hetys</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Itella'>";
  $ulos .= "<option value='ITELLAMAILEC' {$sel["ITELLAMAILEC"]}>Itella Economy Letter</option>";
  $ulos .= "<option value='IT16' {$sel["IT16"]}>Itella Economy Parcel</option>";
  $ulos .= "<option value='IT14' {$sel["IT14"]}>Itella Express Business Day</option>";
  $ulos .= "<option value='ITKY14' {$sel["ITKY14"]}>Itella Express Business Day kuljetusyksikk�</option>";
  $ulos .= "<option value='ITKY14I' {$sel["ITKY14I"]}>Itella Express Business Day pallet (Ulkomaa)</option>";
  $ulos .= "<option value='IT14I' {$sel["IT14I"]}>Itella Express Business Day parcel (Ulkomaa)</option>";
  $ulos .= "<option value='ITEXPC' {$sel["ITEXPC"]}>Itella Express City</option>";
  $ulos .= "<option value='ITKYEXPC' {$sel["ITKYEXPC"]}>Itella Express City kuljetusyksikk�</option>";
  $ulos .= "<option value='IT21' {$sel["IT21"]}>Itella Express Flex</option>";
  $ulos .= "<option value='ITKY21' {$sel["ITKY21"]}>Itella Express Flex kuljetusyksikk�</option>";
  $ulos .= "<option value='IT09' {$sel["IT09"]}>Itella Express Morning</option>";
  $ulos .= "<option value='ITKY09' {$sel["ITKY09"]}>Itella Express Morning kuljetusyksikk�</option>";
  $ulos .= "<option value='TPSTD' {$sel["TPSTD"]}>Itella Logistics Oy, Kappaletavara</option>";
  $ulos .= "<option value='ITELLALOGKR' {$sel["ITELLALOGKR"]}>Itella Logistics Oy, Kotimaan Rahti</option>";
  $ulos .= "<option value='ITELLAMAILPR' {$sel["ITELLAMAILPR"]}>Itella Priority Letter</option>";
  $ulos .= "<option value='ITPR' {$sel["ITPR"]}>Itella Priority Parcel</option>";
  $ulos .= "<option value='ITSP' {$sel["ITSP"]}>Itella SmartPOST</option>";
  $ulos .= "<option value='ITVAK' {$sel["ITVAK"]}>Itella VAK/ADR</option>";
  $ulos .= "<option value='ITKYVAK' {$sel["ITKYVAK"]}>Itella VAK/ADR kuljetusyksikk�</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Bring'>";
  $ulos .= "<option value='PNL359' {$sel["PNL359"]}>Bring CarryOn Budget</option>";
  $ulos .= "<option value='PNL330' {$sel["PNL330"]}>Bring CarryOn Business</option>";
  $ulos .= "<option value='PNL335' {$sel["PNL335"]}>Bring CarryOn Business 09.00</option>";
  $ulos .= "<option value='PNL333' {$sel["PNL333"]}>Bring CarryOn Business BulkReturn</option>";
  $ulos .= "<option value='PNL332' {$sel["PNL332"]}>Bring CarryOn Business BulkSplit</option>";
  $ulos .= "<option value='PNL334' {$sel["PNL334"]}>Bring CarryOn Business BulkSplit 09.00</option>";
  $ulos .= "<option value='PNL336' {$sel["PNL336"]}>Bring CarryOn Business Pallet</option>";
  $ulos .= "<option value='PNL339' {$sel["PNL339"]}>Bring CarryOn Business Pallet 09.00</option>";
  $ulos .= "<option value='PNL331' {$sel["PNL331"]}>Bring CarryOn Business Return</option>";
  $ulos .= "<option value='PNL340' {$sel["PNL340"]}>Bring CarryOn HomeShopping</option>";
  $ulos .= "<option value='PNL343' {$sel["PNL343"]}>Bring CarryOn HomeShopping BulkReturn</option>";
  $ulos .= "<option value='PNL342' {$sel["PNL342"]}>Bring CarryOn HomeShopping BulkSplit</option>";
  $ulos .= "<option value='PNL349' {$sel["PNL349"]}>Bring CarryOn HomeShopping BulkSplit Home</option>";
  $ulos .= "<option value='PNL345' {$sel["PNL345"]}>Bring CarryOn HomeShopping BulkSplit Mini</option>";
  $ulos .= "<option value='PNL341' {$sel["PNL341"]}>Bring CarryOn HomeShopping Return</option>";
  $ulos .= "<option value='PNLWAY' {$sel["PNLWAY"]}>Bring CarryOn Waybill</option>";
  $ulos .= "<option value='BOXBD' {$sel["BOXBD"]}>Bring Express Business Distribution</option>";
  $ulos .= "<option value='BOXBDP' {$sel["BOXBDP"]}>Bring Express Business Distribution Pallet</option>";
  $ulos .= "<option value='BOXCA' {$sel["BOXCA"]}>Bring Express Courier Ad-Hoc</option>";
  $ulos .= "<option value='BOXCD' {$sel["BOXCD"]}>Bring Express Courier Distribution</option>";
  $ulos .= "<option value='BOXHD' {$sel["BOXHD"]}>Bring Express Home Delivery</option>";
  $ulos .= "<option value='BOXHDR' {$sel["BOXHDR"]}>Bring Express Home Delivery Return</option>";
  $ulos .= "<option value='BOXQP' {$sel["BOXQP"]}>Bring Express QuickPack</option>";
  $ulos .= "<option value='BOXSHD' {$sel["BOXSHD"]}>Bring Express Store Home Delivery</option>";
  $ulos .= "<option value='BOXSHDR' {$sel["BOXSHDR"]}>Bring Express Store Home Delivery Return </option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Dachser'>";
  $ulos .= "<option value='DACTFIX' {$sel["DACTFIX"]}>Dachser Targofix</option>";
  $ulos .= "<option value='DACTFIX10' {$sel["DACTFIX10"]}>Dachser Targofix 10:00</option>";
  $ulos .= "<option value='DACTFIX12' {$sel["DACTFIX12"]}>Dachser Targofix 12:00</option>";
  $ulos .= "<option value='DACTFLEX' {$sel["DACTFLEX"]}>Dachser Targoflex</option>";
  $ulos .= "<option value='DACTSPEED' {$sel["DACTSPEED"]}>Dachser Targospeed</option>";
  $ulos .= "<option value='DACTSPEED10' {$sel["DACTSPEED10"]}>Dachser Targospeed 10:00</option>";
  $ulos .= "<option value='DACTSPEED12' {$sel["DACTSPEED12"]}>Dachser Targospeed 12:00</option>";
  $ulos .= "<option value='DACTSPEEDPLUS' {$sel["DACTSPEEDPLUS"]}>Dachser Targospeed Plus</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / DANX'>";
  $ulos .= "<option value='DANXSTD' {$sel["DANXSTD"]}>DANX</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / DB Schenker'>";
  $ulos .= "<option value='SBTLFIEXP' {$sel["SBTLFIEXP"]}>DB SCHENKER Express (Finland)</option>";
  $ulos .= "<option value='SBTLFISY' {$sel["SBTLFISY"]}>DB SCHENKER Finland System</option>";
  $ulos .= "<option value='BBU' {$sel["BBU"]}>DB SCHENKERbudget</option>";
  $ulos .= "<option value='BCSI' {$sel["BCSI"]}>DB SCHENKERcoldsped - Europa</option>";
  $ulos .= "<option value='BCS' {$sel["BCS"]}>DB SCHENKERcoldsped - Sverige</option>";
  $ulos .= "<option value='BDI' {$sel["BDI"]}>DB SCHENKERdirect</option>";
  $ulos .= "<option value='BPA' {$sel["BPA"]}>DB SCHENKERparcel</option>";
  $ulos .= "<option value='BPHDP' {$sel["BPHDP"]}>DB SCHENKERprivpak - Hem Dag (utan avisering och kvittens)</option>";
  $ulos .= "<option value='BPHDAP' {$sel["BPHDAP"]}>DB SCHENKERprivpak - Hem Dag med avisering (och kvittens) (Paket)</option>";
  $ulos .= "<option value='BPHKAP' {$sel["BPHKAP"]}>DB SCHENKERprivpak - Hem Kv�ll med avisering (och kvittens)</option>";
  $ulos .= "<option value='BHP' {$sel["BHP"]}>DB SCHENKERprivpak - Ombud Standard (1 kolli, &lt;20 kg)</option>";
  $ulos .= "<option value='BPOSG' {$sel["BPOSG"]}>DB SCHENKERprivpak - Terminal</option>";
  $ulos .= "<option value='BPTJP' {$sel["BPTJP"]}>DB SCHENKERprivpak - Till Jobbet</option>";
  $ulos .= "<option value='BCF' {$sel["BCF"]}>DB SCHENKERsystem</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / DHL'>";
  $ulos .= "<option value='ASU' {$sel["ASU"]}>DHL Euroconnect</option>";
  $ulos .= "<option value='ASUP' {$sel["ASUP"]}>DHL Euroconnect Plus</option>";
  $ulos .= "<option value='DASECD' {$sel["DASECD"]}>DHL Express 09:00 (Tullinalainen)</option>";
  $ulos .= "<option value='DASE' {$sel["DASE"]}>DHL Express 09:00 (Tullivapaa)</option>";
  $ulos .= "<option value='DATDM' {$sel["DATDM"]}>DHL Express 10:30 (Tullinalainen)</option>";
  $ulos .= "<option value='DATDL' {$sel["DATDL"]}>DHL Express 10:30 (Tullivapaa)</option>";
  $ulos .= "<option value='DAMECD' {$sel["DAMECD"]}>DHL Express 12:00 (Tullinalainen)</option>";
  $ulos .= "<option value='DAME' {$sel["DAME"]}>DHL Express 12:00 (Tullivapaa)</option>";
  $ulos .= "<option value='DAXPD' {$sel["DAXPD"]}>DHL Express Envelope (Tullivapaa)</option>";
  $ulos .= "<option value='DADOM' {$sel["DADOM"]}>DHL Express Worldwide (Kotimaa)</option>";
  $ulos .= "<option value='DAWPX' {$sel["DAWPX"]}>DHL Express Worldwide (Tullinalainen)</option>";
  $ulos .= "<option value='DAECX' {$sel["DAECX"]}>DHL Express Worldwide (Tullivapaa EU: ssa)</option>";
  $ulos .= "<option value='DADOX' {$sel["DADOX"]}>DHL Express Worldwide (Tullivapaa, Ei-EU)</option>";
  $ulos .= "<option value='DHLFREIGHTESTDOM' {$sel["DHLFREIGHTESTDOM"]}>DHL Freight Domestic EE</option>";
  $ulos .= "<option value='DHLFREIGHTESTEC' {$sel["DHLFREIGHTESTEC"]}>DHL Freight Euroconnect EE</option>";
  $ulos .= "<option value='DHLFREIGHTFIEC' {$sel["DHLFREIGHTFIEC"]}>DHL Freight Euroconnect FI</option>";
  $ulos .= "<option value='DHLFREIGHTFIKT' {$sel["DHLFREIGHTFIKT"]}>DHL Freight Kotimaa</option>";
  $ulos .= "<option value='DGFAIR' {$sel["DGFAIR"]}>DHL Global Forwarding Air Freight</option>";
  $ulos .= "<option value='DGFAIRPLUS' {$sel["DGFAIRPLUS"]}>DHL Global Forwarding Air Freight PLUS</option>";
  $ulos .= "<option value='AEX' {$sel["AEX"]}>DHL Paket</option>";
  $ulos .= "<option value='ASP2' {$sel["ASP2"]}>DHL Pall</option>";
  $ulos .= "<option value='ASWP2' {$sel["ASWP2"]}>DHL Parti</option>";
  $ulos .= "<option value='ASPO' {$sel["ASPO"]}>DHL Service Point</option>";
  $ulos .= "<option value='ASPOC' {$sel["ASPOC"]}>DHL Service Point C.O.D.</option>";
  $ulos .= "<option value='ASPOR' {$sel["ASPOR"]}>DHL Service Point Retur</option>";
  $ulos .= "<option value='ASWS2' {$sel["ASWS2"]}>DHL Stycke</option>";
  $ulos .= "<option value='ASWP' {$sel["ASWP"]}>DHL Swednet Partigods</option>";
  $ulos .= "<option value='ASWS' {$sel["ASWS"]}>DHL Swednet Styckegods</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / DSV'>";
  $ulos .= "<option value='DSVFIGRP' {$sel["DSVFIGRP"]}>DSV Road Kappaletavara</option>";
  $ulos .= "<option value='DSVFIFULL' {$sel["DSVFIFULL"]}>DSV Road Osakuorma</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Fennoway'>";
  $ulos .= "<option value='FENNORAHTI' {$sel["FENNORAHTI"]}>Fennoway Fennorahti</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / GLS'>";
  $ulos .= "<option value='GLSFIINT' {$sel["GLSFIINT"]}>GLS Suomi INTERNATIONAL</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Kaukokiito'>";
  $ulos .= "<option value='KKSTD' {$sel["KKSTD"]}>Kaukokiito</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Kiitolinja'>";
  $ulos .= "<option value='KLGRP' {$sel["KLGRP"]}>KIITOLINJA kappaletavara</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / KN Road'>";
  $ulos .= "<option value='KUEHNENAGELROAD' {$sel["KUEHNENAGELROAD"]}>KN Road</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Tyvi'>";
  $ulos .= "<option value='KTYVI' {$sel["KTYVI"]}>Kuljetusliike Tyvi Oy</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Matkahuolto'>";
  $ulos .= "<option value='MH68' {$sel["MH68"]}>Matkahuolto Ahvenanmaan Jakopaketti</option>";
  $ulos .= "<option value='MH63' {$sel["MH63"]}>Matkahuolto Baltian Paketti</option>";
  $ulos .= "<option value='MH10' {$sel["MH10"]}>Matkahuolto Bussipaketti</option>";
  $ulos .= "<option value='MH43' {$sel["MH43"]}>Matkahuolto Dokumenttikuori</option>";
  $ulos .= "<option value='MH3050' {$sel["MH3050"]}>Matkahuolto Jakopaketti/Paikallispaketti</option>";
  $ulos .= "<option value='MH57' {$sel["MH57"]}>Matkahuolto Lavarahti</option>";
  $ulos .= "<option value='MH81' {$sel["MH81"]}>Matkahuolto L�hell�-paketin palautus</option>";
  $ulos .= "<option value='MH80' {$sel["MH80"]}>Matkahuolto L�hell�-paketti</option>";
  $ulos .= "<option value='MH75' {$sel["MH75"]}>Matkahuolto Mannermaan Jakopaketti</option>";
  $ulos .= "<option value='MH74' {$sel["MH74"]}>Matkahuolto Mannermaan Paketti</option>";
  $ulos .= "<option value='MH20' {$sel["MH20"]}>Matkahuolto Pikapaketti</option>";
  $ulos .= "<option value='MH82' {$sel["MH82"]}>Matkahuolto Postaalipaketti</option>";
  $ulos .= "<option value='MH83' {$sel["MH83"]}>Matkahuolto Postaalipaketti palautus</option>";
  $ulos .= "<option value='MH40' {$sel["MH40"]}>Matkahuolto Rahtipussi</option>";
  $ulos .= "<option value='MH42' {$sel["MH42"]}>Matkahuolto Rahtipussi jakopaketti</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Neutraali'>";
  $ulos .= "<option value='FREEG' {$sel["FREEG"]}>Neutraali Kappaletavarapalvelu (osoitekortti + rahtikirja)</option>";
  $ulos .= "<option value='FREEG_793' {$sel["FREEG_793"]}>Neutraali Kappaletavarapalvelu (osoitekortti + rahtikirja): Transpori Oy</option>";
  $ulos .= "<option value='FREEG_794' {$sel["FREEG_794"]}>Neutraali Kappaletavarapalvelu (osoitekortti + rahtikirja): AJ Laine Oy</option>";
  $ulos .= "<option value='FREEB' {$sel["FREEB"]}>Neutraali Kirjepalvelu</option>";
  $ulos .= "<option value='FREEP' {$sel["FREEP"]}>Neutraali pakettipalvelu (osoitekortti)</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Posten Brev'>";
  $ulos .= "<option value='PAF' {$sel["PAF"]}>Posten Brev - Brevpostf�rskott</option>";
  $ulos .= "<option value='BEXPD' {$sel["BEXPD"]}>Posten Brev - Express (kotimaa)</option>";
  $ulos .= "<option value='BREV' {$sel["BREV"]}>Posten Brev - Normaali</option>";
  $ulos .= "<option value='BEXPI' {$sel["BEXPI"]}>Posten Brev - Priority+</option>";
  $ulos .= "<option value='BVAL' {$sel["BVAL"]}>Posten Brev - V�rde</option>";
  $ulos .= "<option value='BREKD' {$sel["BREKD"]}>Posten Brev  Kirjattu kirje (BREKD)</option>";
  $ulos .= "<option value='BREKI' {$sel["BREKI"]}>Posten Brev  Kirjattu kirje (BREKI)</option>";
  $ulos .= "<option value='EMSD2' {$sel["EMSD2"]}>Posten EMS (brev/dokument)</option>";
  $ulos .= "<option value='EMSP2' {$sel["EMSP2"]}>Posten EMS (paket/varor)</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / PostNord'>";
  $ulos .= "<option value='DPDFI' {$sel["DPDFI"]}>PostNord DPD Classic (Suomi)</option>";
  $ulos .= "<option value='P15' {$sel["P15"]}>PostNord Logistics DPD F�retagspaket</option>";
  $ulos .= "<option value='P14' {$sel["P14"]}>PostNord Logistics DPD F�retagspaket 12.00</option>";
  $ulos .= "<option value='DPD' {$sel["DPD"]}>PostNord Logistics DPD Utrikes</option>";
  $ulos .= "<option value='P42' {$sel["P42"]}>PostNord Logistics Express - Express 07.00</option>";
  $ulos .= "<option value='P32' {$sel["P32"]}>PostNord Logistics Hempaket</option>";
  $ulos .= "<option value='DTPGHD' {$sel["DTPGHD"]}>PostNord Logistics Hjemlevering (Norge)</option>";
  $ulos .= "<option value='H48' {$sel["H48"]}>PostNord Logistics InNight</option>";
  $ulos .= "<option value='P31' {$sel["P31"]}>PostNord Logistics Kundretur</option>";
  $ulos .= "<option value='P19' {$sel["P19"]}>PostNord Logistics MyPack</option>";
  $ulos .= "<option value='P19FI' {$sel["P19FI"]}>PostNord Logistics MyPack (Suomi)</option>";
  $ulos .= "<option value='P19NO' {$sel["P19NO"]}>PostNord Logistics MyPack (Norja)</option>";
  $ulos .= "<option value='P24' {$sel["P24"]}>PostNord Logistics MyPack return</option>";
  $ulos .= "<option value='P24FI' {$sel["P24FI"]}>PostNord Logistics MyPack return (Suomi)</option>";
  $ulos .= "<option value='P24NO' {$sel["P24NO"]}>PostNord Logistics MyPack Return (Norja)</option>";
  $ulos .= "<option value='P52' {$sel["P52"]}>PostNord Logistics PALL.ETT</option>";
  $ulos .= "<option value='DTPGPF' {$sel["DTPGPF"]}>PostNord Logistics Partifrakt (Norja)</option>";
  $ulos .= "<option value='P91' {$sel["P91"]}>PostNord Logistics Postpaket Utrikes</option>";
  $ulos .= "<option value='DTPGSG' {$sel["DTPGSG"]}>PostNord Logistics Stykkgods (Norja)</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / Privpak'>";
  $ulos .= "<option value='PPFITRRET' {$sel["PPFITRRET"]}>Privpak Finland (normaali & palautus)</option>";
  $ulos .= "<option value='PPFITR' {$sel["PPFITR"]}>Privpak Finland (normaali)</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / R & P'>";
  $ulos .= "<option value='RPPP' {$sel["RPPP"]}>R & P Kuljetus Pakettipalvelu</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / TK Logistik'>";
  $ulos .= "<option value='TKLOGGODS' {$sel["TKLOGGODS"]}>TK Logistik Gods</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / TNT'>";
  $ulos .= "<option value='TNT08DOMD' {$sel["TNT08DOMD"]}>TNT 08:00 Express (Domestic Docs)</option>";
  $ulos .= "<option value='TNT08DOMN' {$sel["TNT08DOMN"]}>TNT 08:00 Express (Domestic Non Docs)</option>";
  $ulos .= "<option value='TNT09D' {$sel["TNT09D"]}>TNT 09:00 Express (Docs)</option>";
  $ulos .= "<option value='TNT09DOMD' {$sel["TNT09DOMD"]}>TNT 09:00 Express (Domestic Docs)</option>";
  $ulos .= "<option value='TNT09DOMN' {$sel["TNT09DOMN"]}>TNT 09:00 Express (Domestic Non Docs)</option>";
  $ulos .= "<option value='TNT09' {$sel["TNT09"]}>TNT 09:00 Express (Domestic)</option>";
  $ulos .= "<option value='TNT09N' {$sel["TNT09N"]}>TNT 09:00 Express (Non Docs)</option>";
  $ulos .= "<option value='TNT10D' {$sel["TNT10D"]}>TNT 10:00 Express (Docs)</option>";
  $ulos .= "<option value='TNT10DOMD' {$sel["TNT10DOMD"]}>TNT 10:00 Express (Domestic Docs)</option>";
  $ulos .= "<option value='TNT10DOMN' {$sel["TNT10DOMN"]}>TNT 10:00 Express (Domestic Non Docs)</option>";
  $ulos .= "<option value='TNT10' {$sel["TNT10"]}>TNT 10:00 Express (Domestic)</option>";
  $ulos .= "<option value='TNT10N' {$sel["TNT10N"]}>TNT 10:00 Express (Non Docs)</option>";
  $ulos .= "<option value='TNT412' {$sel["TNT412"]}>TNT 12:00 Economy Express (Non Docs)</option>";
  $ulos .= "<option value='TNT12D' {$sel["TNT12D"]}>TNT 12:00 Express (Docs)</option>";
  $ulos .= "<option value='TNT12DOMD' {$sel["TNT12DOMD"]}>TNT 12:00 Express (Domestic Docs)</option>";
  $ulos .= "<option value='TNT12DOMN' {$sel["TNT12DOMN"]}>TNT 12:00 Express (Domestic Non Docs)</option>";
  $ulos .= "<option value='TNT12' {$sel["TNT12"]}>TNT 12:00 Express (Domestic)</option>";
  $ulos .= "<option value='TNT12N' {$sel["TNT12N"]}>TNT 12:00 Express (Non Docs)</option>";
  $ulos .= "<option value='TNT48N' {$sel["TNT48N"]}>TNT Economy Express (Non Docs)</option>";
  $ulos .= "<option value='TNT15D' {$sel["TNT15D"]}>TNT Express (Docs)</option>";
  $ulos .= "<option value='TNT15DOMD' {$sel["TNT15DOMD"]}>TNT Express (Domestic Docs)</option>";
  $ulos .= "<option value='TNT15DOMN' {$sel["TNT15DOMN"]}>TNT Express (Domestic Non Docs)</option>";
  $ulos .= "<option value='TNT15' {$sel["TNT15"]}>TNT Express (Domestic)</option>";
  $ulos .= "<option value='TNT15N' {$sel["TNT15N"]}>TNT Express (Non Docs)</option>";
  $ulos .= "<option value='TNT728' {$sel["TNT728"]}>TNT Special Economy Express</option>";
  $ulos .= "</optgroup>";

  $ulos .= "<optgroup label='Unifaun / UPK'>";
  $ulos .= "<option value='UPKE' {$sel["UPKE"]}>Uudenmaan Pikakuljetus Oy Erikoisaikataulu</option>";
  $ulos .= "<option value='UPKK' {$sel["UPKK"]}>Uudenmaan Pikakuljetus Oy Kotijakelu</option>";
  $ulos .= "<option value='UPK24' {$sel["UPK24"]}>Uudenmaan Pikakuljetus Oy Normal 24h</option>";
  $ulos .= "<option value='UPK24A' {$sel["UPK24A"]}>Uudenmaan Pikakuljetus Oy Normal 24h AVI</option>";
  $ulos .= "</optgroup>";

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "rahdinkuljettaja") {

  $ulos = "<td><select name='{$nimi}'>";

  $query = "SELECT *
            FROM rahdinkuljettajat
            WHERE yhtio = '{$kukarow['yhtio']}'
            ORDER BY nimi";
  $rahdinkuljettajat_res = pupe_query($query);

  $ulos .= "<option value=''>".t("Ei valintaa")."</option>";

  while ($rahdinkuljettajat_row = mysql_fetch_assoc($rahdinkuljettajat_res)) {
    $sel = (isset($trow[$i]) and $trow[$i] == $rahdinkuljettajat_row['koodi']) ? " selected" : "";

    $ulos .= "<option value='{$rahdinkuljettajat_row['koodi']}' {$sel}>{$rahdinkuljettajat_row['nimi']}</option>";
  }


  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "logy_rahtikirjanumerot") {

  $sel1='';
  $sel2='';

  if ($trow[$i]=='K')
    $sel2 = 'SELECTED';
  else
    $sel1 = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value='' $sel1>".t("Ei k�ytet� LOGY:n rahtikirjanumeroita")."</option>";
  $ulos .= "<option value='K' $sel2>".t("K�ytet��n LOGY:n rahtikirjanumeroita")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "merahti") {
  $sel1='';
  $sel2='';

  if ($trow[$i]=='K')
    $sel1 = 'SELECTED';
  else
    $sel2 = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value='K' $sel1>".t("K�ytet��n l�hett�j�n rahtisopimusta")."</option>";
  $ulos .= "<option value=''  $sel2>".t("K�ytet��n vastaanottajan rahtisopimusta")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "tulostustapa") {
  $sel      = array();
  $sel[$trow[$i]]  = " selected";

  $ulos = "<td>
      <select name='$nimi'>
      <option value='E' $sel[E]>".t("Er�tulostus")."</option>
      <option value='H' $sel[H]>".t("Hetitulostus")."</option>
      <option value='K' $sel[K]>".t("Koonti-hetitulostus")."</option>
      <option value='L' $sel[L]>".t("Koonti-er�tulostus")."</option>
      <option value='X' $sel[X]>".t("Rahtikirjansy�tt� ja -tulostus ohitetaan")."</option>
      </select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "extranet") {
  $sel      = array();
  $sel[$trow[$i]]  = " selected";

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Toimitustapa n�ytet��n vain myynniss�")."</option>";
  $ulos .= "<option value='K' $sel[K]>".t("Toimitustapa n�ytet��n vain extranetiss�")."</option>";
  $ulos .= "<option value='M' $sel[M]>".t("Toimitustapa n�ytet��n molemmissa")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "rahtikirja") {

  $vresult = t_avainsana("RAHTIKIRJA");

  $ulos = "<td><select name='$nimi'>";

  while ($row = mysql_fetch_array($vresult)) {
    $sel = "";
    if ($row["selite"] == $trow[$i]) $sel = 'selected';
    $ulos .= "<option value='$row[selite]' $sel>$row[selitetark]</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "osoitelappu") {
  $sel1 = '';
  $sel2 = '';
  $sel3 = '';
  $sel4 = '';

  if ($trow[$i] == 'intrade') {
    $sel2 = 'selected';
  }
  elseif ($trow[$i] == 'tiivistetty') {
    $sel3 = 'selected';
  }
  elseif ($trow[$i] == 'oslap_mg') {
    $sel4 = 'selected';
  }
  else {
    $sel1 = 'selected';
  }

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''       $sel1>".t("Normaali")."</option>";
  $ulos .= "<option value='intrade' $sel2>".t("Intrade")."</option>";
  $ulos .= "<option value='tiivistetty' $sel3>".t("Tiivistetty")."</option>";
  if ($yhtiorow['kerayserat'] == 'K') $ulos .= "<option value='oslap_mg' $sel4>".t("Yksinkertainen, tulostusmedia valitaan kirjoittimen takaa")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "sisamaan_kuljetusmuoto" or mysql_field_name($result, $i) == "kuljetusmuoto") {

  $ulos = "<td><select name='$nimi'>";
  $ulos .= "<option value = '' >".t("Valitse")."</option>";

  $vresult = t_avainsana("KM");

  while ($vrow=mysql_fetch_array($vresult)) {
    $sel="";
    if ($trow[$i] == $vrow['selite']) {
      $sel = "selected";
    }
    $ulos .= "<option value = '$vrow[selite]' $sel>$vrow[selitetark]</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}


if (mysql_field_name($result, $i) == "kauppatapahtuman_luonne") {

  $ulos = "<td><select name='$nimi'>";
  $ulos .= "<option value = '' >".t("Valitse")."</option>";

  $vresult = t_avainsana("KT");

  while ($vrow=mysql_fetch_array($vresult)) {
    $sel="";
    if ($trow[$i] == $vrow['selite']) {
      $sel = "selected";
    }
    $ulos .= "<option value = '$vrow[selite]' $sel>$vrow[selitetark]</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "poistumistoimipaikka_koodi") {

  $ulos = "<td><select name='$nimi'>";
  $ulos .= "<option value = ''>".t("Valitse")."</option>";

  $vresult = t_avainsana("TULLI");

  while ($vrow=mysql_fetch_array($vresult)) {
    $sel="";
    if ($trow[$i] == $vrow['selite']) {
      $sel = "selected";
    }
    $ulos .= "<option value = '$vrow[selite]' $sel>$vrow[selite] - $vrow[selitetark]</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "lajittelupiste") {

  $ulos = "<td><select name='{$nimi}'>";
  $ulos .= "<option value = ''>".t("Valitse")."</option>";

  $vresult = t_avainsana("TOIMTAPALP");

  while ($vrow = mysql_fetch_assoc($vresult)) {
    $sel = $trow[$i] == $vrow['selite'] ? " selected" : "";
    $ulos .= "<option value = '{$vrow['selite']}' {$sel}>{$vrow['selitetark']}</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "kontti") {

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value = ''>".t("Valitse")."</option>";

  $chk1 = '';
  $chk2 = '';

  if ($trow[$i] == "1") {
    $chk1 = 'selected';
  }
  if ($trow[$i] == "0") {
    $chk2 = 'selected';
  }

  $ulos .= "<option value='1' $chk1>".t("Kyll�")."</option>";
  $ulos .= "<option value='0' $chk2>".t("Ei")."</option>";

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "jvkielto") {

  $sel = $sela = '';
  if ($trow[$i]!='') $sel = 'SELECTED';
  else $sela = 'SELECTED';

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value='' $sela>".t("Toimitustavalla saa toimittaa j�lkivaatimuksia")."</option>";
  $ulos .= "<option value='o' $sel>".t("Toimitustavalla ei saa toimittaa j�lkivaatimuksia")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "vak_kielto") {

  $sel      = array();
  $sel[$trow[$i]]  = " selected";

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value=''>".t("Toimitustavalla saa toimittaa VAK-tuotteita")."</option>";
  $ulos .= "<option value='K' $sel[K]>".t("Toimitustavalla ei saa toimittaa VAK-tuotteita")."</option>";

  $query = "SELECT DISTINCT selite
            FROM toimitustapa
            WHERE yhtio    = '{$kukarow['yhtio']}'
            AND vak_kielto = ''
            AND nouto      = ''";
  $alt_toimitustapa_res = pupe_query($query);

  while ($alt_toimitustapa_row = mysql_fetch_assoc($alt_toimitustapa_res)) {
    $ulos .= "<option value='$alt_toimitustapa_row[selite]' ".$sel[$alt_toimitustapa_row['selite']].">".t("VAK-tuotteet toimitetaan toimitustavalla")." $alt_toimitustapa_row[selite]</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "vaihtoehtoinen_vak_toimitustapa") {

  $sel = array();
  $sel[$trow[$i]] = "selected";

  $ulos = "<td>
             <select name='{$nimi}'>
               <option value>" . t("VAK-tuotteita ei siirret� omalle tilaukselleen") . "</option>";

  $query = "SELECT DISTINCT selite
            FROM toimitustapa
            WHERE yhtio    = '{$kukarow['yhtio']}'
            AND vak_kielto = ''
            AND nouto      = ''";
  $toimitustapa_result = pupe_query($query);

  while ($row = mysql_fetch_assoc($toimitustapa_result)) {
    $ulos .= "<option value='{$row["selite"]}' {$sel[$row['selite']]}>" .
      t("VAK-tuotteet siirret��n omalle tilaukselleen toimitustavalla") .
      " {$row["selite"]}</option>";
  }

  $ulos .= "</select></td>";
  $jatko = 0;
}


if (mysql_field_name($result, $i) == "erikoispakkaus_kielto") {

  $sel = $sela = '';
  if ($trow[$i] != '') {
    $sel = 'selected';
  }
  else {
    $sela = 'selected';
  }

  $ulos  = "<td><select name='$nimi'>";
  $ulos .= "<option value='' $sela>".t("Toimitustavalla saa toimittaa erikoispakkauksia")."</option>";
  $ulos .= "<option value='K' $sel>".t("Toimitustavalla ei saa toimittaa erikoispakkauksia")."</option>";
  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "ei_pakkaamoa") {

  $ulos  = "<td><select name='$nimi'>";
  $chk1 = '';
  $chk2 = '';

  if ($trow[$i] == "1") {
    $chk1 = 'selected';
  }
  if ($trow[$i] == "0") {
    $chk2 = 'selected';
  }

  $ulos .= "<option value='0' $chk2>".t("Toimitustavan tilaukset varaavat pakkaamolokeron")."</option>";
  $ulos .= "<option value='1' $chk1>".t("Toimitustavan tilaukaset eiv�t varaa pakkaamolokeroa")."</option>";

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "erittely") {

  $ulos  = "<td><select name='$nimi'>";
  $chk1 = '';
  $chk2 = '';
  $chk3 = '';

  if ($trow[$i] == "k") {
    $chk1 = 'selected';
  }
  if ($trow[$i] == "") {
    $chk2 = 'selected';
  }
  if ($trow[$i] == "t") {
    $chk3 = 'selected';
  }

  $ulos .= "<option value='' $chk2>".t("Toimitustavalle ei tulosteta rahtikirjaerittely�")."</option>";
  $ulos .= "<option value='t' $chk3>".t("Toimitustavalle tulostetaan rahtikirjaerittely")."</option>";
  $ulos .= "<option value='k' $chk1>".t("Toimitustavalle tulostetaan rahtikirjaerittely per asiakas")."</option>";

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "uudet_pakkaustiedot") {

  $ulos  = "<td><select name='$nimi'>";

  $sel      = array();
  $sel[$trow[$i]]  = " selected";

  $ulos .= "<option value=''>".t("Koonti-er�tulostuksessa ei voi sy�tt�� uusia pakkaustietoja ennen tulostusta")."</option>";
  $ulos .= "<option value='K' $sel[K]>".t("Koonti-er�tulostuksessa voi sy�tt�� uudet pakkaustiedot ennen tulostusta")."</option>";

  $ulos .= "</select></td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "sallitut_alustat") {
  $ulos = "<td>";

  $sel = explode(",", $trow[$i]);

  $query = "SELECT *
            FROM pakkaus
            WHERE yhtio = '{$kukarow['yhtio']}'";
  $pakkaus_result = pupe_query($query);

  $ulos .= "<input type='hidden' name='{$nimi}[]' value='default' />";

  while ($pakkaus_row = mysql_fetch_assoc($pakkaus_result)) {

    $chk = in_array($pakkaus_row['tunnus'], $sel) ? 'checked' : '';

    $ulos .= "<input type='checkbox' name='{$nimi}[]' value='{$pakkaus_row['tunnus']}' {$chk}/> ".t_tunnus_avainsanat($pakkaus_row, "pakkaus", "PAKKAUSKV")." ".t_tunnus_avainsanat($pakkaus_row, "pakkauskuvaus", "PAKKAUSKV")."<br />";
  }

  $ulos .= "</td>";
  $jatko = 0;
}

if (mysql_field_name($result, $i) == "jvkulu" or
  mysql_field_name($result, $i) == "kuluprosentti" or
  mysql_field_name($result, $i) == "ulkomaanlisa" or
  mysql_field_name($result, $i) == "kuljetusvakuutus") {

  if ($trow[$i] == 0) {
    $trow[$i] = "";
  }
}

if (mysql_field_name($result, $i) == "kuljetusvakuutus_tyyppi") {

  $ulos = "<td><select name='$nimi' ".js_alasvetoMaxWidth($nimi, 400).">";

  $sel = array();
  $apu = $trow[$i];
  $sel[$apu] = "selected";

  $ulos .= "<option value = ''>".t("Yhti�n oletus")."</option>";
  $ulos .= "<option value = 'E' $sel[E]>".t("Ei kuljetusvakuutusta")."</option>";
  $ulos .= "<option value = 'A' $sel[A]>".t("Valuuttam��r�inen kuljetusvakuutus lis�t��n")."</option>";
  $ulos .= "<option value = 'B' $sel[B]>".t("Prosentuaalinen kuljetusvakuutus lis�t��n")."</option>";
  $ulos .= "<option value = 'F' $sel[F]>".t("Valuuttam��r�inen kuljetusvakuutus lis�t��n. K�ytet��n kuljetusvakuutustuotteen asiakashintaa ja alennusta")."</option>";
  $ulos .= "<option value = 'G' $sel[G]>".t("Prosentuaalinen kuljetusvakuutus lis�t��n. K�ytet��n kuljetusvakuutustuotteen asiakasalennusta")."</option>";
  $ulos .= "</select></td>";

  $jatko = 0;
}
