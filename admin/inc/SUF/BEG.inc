<?php
//Uebersicht ueber die ToDo

$wastun = $_POST['wastun'];
$begriff = $_POST['begriff'];
$ersetzung = $_POST['ersetzung'];
$begr_id = $_POST['begr_id'];

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// Begriff loeschen ************************************************************************
if($wastun == 'loeschen'){


		$SQL = "DELETE FROM "._sufubegriffe." WHERE id='".$begr_id."'";
		# SQL ausführen
		mysql_query($SQL);
		#Anzahl betroffener Datensätze ausgeben:
		$meldung = "Gelöscht";
}

// Begr hinzufuegen ******************************************************************************
elseif($wastun == 'hinzf') {
	//Datenbankeintrag generieren
	$SQL = "INSERT INTO "._sufubegriffe." (string, ersetzung) VALUES ('".$begriff."', '".$ersetzung."')";
	
	//DB fuellen
	if(!mysql_query($SQL)) {$meldung = "Fehler beim Eintrag in die Datenbank<br>"; mysql_error();}
	else {$meldung = "Eintrag erfolgreich<br>"; }
	

}

$SQL = "SELECT * FROM "._sufubegriffe;
$query = mysql_query($SQL);
?>
<h3>Suchfunktion Begriffe</h3><br><br>
<span class="textRot"><b> <?php echo $meldung; ?> </b></span><br>
<fieldset><legend>Bergiffe</legend><br>

<div style="float: none; clear: left;">
	<div style="float:left; width:150px"> <u><b>Begriff</b></u> </div>
	<div style="float:left; width:150px"> <u><b>Ersetzung</b></u> </div>
	<div style="float:left"> <u><b>Löschen</b></u> </div>
</div>

<?php  while($wert = mysql_fetch_object($query)) { ?>
<div style="float: none; clear: left;">
	<div style="float:left; width:150px"> <?php echo $wert->string; ?> </div>
	<div style="float:left; width:150px"> <?php echo $wert->ersetzung; ?> </div>
	<div style="float:left"> <form method="post" action="">
								<input type="hidden" name="wastun" value="loeschen">
								<input type="hidden" name="begr_id" value="<?php echo $wert->id; ?>">
								<input type="submit" name="submit" value="X">
							 </form>
	</div>
</div>
<?php } ?>
</fieldset><br><br><br>
<fieldset><legend>Neuen Begriff schreiben</legend>
<form method="post" action="">
	<input type="text" name="begriff" value="">
	<input type="text" name="ersetzung" value="">
	<input type="hidden" name="wastun" value="hinzf">
	<input type="submit" name="submit" value="Hinzufügen">

</form>

</fieldset>

