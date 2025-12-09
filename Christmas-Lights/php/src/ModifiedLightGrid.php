<?php

abstract class ModifiedLightGrid extends LightGrid
{
    final protected function __construct(
        private readonly LightGrid $original,
        private readonly Rectangle $selection,
    ) {
        parent::__construct($this->original->width, $this->original->height);
    }

    final public function __toString(): string
    {
        return sprintf(
            "%s\n\t|-%-10s %s",
            $this->original,
            $this->getModification(),
            $this->selection
        );
    }


    protected function getBrightness(int $x, int $y): int
    {
        return $this->original->getBrightness($x, $y);
    }

    abstract protected function getModification(): string;

    final protected function isSelected(int $x, int $y): bool
    {
        return $this->selection->contains($x, $y);
    }

    protected function isOn(int $x, int $y): bool
    {
        return $this->original->isOn($x, $y);
    }
}