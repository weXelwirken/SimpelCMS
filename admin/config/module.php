<?php
// Settings der SimpelCMS Module
// """""""""""""""""""""""""""""

// MiniKal Settings ********************************************
// Version 0001 (Stand 24.03.2009)

// Datenkrake Settings ****************************************
// Version 0001 (Stand 29.08.2008)


// Newsletter Settings ****************************************
// Version 0001 (Stand 23.03.2010)
$newsletter_abbestellen_seite = $HttpRoot."/index.php?id=79&ord=54";
$newsletter_anzahl_UserProSeite = "20";
$newsletter_absender = $SiteTitle." <".$MailInfo.">";
$newsletter_newsletter_bgrTest = "unser neuer Newsletter ist da! \r\n\r\n";




//*************************************************************
// Arrays aufladen

// ModusArrayMODULE
$modusArrayMODULE = array(	

			
			
			
	"DAT" => array(
		"Farbe" => "Orange",
		"Wert" => "#FF9900",
		"Titel" => "Datenkrake",
		"Kurz" => "DAT",
		"Rolle" => "1",
		"Inc" => array(
			"UEB" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "1"
				),
			"KON" => array(
				"Name" => "Kontakte",
				"Rolle" => "1"
				),
			"MAI" => array(
				"Name" => "eMail",
				"Rolle" => "2"
				),
			"KLA" => array(
				"Name" => "Klassen",
				"Rolle" => "1"
				),
			"IMP" => array(
				"Name" => "Import & Export",
				"Rolle" => "2"
				),
			"DUB" => array(
				"Name" => "Dubletten-Suche",
				"Rolle" => "1"
				),
			"AEN" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"ANL" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"KAE" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"KAN" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"KLO" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"LOE" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			),
		),
		
	"MIN" => array(
			"Farbe" => "Orange",
			"Wert" => "#FF9900",
			"Titel" => "MiniKal",
			"Kurz" => "MIN",
			"Rolle" => "1",
			"Inc" => array(
				"MUE" => array(
					"Name" => "&Uuml;bersicht",
					"Rolle" => "1"
					),
				"MAN" => array(
					"Name" => "Neuen Eintrag anlegen",
					"Rolle" => "2"
					),
				"MAE" => array(
					"Name" => "",
					"Rolle" => "1"
					),
				"MLO" => array(
					"Name" => "",
					"Rolle" => "2"
					),
				),
			),
			
			
		
		"NEW" => array(
			"Farbe" => "Orange",
			"Wert" => "#FF9900",
			"Titel" => "Newsletter",
			"Kurz" => "NEW",
			"Rolle" => "1",
			"Inc" => array(
				"NLU" => array(
					"Name" => "Newsletter",
					"Rolle" => "1"
					),
				"EUE" => array(
					"Name" => "Empf&auml;nger",
					"Rolle" => "1"
					),
				"NSE" => array(
					"Name" => "",
					"Rolle" => "1"
					),
				"NLB" => array(
					"Name" => "",
					"Rolle" => "1"
					),			
				),
			),
		
	"SHO" => array(
		"Farbe" => "Orange",
		"Wert" => "#FF9900",
		"Titel" => "Shop",
		"Kurz" => "SHO",
		"Rolle" => "1",
		"Inc" => array(
			"UEB" => array(
				"Name" => "&Uuml;bersicht",
				"Rolle" => "1"
				),
			"AGU" => array(
				"Name" => "Alle Gruppen",
				"Rolle" => "1"
				),
			"AGN" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"AGA" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"AGL" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"AUE" => array(
				"Name" => "Alle Artikel",
				"Rolle" => "1"
				),
			"AAN" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"AAE" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"ALO" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			"BUE" => array(
				"Name" => "",
				"Rolle" => "1"
				),
			"BLO" => array(
				"Name" => "",
				"Rolle" => "2"
				),
			),
		),
		
	"SUF" => array(
		"Farbe" => "Orange",
		"Wert" => "#FF9900",
		"Titel" => "Suche",
		"Kurz" => "SUF",
		"Rolle" => "1",
		"Inc" => array(
			"BEG" => array(
				"Name" => "Begriffe",
				"Rolle" => "1"
				),
			"SET" => array(
				"Name" => "Settings",
				"Rolle" => "1"
				),		
			),
		),	

	);
?>