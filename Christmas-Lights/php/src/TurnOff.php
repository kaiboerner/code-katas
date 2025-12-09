<?php

final class TurnOff extends ModifiedLightGrid
{
    protected function getBrightness(int $x, int $y): int
    {
        $brightness = parent::getBrightness($x, $y);
        $turnedOff = $this->isSelected($x, $y);

        if ($turnedOff) {
            $brightness = max(0, $brightness - 1);
        }

        return $brightness;
    }

    protected function getModification(): string
    {
        return "turned off";
    }

    protected function isOn(int $x, int $y): bool
    {
        if ($this->isSelected($x, $y)) {
            return false;
        }

        return parent::isOn($x, $y);
    }
}
