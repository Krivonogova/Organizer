#pragma once
#include<iostream>
struct DataEvent
{
	int day;
	int month;
	int year;
	int hour;
	int min;
	std::string pEvent;
};

class Compare : public std::binary_function<bool, const DataEvent &, const DataEvent &>
{
public:
	bool operator()(const DataEvent &, const DataEvent &);
};