#include "NoteManager.h"

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