#pragma once
#include <string>
#include "Student.h"
struct TeachingAssistant {
	std::string name;
	int startTime[3];
	int endTime[3];
	Student studentwithTA;
	int minute;
	bool availible;
	int day[3];
};