#include "Ñalendar.h"
#include <string>
#include <sstream>

Ñalendar::Ñalendar()
{
	time_t second = time(NULL);
	tm* timeinfo = localtime(&second);
	month = timeinfo->tm_mon;
	year = 1900 + timeinfo->tm_year;
	pDay = -1;
	pMonth = -1;
	pYear = -1;
	data = MultisetD();
	std::ifstream fin(FILE, std::ios_base::in);
	if (!fin.is_open())
	{
		fin.close();
		return;
	}
	while (fin.good())
	{
		DataEvent itsEvent;
		fin >> itsEvent.hour >> itsEvent.min >> itsEvent.day >> itsEvent.month >> itsEvent.year;
		std::getline(fin, itsEvent.pEvent, '\0');
		if (!fin.good())
			break;
		data.insert(itsEvent);
		fin.get();
		if (itsEvent.day == timeinfo->tm_mday)//&&(itsEvent.hour>=timeinfo->tm_hour))
		{
			int time = itsEvent.hour * 60 + itsEvent.min;
			Event.insert(std::make_pair(time, itsEvent.pEvent));
		}
	}
	fin.close();
}


Ñalendar::~Ñalendar()
{
	std::ofstream fout(FILE, std::ios_base::out | std::ios_base::trunc);
	if (!fout.is_open())
	{
		fout.close();
		return;
	}
	MultisetD::iterator it;
	MultisetD::iterator end;
	for (it = data.begin(), end = data.end(); it != end; ++it)
	{
		fout << it->hour << " " << it->min << " " << it->day << " " << it->month << " " << it->year << " " << it->pEvent << '\0';
		fout << '\0';
	}
	fout.close();
	Event.clear();
}

bool Ñalendar::NewEvent(const char *line, int & hour, int & min)
{
	if (pDay < 0 || pMonth < 0 || pYear < 0)
		return true;
	DataEvent newEvent;
	newEvent.day = pDay;
	newEvent.month = pMonth;
	newEvent.year = pYear;
	newEvent.hour = hour;
	newEvent.min = min;
	newEvent.pEvent;
	newEvent.pEvent = line;
	data.insert(newEvent);
	return false;
}

void Ñalendar::newDate(int newDay, int newMonth, int newYear)
{
	this->pDay = newDay;
	this->pMonth = newMonth;
	this->pYear = newYear;
}

int Ñalendar::GetMonth()
{
	return this->month;
}

int Ñalendar::GetYear()
{
	return this->year;
}

void Ñalendar::plusMonth()
{
	++month;
	if (month > 11)
	{
		month = 0;
		++year;
	}
}

void Ñalendar::minusMonth()
{
	--month;
	if (month < 0)
	{
		month = 11;
		--year;
	}
}

void Ñalendar::DeleteEvent(std::string str)
{
	int num = Compare(str);
	if (num == -1)
	{
		MessageBox::Show("Ñîáûòèå íå óäàëåíî");
		return;
	}
	MultisetD::iterator it = data.begin();
	MultisetD::iterator end = data.end();
	for (int k; k!= num; k++, it++);
		data.erase(it);
	return;
}

int Ñalendar::Compare(std::string str)
{
	std::vector<std::string> stringLine = getString();
	for(int i = 0; i<stringLine.size(); i++)
		if (stringLine[i]==str)
			return i;
	return -1;
}

std::string Ñalendar::MesEvent(int comp)
{
	time_t second = time(NULL);
	tm* timeinfo = localtime(&second);
	std::unordered_multimap<int, std::string> ::iterator it = Event.begin();
	if (!Event.empty())
	{
		for (int i = 0; i < Event.size(); i++, it++)
		{
			if (((timeinfo->tm_hour * 60 + timeinfo->tm_min)<it->first) && ((it->first - ((timeinfo->tm_hour * 60) + timeinfo->tm_min)) <= comp))
			{
				std::string mes = it->second;
				Event.erase(it);
				return mes;
			}
		}
	}
	return "null";
}

std::vector<std::string> Ñalendar::getString()
{
	std::vector<std::string> string(data.size());
	MultisetD::iterator it = data.begin();
	MultisetD::iterator end = data.end();
	for (int i = 0; it != end; ++i, ++it)
	{
		std::stringstream out;
		out << it->hour << ":" << it->min << " " << it->day << "." << it->month + 1 << "." << it->year << " - "<< it->pEvent;
		string[i] = out.str();
		out.clear(); 
	}
	return string;
}

