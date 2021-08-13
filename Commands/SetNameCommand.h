#pragma once

#include "../Common.h"
#include "../CorporateStructure.h"
#include "../Employee.h"
#include "../Patterns/Command.h"

class SetNameCommand : public Command {
	ptr<Component> m_where=nullptr;
	std::string m_old_name;
	std::string m_new_name;
public:
	SetNameCommand(ptr<Component> where_to, std::string name);
	void Execute() override { m_old_name = m_where->GetName(); m_where->SetName(m_new_name); }
	void Undo() override { m_where->SetName(m_old_name); }
	void Redo() override { Execute(); }
};

SetNameCommand::SetNameCommand(ptr<Component> where_to, std::string name) {
	if (!where_to)
		throw std::runtime_error("Nullptr component was passed to SetNameCommand constructor");
	m_where = where_to;
	m_new_name = name;
}