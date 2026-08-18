#pragma once
#include <iostream>
#include <fstream>
#include <string>

class NoteManager {
	std::fstream* file;
	bool owns_file;
public:
	NoteManager();
	NoteManager(const std::string& file_path);
	NoteManager(std::fstream* f);
	~NoteManager();
};