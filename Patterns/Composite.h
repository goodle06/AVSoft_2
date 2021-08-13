#pragma once
#include "Component.h"


class Composite : public Component {

protected:
	template <class Child>
	friend ptr<Child> Find(std::string name, ptr<Component> head);

	std::vector<ptr<Component>> m_components;
public:
	virtual ~Composite() {}
	using Component::Component;

	void AddComponent(ptr<Component> component) override;
	void RemoveComponent(ptr<Component> component) override;
	virtual Composite* GetComposite() override;
	virtual void Print(int tabs=0) override;

	friend class Component;
};


