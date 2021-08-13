#include "Composite.h"


void Composite::AddComponent(ptr<Component> component) { 
	if (!component)
		throw std::runtime_error("Trying to add empty component to the composite");

	component->SetParent(this);
	m_components.push_back(component); 
}
void Composite::RemoveComponent(ptr<Component> component)  { 
	if (!component)
		throw std::runtime_error("Trying to remove empty component from the composite");
	auto iter = std::find(m_components.begin(), m_components.end(), component);
	(*iter)->SetParent(nullptr);
	m_components.erase(iter); 
}
Composite* Composite::GetComposite() {
	return this; 
}
void Composite::Print(int tabs) {
	Component::Print(tabs);
	tabs++;
	for (auto c : m_components)
		c->Print(tabs);
}