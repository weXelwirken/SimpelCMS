<?php

// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// DB-Verbindung Dokument

$dbDokument = new db($dbHost,$dbUser,$dbPasswort);

$dbDokument -> select_db($dbDatenbank);



// Uebersicht

//###############################################################################

if(!$id)

	{

	// SQL-String bauen

	$sqlString = "SELECT * FROM "._MiniKal." ORDER BY Datum DESC";

	// Ergebnis auslesen

	$ergebnis = $db -> sql($sqlString);

	if($ergebnis)

        {

        while($zeile = mysql_fetch_array($ergebnis))

            {

            // Datum vorbereiten

            $datArray = dateTimeAusgabe($zeile["Datum"]);

            // Off vorbereiten

            if(!$zeile["Online"]){$off=" class=\"textRot\"";}else{$off="";}

            $out.= "<b>&bull;</b> <i>".$datArray["Tag"].".".$datArray["Monat"].".".$datArray["Jahr"]."</i>: <b>&raquo;<a href=\"index.php?modus=MIN&amp;inc=MUE&amp;id=".$zeile["ID"]."\"><span".$off.">".stripslashes($zeile["Titel"])."</span></a>&laquo;</b> (".stripslashes($zeile["Ort"]).")<br>\n";

            }

        }

	else{echo "Fehler: Es konnte kein Ergebnis fuer die Uebersicht ausgelesen werden!<br>\n";}

	

	// Ueberschrift

	echo "<h3>&Uuml;bersicht aller Eintr&auml;ge</h3>

	   <p>

	   ".$out."

	   </p>\n";

	}

//###############################################################################

// /Ubersicht



// Details

//###############################################################################

else

	{	

	// Daten des Eintrags aus DB holen

	// SQL-String bauen

	$sqlString = "SELECT * FROM "._MiniKal." WHERE ID='".$id."' LIMIT 1";

	// Ergebnis auslesen

	$ergebnis = $db -> sql($sqlString);

	if($ergebnis){$zeile = mysql_fetch_array($ergebnis);}

	else{echo "Fehler: Es konnte kein Ergebnis ausgelesen werden!<br>\n";}

	?>



<!-- Content Eintrag Details -->



<table border="0" cellpadding="0" cellspacing="0" width="500">



<tr><td align="left" valign="top">



<!-- Innere Tabelle -->



<table border="0" cellpadding="3" cellspacing="3">



<tr><td><h3 align="left">

	<?php

	// Ueberschrift

	echo $zeile["Titel"];

	?>

</h3></td></tr>



<tr><td>



<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">

    <?php

	// Aktionen

	// Aendern

	echo "<a href=\"index.php?modus=MIN&inc=MAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";

	echo "&nbsp;&nbsp;&nbsp;";

	// Loeschen

	echo "<a href=\"index.php?modus=MIN&inc=MLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";

	?>

<a href="index.php?modus=MIN&inc=MUE">Zur&uuml;ck zur &Uuml;bersicht</a>

</td></tr>



</table>

</fieldset>

<!-- /AKTIONEN ################################################################### -->

<br>

<!-- ALLGEMEIN ################################################################### -->

<fieldset>

<legend><a href="javascript:Show_Stuff('All')" style="text-decoration:none;">[<span id="AllOff" style="display:none;">+</span><span id="AllOn">-</span>]</a> Eintrag</legend>

<div id="All">

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="middle"><b>Titel:<br></b></td><td align="left" valign="top">

    <?php

    // Titel

    echo stripslashes($zeile["Titel"]);

    ?>

</td></tr>



<tr><td align="left" valign="middle" width="75"><b>Datum:<br></b></td><td align="left" valign="top">

	<?php

	// Datum

    $datArray = dateTimeAusgabe($zeile["Datum"]);

    echo $datArray["Tag"].".".$datArray["Monat"].".".$datArray["Jahr"];

	?>

</td></tr>



<tr><td align="left" valign="middle"><b>Ort:<br></b></td><td align="left" valign="top">

    <?php

    // Ort

    echo stripslashes($zeile["Ort"]);

    ?>

</td></tr>



<tr><td align="left" valign="top" width="75"><b>Beschreibung:<br></b></td><td align="left" valign="top" class="anzeigeBox">

	<?php

	// Beschreibung

	echo $zeile["Beschreibung"];

	?>

</td></tr>



</table>

</div>

</fieldset>

<!-- /ALLGEMEIN ################################################################### -->

<br>

<!-- STATUS ################################################################### -->

<fieldset>

<legend><a href="javascript:Show_Stuff('Sta')" style="text-decoration:none;">[<span id="StaOff">+</span><span id="StaOn" style="display:none;">-</span>]</a> Status</legend>

<div id="Sta" style="display:none;">

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top">

	<?php

	// Online

	if($zeile["Online"]==1){echo "<span class=\"textGruen\"><b>Ja</b></span>";}else{echo "<span class=\"textRot\"><b>Nein</b></span>";}

	?>

</td></tr>



<tr><td align="left" valign="top"><b>Erzeugt:<br>Ge&auml;ndert:<br></b></td><td align="left" valign="top">

	<?php

	// Erzeugt

	echo $zeile["Erzeugt"]."<br>\n";

	// Geandert

	echo $zeile["Geaendert"];

	?>

</td></tr>



</table>

</div>

</fieldset>

<!-- /STATUS ################################################################### -->

<br>

<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">

    <?php

	// Aktionen

	// Andern

	echo "<a href=\"index.php?modus=MIN&inc=MAE&id=".$zeile["ID"]."\"><b><span class=\"textGruen\">&Auml;ndern</span></b></a>";

	echo "&nbsp;&nbsp;&nbsp;";

	// Loeschen

	echo "<a href=\"index.php?modus=MIN&inc=MLO&id=".$zeile["ID"]."\"><b><span class=\"textRot\">L&ouml;schen</span></b></a>&nbsp;&nbsp;&nbsp;";

	?>

<a href="index.php?modus=DOK&inc=DUE">Zur&uuml;ck zur &Uuml;bersicht</a>

</td></tr>



</table>

</fieldset>

<!-- /AKTIONEN ################################################################### -->



</td></tr>



</table>



<!-- /Innere Tabelle -->



</td></tr>



</table>



<!-- Content Dokument Details -->



	<?php

	}

//###############################################################################

// /Details

?>