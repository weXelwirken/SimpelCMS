<html>
   <head><title>AutoComplete mit jQuery</title>
	<script type="text/javascript" src="suchjs/jquery.js"></script>
	<script type="text/javascript" src="suchjs/jquery.autocomplete.js"></script>
	      

    <style type="text/css">

    .ac_input {

            width: 200px;

    }

    .ac_results {

            width: 200px;
            background: #eee;

            cursor: pointer;

            position: absolute;

            left: 0;
            font-size: 90%;
            z-index: 101;

    }

    .ac_results ul {

            width: 200px;

            list-style: none;

            padding: 0px;

            margin: 0px;

            border: 1px solid #000;

    }

    .ac_results li {

            width: 190px;

            padding: 2px 5px;

    }

    .ac_results a {

            width: 100%;

    }

    /* thanks udoline: this fixed position error into msie */

    .ac_results iframe {

            width: 200px;

            position: absolute;

    }

    .ac_loading {

            background : url('/indicator.gif') right center no-repeat;

    }

    .over {

            background: yellow;

    }



</style></head>

 

<body>
    <p><input id="autocomplete" type="text"></p>

    <script type="text/javascript">

    function selectItem(li) {

            return false;

    }

    function formatItem(row) {

            return row[0] + "<i style='float:right; margin-right:5px'>" + row[1] + "</i>";

    }

    $(document).ready(function() {

            $("#autocomplete").autocomplete("autocpl.php", {

                    minChars:1,

                    matchSubset:1,

                    matchContains:1,

                    cacheLength:5,

                    onItemSelect:selectItem,

                    formatItem:formatItem,

                    selectOnly:1

            });

    });


</script>

</div>

</body>

</html>