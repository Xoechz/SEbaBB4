<?php
declare(strict_types=1);

error_reporting(E_ALL);
ini_set('display_errors', 1);

// define default view
$default_view = 'welcome';

spl_autoload_register(function (string $class) {
   $filename = __DIR__ . '/../lib/' . str_replace('\\', DIRECTORY_SEPARATOR, $class) . '.php';
   if (file_exists($filename)) {
       require_once $filename;
   }
});

$dbmode = 'mock';
switch ($dbmode) {

    case 'pdo':
        $class = 'mysqlpdo';
        break;
    default:
        $class = 'mock';
        break;
}

require_once (__DIR__ . '/../lib/Data/DataManager_' . $class . '.php');