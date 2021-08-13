#include "Employee.h"


void Employee::Print(int tabs) {
	Component::Print(tabs);
	std::cout << ", " << GetPosition() << ", " << GetWage();

}

void Employee::SetWage(int new_wage) {
	if (new_wage < 0)
		throw std::runtime_error("Wage cannot be less than zero");
	m_wage = new_wage;
}

void Employee::SetPosition(std::string new_pos) {
	m_position = new_pos;
}