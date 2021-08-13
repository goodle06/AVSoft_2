#pragma once

#include "../Common.h"


class Command {
public:
	virtual void Execute() = 0 ;
	virtual void Undo() = 0;
	virtual void Redo() = 0;
};