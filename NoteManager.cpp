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

void NoteManager::AddNote(Note& n) {
	size_t id = 0;
	if (!get_free_id(id)) return;
	json json_note = {
		{"id", id},
		{"title", n.get_title()},
		{"creation_date", Date::today().to_string()},
		{"target_date", n.get_date().to_string()}
	};
	*file << "\n" << json_note.dump();
}

void NoteManager::ListNotes() {
	std::string line;
	while (std::getline(*file, line))
	{
		nlohmann::json note = nlohmann::json::parse(line);
		std::cout << "ID: " << note["id"] << " ; Title: " << note["title"] << " ; Creation Date: "
			<< note["creation_date"] << " ; Target Date: " << note["target_date"] << std::endl;
	}
}

bool NoteManager::get_free_id(size_t& id) {
	std::vector<size_t> ids = {};
	std::string str;
	while (std::getline(*file, str)) {
		nlohmann::json note = nlohmann::json::parse(str);
		try {
			ids.push_back(note["id"].get<size_t>());
		}
		catch (const std::exception& e) {
			std::cout << "Error parsing ID: " << e.what() << std::endl;
			std::cout << "Note storage may be corrupeted. Please check the file.\n";
			return false;
		}
	}
	std::sort(ids.begin(), ids.end());
	size_t counter = 0;
	for (auto i : ids) {
		counter++;
		if (counter != i) {
			id = counter;
			file->clear();
			file->seekp(0, std::ios::end);
			return true;
		}
	}
	id = counter + 1;
	file->clear();
	file->seekp(0, std::ios::end);
	return true;
}