#pragma once

#include "Patterns/Composite.h"

 class Employee final : public Component {
 public:
	 using Component::Component;

	 void AddComponent(ptr<Component> component) override { throw std::runtime_error("Employee is not a composite object");}
	 void RemoveComponent(ptr<Component> component) override { throw std::runtime_error("Employee is not a composite object"); }

	 void SetWage(int wage);
	 void SetPosition(std::string position);
	 int GetWage() const { return m_wage; }
	 std::string GetPosition() const { return m_position; }

	 void Print(int tabs) override;
 private:
	 int m_wage = 0;
	 std::string m_position;
};