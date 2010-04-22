<?php
//Newsletter verschicken
$nlid = $_POST['nlid'];
if(isset($_GET['nlid'])){$nlid = $_GET['nlid']; }
$senden = $_POST['senden'];

$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);

//newsletter holen
$querymail = mysql_query('SELECT titel, inhalt, datum FROM '._newslnewsl.' WHERE id ='.$nlid) or die(mysql_error());
$newsletter= mysql_fetch_object($querymail);

//inhalt in string um db auslastung zu sparen
$titel = $newsletter->titel;
$inhalt = $newsletter->inhalt;
$datum = $newsletter->datum;

//user holen
$queryuser = mysql_query('SELECT anrede, vorname, nachname, email FROM '._newslempfaenger.' WHERE optin_value = 1') or die(mysql_error()."   ".$auslesen);
$anzempf = mysql_num_rows($queryuser);

if($senden==1) {
	$i=1;
	//senden der mails
	while($i<=$anzempf) {
	
		//Obejekt laden
		$empfaenger = mysql_fetch_object($queryuser);
		
		$to = $empfaenger->email;
		//$to = "info@wexelwirken.net";
		
		$subject = $titel;
		
		$message = "Hallo ".$empfaenger->anrede." ".$empfaenger->vorname." ".$empfaenger->nachname.", \r\n";
		$message .= $newsletter_newsletter_bgrTest;
		
		$message .= $inhalt." \r\n\r\n\r\n\r\n";
		
		$message .= "Falls Sie keinen weiteren Newsletter erhalten wollen klicken Sie auf den unteren Link\r\n".$newsletter_abbestellen_seite;				
			
		/* "Content-type"-Header. */
		$headers  = "MIME-Version: 1.0 \r\n";
		$headers .= "Content-type: text/plain; charset=utf-8 \r\n";
		
		/* zusaetzliche Header */
		$headers .= "From: ".$SiteTitle." <".$MailInfo.">";
	
	
		//Mail verschicken
		if(!mail($to, $subject, $message, $headers)) {$fehlertext .= "Fehler mit ".$to." Mail Nr. ".$i."<br>";}
		// bei mehr als 200?? mails mehrere mit bcc aufeinmal sonst noch header aktualisieren (geht 21 mal) <- muss gebaut werden bis 400.000 mails in kombi
		$i++;
	
	}
	$i--;
		
	//Seitenbetreiber mail
	mail($MailInfo, $subject, $message, $headers);
	
	//Status des NL akt
	mysql_query('UPDATE '._newslnewsl.' SET status = 2 WHERE id='.$nlid) or die(mysql_error());
	echo $fehlertext."<br>";
	echo $i." - Newsletter erfolgreich verschickt";
	echo "<br><br><a href='index.php?modus=NEW&inc=NLU'>Zur&uuml;ck zur &Uuml;bersicht</a>";
	
}
//newsletter verschicken?
else {

	echo "<h3>Newsletter versenden</h3><br>
			<fieldset><br>
			Soll der Newsletter  \"  ".$titel."  \"  gesendet werden?<br><br>
			<form action='index.php?modus=NEW&inc=NSE&nlid=".$nlid."' method='post'>
				<input type=\"hidden\" name=\"senden\" value=\"1\">
				<input type=\"submit\" value=\"schicken\">
			</form>
			<br><br>
			".$anzempf." Empfaenger<br>
			
			<b><span class='textRot'>!!!ACHTUNG!!! Das Senden kann eingige Zeit in Anspruch nehmen, solange Sie keine Fehlermeldung erhalten nicht weitersurfen oder abbrechen!<span></b></fieldset";
			
	}
	
	
	
	