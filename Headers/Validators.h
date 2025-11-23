#ifndef VALIDATORS_H
#define VALIDATORS_H

#include <string>

bool ValidateDate(const std::string& date);
bool Date_Checker(const std::string &dateStr);
bool Time_Checker(const std::string &timeStr);
std::string NormalizeDate(const std::string &dateStr);
std::string NormalizeTime(const std::string &timeStr);

#endif
