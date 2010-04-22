<?php
//POST UND GET
$senden = $_POST['senden'];
$anrede = $_POST["anrede"];
$vorname = $_POST["vorname"];
$nachname = $_POST["nachname"];
$mail = $_POST["email"];
$cpt_wert = $_POST["cpt_wert"];
$valid = $_GET["valid"];     //BestMail
$valkey = $_GET["valkey"];


//Datenbank
$db = new db($dbHost,$dbUser,$dbPasswort);
$db -> select_db($dbDatenbank);


//Bestaetigungsmail auswerten
if($valid&&$valkey) {

	//Warten
	sleep(0.7);
	
	//value gleich 1 und key loeschen
	$SQL = "UPDATE "._newslempfaenger." SET optin_value='1', optin_key ='0' WHERE id='".$valid."' AND optin_key='".$valkey."'";
	
	# SQL ausführen
	mysql_query($SQL);
	
	#Anzahl betroffener Datensätze ausgeben:
	if (mysql_affected_rows() != 1) { $inhalt = $lang_newsletter_valError;}
	else { $inhalt = $lang_newsletter_bestellt; }  
	
	
	
}



//wenn kein best-link
else {


//Formlar auswerten
if($senden == "1") {


    //Warten
	sleep(0.7);
	
	// Feldtest
	$felherText = "";
	if($anrede=="0"){$fehlerText.="<li>".$lang_newsletter_errorSalutation."\n";}
	if($vorname==""){$fehlerText.="<li>".$lang_newsletter_errorFirstname."\n";}
	if($nachname==""){$fehlerText.="<li>".$lang_newsletter_errorLastname."\n";}
	if($mail==""){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
	else{$mailAt = explode("@", $mail);
		if(count($mailAt)!="2"){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
		else{$mailPunkt = explode(".", $mailAt[1]);
			if(count($mailPunkt)<"2"){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
			else{$mailvorh = mysql_query('SELECT email FROM '._newslempfaenger.' WHERE email ="'.$mail.'"') or die(mysql_error());
				if(mysql_num_rows($mailvorh)){$fehlerText.="<li>".$lang_newsletter_errorMailvorh."\n";}
	}	}	}


    // reCAPTCHA **********************************************
    $privatekey = "6Le_QgUAAAAAAIRa-ih7Uj9Xog6iBBuJz-mVJ3ze";
    $resp = recaptcha_check_answer ($privatekey,
                                    $_SERVER["REMOTE_ADDR"],
                                    $_POST["recaptcha_challenge_field"],
                                    $_POST["recaptcha_response_field"]);

    if(!$resp->is_valid){$fehlerText.="<li>".$lang_contact_errorReCAPTCHA."\n";}
    	
	
	// Fehlermeldung
	if($fehlerText!=""){
        
        $inhalt.= "<h4>".$lang_newsletter_errorTitle."</h4>
            <p>
            ".$lang_newsletter_errorText1."<br>
            <ul>
            ".$fehlerText."
            </ul>
            ".$lang_newsletter_errorText2."<br>
            </p>";
	}
	else{
		$fehlertext = "";
		//Zufallskey wird ermittelt	
		srand ((double)microtime()*1000000);
		while(strlen($bc) < 5){$bc .= rand(0,9);}
		$optinkey = md5($bc);
		
		
		// Anrede umbauen
		$anredeVar = "lang_newsletter_formSalutation".$anrede;
		$anrede = $$anredeVar;
		
		//Datenbankeintrag generieren
		$SQL = "INSERT INTO "._newslempfaenger." (anrede, vorname, nachname, email, optin_key, optin_value) VALUES ('".$anrede."', '".$vorname."', '".$nachname."', '".$mail."', '".$optinkey."', '0')";
		
		//DB fuellen
		if(!mysql_query($SQL)) {$fehlertext .= "<br>".$lang_newsletter_sendErrorDB;}
		
		//Mail generieren
		$to = $mail;
		//$to = "rafael.schniedermann@gmx.de";
		$subject = $SiteTitle." ".$lang_newsletter_messageTitle;
		$message = "".$lang_newsletter_messageAnrede." ".$anrede." ".$vorname." ".$nachname.". \r\n\r\n";
		$message.= $lang_newsletter_messageText1."\r\n";
		$message.= $lang_newsletter_messageText2."\r\n";
		$message.= $HttpRoot."/index.php?id=".$id."&ord=".$ord."&valid=".mysql_insert_id()."&valkey=".$optinkey;
		/* "Content-type"-Header. */
		$headers  = "MIME-Version: 1.0\r\n";
		$headers .= "Content-type: text/plain; charset=utf-8\r\n";
		/* zusaetzliche Header */
		$headers .= "From: ".$SiteTitle." <".$MailInfo.">\r\n";


		//Mail verschicken
		if(!mail($to, $subject, $message, $headers)) {$fehlertext .= "<br>".$lang_newsletter_sendErrorMail;}
		
		
		if($fehlertext != ""){
		
		$inhalt.= "<h4>".$lang_newsletter_sendErrorTitle."</h4><br>
	    		   <p>
				   ".$lang_newsletter_sendErrorText1."<br>
				   ".$fehlertext."
	    		   </p>";
	   	}
		else {
		
		//Ausgabe	
		$inhalt .= " <p>".$lang_newsletter_sendTitle."</p>";
		}
	}



	
}

//Formular bauen
else {
	
	//Newsletter bestellen formualr
	
	
	$inhalt .= "<fieldset><form action=\"index.php?id=".$id."&amp;ord=".$ord."\" method=\"post\">
				 <br>
				<table>
				<tr>
				<td align=\"right\">".$lang_contact_formSalutation."*:&nbsp;&nbsp;&nbsp;<br></td>
				<td><select name=\"anrede\" size=\"1\">
				<option value=\"0\">".$lang_contact_formSalutation0."</option>
				<option value=\"F\">".$lang_contact_formSalutationF."</option>
				<option value=\"M\">".$lang_contact_formSalutationM."</option>
				</select><br></td>
				</tr>
				
				<tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
				
				<tr>
				<td align=\"right\">".$lang_contact_formFirstname."*:&nbsp;&nbsp;&nbsp;<br></td>
				<td><input type=\"text\" name=\"vorname\" maxlength=\"250\" size=\"25\"><br></td>
				</tr>
				
				<tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
				
				<tr>
				<td align=\"right\">".$lang_contact_formLastname."*:&nbsp;&nbsp;&nbsp;<br></td>
				<td><input type=\"text\" name=\"nachname\" maxlength=\"250\" size=\"25\"><br></td>
				</tr>
				
				<tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
				
				<tr>
				<td align=\"right\">".$lang_contact_formMail."*:&nbsp;&nbsp;&nbsp;<br></td>
				<td><input type=\"text\" name=\"email\" maxlength=\"250\" size=\"25\"><br></td>
				</tr>
				
				<tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
				</table><br>
				";
				// Look & Feel
	$inhalt.= " <script type=\"text/javascript\">
				    var RecaptchaOptions = {
				    audio_beta_12_08 : true,
				    theme: 'red',
				    lang: '".strtolower($_SESSION["Lang"])."'
				    };
				    </script>\n";
				
				$publickey = "6Le_QgUAAAAAAJM70peauN48hi-Hf-LVIWefkObW";
				$inhalt.= recaptcha_get_html($publickey);
				
	$inhalt.= " <input type=\"hidden\" name=\"senden\" value=\"1\">
				<input type=\"submit\" value=\"bestellen\">
				
				</form>
				
				</fieldset>";

}


}

?>

