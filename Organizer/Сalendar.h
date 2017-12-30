#pragma once
#include <fstream>
#include <ctime>
#include <fstream>
#include <set>
#include <vector>
#include <stack>
#include <unordered_map>
#include "Compare.h"
#define FILE "Event.txt"
using namespace System::Windows::Forms;

typedef std::multiset <DataEvent, Compare> MultisetD;

class —alendar
{
private:
	std::unordered_multimap <int, std::string> Event;
	MultisetD data; 
	int month, year;
	int pDay, pMonth, pYear; // ÕÓ‚‡ˇ ‰‡Ú‡
public:
	—alendar();
	~—alendar();
	bool NewEvent (const char * , int &, int &);
	void newDate(int, int, int);
	int GetMonth();
	int GetYear();
	void plusMonth();
	void minusMonth();
	void DeleteEvent(std::string);
	int Compare(std::string);
	std::string MesEvent(int comp);
	std::vector<std::string> getString();
};

