<?php 
$wastun =  $_POST['wastun']; 
$nlid = $_GET['nlid'];
$submit = $_POST['submit'];
$titel = $_POST['titel'];
$inhalt = $_POST['inhalt'];
if(isset($_POST['nlid'])) {$nlid = $_POST['nlid'];}
$aktion = "";

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

$datum = date("d.m.Y");


// Fehlertext vorbereiten ***************************************************************************
if($submit =="Ansehen" || $submit =="Speichern"){
	if($titel == "") {$aktion .="Keinen Titel eingegeben<br>";}
	if($inhalt == "") {$aktion .="Keinen Inhalt eingegeben<br>";}
}


// NL speichern / ändern ****************************************************************************
if($submit == "Speichern" && $aktion == "") {

	if(isset($nlid) && $nlid != 0) {
	
		$SQL = "UPDATE "._newslnewsl." SET inhalt='".$inhalt."', titel ='".$titel."' WHERE id='".$nlid."'";
		
		# SQL ausführen
		
		
		#Anzahl betroffener Datensätze ausgeben:
		if(!mysql_query($SQL)) {$aktion .= "Fehler beim &auml;ndern<br>";}
		else { $aktion .= "&Auml;nderungen gespeichert<br>"; }
	}
	else {
		
		//Datenbankeintrag generieren
		$SQL = "INSERT INTO "._newslnewsl." (titel, inhalt, status) VALUES ('".$titel."', '".$inhalt."', '1')";
		
		//DB fuellen
		if(!mysql_query($SQL)) {$aktion .= "Fehler beim Eintrag in die Datenbank<br>";}
		else {$aktion .= "Newsletter gespeichert<br>"; $nlid = mysql_insert_id(); }
	
	}
	$submit = "";
}
 
// NL ansehen ******************************************************************************************************
if($nlid != "" && $submit !="Ansehen") {
	$query = mysql_query('SELECT titel, inhalt, DATE_FORMAT(datum, GET_FORMAT(DATE,"EUR")) as datumform, status FROM '._newslnewsl.' WHERE id ='.$nlid) or die(mysql_error());
	$wert = mysql_fetch_object($query);
	
	$datum = $wert->datumform;
	$inhalt = $wert->inhalt;
	$titel = $wert->titel;
	if($wert->status == "2") {
		$aktion .= "Dieser Newsletter wurde bereits verschickt<br>";
	}
}


if($submit =="" || $submit == "Ansehen") {
?>

<h3>Newsletter bearbeiten </h3><br>
<fieldset>
<form action="index.php?modus=NEW&inc=NSE" method="post" name="schicken"><input type="hidden" name="nlid" value="<?php echo $nlid; ?>"><a style="float:left;" href="index.php?modus=NEW&inc=NLU"><span class="textGruen"><b>&Uuml;bersicht</b></span></a><?php if ($nlid != ""){ ?><a style="float:right;" href="#" onclick="document['schicken'].submit()"><span class="textRot"><b>Verschicken</b></span></a><?php } ?></form>
</fieldset><br>
<span class="textRot"><?php echo $aktion; ?></span><br>
<fieldset><legend>Vorschau</legend>
	<fieldset><legend>Header</legend>
	<u>Datum:</u>&nbsp; <?php echo $datum; ?><br>
	<u>Betreff:</u> <?php echo $titel; ?><br>
	<u>Von:</u>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; <?php echo htmlspecialchars($newsletter_absender); ?>
	</fieldset>
	<fieldset style="background-color:white;"><legend>Nachricht</legend>
	<?php echo nl2br($inhalt); ?>
	</fieldset>

</fieldset><br>
<fieldset><legend>Bearbeiten</legend>

<form method="post" name="hallo">

<div style="clear: left;">Titel: <input type="text" name="titel" maxlength="250" size="25" value="<?php echo $titel; ?>"></div><br>

<div style="clear: left;">Inhalt</div>

<div style="clear: left;"><textarea cols="55" rows="15" name="inhalt"><?php echo $inhalt; ?></textarea></div>
<input type="hidden" name="nlid" value="<?php echo $nlid; ?>">
<input type="submit" name="submit" value="Ansehen"> <input type="submit" name="submit" value="Speichern">
</form>


</fieldset><br>

<fieldset>
<form action="index.php?modus=NEW&inc=NSE" method="post" name="schicken2"><input type="hidden" name="nlid" value="<?php echo $nlid; ?>"><a style="float:left;" href="index.php?modus=NEW&inc=NLU"><span class="textGruen"><b>&Uuml;bersicht</b></span></a><?php if ($nlid != ""){ ?><a style="float:right;" href="#" onclick="document['schicken2'].submit()"><span class="textRot"><b>Verschicken</b></span></a><?php } ?></form>
</fieldset>

<?php } ?>

