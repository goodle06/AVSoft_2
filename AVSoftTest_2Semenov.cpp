// AVSoftTest_2Semenov.cpp : Defines the entry point for the application.
//


#include "CorporateStructure.h"
#include "Employee.h"
#include "3rdparty/tinyxml2.h"
#include "Commands/AllCommands.h"
#include "Patterns/CommandManager.h"

#include <Windows.h>
#define MAX_INPUT_LENGTH 255

void XMLtoComposite(std::string filename, ptr<CorporateStructure> head);
void FishEmployees(ptr<Component> structure, const tinyxml2::XMLElement* department);
ptr<Command> ConsoleInCommand(std::string cinput, ptr<Component> company, CommandManager& mgr);

//Cyrillic input, Windows dependent
std::string UTFconsole();


int main()
{
	CommandManager mgr;
	ptr<Component> Company { new CorporateStructure("AVSoft") };
	std::string filepath;
	std::cout << "Enter filepath to xml file:\n";
	std::getline(std::cin,filepath);

	try {
		XMLtoComposite(filepath, std::static_pointer_cast<CorporateStructure>(Company));
	}
	catch (std::runtime_error& e) {
		std::cout << "ERROR: " << e.what() << std::endl;
	}

	std::string cmd;
	while (cmd != "quit") {
		std::cout << "Enter command...(type 'help' for the list of commands)" << std::endl;
		std::getline(std::cin, cmd);
		try {
			ptr<Command> command = ConsoleInCommand(cmd, Company, mgr);
			if (command) 
				mgr.Execute(command);
		}
		catch (const std::runtime_error& e) {
			std::cout << "ERROR: " << e.what() << "\n";
		}
	}
	return 0;
}


void XMLtoComposite(std::string filename, ptr<CorporateStructure> head) {

	tinyxml2::XMLDocument doc;
	if (doc.LoadFile(filename.c_str()) != tinyxml2::XML_SUCCESS)
		throw std::runtime_error("Couldn't open xml file");

	if (!doc.FirstChild())
		throw std::runtime_error("File is empty or corrupted");

	const tinyxml2::XMLElement* XMLdepartment = doc.FirstChildElement("departments")->FirstChildElement("department");

	while (XMLdepartment) {
		auto department_name= XMLdepartment->FindAttribute("name")->Value();
		if (department_name) {
			ptr<Component> Department{ new CorporateStructure(department_name) };
			head->AddComponent(Department);
			FishEmployees(Department, XMLdepartment);
		}
		else {
			std::cout << "Department name not found\n";
		}
		XMLdepartment = XMLdepartment->NextSiblingElement();
	}
}

void FishEmployees(ptr<Component> structure, const tinyxml2::XMLElement* department) {
	auto employee = department->FirstChildElement("employments")->FirstChildElement("employment");

	while (employee) {
		auto a = employee->FirstChildElement("surname");
		auto b = employee->FirstChildElement("name");
		auto c = employee->FirstChildElement("middleName");
		auto d = employee->FirstChildElement("function");
		auto e= employee->FirstChildElement("salary");

		if (a && b && c && d && e) {
			std::string fio = a->GetText();
			fio += " ";
			fio += b->GetText();
			fio += " ";
			fio += c->GetText();
			std::string position = d->GetText();
			std::string wage =e->GetText();

			ptr<Employee> buff_empl{ new Employee(fio) };
			buff_empl->SetPosition(position);
			buff_empl->SetWage(std::stoi(wage));
			structure->AddComponent(buff_empl);
		}
		else {
			std::cout << "Incomplete employee data (file is still loaded, tree is set, employee in question is removed from the tree)\n";
		}
		employee=employee->NextSiblingElement();
	}
}


ptr<Command> ConsoleInCommand(std::string cinput, ptr<Component> company, CommandManager& mgr) {

	if (cinput == "help") {
		std::cout << "Commands:\n"
			<< "add <e>/<d>" << std::endl
			<< "remove" << std::endl
			<< "heads" << std::endl
			<< "awage" << std::endl
			<< "setwage" << std::endl
			<< "setposition" << std::endl
			<< "setname" << std::endl
			<< "print" << std::endl
			<< "undo" << std::endl
			<< "redo" << std::endl;
		return nullptr;
	}
	if (cinput == "undo")
		mgr.Undo();
	if (cinput == "redo")
		mgr.Redo();

	std::vector<std::string> tokens;
	std::istringstream stream(cinput);
	std::copy(std::istream_iterator<std::string>(stream), std::istream_iterator<std::string>(), std::back_inserter(tokens));

	std::string strcmd = tokens[0];
	std::string in;
	ptr<Command> cmd = nullptr;

	/*Add component command*/
	if (strcmd == "add") {
		ptr<Component> new_component = nullptr;
		if (tokens.size() != 2) {
			std::cout << "ERROR: invalid number of parameters, please refer to help\n";
			return nullptr;
		}
		if (!(tokens[1] == "e" || tokens[1] == "d")) {
			std::cout << "ERROR: invalid parameter, enter 'e' for employee or 'd' for department\n";
			return nullptr;
		}

		std::cout << "Enter name of the new element:\n";
		in = UTFconsole();

		std::string name = in;
		std::cout << "Enter name of the department where new element will be inserted\n";
		in = UTFconsole();
		ptr<Component> department = Find<CorporateStructure>(in, company);
		try {
			if (tokens[1] == "e")
				new_component =ptr<Component>(new Employee(name));
			else if (tokens[1] == "d")
				new_component = ptr<Component>(new CorporateStructure(name));
			if (new_component)
				return cmd =ptr<Command>(new AddCommand(new_component, department));
		}
		catch (const std::runtime_error& e) {
			std::cout << "ERROR: " << e.what() << "\n";
		}

	}

	/*Remove component command*/
	else if (strcmd == "remove") {
		std::cout << "Enter name of the element for removal:\n";
		in = UTFconsole();
		ptr<Component> comp = Find<Component>(in, company);
			return cmd = ptr<Command>( new RemoveCommand(comp));
	}

	/*Count number of employees in particular structure*/
	else if (strcmd == "heads") {
		std::cout << "Enter name of the department:\n";
		in = UTFconsole();

		ptr<CorporateStructure> comp = Find<CorporateStructure>(in, company);
		if (comp)
			std::cout << comp->GetHeadCount() << std::endl;
		else
			std::cout << "ERROR: no such department\n";
		return nullptr;
	}

	/*Calculate average wage of the department*/
	else if (strcmd == "awage") {
		std::cout << "Enter name of the department:\n";
		in = UTFconsole();
		ptr<CorporateStructure> comp = Find<CorporateStructure>(in, company);
		if (comp)
			std::cout << comp->GetAverageWage() << std::endl;
		else
			std::cout << "ERROR: no such department\n";
		return nullptr;
	}

	/*Set wage for employee*/
	else if (strcmd == "setwage") {
		std::cout << "Enter name of the employee:\n";
		std::getline(std::cin, in);
		ptr<Employee> comp = Find<Employee>(in, company);

		std::cout << "Enter new wage number\n";
		in = UTFconsole();
		int wage = 0;
		try {
			wage = std::stoi(in);
			return ptr<Command>(new SetWageCommand(comp, wage));
		}
		catch (const std::exception& e)	{
			std::cout << "ERROR: " << e.what() << "\n";
		}
	}

	/*Set position for employee*/
	else if (strcmd == "setposition") {
		std::cout << "Enter name of the employee:\n";
		in = UTFconsole();
		//std::getline(std::cin, in);
		ptr<Employee> comp = Find<Employee>(in, company);

		std::cout << "Enter new position\n";
		in = UTFconsole();
		return ptr<Command>(new SetPositionCommand(comp, in));
	}

	/*Set name of component*/
	else if (strcmd == "setname") {
		std::cout << "Enter name of the component:\n";
		in = UTFconsole();
		ptr<Component> comp = Find<Component>(in, company);

		std::cout << "Enter new name\n";
		in = UTFconsole();
		return ptr<Command>(new SetNameCommand(comp, in));
	}

	/*prins tree*/
	else if (strcmd == "print") {
		company->Print();
		std::cout << "\n";
	}
	return nullptr;

};

std::string UTFconsole() {
	SetConsoleCP(1251);
	wchar_t wstr[MAX_INPUT_LENGTH];
	char mb_str[MAX_INPUT_LENGTH * 3 + 1];

	unsigned long read;
	void* con = GetStdHandle(STD_INPUT_HANDLE);
	ReadConsoleW(con, wstr, MAX_INPUT_LENGTH, &read, NULL);

	int size = WideCharToMultiByte(CP_UTF8, 0, wstr, read, mb_str, sizeof(mb_str), NULL, NULL);
	mb_str[size] = 0;

	std::string res(mb_str, mb_str + size - 2);
	return res;
}