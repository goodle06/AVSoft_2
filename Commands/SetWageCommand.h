#pragma once


#include "../Common.h"
#include "../CorporateStructure.h"
#include "../Employee.h"
#include "../Patterns/Command.h"

class SetWageCommand : public Command {
	ptr<Employee> m_where=nullptr;
	int m_old_wage=0;
	int m_new_wage=0;
public:
	SetWageCommand(ptr<Employee> where_to, int wage);
	void Execute() override { m_old_wage = m_where->GetWage(); m_where->SetWage(m_new_wage); }
	void Undo() override { 
		m_where->SetWage(m_old_wage); 
	}
	void Redo() override { 
		Execute(); 
	}
};

SetWageCommand::SetWageCommand(ptr<Employee> where_to, int wage) {
	if (!where_to)
		throw std::runtime_error("Nullptr component was passed to constructor");
	m_where = where_to;
	m_new_wage = wage;

}