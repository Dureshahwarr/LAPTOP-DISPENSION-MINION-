#include "TeachingAssistant.h"
#include "Node.h"
#include <stack>
#include <queue>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <conio.h>

using namespace std;

ofstream outfile;
int durationtime[3] = { 0,0,0 };
stack<int> laptopstack;
queue<Student> laptopqueue;
queue<Student> taqueue;
queue<Student> outside;
Node* simulation;
TeachingAssistant* teachingassistant;
TeachingAssistant* backup;
int numberofsimulation;
int numberofstudent[3];
int numberofteachingassistance;
Student* student;
int t = 0;
int frustratedcount[3] = { 0,0,0 };
int happycount[3] = { 0,0,0 };

void readfile();
void assignlaptop();
void assignteachingassistant();
void simulationtime();

void main()
{
	outfile.open("output.txt");
	readfile();
	backup = teachingassistant;
	while (t < 3)
	{
		backup = teachingassistant;
		cout << "Program " << t + 1 << "\n\n\n";
		outfile << "Program " << t + 1 << "\n\n\n";
		//thread t1{ assignlaptop };
		//thread t2{ assignteachingassistant };
		assignlaptop();
		assignteachingassistant();
		//t1.detach();
		//t2.detach();
		string day;
		if (t == 0)
			day = "Monday";
		else if (t == 1)
			day = "Wednesday";
		else
			day = "Friday";
		cout << endl << endl << endl << day << " Lab Summary\n" << "Lab was open for " << durationtime[t] << endl << numberofstudent[t] << " showed up today. " << happycount[t] << " went happy, " << frustratedcount[t] << " went frustated \n";
		t++;
	}
	outfile.close();
	_getch();
}

void readfile()
{
	int size;
	int stack;
	bool stackcheck = false;
	bool ta = false;
	bool noofsim = false;
	bool iteration = false;
	string line;
	ifstream file;
	file.open("input.txt", ios::beg);
	if (file.is_open())
	{
		while (!file.eof())
		{
			getline(file, line);
			size = stoi(line);
			while (size != 0 && !stackcheck)
			{
				getline(file, line);
				stack = stoi(line);
				laptopstack.push(stack);
				size--;
				if (size == 0)
					stackcheck = true;
			}
			getline(file, line);
			size = stoi(line);
			if (stackcheck)
			{
				teachingassistant = new TeachingAssistant[size];
				numberofteachingassistance = size;
				size = 0;
			}
			while (size != numberofteachingassistance && !ta)
			{
				string sample;
				for (int i = 0; size < numberofteachingassistance; size++)
				{
					getline(file, line);
					while (line[i] != ' ')
					{
						sample += line[i];
						i++;
					}
					teachingassistant[size].name = sample;
					sample = "";
					i++;
					//-----------------------------------------------
					while (line[i] != ' ')
					{
						sample += line[i];
						i++;
					}
					teachingassistant[size].startTime[0] = stoi(sample);
					sample = "";
					i++;
					//-----------------------------------------------
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					teachingassistant[size].endTime[0] = stoi(sample);
					sample = "";
					i++;
					//-----------------------------------------------
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					teachingassistant[size].startTime[1] = stoi(sample);
					sample = "";
					i++;
					//-----------------------------------------------
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					teachingassistant[size].endTime[1] = stoi(sample);
					sample = "";
					i++;
					//-----------------------------------------------
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					teachingassistant[size].startTime[2] = stoi(sample);
					sample = "";
					i++;
					//-----------------------------------------------
					sample += line[i];
					i++;
					sample += line[i];
					i++;
					sample += line[i];
					teachingassistant[size].endTime[2] = stoi(sample);
					sample = "";
					//-----------------------------------------------
					teachingassistant[size].availible = true;
					teachingassistant[size].minute = 0;
					i = 0;
					if (teachingassistant[size].endTime[0] == 0)
					{
						teachingassistant[size].day[0] = 0;
					}
					else if (teachingassistant[size].endTime[1] == 0)
					{
						teachingassistant[size].day[1] = 0;
					}
					else if (teachingassistant[size].endTime[2] == 0)
					{
						teachingassistant[size].day[2] = 0;
					}
				}
				ta = true;
			}
			getline(file, line);
			size = stoi(line);
			if (ta)
			{
				numberofsimulation = size;
				simulation = new Node[size];
				noofsim = true;
			}
			if (noofsim)
			{
				while (numberofsimulation != 0)
				{
					int j = 0;
					while (j < 3)
					{
						getline(file, line);
						size = stoi(line);
						numberofstudent[j] = size;
						student = new Student[size];
						size = 0;
						while (numberofstudent[j] != size)
						{
							string sample = "";
							for (int i = 0; numberofstudent[j] != size; i++)
							{
								i = 0;
								getline(file, line);
								while (line[i] != ' ')
								{
									sample += line[i];
									i++;
								}
								student[size].entertime = stoi(sample);
								sample = "";
								i++;
								while (line[i] != ' ')
								{
									sample += line[i];
									i++;
								}
								student[size].first_name = sample;
								sample = "";
								i++;
								while (line[i] != ' ')
								{
									sample += line[i];
									i++;
								}
								student[size].last_name = sample;
								sample = "";
								i++;
								while (i <= (line.size()))
								{
									sample += line[i];
									i++;
								}
								student[size].question = stoi(sample);
								student[size].laptop_serialnumber = -1;
								laptopqueue.push(student[size]);
								student[size].day = (j + 1);
								size++;
							}
						}
						simulation[numberofsimulation - 1].Node::student[j] = student;
						j++;
					}
					numberofsimulation--;
				}
			}
		}
	}
	else
		cout << "Error in Opening Input file\n";
}

void assignlaptop()
{
	if (t < 3)
	{
		while ((laptopqueue.size() != 0) && (laptopstack.size() != 0))
		{
			if (laptopqueue.front().laptop_serialnumber == -1)
			{
				laptopqueue.front().laptop_serialnumber = laptopstack.top();
				laptopstack.pop();
				taqueue.push(laptopqueue.front());
				cout << laptopqueue.front().first_name << " " << laptopqueue.front().last_name << " has borrowed laptop " << laptopqueue.front().laptop_serialnumber << " and moved to TA line.\n";
				outfile << laptopqueue.front().first_name << " " << laptopqueue.front().last_name << " has borrowed laptop " << laptopqueue.front().laptop_serialnumber << " and moved to TA line.\n";
				laptopqueue.pop();
			}
			else
			{
				laptopstack.push(laptopqueue.front().laptop_serialnumber);
				outside.push(laptopqueue.front());
				laptopqueue.pop();
			}
			durationtime[t]++;
		}
	}
}

void assignteachingassistant()
{
	while (t < 3)
	{
		int count = 0;
		int studentcount = 0;
		while (taqueue.size() != 0)
		{
			int i = 0;
			if (teachingassistant == NULL || durationtime[t] >= 240)
			{
				cout << taqueue.front().first_name << " could not get help due to time constrain \n";
				outfile << taqueue.front().first_name << " could not get help due to time constrain \n";
				laptopqueue.push(taqueue.front());
				taqueue.pop();
			}
			else
			{
				for (; i < numberofteachingassistance; i++)
				{
					if (teachingassistant[i].availible == false)
						count++;
					if (count == numberofteachingassistance)
					{
						teachingassistant = NULL;
						break;
					}
					else
					{
						if (teachingassistant != NULL)
						{
							if (durationtime[t] >= teachingassistant[i].endTime[t] && teachingassistant[i].startTime[t] != teachingassistant[i].endTime[t])
							{
								cout << teachingassistant[i].name << " has left \n";
								outfile << teachingassistant[i].name << " has left\n";
								teachingassistant[i].availible = false;
							}
							if (teachingassistant[i].availible && taqueue.size() != 0)
							{
								teachingassistant[i].studentwithTA = taqueue.front();
								teachingassistant[i].minute += 2;
								taqueue.front().answer = (rand() % taqueue.front().question) + 1;
								cout << taqueue.front().first_name << " is getting help from " << teachingassistant[i].name << "\n";
								outfile << taqueue.front().first_name << " is getting help from " << teachingassistant[i].name << "\n";
								cout << taqueue.front().first_name << " had one question answered\n";
								outfile << taqueue.front().first_name << " had one question answered\n";
								if (true)
								{
									if ((taqueue.front().answer <= (taqueue.front().question / 2)))
									{
										cout << taqueue.front().first_name << " had questions left to ask\n";
										outfile << taqueue.front().first_name << " had questions left to ask\n";
										taqueue.push(taqueue.front());
									}
									else
									{
										if (taqueue.front().answer >= taqueue.front().question)
										{
											happycount[t]++;
											taqueue.front().reaction = "Happy";
										}
										else
										{
											frustratedcount[t]++;
											taqueue.front().reaction = "Frustrated";
										}
										laptopqueue.push(taqueue.front());
										cout << taqueue.front().first_name << " " << taqueue.front().last_name << " has returned laptop " << taqueue.front().laptop_serialnumber << " and went home " << taqueue.front().reaction << "\n";
										outfile << taqueue.front().first_name << " " << taqueue.front().last_name << " has returned laptop " << taqueue.front().laptop_serialnumber << " and went home " << taqueue.front().reaction << "\n";
									}
									taqueue.pop();
								}
							}
						}
					}
				}
			}
			if (taqueue.size() == 0 && teachingassistant != NULL)
			{
				for (int i = 0; i < numberofteachingassistance; i++)
				{
					cout << teachingassistant[i].name << " has left \n";
					outfile << teachingassistant[i].name << " has left\n";
				}
				teachingassistant = NULL;
			}
		}
		if (teachingassistant == NULL)
		{
			return;
		}
	}
}

void simulationtime()
{
	
}