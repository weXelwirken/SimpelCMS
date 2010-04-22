<?php
//POST und GET
$mail = $_POST["email"];
$cpt_wert = $_POST["cpt_wert"];
$valid = $_GET["valid"];
$valkey = $_GET["valkey"];
$senden = $_POST["senden"];

//CPT Grafiken
//$_SESSION['cpt_namen'] = array("mac", "tux", "win");


//Email auswerten
if($valid&&$valkey) {

	//Warten
	sleep(0.7);
	
	$SQL = "DELETE FROM "._newslempfaenger." WHERE id='".$valid."' AND optin_key='".$valkey."'";
	
	# SQL ausführen
	mysql_query($SQL);
	
	#Anzahl betroffener Datensätze ausgeben:
	if (mysql_affected_rows() != 1) { $inhalt = $lang_newsletter_valError;}
	else { $inhalt = $lang_newsletter_abbestellt; }  
	
	


}
//wenn keine mail 
else {
	
	//wen forumlar best.
	if($senden == "1") {
		//mail kontrollieren
		if($mail==""){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
		else{$mailAt = explode("@", $mail);
			if(count($mailAt)!="2"){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
			else{$mailPunkt = explode(".", $mailAt[1]);
				if(count($mailPunkt)<"2"){$fehlerText.="<li>".$lang_newsletter_errorMail."\n";}
				else{$mailvorh = mysql_query('SELECT email FROM '._newslempfaenger.' WHERE email ="'.$mail.'"') or die(mysql_error());
					if(!mysql_num_rows($mailvorh)){$fehlerText.="<li>".$lang_newsletter_errorMailvorh."\n";}
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
			
			
			//Datenbankeintrag generieren
			$SQL = "UPDATE "._newslempfaenger." SET optin_key = '".$optinkey."' WHERE email ='".$mail."'";
			
			//DB fuellen
			if(!mysql_query($SQL)) {$fehlertext .= "<br>".$lang_newsletter_sendErrorDB;}
			
			$query = mysql_query('SELECT anrede, id, vorname, nachname FROM '._newslempfaenger.' WHERE email = "'.$mail.'"');
			$wert = mysql_fetch_object($query);
			
			//Mail generieren
			$to = $mail;
			//$to = "rafael.schniedermann@gmx.de";
			
			$subject = $SiteTitle." ".$lang_newsletter_abstmessageTitle;
			$message = "".$lang_newsletter_messageAnrede." ".$wert->anrede." ".$wert->vorname." ".$wert->nachname.". \r\n\r\n";
			$message.= $lang_newsletter_abstmessageText1."\r\n";
			$message.= $HttpRoot."/index.php?id=".$id."&ord=".$ord."&valid=".$wert->id."&valkey=".$optinkey."\r\n";
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
			$inhalt .= " <p>".$lang_newsletter_abstsendTitle."</p>";
			}
		
		}
		
		
			
	}
	//Formular
	else {
		
		
		$inhalt = "<fieldset><form action=\"index.php?id=".$id."&amp;ord=".$ord."\" method=\"post\">
					<table>
					<tr>
						<td>".$lang_contact_formMail.": </td>
						<td><input type=\"text\" name=\"email\" maxlength=\"250\" size=\"25\"><td>
					</tr>
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
					
		$inhalt.= "	<input type=\"hidden\" name=\"senden\" value=\"1\">
					<input type=\"submit\" value=\"abbestellen\">
					
					</form>
					</fieldset>";
	}
}

?>

