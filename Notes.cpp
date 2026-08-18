#include <iostream>
#include <fstream>
#include <string>

#include "NoteManager.h"
#include "Note.h"

static const std::string notes_file_path = "notes_data.json";
static const std::string log_file_path = "log.txt";

int main(int argc, char* argv[])
{
    std::fstream notes_file(notes_file_path);
    std::ofstream log(log_file_path);

    NoteManager manager(&notes_file);
}

