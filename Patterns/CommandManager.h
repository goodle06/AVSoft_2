#pragma once

#include "../Common.h"
#include "Component.h"
#include "Command.h"

class CommandManager {
	std::stack<ptr<Command>> m_undo;
	std::stack<ptr<Command>> m_redo;
public:
	CommandManager() {}

	void Execute(ptr<Command> cmd) {
		if (!cmd)
			throw std::runtime_error("Empty command object\n");
		m_redo = {};
		cmd->Execute();
		m_undo.push(cmd);
	}

	void Undo() {
		if (!m_undo.empty()) {
			m_undo.top()->Undo();
			m_redo.push(m_undo.top());
			m_undo.pop();
		}
	}

	void Redo() {
		if (!m_redo.empty()) {
			m_redo.top()->Redo();
			m_undo.push(m_redo.top());
			m_redo.pop();
		}
	}

};