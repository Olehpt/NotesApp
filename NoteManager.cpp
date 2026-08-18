#include "NoteManager.h"

using json = nlohmann::json;

NoteManager::NoteManager() : file(nullptr), owns_file(false) {
	std::cout << "NoteManager created without a file\n";
}

NoteManager::NoteManager(const std::string& file_path) {
	file = new std::fstream(file_path);
	if (!file->is_open()) {
		std::cout << "NoteManager can`t open a notes file\n";
	}
	owns_file = true;
}
NoteManager::NoteManager(std::fstream* f) :file(f) {
	if (!file->is_open()) {
		std::cout << "NoteManager can`t open a notes file\n";
	}
	owns_file = false;
};

NoteManager::~NoteManager() {
	if (owns_file)
		delete file;
}

void NoteManager::AddNote(const Note& n) {
	//todo
}

void NoteManager::ListNotes() {
	json data;
	*file >> data;
	std::cout << "\n";
	for (const auto& note : data["notes"]) {
		std::cout << "Title: " << note["title"] << " | ";
		std::cout << "Target date: " << note["target_date"] << " | ";
		std::cout << "Creation date: " << note["creation_date"] << "\n";
	}
}