<?php

abstract class LightGrid
{
    final public static function start(int $width, int $height): LightGrid
    {
        return new EmptyGrid($width, $height);
    }

    protected function __construct(
        protected readonly int $width,
        protected readonly int $height
    )
    {
    }

    public function __toString(): string
    {
        return sprintf('%s [%d, %d]', get_class($this), $this->width, $this->height);
    }


    abstract protected function getBrightness(int $x, int $y): int;

    abstract protected function isOn(int $x, int $y): bool;

    final public function showSummary(): void
    {
        echo "$this\n";
        $this->showCountLightsOn();
        echo ' | ';
        $this->showSumBrightness();
        echo "\n";
    }

    private function showCountLightsOn(): void
    {
        $count = 0;
        for ($x = 0; $x <= $this->width; ++$x) {
            for ($y = 0; $y <= $this->height; ++$y) {
                if ($this->isOn($x, $y)) {
                    ++$count;
                }
            }
        }

        printf("lights on: %7d", $count);
    }

    private function showSumBrightness(): void
    {
        $brightness = 0;
        for ($x = 0; $x <= $this->width; ++$x) {
            for ($y = 0; $y <= $this->height; ++$y) {
                $brightness += $this->getBrightness($x, $y);
            }
        }

        printf("total brightness: %12d", $brightness);
    }

    final public function toggle(Rectangle $selection): LightGrid
    {
        return new Toggle($this, $selection);
    }

    final public function turnOff(Rectangle $selection): LightGrid
    {
        return new TurnOff($this, $selection);
    }

    final public function turnOn(Rectangle $selection): LightGrid
    {
        return new TurnOn($this, $selection);
    }
}