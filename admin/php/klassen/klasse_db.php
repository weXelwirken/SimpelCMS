<?php

// Db
class Db
	{
	var $connid;
	var $ergebnis;
	
	function db($dbHost,$dbUser,$dbPasswort)
		{
		if(!$this->connid = mysql_connect($dbHost, $dbUser, $dbPasswort))
			{
			echo "Fehler beim Verbinden...<br>\n";
			}
		return $this->connid;
		}
	
	function select_db($db)
		{
		if (!mysql_select_db($db, $this->connid))
			{
			echo "Fehler beim Auswählen der DB...<br>\n";
			}
		}

	function sql($sql)
		{
		if (!$this->ergebnis = mysql_query($sql, $this->connid))
			{
			echo "Fehler beim Senden der Abfrage...<br>\n";
			}
		return $this->ergebnis;
		}
	}	

?>