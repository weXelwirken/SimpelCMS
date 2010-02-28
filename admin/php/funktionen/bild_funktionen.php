<?php
/*******************************************

Bild-Funktionen
"""""""""""""""
Die Datei beinhaltet Skripte, die besondere
Funkionaltitaeten fuer die Bildbehandlung erzeugen.

Copyleft by weXelwirken 2009
********************************************/

// echo "<!-- Bild-Funktionen einbinden -->\n";

//===============================================================================
// AusschnittThumb
// """""""""""""""
// Beschreibung: Schneidet aus einem gegeben Bild einen Ausschnitt heraus und speichert es als neues Bild ab.
// Verwendung:	./inc/zimmerFrei.php

function AusschnittThumb($quelle, $ziel, $weite, $hoehe)
    {
    $w = $weite;
    $h = $hoehe;
    $image = $quelle;
    $sizes = getimagesize($image);
    $img = imagecreatefromjpeg($image);
    $original_w = $sizes[0];
    $original_h = $sizes[1];
    $left = $original_w-$w;
    $top = $original_h-$h;
    $left = ceil($left/2);
    $top = ceil($top/3);
    $old_img = $img;
    $img = imagecreatetruecolor($w,$h);
    imagecopy($img,$old_img,0,0,$left,$top,$w,$h);
    imagejpeg($img,$ziel,100);
    }


//===============================================================================
// thumb
// """""
// Beschreibung: Erzeugt aus einem gegeben Bild eine verkleinertes Thumbnail.
// Verwendung:

function thumb($file, $save, $width, $height, $prop = TRUE) {
    // Requires GD-Lib > 2.0
    // Ist $prop=TRUE, so werden die Proportionen des Bildes
    // auch im Thumbnail eingehalten

    @unlink($save);
    $infos = @getimagesize($file);
    if($prop) {
        // Proportionen erhalten
        $iWidth = $infos[0];
        $iHeight = $infos[1];
        $iRatioW = $width / $iWidth;
        $iRatioH = $height / $iHeight;
        if ($iRatioW < $iRatioH)
        {
        $iNewW = $iWidth * $iRatioW;
        $iNewH = $iHeight * $iRatioW;
        } else {
        $iNewW = $iWidth * $iRatioH;
        $iNewH = $iHeight * $iRatioH;
        } // end if
    } else {
        // Strecken und Stauchen auf Größe
        $iNewW = $width;
        $iNewH = $height;
    }

    if($infos[2] == 2) {
        // Bild ist vom Typ jpg
        $imgA = imagecreatefromjpeg($file);
        $imgB = imagecreatetruecolor($iNewW,$iNewH);
        imagecopyresampled($imgB, $imgA, 0, 0, 0, 0, $iNewW,
                           $iNewH, $infos[0], $infos[1]);
        imagejpeg($imgB, $save);
    } elseif($infos[2] == 3) {
        // Bild ist vom Typ png
        $imgA = imagecreatefrompng($file);
        $imgB = imagecreatetruecolor($iNewW, $iNewH);
        imagecopyresampled($imgB, $imgA, 0, 0, 0, 0, $iNewW,
                           $iNewH, $infos[0], $infos[1]);
        imagepng($imgB, $save);
    } else {
        return FALSE;
    }
}

?>