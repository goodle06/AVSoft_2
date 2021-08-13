#include "CorporateStructure.h"


int CorporateStructure::GetHeadCount() const {
	int heads = 0;
	for (auto c : m_components) {
		if (dynamic_cast<Employee*>(&(*c)))
			heads++;
	}
	return heads;
}

float CorporateStructure::GetAverageWage() const {
	int heads = GetHeadCount();
	if (heads == 0) return 0.0f; //null check
	int wage = 0;
	for (auto c : m_components) {
		Employee* mc = dynamic_cast<Employee*>(&(*c));
		if (mc) {
			wage += mc->GetWage();
		}
	}
	return wage / float(heads);
}