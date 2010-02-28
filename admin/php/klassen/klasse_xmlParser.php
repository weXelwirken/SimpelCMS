<?php

/*****************************************************

SEB'S XML PARSER v0.1a
----------------------

written by Sebastian Bechtold
contact: sebastian_bechtold@web.de

*****************************************************/

class XML_document
{
function callback_openElement($parser, $name, $attributes)

// ########  called by start element event handler to add new elements to xml data and update stack ########
{
$element = & $this->XMLdata;	// start at root...

foreach($this->XMLstack as $stack_element)	// ...and jump up to the current element guided by stack information
{
$element = & $element[$stack_element][count($element[$stack_element]) - 1];
}

        $element[$name][]['ATTRS'] = $attributes;	// create element by applying attributes to it

array_push($this->XMLstack, $name);	// finally, add element name to stack
}


function callback_closeElement($parser, $name)

// ########  called by end element event handler to remove last element from stack ########
{
array_pop($this->XMLstack);			
}


function callback_cdata($parser, $cdata)

// ########  called by cdata element event handler to apply current cdata to current element ########
{
$element = & $this->XMLdata;	// start at root...
    
    foreach($this->XMLstack as $stack_element)	// ...and jump up to the current element guided by stack information
{
            $element = & $element[$stack_element][count($element[$stack_element])-1];
        }

        $element['CDATA'] .= $cdata;	// apply cdata to current element
}


function XML_document($file)

// ########  create parser instance, open and parse xml document ########
{
if (!($fp = fopen($file, 'r')))
{
die("could not open XML file");
}

$this->XMLdata = array();
$this->XMLstack = array();

$this->parser = xml_parser_create();

xml_set_object($this->parser, & $this);
xml_set_element_handler($this->parser, 'callback_openElement', 'callback_closeElement');
xml_set_character_data_handler($this->parser, 'callback_cdata');

while ($data = fread($fp, 4096))
{
if (!xml_parse($this->parser, $data, feof($fp))) 
{
die(sprintf("XML error: %s at line %d", xml_error_string(xml_get_error_code($this->parser)), xml_get_current_line_number($this->parser)));
}
}

fclose($fp);
xml_parser_free($this->parser);
}
}

?>