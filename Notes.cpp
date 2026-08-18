#include <iostream>
#include <fstream>
#include <string>

#include "NoteManager.h"
#include "Note.h"
#include "Parser.h"

static const std::string notes_file_path = "notes_data.json";
static const std::string log_file_path = "log.txt";

int main(int argc, char* argv[])
{
    std::fstream notes_file(notes_file_path);
    std::ofstream log(log_file_path);

    NoteManager manager(&notes_file);

    Parser p(argc, argv);
	action act = p.parse();
	switch (act) {				//TODO
	case(list):
		std::cout << "List notes\n";
		break;
	case(add):
		std::cout << "Add note\n";
		break;
	case(rm):
		std::cout << "Remove note\n";
		break;
	case(modify):
		std::cout << "Modify note\n";
		break;
	default:
		std::cout << "Unknown action\n";
		break;
	}
}

