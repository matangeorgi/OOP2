#pragma once

#include "UnPickable.h"

class Floor : public UnPickable
{
public:
	Floor(int row, int col);
	~Floor();
private:
};