#include "Compare.h"

bool Compare::operator()(const DataEvent &left, const DataEvent &right)
{
	if (left.year != right.year)
		return left.year < right.year;
	if (left.month != right.month)
		return left.month < right.month;
	if (left.day != right.day)
		return left.day < right.day;
	if (left.hour != right.hour)
		return left.hour < right.hour;
	return left.min < right.min;
}