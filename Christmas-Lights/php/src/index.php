<?php

spl_autoload_register(function (string $class): bool {
    if (file_exists($file = __DIR__."/$class.php")) {
        require_once $file;

        return true;
    }

    return false;
});

$startGrid = LightGrid::start(999, 999);

$startGrid
    ->turnOn(new Rectangle(   0,   0, 999, 999))
    ->toggle(new Rectangle(   0,   0, 999,   0))
    ->turnOff(new Rectangle(499, 499, 500, 500))
    ->showSummary()
;

echo "==========\n";

$startGrid
    ->turnOn(new Rectangle(0, 0,   0,   0))
    ->toggle(new Rectangle(0, 0, 999, 999))
    ->showSummary()
;

echo "==========\n";

$startGrid
    ->turnOn(new Rectangle( 887,   9, 959, 629))
    ->turnOn(new Rectangle( 454, 398, 844, 448))
    ->turnOff(new Rectangle(539, 243, 559, 965))
    ->turnOff(new Rectangle(370, 819, 676, 868))
    ->turnOff(new Rectangle(145,  40, 370, 997))
    ->turnOff(new Rectangle(301,   3, 808, 453))
    ->turnOn(new Rectangle( 351, 678, 951, 908))
    ->toggle(new Rectangle( 720, 196, 897, 994))
    ->toggle(new Rectangle( 831, 394, 904, 860))
    ->showSummary()
;
