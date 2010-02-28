<?php
/*
Settings-Datei vom SimpelCMS
""""""""""""""""""""""""""""
Version: SimpelCMS v08/15.0015 (Stand 28.02.2010)
*/

//*************************************************************
// Grundlegendes

// Einstellungen
$SiteUrl =              "http://localhost:8888";    // URL der Website
$RelativePath =         "/scms";                    // Pfad relativ zum DocumentRoot bzw. HttpRoot
$MainCss =              "scms.css";                 // Dateiname der Haupt-CSS-Datei
$ScmsTpl =              "scms.tpl";                 // Name des verwendeten Smarty-Templates

// Features
$ScmsAuth =             true;                       // Nutzer-Authentifizierung im Frontend
$ScmsLang =             true;                       // MultilingualitŠt
$ScmsVerweise =         true;                       // Verweise


//*************************************************************
// Variablen aufladen

$ServerRoot =           $_SERVER['DOCUMENT_ROOT'].$ServerRootPath;      // Server Wurzel
$HttpRoot =             $SiteUrl.$ServerRootPath;                       // HTTP Wurzel
$ImgPfad =              $HttpRoot."/img";                               // IMG-Pfad
$ImgPfadAdmin =         $HttpRoot."/admin/img";                         // IMG-Admin-Pfad
$OneGif =               $ImgPfad."/one.gif";                            // OneGif-Pfad
$PdfPfad =              $HttpRoot . "/pdf";                             // PDF-Pfad
$PmaPfad =              "http://confixx.wexelwirken.de/phpMyAdmin/";    // PMA-Pfad
$CssPfad =              $HttpRoot."/".$MainCss;                         // CSS-Pfad
$CssPfadJs =            "../scms.css";                                  // CSS-Pfad TinyMCE
$CssPfadAdmin =         $HttpRoot . "/admin/admin.css";                 // CSS-Pfad Admin
$JsPfad =               $HttpRoot . "/scms.js";                         // JS-Pfad
$SlimboxSrc =           "/admin/jscripts/slimbox";                      // SlimboxSrc
$InterfaceLang =        "DE";                                           // Standard-Sprache


//*************************************************************
// Dateien einbinden

include($ServerRoot . "/admin/php/klassen/klassen.php");                // Klassen einbinden
include($ServerRoot . "/admin/php/funktionen/funktionen.php");          // Funktionen einbinden
require($ServerRoot . "/admin/php/smarty/MySmarty.class.php");          // Smarty einbinden
include($ServerRoot . "/admin/config/verbindungsdaten.php");            // Verbindungsdaten einbinden
include($ServerRoot . "/admin/config/userSettings.php");                // User-Settings einbinden
include($ServerRoot . "/admin/config/module.php");                      // Module einbinden
include($ServerRoot . "/admin/lang/".$InterfaceLang.".php");            // InterfaceLang einbinden



//*************************************************************
// Arrays aufladen

// SCMS Lang Array
$ScmsLangArray = array(
    "DE" => "Deutsch",
    "EN" => "English"
    );
    
// Rollen Array
$RollenArray = array(
    "0" => "USER",
    "1" => "EDITOR",
    "2" => "REDAKTEUR",
    "3" => "ADMIN"
    );

// ModusArrayADMIN
$modusArrayADMIN = array(
	"HOM" => array(
		"Farbe" => "Blaugrau",
		"Wert" => "#7799ab",
		"Titel" => "Home",
		"Kurz" => "HOM",
		"Rolle" => "1",
		"Inc" => array(
			"SDA" => array(
				"Name" => "Startseite des Adminbereichs",
				"Rolle" => "1"
				),
			"ROL" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			),
		),
	"EIN" => array(
		"Farbe" => "Blaugrau",
		"Wert" => "#7799aa",
		"Titel" => "Einstellungen",
		"Kurz" => "EIN",
		"Rolle" => "3",
		"Inc" => array(
			"EUE" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "3"
				),
			),
		),
	"DOK" => array(
		"Farbe" => "Blaugrau",
		"Wert" => "#7799aa",
		"Titel" => "Dokumente",
		"Kurz" => "DOK",
		"Rolle" => "1",
		"Inc" => array(
			"DUE" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "1"
				),
			"DAN" => array(
				"Name" => "Dokument anlegen",
				"Rolle" => "1"
				),
			"DAE" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"DLO" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			),
		),
	"ORD" => array(
		"Farbe" => "Blaugrau",
		"Wert" => "#7799aa",
		"Titel" => "Ordner",
		"Kurz" => "ORD",
		"Rolle" => "2",
		"Inc" => array(
			"OUE" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "2"
				),
			"OAN" => array(
				"Name" => "Ordner anlegen",
				"Rolle" => "2"
				),
			"OAE" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"OLO" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			),
		),
	"NUT" => array(
		"Farbe" => "Blaugrau",
		"Wert" => "#7799aa",
		"Titel" => "Nutzer",
		"Kurz" => "NUT",
		"Rolle" => "3",
		"Inc" => array(
			"NUE" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "3"
				),
			"NAN" => array(
				"Name" => "Nutzer anlegen",
				"Rolle" => "3"
				),
			"NAE" => array(
				"Name" => "",
				"Rolle" => "3"
				),
			"NLO" => array(
				"Name" => "",
				"Rolle" => "3"
				)
			)
		)
	);
	
// Admin- und Modul-Array zusammenfuegen
if($modusArrayMODULE){$modusArrayADMIN = array_merge($modusArrayADMIN, $modusArrayMODULE);}

?>