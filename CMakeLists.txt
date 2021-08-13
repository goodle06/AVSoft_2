# CMakeList.txt : CMake project for AVSoftTest_2Semenov, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("AVSoftTest_2Semenov")

# Add source to this project's executable.
add_executable (AVSoftTest_2Semenov "AVSoftTest_2Semenov.cpp"  
	"Patterns/Composite.h" 
	"Patterns/Composite.cpp" 
	"Patterns/Command.h" 
	"Patterns/Command.cpp" 
	"Common.h" 
	"Patterns/Component.h" 
	"Patterns/Component.cpp"   
	"CorporateStructure.h"  
	"Employee.h" 
	"CorporateStructure.cpp"
	"3rdparty/tinyxml2.h"
	"3rdparty/tinyxml2.cpp"
	 "Commands/AddCommand.h" 
	 "Commands/RemoveCommand.h" 
	 "Commands/SetNameCommand.h" 
	 "Commands/SetWageCommand.h" 
	 "Commands/SetPositionCommand.h" 
	 "Commands/AllCommands.h" 
	 "Patterns/CommandManager.h" 
	 "Employee.cpp"
	    )

# TODO: Add tests and install targets if needed.
