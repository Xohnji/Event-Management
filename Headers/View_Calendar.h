#ifndef VIEW_CALENDAR_H
#define VIEW_CALENDAR_H

#include <string>
#include <vector>

using std::string;
using std::vector;
using std::size_t;

string GetColumnValue(const vector<string>& columns, size_t index, const string& defaultValue = "");
vector<string> ParseCSVLine(const string& line);
void View_Booking_Calendar();

#endif