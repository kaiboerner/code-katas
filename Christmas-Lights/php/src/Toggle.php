<?php

final class Toggle extends ModifiedLightGrid
{
    protected function isOn(int $x, int $y): bool
    {
        $originalIsOn = parent::isOn($x, $y);
        $isToggled = $this->isSelected($x, $y);

        return $isToggled ? !$originalIsOn : $originalIsOn;
    }

    protected function getBrightness(int $x, int $y): int
    {
        $brightness = parent::getBrightness($x, $y);
        $isToggled = $this->isSelected($x, $y);

        if ($isToggled) {
            $brightness += 2;
        }

        return  $brightness;
    }

    protected function getModification(): string
    {
        return "toggled";
    }
}