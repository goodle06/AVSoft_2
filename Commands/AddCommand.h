#pragma once

#include "../Common.h"
#include "../CorporateStructure.h"
#include "../Employee.h"
#include "../Patterns/Command.h"

class AddCommand : public Command {
	ptr<Component> m_what=nullptr;
	ptr<Component> m_where=nullptr;
public:
	AddCommand(ptr<Component> what, ptr<Component> where_to);
	void Execute() override { m_where->AddComponent(m_what); }
	void Undo() override { m_where->RemoveComponent(m_what); }
	void Redo() override { Execute(); }
};

AddCommand::AddCommand(ptr<Component> what, ptr<Component> where_to) {
	if (!what)
		throw std::runtime_error("Trying to create Add command on empty 'what' object");
	if (!where_to)
		throw std::runtime_error("Trying to create Add commant on empty target Composite");
	m_what=what; m_where=where_to;
}