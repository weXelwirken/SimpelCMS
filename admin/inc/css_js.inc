<!-- CSS & JS -->
<link href="<?php echo $CssPfadAdmin; ?>" rel="stylesheet">
<link rel="shortcut icon" href="img/scmsIcons_scms.ico">

<script language="javascript" type="text/javascript" src="jscripts/menuBar.js"></script>
<script language="javascript" type="text/javascript" src="jscripts/tinymce/jscripts/tiny_mce/tiny_mce.js"></script>
<script language="javascript" type="text/javascript">

// TinyMCE-Editor ###############################################################################

tinyMCE.init({
    language : "de",
	mode : "specific_textareas",
	editor_selector : "mceEditor",
	theme : "advanced",
	plugins : "table,style,advlink,contextmenu,paste,directionality,fullscreen,noneditable,visualchars,nonbreaking,xhtmlxtras,advimage",
    theme_advanced_buttons1 : "formatselect,styleselect,pastetext,styleprops,|,bold,italic,underline,|,justifyleft,justifycenter,justifyright,justifyfull",
	theme_advanced_buttons2 : "forecolor,backcolor,|,outdent,indent,|,bullist,numlist,|,link,unlink,fullscreen,code,image",
	theme_advanced_buttons3 : "tablecontrols,|,charmap",
	theme_advanced_toolbar_location : "top",
	theme_advanced_toolbar_align : "left",
	extended_valid_elements : "a[name|href|target|title|onclick|rel|onmouseover|onmouseout],embed[allowfullscreen|flashvars|menu|src|style|type],fieldset,font[face|size|color|style],span[class|align|style],hr[class|width|size|noshade],img[class|src|border=0|alt|title|hspace|vspace|width|height|align|onmouseover|onmouseout|name],legend,object[style],param[name|value]",
    content_css : "<?php echo $CssPfadJs; ?>"

});


// Klapp-Funktion #################################################################################
function Show_Stuff(id)
{
    var content = document.getElementById(id);
    var contentOff = document.getElementById(id+"Off")
    var contentOn = document.getElementById(id+"On");
    if (content.style.display == "none")
    {
        content.style.display = "";
        contentOn.style.display = "";
        contentOff.style.display = "none";
    }
    else
    {
        content.style.display = "none";
        contentOn.style.display = "none";
        contentOff.style.display = "";
    }
}

// Ladebalken ####################################################################################
function loading_box(res)
    {
    var box = document.getElementById(res);
    if (box.style.display == "none") {
      box.style.display = "";
    } else {
      box.style.display = "none";
    }
    }

function no_loading_box(res)
    {
    var box = document.getElementById(res);
    box.style.display = "none";
    }

</script>


<!-- /CSS & JS -->