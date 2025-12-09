<?php

final class Rectangle
{
    public function __construct(
        private readonly int $topLeftX,
        private readonly int $topLeftY,
        private readonly int $bottomRightX,
        private readonly int $bottomRightY
    )
    {
        assert($this->topLeftX >= 0);
        assert($this->topLeftX <= $this->bottomRightX);
        assert($this->topLeftY >= 0);
        assert($this->topLeftY <= $this->bottomRightY);
    }

    public function __toString(): string
    {
        return sprintf(
            '[%3d, %3d, %3d, %3d]',
            $this->topLeftX,
            $this->topLeftY,
            $this->bottomRightX,
            $this->bottomRightY
        );
    }

    public function contains(int $x, int $y): bool
    {
        return $x >= $this->topLeftX
            && $x <= $this->bottomRightX
            && $y >= $this->topLeftY
            && $y <= $this->bottomRightY
        ;
    }
}