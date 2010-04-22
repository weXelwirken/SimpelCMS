<?php
//uebersicht ueber user
$site = $_GET["site"];
$wastun = $_POST['wastun'];
$nutzerid = $_POST['nutzerid'];
$submit = $_POST['submit'];
$nutzer = $_POST['nutzer'];

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);


//AUSGABE****************************************************************
//******************************************
//**************

//Nutzer loeschen*********************************************************
if($wastun == "loeschen") {
	if($submit == 'true'){
	
	$SQL = "DELETE FROM "._newslempfaenger." WHERE id='".$nutzerid."'";
		
		# SQL ausführen
		mysql_query($SQL);
		
		#Anzahl betroffener Datensätze ausgeben:
		if (mysql_affected_rows() != 1) { $aktion = "<br>Fehler beim l&ouml;schen<br>"; }
		else { $aktion = "<br>Empf&auml;nger gel&ouml;scht<br><br>"; }  
		$wastun='';
		
	}
	else{
	
		$query = mysql_query('SELECT anrede, vorname, nachname, email FROM '._newslempfaenger.' WHERE id = "'.$nutzerid.'"') or die(mysql_error());
		$wert = mysql_fetch_object($query);
		
		echo "<h3>Empf&auml;nger l&ouml;schen</h3><br><fieldset>";
		echo "Soll ".$wert->anrede." ".$wert->vorname." ".$wert->nachname." | ".$wert->email." | wirklich gel&ouml;scht werden<br><br>";
		
		echo '<form method="post">
	
	
					<input type="hidden" name="submit" value="true">
					<input type="hidden" name="wastun" value="loeschen">
					<input type="hidden" name="nutzerid" value="'.$nutzerid.'">
					<input type="submit" value="l&ouml;schen">
					
			  </form>
			  </fieldset>
			  ';
	
	}

}
//Nutzer hinzf************************************************************
elseif($wastun =="hinzfu"){
	if($submit=='speichern'){
		//Array1
		$nutzer = str_replace("\r\n", ";", $nutzer);
		$nutzer = explode(";", $nutzer);
		$aktion = "";
		foreach($nutzer as $nutzerreihe){
		
			//Array2
			$nutzerreihe = explode(",", $nutzerreihe);
		
			
			//Mail checken
			$mailAt = $nutzerreihe[3];
			$mailAt = explode("@", $nutzerreihe[3]);
				if(count($mailAt)!="2"){$aktion .= "Die Mailadresse ".$nutzerreihe[3]." ist ungultig<br>";}
				else{$mailPunkt = explode(".", $mailAt[1]);
					if(count($mailPunkt)<"2"){$aktion .= "Die Mailadresse ".$nutzerreihe[3]." ist ungultig<br>";}
					else{$mailvorh = mysql_query('SELECT email FROM '._newslempfaenger.' WHERE email ="'.$nutzerreihe[3].'"') or die(mysql_error());
						if(mysql_num_rows($mailvorh)){$aktion .= "Die Mailadresse ".$nutzerreihe[3]." ist schon vorhanden<br>";}
						else{
							$SQL = "INSERT INTO "._newslempfaenger." (anrede, vorname, nachname, email, optin_value) VALUES ('".$nutzerreihe[0]."', '".$nutzerreihe[1]."', '".$nutzerreihe[2]."', '".$nutzerreihe[3]."', '1')";
							
							//DB fuellen
							if(!mysql_query($SQL)) {$aktion .= "Fehler bei DB Eintrag<br>";}
			}	}	}	}
			$aktion .= "<br>Datebankeintrag komplett<br><br>";
			$wastun='';
	}
	elseif($submit =="ansehen"){

		//Textarea Zeilenümbrüche durch ; ersetzen
		$nutzer2 = str_replace("\r\n", ";", $nutzer);
		
		//Array1
		$nutzer3 = explode(";", $nutzer2);


		echo '<h3>Empf&auml;nger hinzuf&uuml;gen</h3><br>
			<fieldset><legend>Nutzer</legend>
			<span class="textRot">Diese Tabelle sollte korrekt dargestellt werden</span><br><br>
			<table style="border: 1px solid #7799AA;">';

		//Schleife 1
		foreach($nutzer3 as $einzelnd){
		
			//Array2
			$einzelnd = explode(",", $einzelnd);
			
			echo "<tr style='border: 1px solid #7799AA;'>";
			//Schleife 2
			foreach($einzelnd as $wert) {
				echo"<td style='border: 1px solid #7799AA;'>";
				echo $wert;
				echo "</td style='border: 1px solid #7799AA;'>";
			}
			echo "</tr>";
		
		}
		echo '</table><br></fieldset><br>
		<fieldset><legend>Bearbeiten</legend><br>
		<form method="post">
		<div>
			<input type="hidden" name="senden" value="1">
			<textarea cols="65" rows="10" name="nutzer" wrap="off">'.$nutzer.'</textarea>
			
		</fieldset><br>
			<input type="hidden" name="wastun" value="hinzfu">
			<input type="submit" name="submit" value="speichern">
			<input type="submit" name="submit" value="ansehen">
		</div>
		</form>
		
		
		';
	
	}
	else{
		echo '<h3>Empf&auml;nger hinzuf&uuml;gen</h3><br>
			<fieldset>
				<div style="clear: left;"><legend>Nutzer hinzuf&uuml;gen</legend>  </div> <br>				
				<form method="post">
				<div>Es m&uuml;ssen "Anrede, Vorname, Nachname, Email" angegeben werden! Durch Enter kann man mehrere aufeinmal hinzuf&uuml;gen <br>
				<br>
				<div style="clear: left;">Empf&auml;nger:</div>
				
				<div style="clear: left;">
				<textarea cols="65" rows="10" name="nutzer" wrap="off">Herr,Max,Mustermann,max@mustermann.de
Frau,Michaela,Musterfrau,machaeala@musterfrau.de</textarea>
				</div>
				
				<div>
				
					<input type="hidden" name="wastun" value="hinzfu">
					<input type="submit" name="submit" value="ansehen">
				</div>
				</form>   
				</fieldset>
		';	
	}
	
	
} //ueberischt**********************************************************
if($wastun==''){

	//Seitenzhalen berechnen
	$auswahlanf = $site * $newsletter_anzahl_UserProSeite;
	$eintraege = mysql_query('SELECT id FROM '._newslempfaenger);
	$eintraege = mysql_num_rows($eintraege);
	
	//aufrunden und anzahl seiten errechnen
	$seiten =  ceil($eintraege / $newsletter_anzahl_UserProSeite);
	
	//db mit beschraenkung auf seite
	$query = mysql_query('SELECT id, anrede, vorname, nachname, email, optin_value FROM '._newslempfaenger.' LIMIT '.$auswahlanf.', '.$newsletter_anzahl_UserProSeite) or die(mysql_error()."   ".$auslesen);
	
	//seitenzahlen in string
	$seitenzahlen = "<a href=\"index.php?modus=NEW&inc=EUE&site=0\">1</a> ";
	//wenn mehr als eine seite diese anhaengen
	if($seiten > "1") {
		$i=1;
		while($seiten > $i) {
			$seitenzahlen .= " <a href=\"index.php?modus=NEW&inc=EUE&site=".$i."\"> ".$i." </a> ";
			$i++;
	}	}

?>
	
	<h3>Empf&auml;nger des Newsletters</h3><br>
	<fieldset>
	<form method="post" name="hinzfu"><input type="hidden" name="wastun" value="hinzfu">Aktionen: <a href="#" onclick="document['hinzfu'].submit()"><span class="textGruen">Empf&auml;nger hinzuf&uuml;gen</span></a></form><br>
	<center> <?php echo $seitenzahlen; ?> </center>
	</fieldset><br>
	<span class="textRot"><?php echo $aktion; ?></span>
	<fieldset><legend>Empf&auml;nger</legend>
	<table border="0">
		<tr>
			<td width="100px" style="border: 1px solid #7799AA;">
				Anrede
			</td>
			<td width="100px" style="border: 1px solid #7799AA;">
				Vorname
			</td>
			<td width="100px" style="border: 1px solid #7799AA;">
				Nachname
			</td>
			<td width="280px" style="border: 1px solid #7799AA;">
				E-Mail
			</td>
			<td style="border: 1px solid #7799AA;">
				G&uuml;ltig
			</td>
			<td width="15px" style="border: 1px solid #7799AA;">&nbsp;L&nbsp;</td>
		</tr>
		
		<?php
		for($i = 0; $i < mysql_num_rows($query); $i++)
		{
			$wert = mysql_fetch_object($query);
			$optinfield= '<td style="border: 1px dotted #7799AA;"><center>Nein</center></td>';
						  
			if($wert->optin_value == "1") {
			$optinfield= '<td style="border: 2px solid #009900;"><center>Ja</center></td>';}
	
		?>
		<tr>
			<td style="border: 1px dotted #7799AA;">
				<?php echo $wert->anrede; ?>
			</td>		
			<td style="border: 1px dotted #7799AA;">
				<?php echo $wert->vorname; ?>
			</td>
			<td style="border: 1px dotted #7799AA;">
				<?php echo $wert->nachname; ?>
			</td>
			<td style="border: 1px dotted #7799AA;">
				<?php echo $wert->email; ?>
			</td>
			<?php echo $optinfield; ?>
			<td style="border: 1px dotted #7799AA;">
				<?php echo '<form method="post" name="loeschenX'.$wert->id.'"><input type="hidden" name="wastun" value="loeschen"><input type="hidden" name="nutzerid" value="'.$wert->id.'"><a href="#" onclick="document[\'loeschenX'.$wert->id.'\'].submit()"><span class="textRot"><b>&nbsp;X&nbsp;</b></span></a></form>'; ?>
			</td>
		</tr>
		<?php } ?>
	</table><br>
	</fieldset>
	<br>
	<fieldset>
	<form method="post" name="hinzfu2">
	<input type="hidden" name="wastun" value="hinzfu">
	Aktionen: <a href="#" onclick="document['hinzfu2'].submit()"><span class="textGruen">Empf&auml;nger hinzuf&uuml;gen</span></a>
	</form><br>
	<center> <?php echo $seitenzahlen; ?> </center>
	</fieldset>
<?php } ?>