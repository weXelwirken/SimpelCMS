<!-- ---------------------------------------------------- -->
<!-- JavaScript                                           -->
<!-- ---------------------------------------------------- -->

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

// Klapp-Menue #####################################################################################
function ShowMenu(Layer_Name)
{
  var GECKO = document.getElementById? 1:0 ;
  var NS = document.layers? 1:0 ;
  var IE = document.all? 1:0 ;

  if (GECKO)
       {document.getElementById(Layer_Name).style.display=
	   (document.getElementById(Layer_Name).style.display=='block') ? 'none' : 'block';}
  else if (NS)
       {document.layers[Layer_Name].display=(document.layers[Layer_Name].display==
	   'block') ? 'none' : 'block';}
  else if (IE)
       {document.all[Layer_Name].style.display=(document.all[Layer_Name].style.display==
	   'block') ? 'none' : 'block';}
}

// Blend-Effekte ###################################################################################
function opacity(id, opacStart, opacEnd, millisec) { 
    //speed for each frame 
    var speed = Math.round(millisec / 100); 
    var timer = 0; 

    //determine the direction for the blending, if start and end are the same nothing happens 
    if(opacStart > opacEnd) { 
        for(i = opacStart; i >= opacEnd; i--) { 
            setTimeout("changeOpac(" + i + ",'" + id + "')",(timer * speed)); 
            timer++; 
        }   
    } else if(opacStart < opacEnd) { 
        for(i = opacStart; i <= opacEnd; i++) 
            { 
            setTimeout("changeOpac(" + i + ",'" + id + "')",(timer * speed)); 
            timer++; 
        } 
    } 
} 

function changeOpac(opacity, id) { 
    //change the opacity for different browsers 
    var object = document.getElementById(id).style; 
    object.opacity = (opacity / 100); 
    object.MozOpacity = (opacity / 100); 
    object.KhtmlOpacity = (opacity / 100); 
    object.filter = "alpha(opacity=" + opacity + ")"; 
}