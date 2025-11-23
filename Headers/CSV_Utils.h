#ifndef CSV_UTILS_H
#define CSV_UTILS_H

#include <string>
void AppendToCSV(const std::string &csvToUse);
std::string ResolveCSVPath(const std::string &csvPath);
bool IsCSVReadable(const std::string &csvPath);
bool IsDateTaken(const std::string &dateStr, const std::string &csvPath);

#endif
