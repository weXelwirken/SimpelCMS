<?php
session_start();

include("../admin/config/settings.php");

//Format Zum Debug heder entfernen
header('Content-Type: image/jpeg');

////grafiken uebergeben
$grafiken = $_SESSION['cpt_namen'];

//CPT Img Pfad
$cptpfad = $ServerRoot."/img/cpt/";

//Anzahl der Symbole
$Sym_Pro_Reihe = 5;
$Anz_Reihen = 2;

//Groesse des Captcha
$cpt_gr_X = 250;
$cpt_gr_Y = 100;

// Werte ausgabe Ÿber pos grafik $cpt_anz_sym
$cpt_anz_sym = array();

//Winkel der drehung
$rotate_R = -20;
$rotate_L = 20;


//Rechnen
$Anz_symbole = $Sym_Pro_Reihe * $Anz_Reihen;
$Sym_Gr_X = $cpt_gr_X / $Sym_Pro_Reihe;
$Sym_Gr_Y = $cpt_gr_Y / $Anz_Reihen;
$graf_anz_zuf = count($grafiken)-1;


//Laden der Grafiken, drehen, grš§e anpassen und schreiben in ein Array
$i = 0;
$bilder = array();
while($i < $Anz_symbole) {

	//Neues leeres Bild im Array Erzeugen 50x50
	$bilder[$i] = imagecreatetruecolor($Sym_Gr_X, $Sym_Gr_Y);
	
	//Zufallsentscheidenung und dann Grafik als src
	$zuf_bild = rand(0, count($grafiken)-1);
	$src = imagecreatefrompng($cptpfad.$grafiken[$zuf_bild].".png");
	$cpt_anz_sym[$zuf_bild]++;
	
	//Drehen des Bildes
	//$degrees = rand($rotate_R, $rotate_L);
	//$srccolor = imagecolorallocate($src, 255, 255, 255);
	//$src = imagerotate($src, $degrees, $srccolor);

	//€ndern der Groesse und schreiben in Array
	imagecopyresized($bilder[$i], $src, 0, 0, 0, 0, $Sym_Gr_X, $Sym_Gr_Y, ImageSX($src), ImageSY($src));
	//Temp aus Speicher lšschen
	imagedestroy($src);
$i++;
}
	//Leeres Captcha erstllen und weiss machen
	$cptpic = imagecreatetruecolor($cpt_gr_X, $cpt_gr_Y);
	$back_color_pointer = imagecolorallocate($cptpic, 255, 255, 255);	
	
	//Einzelne Cpt in pic schrieben
	$posY = 0;
	$zaehlerSpal = 0;
	$posX = 0;
	foreach($bilder as $bild){
			//Zaehler Definieren 
			if($zaehlerSpal == $Sym_Pro_Reihe) {
				$posY = $posY + $Sym_Gr_Y;
				$zaehlerSpal = 0;
				$posX = 0;
			}
		//Kopieren
		imagecopy($cptpic, $bild, $posX, $posY, 0, 0, $Sym_Gr_X, $Sym_Gr_Y);
		//Zaehlen u. Rechnen
		$zaehlerSpal++;
		$posX = $zaehlerSpal * $Sym_Gr_X;
	}
// Array mit den Werten zur ueberpruefung in Session
$_SESSION['cpt_werte'] = $cpt_anz_sym;

// Bild ausgeben*/
imagejpeg($cptpic);
?>