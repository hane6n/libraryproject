#ifndef STORAGE_H
#define STORAGE_H
#include "library.h"

void saveDatabase(const LibraryState& state, const std::string& dbPath);
void loadDatabase(LibraryState& state, const std::string& dbPath);

#endif