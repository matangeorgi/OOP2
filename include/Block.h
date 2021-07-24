#pragma once

#include "UnPickable.h"

class Block : public UnPickable
{
public:
	Block(int row, int col);

	~Block();
private:

};