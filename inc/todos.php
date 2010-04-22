<?php
//Uebersicht ueber die ToDo

$submit = $_POST['wastun'];
$inhalt = $_POST['inahlt'];
$todo_id = $_POST['todo_id'];

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

// ToDo Status ändern/löschen ************************************************************************
if($submit == 'status'){
	$newstatus = $_POST['status'];
	if($newstatus == '5'){
		$SQL = "DELETE FROM todo WHERE id='".$todo_id."'";
		# SQL ausführen
		mysql_query($SQL);
		#Anzahl betroffener Datensätze ausgeben:
		if (mysql_affected_rows() != 1) { $inhalt =  "Fehler beim l&ouml;schen<br>";}
		else { $inhalt =  "Eintrag gel&ouml;scht<br>"; }  
	}
	else{
	$SQL = "UPDATE todo SET status='".$newstatus."' WHERE id='".$todo_id."'";
	# SQL ausführen
	mysql_query($SQL);
	#Anzahl betroffener Datensätze ausgeben:
	if (mysql_affected_rows() != 1) {$inhalt = "Fehler beim &auml;ndern<br>";}
	else { $inhalt = "Status ge&auml;ndert<br>"; }
	}
}

// ToDO hinzufügen ******************************************************************************
elseif($submit == 'hinzu') {
	$inhalt = $_POST['inhalt'];
	$status = $_POST['status'];
	//Datenbankeintrag generieren
	$SQL = "INSERT INTO todo (inhalt, status) VALUES ('".$inhalt."', '".$status."')";
	
	//DB fuellen
	if(!mysql_query($SQL)) {$inhalt = "Fehler beim Eintrag in die Datenbank<br>"; mysql_error();}
	else {$inhalt = "Eintrag erfolgreich<br>"; }
	

}

// ToDo Ausgabe *********************************************************************************	
$query = mysql_query("SELECT id, inhalt, status, DATE_FORMAT(datum, GET_FORMAT(DATE,'EUR')) as 'datumform' FROM todo") or die(mysql_error());

$status0 = 'style="border:none"';
$status1 = 'style="border: 2px dotted red; color: black"';
$status2 = 'style="border: 2px dotted #00FF00; color: black"';
$status3 = 'style="border: 2px dotted yellow; color: black"';
$status4 = 'style="border: 2px dotted blue; color: black"';


$inhalt .= '<br><fieldset><br><table  style="border:none">
			<tr style="border:none">
				<td style="border: none; color: black">
					Datum
				</td>
				<td width="370px" style="border: none; color: black">
					Titel
				</td>
				<td style="border: none; color: black">
					Status
				</td>
			</tr>';

$reihen = mysql_num_rows($query);
for($i = 0; $i < $reihen; $i++)
{
	$wert = mysql_fetch_object($query);
	
	$status = $wert->status;
	$sel0 =""; $sel1=""; $sel2 =""; $sel3=""; $sel4 =""; $sel5="";
	if($status==0){$sel0 = "selected";}
	elseif($status==1){$sel1 = "selected";} 
	elseif($status==2){$sel2 = "selected";} 
	elseif($status==3){$sel3 = "selected";} 
	elseif($status==4){$sel4 = "selected";} 
	elseif($status==5){$sel5 = "selected";} 
	 
	$color = "status".$wert->status;

	$inhalt .=' <tr style="border:none">
					<td '.$$color.'>'.$wert->datumform.'</td>
					<td '.$$color.'>'.$wert->inhalt.'</td>
					
					<td><form action="#" method="post" name="status"> <input type="hidden" name="todo_id" value="'.$wert->id.'"> <input type="hidden" name="wastun" value="status"><select name="status" size="1" width="10px" onchange="this.form.submit();">
						<option '.$sel0.' value="0" background-color="red">Unwichtig</option>
						<option '.$sel1.' value="1">Wichtig</option>
						<option '.$sel2.' value="2">Erledigt</option>
						<option '.$sel3.' value="3">Checken</option>
						<option '.$sel4.' value="4">Neu</option>
						<option value="5">Löschen</option>
					</select>
					</form>
				</tr>
	';	
}
$inhalt .='</table><br>
			Neuer Eintrag<br>
			<form action="#" method="post" name="hinzu">  <input type="hidden" name="wastun" value="hinzu">
			<input type="text" name="inhalt" maxlength="250" size="50">
			<select name="status" size="1">
				<option value="0">Unwichtig</option>
				<option value="1">Wichtig</option>
				<option value="2">Erledigt</option>
				<option value="3">Checken</option>
				<option value="4">Neu</option>
			</select>
			<input type="submit" value="hinzuf&uuml;gen">
			</form>
';

?>
