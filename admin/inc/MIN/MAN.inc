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

if($_POST["erzeugt"]){$erzeugt = $_POST["erzeugt"];}

if($_POST["geaendert"]){$geaendert = $_POST["geaendert"];}

if($_POST["modus"]){$modus = $_POST["modus"];}

if($_POST["inc"]){$inc = $_POST["inc"];}



// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// Testen ob Arbeitsschritt gesetzt

if($step==""){$step = 0;}

?>



<!-- Content Eintrag anlegen -->



<table border="0" cellpadding="0" cellspacing="0">



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



<tr><td align="left"><h3>Eintrag anlegen</h3></td></tr>



<tr><td>



<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top"><a href="index.php?modus=MIN&inc=MUE">Zur&uuml;ck zur &Uuml;bersicht</a></td></tr>



</table>

</fieldset>

<!-- /AKTIONEN ################################################################### -->

<br>

<!-- ALLGEMEIN ################################################################### -->

<fieldset>

<legend>Allgemein</legend>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="middle"><b>Titel:<br></b></td><td align="left" valign="top"><input type="text" name="titel" size="50" maxlength="255"></td></tr>



<tr><td align="left" valign="middle"><b>Datum:<br></b></td><td align="left" valign="top">

<select name="tag" size="1"><option value="--">--</option><option>01</option><option>02</option><option>03</option><option>04</option><option>05</option><option>06</option><option>07</option><option>08</option><option>09</option><option>10</option><option>11</option><option>12</option><option>13</option><option>14</option><option>15</option><option>16</option><option>17</option><option>18</option><option>19</option><option>20</option><option>21</option><option>22</option><option>23</option><option>24</option><option>25</option><option>26</option><option>27</option><option>28</option><option>29</option><option>30</option><option>31</option></select>.

<select name="monat" size="1"><option value="--">--</option><option>01</option><option>02</option><option>03</option><option>04</option><option>05</option><option>06</option><option>07</option><option>08</option><option>09</option><option>10</option><option>11</option><option>12</option></select>.

<select name="jahr" size="1"><option value="----">----</option>

<?php

// Jahr dynamisch erzeugen

$heute = getdate();

for($c=$heute['year']; $c<($heute['year']+4); $c++)

	{

	echo "<option>".$c."</option>";

	}

?>

</select>

</td></tr>



<tr><td align="left" valign="middle"><b>Ort:<br></b></td><td align="left" valign="top"><input type="text" name="ort" size="25" maxlength="255"></td></tr>



<tr><td align="left" valign="top" width="75"><b>Beschreibung:<br></b></td><td align="left" valign="top"><textarea name="beschreibung" cols="50" rows="25" class="mceEditor"></textarea></td></tr>



</table>

</fieldset>

<!-- /ALLGEMEIN ################################################################### -->

<br>

<!-- STATUS ################################################################### -->

<fieldset>

<legend>Status</legend>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Online:<br></b></td><td align="left" valign="top"><input type="radio" name="online" id="onlineJa" value="1" checked><label for="onlineJa">Ja</label>&nbsp;<input type="radio" name="online" id="onlineNein" value="0"><label for="onlineNein">Nein</label></td></tr>



</table>

</fieldset>

<!-- /STATUS ################################################################### -->

<br>

<!-- AKTIONEN ################################################################### -->

<fieldset>

<table border="0" cellpadding="3" cellspacing="3" width="450">



<tr><td align="left" valign="top" width="75"><b>Aktionen:<br></b></td><td align="left" valign="top"><a href="index.php?modus=MIN&inc=MUE">Zur&uuml;ck zur &Uuml;bersicht</a></td></tr>



</table>



</fieldset>

<!-- /AKTIONEN ################################################################### -->



</td></tr>



<tr><td align="center"><input type="submit" value="Eintrag anlegen"></td></tr>



</table>



<!-- /Innere Tabelle Eingabe -->



<?php

// Datum erzeugen

$erzeugt = datetimemaker(time());

$geaendert = $erzeugt;

?>



<input type="hidden" name="erzeugt" value="<?php echo $erzeugt; ?>">

<input type="hidden" name="geaendert" value="<?php echo $geaendert; ?>">

<input type="hidden" name="modus" value="<?php echo $modus; ?>">

<input type="hidden" name="inc" value="<?php echo $inc; ?>">

<input type="hidden" name="step" value="1">



</form>



<?php

	}

//######################################################################################

// /Step 0: Eingabe



// Step 1: Pruefen und speichern

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

	if($fehler!="")

		{

		echo $fehlerStr;

		}

	// Speichern

	//######################################################################################

	else

		{

		// SQL-String bauen

		$sqlString = "INSERT INTO "._MiniKal." (Titel,Datum,Ort,Beschreibung,Online,Erzeugt,Geaendert) VALUES ('".addslashes($titel)."','".$jahr."-".$monat."-".$tag." 00:00:00','".addslashes($ort)."','".$beschreibung."','".$online."','".$erzeugt."','".$geaendert."')";

	

		// Neue Veranstaltung in DB speichern

		$ergebnis = $db -> sql($sqlString);

		

		// Fehlerbehandlung

		if($ergebnis){echo "<h3 align=\"left\">Neuer Eintrag angelegt</h3>\nDer Eintrag wurden erfolgreich in der Datenbank gespeichert.<br>\n<br>\n<a href=\"index.php?modus=MIN&inc=MUE\">zur &Uuml;bersicht...</a> oder <a href=\"index.php?modus=MIN&inc=MUE&id=".mysql_insert_id()."\">...zum angelegten Eintrag</a><br>\n";}

		else{echo "<h3 align=\"left\">Fehler!</h3>\nDer Eintrag konnten nicht in der Datenbank gespeichert werden.<br>\nBitte versuchen Sie es erneut!<br>\n<br>\n<a href=\"javascript:history.back()\">zur&uuml;ck...</a><br>\n";}

		}

	}

//######################################################################################

// /Step 1: Pruefen und speichern

?>



<br><br>



</td>

</tr>



</table>



<!-- Content Dokument anlegen -->