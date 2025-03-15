<?php
require_once('inc/bootstrap.php');

$view = $_default_view;

if (isset($_REQUEST['view'])
    && !empty($_REQUEST['view'])
    && file_exists('views/' . $_REQUEST['view'] . '.php'))
{
    $view = $_REQUEST['view'];
}

require_once('views/' . $view . '.php');
?>
