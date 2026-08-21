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
	file->clear();
	file->seekp(0, std::ios::end);
	*file << json_note.dump() << "\n";
}

void NoteManager::ListNotes() {
	std::string line;
	while (std::getline(*file, line))
	{
		nlohmann::json note = nlohmann::json::parse(line);
		std::cout << "ID: " << note["id"] << " ; Title: " << note["title"] << " ; Creation Date: "
			<< note["creation_date"] << " ; Target Date: " << note["target_date"] << std::endl;
	}
	file->clear();
}

bool NoteManager::get_free_id(size_t& id) {
	file->clear();
	file->seekg(0, std::ios::beg);
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
	if (ids.empty()) {
		id = 1;
		file->clear();
		file->seekg(0, std::ios::beg);
		return true;
	}
	std::sort(ids.begin(), ids.end());
	size_t counter = 0;
	for (auto i : ids) {
		counter++;
		if (counter != i) {
			id = counter;
			file->clear();
			file->seekg(0, std::ios::beg);
			return true;
		}
	}
	id = counter + 1;
	return true;
}

void NoteManager::RemoveNote(size_t id) {
	file->clear();
	file->seekg(0, std::ios::beg);
	std::string str;
	std::vector<Note> notes = {};
	while (std::getline(*file, str)) {
		nlohmann::json note = nlohmann::json::parse(str);
		if (note["id"] == id) continue;
		
		std::stringstream ss(note["target_date"].get<std::string>());
		int d, m, y; char sep;
		Date td, cd;
		ss >> d >> sep >> m >> sep >> y;
		td = Date(d, m, y);
		ss = std::stringstream(note["creation_date"].get<std::string>());
		ss >> d >> sep >> m >> sep >> y;
		cd = Date(d, m, y);
		Note n((size_t)note[id], note["title"], td, cd);
		notes.push_back(n);
	}
	file->close();
	file = nullptr;
	std::fstream* new_file = new std::fstream("notes_data.jsonl", std::ios::out | std::ios::trunc);
	file = new_file;
	for (auto n : notes) {
		AddNote(n);
	}
}