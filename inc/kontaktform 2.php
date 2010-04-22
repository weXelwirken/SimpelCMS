<?php
// POST und GET extrahieren
$senden = $_POST["senden"];
$anrede = $_POST["anrede"];
$vorname = $_POST["vorname"];
$nachname = $_POST["nachname"];
$orga = $_POST["orga"];
$mail = $_POST["mail"];
$betreff = $_POST["betreff"];
$nachricht = $_POST["nachricht"];
$cc = $_POST["cc"];
$cpt_wert = $_POST["cpt_wert"];

//CPT Grafiken
$_SESSION['cpt_namen'] = array("mac", "tux", "win");

// ********************************************************************************************************************
// Mail senden ********************************************************************************************************   
if($senden=="1")
	{
	    	
    //Warten
	sleep(0.7);
	
	// Feldtest
	$felherText = "";
	if($anrede=="0"){$fehlerText.="<li>".$lang_contact_errorSalutation."\n";}
	if($vorname==""){$fehlerText.="<li>".$lang_contact_errorFirstname."\n";}
	if($nachname==""){$fehlerText.="<li>".$lang_contact_errorLastname."\n";}
	if($mail==""){$fehlerText.="<li>".$lang_contact_errorMail."\n";}
	else
		{
		$mailAt = explode("@", $mail);
		if(count($mailAt)!="2"){$fehlerText.="<li>".$lang_contact_errorMail."\n";}
		else{$mailPunkt = explode(".", $mailAt[1]);if(count($mailPunkt)<"2"){$fehlerText.="<li>".$lang_contact_errorMail."\n";}}
		}

    // CAPTCHA **********************************************
    
    if($_POST['cpt_wert']!=$_SESSION['cpt_werte'][$_SESSION['cpt_zuf']]) {
    	
    	$fehlerText.="<li>".$lang_contact_errorReCAPTCHA."\n";
    }
    
	//CPT loeschen 
	unset($_SESSION['cpt_namen']);
	unset($_SESSION['cpt_werte']);
    	
	
	// Fehlermeldung
	if($fehlerText!="")
		{
        $inhalt.= "<h4>".$lang_contact_errorTitle."</h4>
            <p>
            ".$lang_contact_errorText1."<br>
            <ul>
            ".$fehlerText."
            </ul>
            ".$lang_contact_errorText2."<br>
            </p>";
		}
	// Senden
	else
		{
		// Anrede umbauen
		$anredeVar = "lang_contact_formSalutation".$anrede;
		$anrede = $$anredeVar;
		
		if($orga){$orga=", ".$orga;}else{$orga="";}
		// Mail vorbereiten
		$to = $MailInfo;
		// Debug: $to = "info@wexelwirken.de";
		$subject = $betreff;
		$message = $lang_contact_messageText1."<br>\r\n";
		$message.= "<b>".$anrede." ".$vorname." ".$nachname." (".$mail.$orga.")</b><br>\r\n<br>\r\n";
		$message.= $lang_contact_messageText2."<br>\r\n";
		$message.= "<b>\"".nl2br($nachricht)."\"</b><br>\r\n";
		
		/* "Content-type"-Header. */
		$headers  = "MIME-Version: 1.0\r\n";
		$headers .= "Content-type: text/plain; charset=utf-8\r\n";

		/* zusaetzliche Header */
		$headers .= "From: ".$vorname." ".$nachname." <".$mail.">\r\n";
		if($cc){$headers .= "CC: ".$vorname." ".$nachname." <".$mail.">\r\n";}

		/* Verschicken der Mail */
		if(!mail($to, $subject, $message, $headers))
			{
			$inhalt.= "<h4>".$lang_contact_sendErrorTitle."</h4>
                <p>
                ".$lang_contact_sendErrorText1." ".$anrede." ".$nachname."".$lang_contact_sendErrorText2." <a href=\"mailto:".$MailInfo."\">".$MailInfo."</a>.<br>
                <br>
                ".$lang_contact_sendErrorText3."<br>
                <br>
                <br>
                ".$lang_contact_sendErrorText4."<br>
                </p>";
			}
		else
			{
			$inhalt.= "<h4>".$lang_contact_sendTitle."</h4>
                <p>
                ".$lang_contact_sendText1." ".$anrede." ".$nachname."".$lang_contact_sendText2."<br>
                <br>
                ".$lang_contact_sendText3."<br>
                </p>
                <p>
                ".$lang_contact_sendText4."<br>
                </p>";
			}
		}
	}
// ********************************************************************************************************************
// Formular ***********************************************************************************************************
else
	{
    $inhalt.= $lang_contact_text."
        <br>
        <fieldset>
        <legend>".$lang_contact_formTitle."</legend>
        
        <div style=\"padding:5px 5px 25px 5px;\">
        ".$lang_contact_formText1."<br>
        </div>
        
        <form action=\"index.php?id=".$id."&amp;ord=".$ord."\" method=\"post\">
        
        <table border=\"0\" cellpadding=\"0\" cellspacing=\"0\" align=\"center\">
        
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
        <td align=\"right\">".$lang_contact_formOrganisation.":&nbsp;&nbsp;&nbsp;<br></td>
        <td><input type=\"text\" name=\"orga\" maxlength=\"250\" size=\"25\"><br></td>
        </tr>
        
        <tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
        
        <tr>
        <td align=\"right\">".$lang_contact_formMail."*:&nbsp;&nbsp;&nbsp;<br></td>
        <td><input type=\"text\" name=\"mail\" maxlength=\"250\" size=\"25\"><br></td>
        </tr>
        
        <tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
        
        <tr>
        <td align=\"right\">".$lang_contact_formSubject.":&nbsp;&nbsp;&nbsp;<br></td>
        <td><input type=\"text\" name=\"betreff\" maxlength=\"250\" size=\"46\" value=\"".$lang_contact_formSubjectText."\"><br></td>
        </tr>
        
        <tr>
        <td align=\"right\" valign=\"top\">".$lang_contact_formMessage.":&nbsp;&nbsp;&nbsp;<br></td>
        <td><textarea name=\"nachricht\" rows=\"10\" cols=\"40\"></textarea></td>
        </tr>
        
        <tr>
        <td align=\"right\">".$lang_contact_formCopy.":&nbsp;&nbsp;&nbsp;<br></td>
        <td><input type=\"checkbox\" name=\"cc\" value=\"1\" checked><span class=\"klein\">".$lang_contact_formCopyText."</span><br></td>
        </tr>
        
        <tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
        
        <tr><td colspan=\"2\" align=\"center\">\n";
    
    // ****************************************************************************************
    // CAPTCHA ******************************************************************************
    	

	
	//CPT Zufallswert fuer Frage ausknobeln
	$_SESSION['cpt_zuf'] = rand(0, count($_SESSION['cpt_namen'])-1);
	
	
    // Look & Feel
	$inhalt.= '<img src="inc/cpt.php" alt="CPTCHA">	<br>
	Wie viele '.$_SESSION["cpt_namen"][$_SESSION["cpt_zuf"]].' - Symbole sind vorhanden? <br>
	
	<input type="text" name="cpt_wert" maxlength="2" >';
    
    
    $inhalt.= "</td></tr>
        
        <tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
        
        <tr><td colspan=\"2\" align=\"center\">
        <input type=\"hidden\" name=\"senden\" value=\"1\">
        <input type=\"hidden\" name=\"authId\" value=\"".$authId."\">
        <input type=\"submit\" value=\"".$lang_contact_formSubmit."\">
        </td></tr>
        
        <tr><td colspan=\"2\"><img src=\"img/one.gif\" width=\"1\" height=\"10\" border=\"0\" alt=\"\"></td></tr>
        
        </table>
       
        </form>
        
        </fieldset>";
	}
?>