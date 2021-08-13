#pragma once

#include "Patterns/Composite.h"
#include "Employee.h"


class CorporateStructure final : public Composite {
public:


	using Composite::Composite;

	int GetHeadCount() const;
	float GetAverageWage() const;
};