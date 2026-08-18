#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Note.h"

class NoteManager {
	std::fstream* file;
	bool owns_file;
public:
	NoteManager();
	NoteManager(const std::string& file_path);
	NoteManager(std::fstream* f);
	~NoteManager();
	void AddNote(const Note& n);
	void ListNotes();
};