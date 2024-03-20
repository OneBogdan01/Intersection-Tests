#pragma once
struct Cell
{
	int x;
	int y;
	int z;
	Cell(int x, int y, int z) : x(x), y(y), z(z) {}
	Cell() : x(0), y(0), z(0) {}
	bool operator==(const Cell& other) const
	{
		return x == other.x && y == other.y && z == other.z;
	}
	bool operator!=(const Cell& other) const
	{
		return !(*this == other);
	}
};