<?php

// POST und GET extrahieren

$step = $_POST["step"];

$titel = $_POST["titel"];

$tag = $_POST["tag"];

$monat = $_POST["monat"];

$jahr = $_POST["jahr"];

$ort = $_POST["ort"];

$beschreibung = $_POST["beschreibung"];

$online = $_POST["online"];

if($_POST["id"]){$id = $_POST["id"];}

if($_POST["geaendert"]){$geaendert = $_POST["geaendert"];}

if($_POST["modus"]){$modus = $_POST["modus"];}

if($_POST["inc"]){$inc = $_POST["inc"];}





// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// Testen ob Arbeitsschritt gesetzt

if($step==""){$step = 0;}



// Daten fuer Eintrag aus DB holen

// SQL-String bauen

$sqlString = "SELECT * FROM "._MiniKal." WHERE ID='".$id."'";



// Ergebnis auslesen

$ergebnis = $db -> sql($sqlString);

if($ergebnis){$zeile = mysql_fetch_array($ergebnis); mysql_free_result($ergebnis);}

else{echo "Fehler: Es konnte kein Ergebnis fuer den Eintrag ausgelesen werden!<br>\n";}

	

?>



<!-- Content Eintrag aendern -->



<table border="0" cellpadding="0" cellspacing="0" width="480">



<tr>

<td align="left" valign="top">



<?php

// Step 0: Eingabe

//######################################################################################

if($step==0)

	{

?>



<form name="formular" action="<?php echo $PHP_SELF; ?>" enctype="multipart/form-data" method="post">



<!-- Innere Tabelle Eingabe -->



<table border="0" cellpadding="3" cellspacing="3" width="500">



<tr><td align="left"><h3>Eintrag &auml;ndern</h3></td></tr>



<tr><td>



<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">

<a href="index.php?modus=MIN&inc=MUE&id=<?php echo $id; ?>">Dokumentenansicht</a>&nbsp;

<a href="index.php?modus=MIN&inc=MUE">&Uuml;bersicht</a>

</td></tr>



</table>

</fieldset>

<!-- /AKTIONEN ################################################################### -->

<br>

<!-- ALLGEMEIN ################################################################### -->

<fieldset>

<legend>Allgemein</legend>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="middle"><b>Titel:<br></b></td><td align="left" valign="top"><input type="text" name="titel" size="50" maxlength="255" value="<?php echo stripslashes($zeile["Titel"]); ?>"></td></tr>



<tr><td align="left" valign="middle" width="75"><b>Datum:<br></b></td><td align="left" valign="top">

<select name="tag" size="1"><option value="0">--</option>

<?php

// DateTimeArray erzeugen

$dateTime = dateTimeAusgabe($zeile["Datum"]);



// Tag dynamisch erzeugen

for($c=1; $c<32; $c++)

	{

	if(strlen($c)<"2"){$str="0".$c;}else{$str=$c;}

	echo "<option";

	if($str==$dateTime["Tag"])

		{

		echo " selected";

		}

	echo ">".$str."</option>";

	}

?>

</select>.

<select name="monat" size="1"><option value="0">--</option>

<?php

// Monat dynamisch erzeugen

for($c=1; $c<13; $c++)

	{

	if(strlen($c)<"2"){$str="0".$c;}else{$str=$c;}

	echo "<option";

	if($str==$dateTime["Monat"])

		{

		echo " selected";

		}

	echo ">".$str."</option>";

	}

?>

</select>.

<select name="jahr" size="1"><option value="0">----</option>

<?php

// Jahr dynamisch erzeugen

$heute = getdate();

if($dateTime["Jahr"]<$heute['year']){$start=$dateTime["Jahr"];}

else{$start=$heute['year'];}

for($c=$start; $c<($heute['year']+4); $c++)

	{

	echo "<option";

	if($c==$dateTime["Jahr"])

		{

		echo " selected";

		}

	echo ">".$c."</option>";

	}

?>

</select>

</td></tr>



<tr><td align="left" valign="middle"><b>Ort:<br></b></td><td align="left" valign="top"><input type="text" name="ort" size="25" maxlength="255" value="<?php echo stripslashes($zeile["Ort"]); ?>"></td></tr>



<tr><td align="left" valign="top" width="75"><b>Beschreibung:<br></b></td><td align="left" valign="top"><textarea name="beschreibung" cols="50" rows="25" class="mceEditor"><?php echo $zeile["Beschreibung"]; ?></textarea></td></tr>



</table>

</fieldset>

<!-- /ALLGEMEIN ################################################################### -->

<br>

<!-- STATUS ################################################################### -->

<fieldset>

<legend>Status</legend>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top"><input type="radio" name="online" id="onlineJa" value="1"<?php if($zeile["Online"]==1){echo " checked";}?>><label for="onlineJa">Ja</label>&nbsp;<input type="radio" name="online" id="onlineNein" value="0"<?php if($zeile["Online"]==0){echo " checked";}?>><label for="onlineNein">Nein</label></td></tr>



</table>

</fieldset>

<!-- /STATUS ################################################################### -->

<br>

<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top">

<a href="index.php?modus=MIN&inc=MUE&id=<?php echo $id; ?>">Dokumentenansicht</a>&nbsp;

<a href="index.php?modus=MIN&inc=MUE">&Uuml;bersicht</a>

</td></tr>



</table>

</fieldset>

<!-- /AKTIONEN ################################################################### -->



</td></tr>



<tr><td align="center"><input type="submit" value="Eintrag &auml;ndern"></td></tr>



</table>



<!-- /Innere Tabelle Eingabe -->



<?php

// Anderungs-Datum erzeugen

$geaendert = datetimemaker(time());

?>



<input type="hidden" name="id" value="<?php echo $zeile["ID"]; ?>">

<input type="hidden" name="geaendert" value="<?php echo $geaendert; ?>">

<input type="hidden" name="modus" value="<?php echo $modus; ?>">

<input type="hidden" name="inc" value="<?php echo $inc; ?>">

<input type="hidden" name="step" value="1">



</form>



<?php

	}

//######################################################################################

// /Step 0: Eingabe



// Step 1: Prufen und speichern

//######################################################################################

if($step==1)

	{

	// Fehlerbehandlung

	//######################################################################################

	

	$fehlerStr = "<h3 align=\"left\">Fehler!</h3>\nEs ist folgender Fehler aufgetreten:<br>\n<ul>";

		

	// Feldtest

	if(!$titel){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Titel wurde nicht angegeben.\n";}

	if(!$tag OR !$monat OR !$jahr){$fehler=1; $fehlerStr = $fehlerStr."<li>Es wurde kein korrektes Datum angegeben.\n";}

	if(!$ort){$fehler=1; $fehlerStr = $fehlerStr."<li>Der Ort wurde nicht angegeben.\n";}

	if(!$beschreibung){$fehler=1; $fehlerStr = $fehlerStr."<li>Die Beschreibung wurde nicht angegeben.\n";}

	

	$fehlerStr = $fehlerStr."</ul>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";

	

	// Fehlerausgabe

	if($fehler)

		{

		echo $fehlerStr;

		}

	// Speichern

	//######################################################################################

	else

		{

		if($id!="1"){$on=",Online='".$online."'";}	

		// SQL-String bauen

		$sqlString = "UPDATE "._MiniKal." SET Titel='".addslashes($titel)."',Datum='".$jahr."-".$monat."-".$tag." 00:00:00',Ort='".addslashes($ort)."',Beschreibung='".$beschreibung."',Online='".$online."',Geaendert='".$geaendert."' WHERE ID='".$id."'";

	

		// Neue Veranstaltung in DB speichern

		$ergebnis = $db -> sql($sqlString);

		

		// Fehlerbehandlung

		if($ergebnis){echo "<h3 align=\"left\">Eintrag ge&auml;ndert</h3>\nDer Eintrag wurde erfolgreich ge&auml;ndert und in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=MIN&inc=MUE\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=MIN&inc=MUE&id=".$id."\">...zum ge&auml;nderten Eintrag</a><br>\n";}

		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Eintrag konnte nicht ge&auml;ndert und in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}

		}

	}

//######################################################################################

// /Step 1: Pruefen und speichern

?>



<br><br>



</td>

</tr>



</table>



<!-- Content Eintrag aendern -->