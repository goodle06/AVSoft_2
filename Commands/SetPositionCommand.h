#pragma once


#include "../Common.h"
#include "../CorporateStructure.h"
#include "../Employee.h"
#include "../Patterns/Command.h"

class SetPositionCommand : public Command {
	ptr<Employee> m_where=nullptr;
	std::string m_old_position;
	std::string m_new_position;
public:
	SetPositionCommand(ptr<Employee> where_to, std::string position);
	void Execute() override { m_old_position = m_where->GetPosition(); m_where->SetPosition(m_new_position); }
	void Undo() override { m_where->SetPosition(m_old_position);}
	void Redo() override { Execute(); }
};

SetPositionCommand::SetPositionCommand(ptr<Employee> where_to, std::string position) {

	if (!where_to)
		throw std::runtime_error("Nullptr component was passed to constructor");
	m_where = where_to;
	m_new_position = position;
}