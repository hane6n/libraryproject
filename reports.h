#ifndef REPORTS_H
#define REPORTS_H
#include "library.h"

void generateOverdueReport(const LibraryState& state);
void exportOverdueBooks(const LibraryState& state, const std::string& filename);

#endif