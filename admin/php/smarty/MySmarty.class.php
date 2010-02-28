<?php
define("ROOT", $ServerRoot."/admin/php/smarty/");

require(ROOT.'libs/Smarty.class.php');
class MySmarty extends Smarty
    {
    function MySmarty()
        {
        $this->Smarty();
        $this->template_dir=ROOT.'templates/';
        $this->config_dir=ROOT.'configs/';
        $this->compile_dir=ROOT.'templates_c/';
        $this->cache_dir=ROOT.'cache/';
        }
    }
?>
