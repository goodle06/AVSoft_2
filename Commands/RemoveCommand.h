#pragma once


#include "../Common.h"
#include "../CorporateStructure.h"
#include "../Employee.h"
#include "../Patterns/Command.h"

class RemoveCommand : public Command {
	ptr<Component> m_what=nullptr;
	Component* m_where=nullptr;
public:
	RemoveCommand(ptr<Component> what);
	void Execute() override { m_where->RemoveComponent(m_what); }
	void Undo() override { m_where->AddComponent(m_what); }
	void Redo() override { Execute(); }
};

RemoveCommand::RemoveCommand(ptr<Component> what) {
	if (!what)
		throw std::runtime_error("Trying to pass empty object to RemoveCommand constructor");
	if (!what->GetParent())
		throw std::runtime_error("Trying to pass object with no parent to RemoveCommand constructor");

	m_what = what; m_where = what->GetParent();
}