<html xmlns="http://www.w3.org/1999/xhtml">
  <head>
    <style type="text/css">
#map {
        width: 100%;
        height: 100%;
        border: 0px;
        padding: 0px;
        position: absolute;
     }
body {
        border: 0px;
        margin: 0px;
        padding: 0px;
        height: 100%;
     }
    </style>
    <script src="http://www.openlayers.org/api/OpenLayers.js"></script>
    <script src="http://www.openstreetmap.org/openlayers/OpenStreetMap.js"></script>
    <script type="text/javascript">
        <!--
        var map;
 
        function init(){
            map = new OpenLayers.Map('map',
                    { maxExtent: new OpenLayers.Bounds(-20037508.34,-20037508.34,20037508.34,20037508.34),
                      numZoomLevels: 19,
                      maxResolution: 156543.0399,
                      units: 'm',
                      projection: new OpenLayers.Projection("EPSG:900913"),
                      displayProjection: new OpenLayers.Projection("EPSG:4326")
                    });
 
            var layerMapnik = new OpenLayers.Layer.OSM.Mapnik("Mapnik (updated weekly)");
 
            var layerTah = new OpenLayers.Layer.OSM.Osmarender("Tiles@Home");
 
            map.addLayers([layerMapnik,layerTah]);
 
            var pois = new OpenLayers.Layer.Text( "My Points", { location:"./textfile.txt", projection: new OpenLayers.Projection("EPSG:4326")} );
            map.addLayer(pois);
 
            map.addControl(new OpenLayers.Control.LayerSwitcher());
 
            map.setCenter(new OpenLayers.LonLat(7.581,47.564).transform(new OpenLayers.Projection("EPSG:4326"), new OpenLayers.Projection("EPSG:900913")), 12);
        }
        // -->
    </script>
  </head>
  <body onload="init()">
    <div id="map"></div>
  </body>
</html>