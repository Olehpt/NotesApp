#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Note.h"
#include <vector>
#include <algorithm>

class NoteManager {
	std::fstream* file;
	bool owns_file;
	bool NoteManager::get_free_id(size_t& id);
public:
	NoteManager();
	NoteManager(const std::string& file_path);
	NoteManager(std::fstream* f);
	~NoteManager();
	void AddNote(Note& n);
	void ListNotes();
};