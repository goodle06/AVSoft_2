#pragma once
#include "../Common.h"

class Composite;
class Component;

template <class Child>
ptr<Child> Find(std::string name, ptr<Component> head);


class Component {
public:
	Component(std::string name);
	virtual ~Component() {}

	void SetParent(Component* parent) { m_parent = parent; }
	Component* GetParent() const { return m_parent; }

	virtual void AddComponent(ptr<Component> item) {};
	virtual void RemoveComponent(ptr<Component> item) {};

	virtual void SetName(std::string name);
	virtual std::string GetName() const { return m_name; }

	virtual Composite* GetComposite() { return nullptr; }
	
	template <class Child>
	friend ptr<Child> Find(std::string name, ptr<Component> head);
	//ptr<Child> Find(std::string name);
	virtual void Print(int tabs=0);

protected:
	Component* m_parent = nullptr;

private:
	std::string m_name;
};



template <class Child>
ptr<Child> Find(std::string name, ptr<Component> head) {

	if (std::dynamic_pointer_cast<Child>(head)) {
		if (head->GetName() == name)
			return std::static_pointer_cast<Child>(head);
	}

	if (head->GetComposite()) {
		ptr<Composite> comp = std::static_pointer_cast<Composite>(head);
		auto iter = comp->m_components.begin();
		auto iter_end = comp->m_components.end();
		for (; iter != iter_end; ++iter) {
			ptr<Child> res = Find<Child>(name, *iter);
			if (res) return res;
		}
	}

	return nullptr;
}