<?php
$wastun = $_POST['wastun'];
$senden = $_POST['senden'];
$nlid = $_POST['nlid'];
//Uebersicht ueber die newsletter

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);


// NL lšschen ***************************************************************************************
if($wastun == "loeschen"){
	if($senden == 1) {
	
		$SQL = "DELETE FROM "._newslnewsl." WHERE id='".$nlid."'";
		# SQL ausführen
		mysql_query($SQL);
		#Anzahl betroffener Datensätze loeschen
		if (mysql_affected_rows() != 1) { $aktion = "Fehler beim l&ouml;schen";}
		else { $aktion = "<br>Newsletter gel&ouml;scht"; }  
		$wastun = "";
	
	}
	else {
		
		$query = mysql_query('SELECT titel FROM '._newslnewsl.' WHERE id = "'.$nlid.'"') or die(mysql_error());
		$wert = mysql_fetch_object($query);
		
		echo "<h3>Newsletter l&ouml;schen</h3><br><fieldset><br><br>Soll der Newsletter '".$wert->titel."' gel&ouml;scht werden";
		
		echo "<br><br><form method=\"post\">
	
					
					<input type=\"hidden\" name=\"senden\" value=\"1\">
					<input type=\"hidden\" name=\"wastun\" value=\"loeschen\">
					<input type=\"hidden\" name=\"nlid\" value=\"".$nlid."\">
					<input type=\"submit\" value=\"l&ouml;schen\">
					
					</form></fieldset>
					";
		}
}
//**********************************Newsletter uebersicht
if ($wastun == ""){
$query = mysql_query("SELECT id, titel, DATE_FORMAT(datum, GET_FORMAT(DATE,'EUR')) as 'datumform', status FROM "._newslnewsl." ORDER BY status ASC, datum DESC") or die(mysql_error());

?>
<h3>Newsletter</h3><br>
<fieldset>
<form method="post" name="hinzfu" action="index.php?modus=NEW&inc=NLB"><input type="hidden" name="wastun" value="hinzuf">Aktionen: <a href="#" onclick="document['hinzfu'].submit()"><span class="textGruen">Newsletter schreiben</span></a></form>
</fieldset><br>
<span class="textRot"><?php echo $aktion; ?></span><br>
<fieldset><legend>Newsletter</legend>
<table border="0">
	<tr>
		<td width="65px" style="border: 1px solid #7799AA;">
			Datum
		</td>
		<td width="260px" style="border: 1px solid #7799AA;">
			Titel
		</td>
		<td style="border: 1px solid #7799AA;">
			Status
		</td>
		<td width="15px" style="border: 1px solid #7799AA;">&nbsp;L&nbsp;</td>
	</tr>
	
	<?php
	for($i = 0; $i < mysql_num_rows($query); $i++)
	{
		$wert = mysql_fetch_object($query);
		$statusfield = '<td style="border: 2px solid #009900;" onclick="window.location.href=\'index.php?modus=NEW&inc=NLB&nlid='.$wert->id.'\';"><center>verschickt</center></td>';
					  
		if($wert->status == "1") {
		$statusfield = '<td style="border: 2px solid #FF9933;" onclick="window.location.href=\'index.php?modus=NEW&inc=NLB&nlid='.$wert->id.'\';"><center>in Bearbeitung</center></td>';}

	?>
	<tr onMouseOver="this.style.backgroundColor='#FFFFFF'; this.style.cursor='hand';"  onMouseOut="this.style.backgroundColor='transparent'">
		<td onclick="window.location.href='index.php?modus=NEW&inc=NLB&nlid=<?php echo $wert->id; ?>';">
			<?php echo $wert->datumform; ?>
		</td>
		<td onclick="window.location.href='index.php?modus=NEW&inc=NLB&nlid=<?php echo $wert->id; ?>';">
			<?php echo $wert->titel; ?>
		</td>
		<?php echo $statusfield; ?>
		<td><?php echo '<form method="post" name="loeschenX'.$wert->id.'"><input type="hidden" name="wastun" value="loeschen"><input type="hidden" name="nlid" value="'.$wert->id.'"><a href="#" onclick="document[\'loeschenX'.$wert->id.'\'].submit()"><span class="textRot"><b>&nbsp;X&nbsp;</b></span></a></form>'; ?></td>
	</tr>
	<?php } ?>
</table>
</fieldset>
<br>
<fieldset>
<form action="index.php?modus=NEW&inc=NLB" method="post" name="hinzfu2">
<input type="hidden" name="wastun" value="hinzuf">
Aktionen: <a href="#" onclick="document['hinzfu2'].submit()"><span class="textGruen">Newsletter schreiben</span></a>
</form>
</fieldset>
<?php } ?>