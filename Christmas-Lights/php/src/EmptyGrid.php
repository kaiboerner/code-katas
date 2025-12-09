<?php

final class EmptyGrid extends LightGrid
{
    protected function getBrightness(int $x, int $y): int
    {
        return 0;
    }

    protected function isOn(int $x, int $y): bool
    {
        return false;
    }
}