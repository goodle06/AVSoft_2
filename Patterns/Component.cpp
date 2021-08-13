#include "Component.h"


Component::Component(std::string name)  {
	SetName(name);
}

void Component::SetName(std::string name) {
	if (name.empty())
		throw std::runtime_error("Name can't be empty");
	m_name = name;
}

void Component::Print(int tabs) {

	std::cout << "\n";
	for (int i = 0; i < tabs; i++) std::cout << "\t";
	std::cout << GetName();
}