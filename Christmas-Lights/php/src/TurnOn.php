<?php

final class TurnOn extends ModifiedLightGrid
{
    protected function getBrightness(int $x, int $y): int
    {
        $brightness = parent::getBrightness($x, $y);
        $turnedOn = $this->isSelected($x, $y);

        if ($turnedOn) {
            ++$brightness;
        }

        return $brightness;
    }

    protected function getModification(): string
    {
        return "turned on";
    }

    protected function isOn(int $x, int $y): bool
    {
        if (parent::isOn($x, $y)) {
            return true;
        }

        return $this->isSelected($x, $y);
    }
}
