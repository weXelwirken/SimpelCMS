<?php

// DB-Verbindung

$db = new db($dbHost,$dbUser,$dbPasswort);

$db -> select_db($dbDatenbank);



// POST und GET extrahieren

$Anrede = $_POST["Anrede"];

$Titel = $_POST["Titel"];

$Vorname = $_POST["Vorname"];

$Nachname = $_POST["Nachname"];

$Spitzname = $_POST["Spitzname"];

$Firma = $_POST["Firma"];

$Position = $_POST["Position"];

$BueroStrasse = $_POST["BueroStrasse"];

$BueroPLZ = $_POST["BueroPLZ"];

$BueroOrt = $_POST["BueroOrt"];

$BueroBundesland = $_POST["BueroBundesland"];

$BueroLand = $_POST["BueroLand"];

$PrivatStrasse = $_POST["PrivatStrasse"];

$PrivatPLZ = $_POST["PrivatPLZ"];

$PrivatOrt = $_POST["PrivatOrt"];

$PrivatBundesland = $_POST["PrivatBundesland"];

$PrivatLand = $_POST["PrivatLand"];

$TeleBuero = $_POST["TeleBuero"];

$TelePrivat = $_POST["TelePrivat"];

$TeleFax = $_POST["TeleFax"];

$TeleMobil = $_POST["TeleMobil"];

$MailBuero = $_POST["MailBuero"];

$MailPrivat = $_POST["MailPrivat"];

$Netz = $_POST["Netz"];

$Geburt = $_POST["Geburt"];

$SkypeID = $_POST["SkypeID"];

$ICQ = $_POST["ICQ"];

$KontoInhaber = $_POST["KontoInhaber"];

$KontoBank = $_POST["KontoBank"];

$KontoNummer = $_POST["KontoNummer"];

$KontoBLZ = $_POST["KontoBLZ"];

$Klassen = $_POST["Klassen"];

$Notizen = $_POST["Notizen"];

$step = $_POST["step"];

if(!$step){$step = $_GET["step"];}



// Testen ob Arbeitsschritt gesetzt

if($step==""){$step = 0;}



// Parameter

$inputImport = "inc/DAT/import/import.html";

$betweenImport = "inc/DAT/import/importB.html";

$outputImport = "inc/DAT/import/import.csv";



$exportPath = "inc/DAT/export/";

?>



<!-- Content Import & Export -->



<table border="0" cellpadding="0" cellspacing="0" width="480">



<tr>

<td align="left" valign="top">



<?php

// Step 0: Eingabe

//#############################################################################

if($step==0)

	{

    // Import parsen ***********************************************************

    

    if(file_exists($inputImport))

        {

        // Vorbereiten

        $handle = fopen ($inputImport, "r");

        while (!feof($handle))

            {

            $count++;

            $bufferTest = fgets($handle, 10000);

            

            // Korrekter Anfang

            if($count==18){$buffer.=str_replace("</TR>", "<TABLE>", $bufferTest);}

            if($count>18)

                {

                $buffer.= str_replace("</TABLE></BODY></HTML>", "</TABLE>", str_replace("<BR>", "xxxBRxxx", $bufferTest));

                }

            }

        fclose ($handle);

        

        $fp = fopen($betweenImport, 'w');

        fputs($fp, $buffer);

        fclose($fp);

        

        // Parsen

        $tabelle = new XML_document($betweenImport);

        $sep_char = '|';

        

        foreach($tabelle->XMLdata['TABLE'][0]['TR'] as $row)

            {

            foreach($row['TD'] as $cell)

                {

                $csv .= $cell['CDATA'] . $sep_char;

                }

            $csv .= "\n";

            }

        $fp = fopen($outputImport, 'w');

    

        

        // Umbruch ersetzen

        $csv = str_replace("xxxBRxxx", "<BR>", $csv);

        

        fputs($fp, $csv);

        fclose($fp);

        unlink($inputImport);

        unlink($betweenImport);

        unset($csv);

        unset($tabelle);

        unset($buffer);

        unset($count);

        // echo "Import OK!<br>";

        }

    // /Seminare ***************************************************************

	?>



<h3>Import & Export</h3>



<!-- Innere Tabelle Eingabe -->



<p>

<fieldset><legend>Import</legend>



<p>

    <?php

    /* Kommentare entfernen um Import zu aktivieren

    // Import vorhanden

    if(file_exists($outputImport))

        {

        // Datensaetze errechnen

        $anzahlDs = count(file($outputImport));

        // Ausgabe

        echo "Es steht eine neue Import-Datei mit <b>".$anzahlDs." Datens&auml;tzen</b> zur Verf&uuml;gung.<br>\n<div align=right><a href=\"index.php?modus=DAT&inc=IMP&step=1\">Import jetzt vorbereiten...</a><br></div>\n";

        }

    // Import nicht vorhanden

    else

        {

        echo "Zur Zeit steht keine Import-Datei zur Verf&uuml;gung. Bitte laden Sie Daten, die Sie in den Datenpool importieren m&ouml;chten, via FTP hoch.<br>\n";

        }

    */

    ?>

Die Datenkrake ist in der Lage Massenimporte von Adressdaten zu verarbeiten. Dazu ist jedoch eine Anpassung auf das von Ihnen verwendete Datenformat n&ouml;tig. Bitte wenden Sie sich an <a href="mailto:info@wexelwirken.net">info@wexelwirken.net</a> und lassen Sie sich eine unverbindliches Aufwandsabsch&auml;tzung zuschicken.

</p>



</form>



</table>

</fieldset>

</p>





<p>

<fieldset><legend>Export</legend>



<p>

<?php

     

	$handle = opendir($exportPath);

    while ($file = readdir ($handle)) 

	   {

	    if($file != "." && $file != "..")

	       {

            $fileArray[] = $file;

		   }		    

       }

    closedir($handle);

    if (isset($fileArray))

	  {

       rsort($fileArray);



       echo "Folgende Exportdateien sind zum Download vorhanden:<br><br>\n";

	  

       foreach($fileArray as $row)  

   	     {

          echo "<a href=\"".$exportPath.$row."\"><b>".$row."</b></a><br>\n";

         }

	  }

	else

	  {

	   echo "Es sind keine Exportdateien zum Download vorhanden.<br>\n";

	  }

	echo "<br>\n";

    echo "<div align=right><a href=\"index.php?modus=DAT&inc=IMP&step=3\">Eine neue Export-Datei erzeugen...</a><br></div>\n";



?>

</p>



</table>

</fieldset>

</p>



<!-- /Innere Tabelle Eingabe -->



    <?php

	}

// ############################################################################

// /Step 0: Eingabe



// Step 1: Analyse

//#############################################################################

if($step==1)

	{

    // DATEI AUSLESEN ******************************************************

    $dsNeu = 0;

    $dsAlt = 0;

    $handle = fopen ($outputImport,"r");

    while ( ($data = fgetcsv ($handle, 10000, "|")) !== FALSE )

        {

        // Daten aus DB holen

        // SQL-String bauen

        $sqlString = "SELECT ID FROM datenpool WHERE Vorname='".$data["1"]."' AND Nachname='".$data["2"]."'";

        // Ergebnis auslesen

        $ergebnis = $db -> sql($sqlString);

        if($ergebnis)

            {

            // Datensatz in DB noch nicht vorhanden

            if(mysql_num_rows($ergebnis)<"1")

                {

                $dsNeu++;

                }

            // Datensatz in DB schon vorhanden

            else{$dsAlt++;}

            }

        }

    fclose ($handle);

    // /DATEI AUSLESEN ********************************************************

    

    // Ausgabe

    // Datensaetze errechnen

    $anzahlDs = count(file($outputImport));

    echo "<h3>Import</h3>\n";

    echo "<br><fieldset><legend>Import vorbereitet</legend>

        <p>Von ".$anzahlDs." neuen Datens&auml;tzen werden:

        <ul>

        <li><b>".$dsNeu." Datens&auml;tze</b> importiert und als \"Neu\" gekennzeichnet

        <li><b>".$dsAlt." Datens&auml;tze</b> nicht ber&uuml;cksichtigt, da sie schon vorhanden sind

        </ul>

        </p>

        <p align=right>

        <a href=\"index.php?modus=DAT&inc=IMP&step=2\">Import jetzt durchf&uuml;hren...</a><br>

        </p>

        </fieldset>\n";

	}

// ############################################################################

// /Step 1: Analyse



// Step 2: Einfuegen in DB

//#############################################################################

if($step==2)

	{

    // DATEI EINLESEN ******************************************************

    $dsNeu = 0;

    $handle = fopen ($outputImport,"r");

    while ( ($data = fgetcsv ($handle, 10000, "|")) !== FALSE )

        {

        // Daten aus DB holen

        // SQL-String bauen

        $sqlString = "SELECT ID FROM datenpool WHERE Vorname='".$data["1"]."' AND Nachname='".$data["2"]."'";

        // Ergebnis auslesen

        $ergebnis = $db -> sql($sqlString);

        if($ergebnis)

            {

            // Datensatz in DB noch nicht vorhanden

            if(mysql_num_rows($ergebnis)<"1")

                {

                // Notiz bauen

                $notizen = addslashes("Angelegt durch Datenimport aus FileMaker\n[".datetimemaker(time())."]\n\n");

                // DatenArray vorbereiten

                for($c=0;$c<count($data);$c++)

                    {if($data[$c]=="<BR>"){$data[$c]="";}}



                // SQL-String bauen

                $sqlString1 = "INSERT INTO datenpool (Neu,Titel,Vorname,Nachname,Firma,Strasse,PLZ,Ort,Land,TeleBuero,TelePrivat,TeleFax,TeleMobil,MailPrivat,Notizen,Erzeugt,Geaendert) VALUES ('1','".$data["0"]."','".$data["1"]."','".$data["2"]."','".$data["3"]."','".$data["4"]."','".$data["5"]."','".$data["6"]."','".$data["7"]."','".$data["9"]."','".$data["8"]."','".$data["10"]."','".$data["11"]."','".$data["12"]."','".$notizen."','".datetimemaker(time())."','".datetimemaker(time())."')";

                // Einlesen

                $ergebnis1 = $db -> sql($sqlString1);

                $dsNeu++;

                }

            }

        }

    fclose ($handle);

    // /DATEI EINLESEN ********************************************************

    

    // Ausgabe

    echo "<h3>Import</h3>\n";

    echo "<br><fieldset><legend>Import abgeschlossen</legend>

        <p>Es wurden <b>".$dsNeu." Datens&auml;tze</b> in den Datenpool eingef&uuml;gt und als \"Neu\" gekennzeichnet.</p>

        <p align=right>

        <a href=\"index.php?modus=DAT&inc=UEB\">Eingef&uuml;gte Datens&auml;tze ansehen...</a><br>

        </p>

        </fieldset>\n";

    // CSV-Datei loeschen

    unlink($outputImport);

	}

// ############################################################################

// /Step 2: Einfuegen in DB



// Step 3: Feldauswahl des Exports

//#############################################################################

if($step==3)

	{

?>



<h3>Export</h3>

<p>

<fieldset><legend>Export Felder</legend>



	 <form id="form1" name="form1" method="post" action="index.php?modus=DAT&inc=IMP&step=4">

   <table width="400" border="0" align="center" cellpadding="0" cellspacing="0">

   <tr><td colspan="5"><b>Markieren Sie alle Felder, die Sie exportieren m&ouml;chten:<br><br></b></td></tr>

    <tr>

      <td width="120">Anrede</td>

      <td width="60"><div align="right">

        <input name="Anrede" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">TeleBuero</td>

      <td width="60"><div align="right">

        <input name="TeleBuero" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>



    <tr>

      <td width="120">Titel</td>

      <td width="60"><div align="right">

        <input name="Titel" type="checkbox" value="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">TelePrivat</td>

      <td width="60"><div align="right">

        <input name="TelePrivat" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">Vorname</td>

      <td width="60"><div align="right">

        <input name="Vorname" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">TeleFax</td>

      <td width="60"><div align="right">

        <input name="TeleFax" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">Nachname</td>

      <td width="60"><div align="right">

        <input name="Nachname" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">TeleMobil</td>

      <td width="60"><div align="right">

        <input name="TeleMobil" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">Spitzname</td>

      <td width="60"><div align="right">

        <input name="Spitzname" type="checkbox" value="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">MailBuero</td>

      <td width="60"><div align="right">

        <input name="MailBuero" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">Firma</td>

      <td width="60"><div align="right">

        <input name="Firma" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">MailPrivat</td>

      <td width="60"><div align="right">

        <input name="MailPrivat" type="checkbox" value="checked" checked="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">Position</td>

      <td width="60"><div align="right">

        <input name="Position" type="checkbox" value="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">Netz</td>

      <td width="60"><div align="right">

        <input name="Netz" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">BueroStrasse</td>

      <td width="60"><div align="right">

        <input name="BueroStrasse" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">Geburt</td>

      <td width="60"><div align="right">

        <input name="Geburt" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">BueroPLZ</td>

      <td width="60"><div align="right">

        <input name="BueroPLZ" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">SkypeID</td>

      <td width="60"><div align="right">

        <input name="SkypeID" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">BueroOrt</td>

      <td width="60"><div align="right">

        <input name="BueroOrt" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">ICQ</td>

      <td width="60"><div align="right">

        <input name="ICQ" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">BueroBundesland</td>

      <td width="60"><div align="right">

        <input name="BueroBundesland" type="checkbox" value="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">KontoInhaber</td>

      <td width="60"><div align="right">

        <input name="KontoInhaber" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">BueroLand</td>

      <td width="60"><div align="right">

        <input name="BueroLand" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">KontoBank</td>

      <td width="60"><div align="right">

        <input name="KontoBank" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">PrivatStrasse</td>

      <td width="60"><div align="right">

        <input name="PrivatStrasse" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">KontoNummer</td>

      <td width="60"><div align="right">

        <input name="KontoNummer" type="checkbox" value="checked"/>

      </div></td>

    </tr>

    <tr>

      <td width="120">PrivatPLZ</td>

      <td width="60"><div align="right">

        <input name="PrivatPLZ" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">KontoBLZ</td>

      <td width="60"><div align="right">

        <input name="KontoBLZ" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">PrivatOrt</td>

      <td width="60"><div align="right">

        <input name="PrivatOrt" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">Klassen</td>

      <td width="60"><div align="right">

        <input name="Klassen" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">PrivatBundesland</td>

      <td width="60"><div align="right">

        <input name="PrivatBundesland" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">Notizen</td>

      <td width="60"><div align="right">

        <input name="Notizen" type="checkbox" value="checked" />

      </div></td>

    </tr>

    <tr>

      <td width="120">PrivatLand</td>

      <td width="60"><div align="right">

        <input name="PrivatLand" type="checkbox" value="checked" checked="checked" />

      </div></td>

      <td width="100">&nbsp;</td>

      <td width="120">&nbsp;</td>

      <td width="60"><div align="right">

        &nbsp;

      </div></td>

    </tr>

    <tr>

      <td colspan="5">&nbsp;</td>

     </tr>

    <tr>

      <td colspan="5"><div align="center">

        <label>

        <input type="submit" name="Submit" value="Exportieren" />

        </label>

      </div></td>

     </tr>



  </table>

</form>

</fieldset>



<?php

	}

// ############################################################################

// Step 3: Feldauswahl des Exports



// Step 4: Export der gewahlten Felder

//#############################################################################

if($step==4)

	{

	 $datum = date('Y-m-d');

	 $count = "1";	 

	 $type  = ".csv";

	 $feldeinfassung = "\"";

	 $feldtrenner   = ";";

	 $expFeldArray = array(

        "Anrede",

        "Titel",

        "Vorname",

        "Nachname",

        "Spitzname",

        "Firma",

        "Position",

        "BueroStrasse",

        "BueroPLZ",

        "BueroOrt",

        "BueroBundesland",

        "BueroLand",

        "PrivatStrasse",

        "PrivatPLZ",

        "PrivatOrt",

        "PrivatBundesland",

        "PrivatLand",

        "TeleBuero",

        "TelePrivat",

        "TeleFax",

        "TeleMobil",

        "MailBuero",

        "MailPrivat",

        "Netz",

        "Geburt",

        "SkypeID",

        "ICQ",

        "KontoInhaber",

        "KontoBank",

        "KontoNummer",

        "KontoBLZ",

        "Klassen",

        "Notizen");



	 while (file_exists($exportPath."export_".$datum."_".substr("0000",0,3-strlen($count)).$count.$type)) { $count++; }

	  

	 $filename = "export_".$datum."_".substr("0000",0,3-strlen($count)).$count.$type;

	 

 	 $handle = opendir($exportPath);

     while ($file = readdir ($handle)) 

	    {

	     if($file != "." && $file != "..")

	        {

             unlink($exportPath.$file);

		    }		    

        }

     closedir($handle);



     $handle = fopen ($exportPath.$filename,"w");



    // DATENBANK AUSLESEN ************************************************



    $sqlString = "SELECT * FROM "._KrakeDatenpool;

	$ergebnis = $db -> sql($sqlString);

 

    // Ergebnis schreiben *************************************************

    // Kopfzeile

    foreach($expFeldArray as $key => $item){if($$item=="checked"){$kopfArray[]=$feldeinfassung.$item.$feldeinfassung;}}

    $kopfzeile = implode($feldtrenner, $kopfArray);

	fwrite ($handle, $kopfzeile."\r\n");



    while($zeile=mysql_fetch_array($ergebnis))

        {

        foreach($expFeldArray as $key => $item){if($$item=="checked"){$expZeileArray[]=$feldeinfassung.$zeile[$item].$feldeinfassung;}}

        $expZeile = implode($feldtrenner, $expZeileArray);

        fwrite ($handle, $expZeile."\r\n");

        unset($expZeileArray);

        unset($expZeile);

        }

    // DATENBANK AUSLESEN ************************************************

    fclose ($handle);

?>	

<h3>Export</h3>

<p>

<fieldset>

<legend>Export Report</legend>

   <table width="400" border="0" align="center" cellpadding="0" cellspacing="0">

    <tr>

      <td>	  </td>

     </tr>

    <tr>

      <td>Die Daten wurden erfolgreich exportiert </td>

     </tr>

    <tr>

      <td>&nbsp;</td>

    </tr>

    <tr>

      <td><div align="center"><a href="index.php?modus=DAT&inc=IMP&step=0">Zur&uuml;ck zum Downloadbereich </a></div></td>

    </tr>

  </table>

</fieldset>



<?php	



    }

// ############################################################################

// Step 4: Export der gewahlten Felder



?>



<br><br>



</td>

</tr>



</table>



<!-- Content Import & Export -->