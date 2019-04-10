#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
#include <windows.h>
using namespace std;

const int MAXSIZE = 10,
		  NUMGRP = 7;

struct Project
{
	int numPro;
	string subDeadline[MAXSIZE];
	string subDate[MAXSIZE];
	string state[MAXSIZE];
};

struct Troy
{
	string name[MAXSIZE];		
	int numStu;
	Project data;
};

void showMainMenu();
int getChoice();
void showInnerMenu1();
int getInnerChoice1();
void getInfo(Troy *);
bool isName_Duplicated(Troy *, string, int, int);
void displayInfo(Troy *);
void saveInfo(Troy *);
void showInnerMenu2();
int getInnerChoice2();
void proAssign(Troy *);
void proSubmit(Troy *);
void statistic(Troy *);
void overallStat(Troy *);
void findIncompleteGroup(Troy *);

int main()
{
	HANDLE screen = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(screen, 11);
	
	Troy group[NUMGRP];
	int choice, choice1, choice2;
	
	do
	{
		system("cls");
		showMainMenu();
		choice = getChoice();
		
			switch (choice)
			{
				case 1: system("cls");
						showInnerMenu1();
						choice1 = getInnerChoice1();
						switch (choice1)
						{
							case 1: getInfo(group);
									break;
							case 2: displayInfo(group);
									break;
							case 3: saveInfo(group);
									break;
						}
						break;
				case 2: system("cls");
						showInnerMenu2();
						choice2 = getInnerChoice2();
						switch (choice2)
						{
							case 1: proAssign(group);
									break;
							case 2: proSubmit(group);
									break;
						}
						break;
				case 3: system("cls");
						statistic(group);
						break;
				case 4: system("cls");
						overallStat(group);
						break;
				case 5: system("cls");
						findIncompleteGroup(group);
						break;
			}
		
	} while (choice != 6);
	
	SetConsoleTextAttribute(screen, 7);
	return 0;
}

void showMainMenu()
{
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << "1. Group information\n";
	cout << "2. Project assignment and submit\n";
	cout << "3. Statistic\n";
	cout << "4. Overall statistic\n";
	cout << "5. Groups do not complete or submit on time\n";
	cout << "6. Quit\n";
}

int getChoice()
{
	int choice;
	
	cout << "\nEnter a choice: ";
	cin >> choice;
	while (choice < 1 || choice > 6)
	{
		cout << "Please enter a valid choice from 1-6: ";
		cin >> choice;
	}
	return choice;
}

void showInnerMenu1()
{
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << "1. Input information of group\n";
	cout << "2. Display information\n";
	cout << "3. Save group information to a file\n"; 
}

int getInnerChoice1()
{
	int choice;
	
	cout << "\nEnter a choice: ";
	cin >> choice;
	while (choice < 1 || choice > 3)
	{
		cout << "Please enter a valid choice from 1-3: ";
		cin >> choice;
	}
	cin.get();
	return choice;	
}

void getInfo(Troy *group)
{
	cout << endl;
	for (int i = 0; i < NUMGRP; i++)
	{
		cout << "How many students does group " << i + 1 << " have? ";
		cin >> (group + i)->numStu;
		cin.ignore();
		while ((group + i)->numStu < 1)
		{
			cout << "Each group must have atleast 1 student, enter again: ";
			cin >> (group + i)->numStu;
			cout << endl;
			cin.ignore();
		}
		for (int j = 0; j < (group + i)->numStu; j++)
		{
			cout << "Enter student #" << j + 1 << "'s name: ";
			getline(cin, (group + i)->name[j]);
			if (i == 0 && j == 0)
				continue;
			else
			{
				while (!isName_Duplicated(group, (group + i)->name[j], i, j))
				{
					cout << "Duplicated name! Pleas enter another name: ";
					getline(cin, (group + i)->name[j]);
				}
			}
		}
		cout << endl;
	}
	cout << "Press enter to go back to main menu ";
	cin.get();
}

bool isName_Duplicated(Troy *group, string enteredName, int groupPos, int personPos)
{
	for (int i = 0; i <= groupPos; i++)
	{
		for (int k = 0; k < MAXSIZE; k++)
		{
			if (i == groupPos && k == personPos)
				continue;
			else
			{
				if ((group + i)->name[k] == enteredName)
					return false;
			}
		}
	}
	return true;
}

void displayInfo(Troy *group)
{
	char choice;
	int groupNum;
	
	cout << "\nDo you want to see members of one group or the whole class? (O/W) ";
	cin >> choice;
	while (toupper(choice) != 'O' && toupper(choice) != 'W')
	{
		cout << "Please enter either \"O\" or \"W\": ";
		cin >> choice;	
	}
	if (toupper(choice) == 'O')
	{
		cout << "Enter group number: ";
		cin >> groupNum;
		while (groupNum < 1 || groupNum > NUMGRP)
		{
			cout << "Please enter a number between 1 and " << NUMGRP << ": ";
			cin >> groupNum;
		}
		for (int i = 0; i < 29; i++)
			cout << "_";
		cout << left << setw(9) << "\nGroup |" << "   Student's name    |" << endl;
		for (int j = 0; j < 28; j++)
		{
			cout << "_";
			if (j == 5 || j == 27)
				cout << "|";
		}
		cout << endl;
		for (int k = 0; k < (group + (groupNum - 1))->numStu; k++)
		{
			if (k == 0)
			{
					cout << left << setw(6) << groupNum << "| " << setw(21);
				cout << (group + (groupNum - 1))->name[k] << "|" << endl;
			}	
			else
			{
					cout << left << setw(6) << " " << "| " << setw(21);
				cout << (group + (groupNum - 1))->name[k] << "|" << endl;
			}
		}
		for (int j = 0; j < 28; j++)
		{
			cout << "_";
			if (j == 5 || j == 27)
				cout << "|";
		}
		cout << "\n\nEnter to return to main menu ";
		cin.get();
		cin.get();
	}
	else
	{	
		for (int i = 0; i < 29; i++)
			cout << "_";
		cout << left << setw(9) << "\nGroup |" << "   Student's name    |" << endl;
		for (int j = 0; j < 28; j++)
		{
			cout << "_";
			if (j == 5 || j == 27)
				cout << "|";
		}
		cout << endl;
		for (int k = 0; k < NUMGRP; k++)
		{
			for (int l = 0; l < (group + k)->numStu; l++)
			{
				if (l == 0)
				{
					cout << left << setw(6) << k + 1 << "| ";
					cout << setw(21) << (group + k)->name[l] << "|" << endl;
				}
				else
				{
					cout << left << setw(6) << " " << "| ";
					cout << setw(21) << (group + k)->name[l] << "|" << endl;	
				}	
			}
			for (int j = 0; j < 28; j++)
			{
				cout << "_";
				if (j == 5 || j == 27)
					cout << "|";
			}
			cout << endl;
		}
		cout << "\nEnter to return to main menu ";
		cin.get();
		cin.get();
	}
}

void saveInfo(Troy *group)
{
	fstream outputFile;
	
	outputFile.open("group.txt", ios::out);
	for (int i = 0; i < 29; i++)
		outputFile << "_";
	outputFile << left << setw(9) << "\nGroup |" << "   Student's name    |" << endl;
	for (int j = 0; j < 28; j++)
	{
		outputFile << "_";
		if (j == 5 || j == 27)
			outputFile << "|";
	}
	outputFile << endl;
	for (int k = 0; k < NUMGRP; k++)
	{
		for (int l = 0; l < (group + k)->numStu; l++)
		{
			if (l == 0)
			{
				outputFile << left << setw(6) << k + 1 << "| ";
				outputFile << setw(21) << (group + k)->name[l] << "|" << endl;
			}
			else
			{
				outputFile << left << setw(6) << " " << "| ";
				outputFile << setw(21) << (group + k)->name[l] << "|" << endl;
			}		
		}
		for (int j = 0; j < 28; j++)
		{
			outputFile << "_";
			if (j == 5 || j == 27)
				outputFile << "|";
		}
		outputFile << endl;
	}
	if (outputFile)
		cout << "\nYour data has been successfully saved!";
	outputFile.close();
	cout << "\nEnter to return to main menu ";
	cin.get();
}

void showInnerMenu2()
{
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << "1. Project deadline declaration\n";
	cout << "2. Submit project\n";
}

int getInnerChoice2()
{
	int choice;
	
	cout << "\nEnter a choice: ";
	cin >> choice;
	while (choice < 1 || choice > 2)
	{
		cout << "Please enter a valid choice from 1-2: ";
		cin >> choice;
	}
	cin.get();
	return choice;
}

void proAssign(Troy *group)
{
	int num;
	string *ptr = NULL;
		   		   
	cout << "\nHow many projects does this course have? ";
	cin >> num;
	while (num < 1)
	{
		cout << "Must have atleast 1 project!, enter again: ";
		cin >> num;
	}
	cin.ignore();
	cout << endl;
	for (int i = 0; i < NUMGRP; i++)
		(group + i)->data.numPro = num;
		
	ptr = new string[num];
	
	for (int i = 0; i < num; i++)
	{
		cout << "Enter submission deadline for project " << i + 1 << " (yyyy-mm-dd): ";
		getline(cin, *(ptr + i));
		for (int j = 0; j < NUMGRP; j++)
		{
			(group + j)->data.subDeadline[i] = *(ptr + i);
		}
	}
	delete []ptr;
	ptr = 0;
	cout << "\nEnter to return to main menu ";
	cin.get();
}

void proSubmit(Troy *group)
{
	int p, g;
	char choice1, choice2;
	
	cout << endl;
	do
	{
		cout << "Which project do you want to submit? ";
		cin >> p;
		while (p < 1 || p > group->data.numPro)
		{
			cout << "Must enter a number between 1 - " << group->data.numPro << ": ";
			cin >> p;
		}
		cout << "Which group do you want to submit this project? ";
		cin >> g;
		while (g < 1 || g > 7)
		{
			cout << "Must enter a number between 1 - " << NUMGRP << ": ";
			cin >> g;
		}
		cout << "Submit or not (y/n): ";
		cin >> choice1;
		cin.ignore();
		if (toupper(choice1) == 'Y')
		{
			cout << "Enter date of submission (yyyy-mm-dd): ";
			getline(cin, (group + (g - 1))->data.subDate[p - 1]);
		}
		cout << "Do you want to continue? ";
		cin >> choice2;
		cout << endl;
	} while (toupper(choice2) == 'Y');
	
	cout << "Enter to return to main menu ";
	cin.get();
	cin.get();
}
void statistic(Troy *group)
{
	int choice1, choice2;
	
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << "Enter project number: ";
	cin >> choice1;
	while (choice1 < 1 || choice1 > group->data.numPro)
	{
		cout << "Please enter a number betweeen 1 and " << group->data.numPro << ": ";
		cin >> choice1;
	}
	for (int i = 0; i < 46; i++)
		cout << "_";
	cout << left << setw(7) << "\nGroup |"<< setw(16) << " Deadline date |" << setw(14) << " Submit date |" << " Status  |\n";
	for (int j = 0; j < 43; j++)
	{
		cout << "_";
		if (j == 5 || j == 20 || j == 33 || j == 42)
			cout << "|";
	}
	cout << endl;
	for (int k = 0; k < NUMGRP; k++)
	{
		if ((group + k)->data.subDate[choice1 - 1] == "\0")
			(group + k)->data.state[choice1 - 1] = " ";
		else if ((group + k)->data.subDate[choice1 - 1] <= (group + k)->data.subDeadline[choice1 - 1])
			(group + k)->data.state[choice1 - 1] = "On time";
		else if ((group + k)->data.subDate[choice1 - 1] > (group + k)->data.subDeadline[choice1 - 1])
			(group +k)->data.state[choice1 - 1] = "Late";
		cout << left << setw(6) << k + 1 << "| "<< setw(14) << (group + k)->data.subDeadline[choice1 - 1];
		cout << "| " << setw(12) << (group + k)->data.subDate[choice1 - 1] << "| ";
		cout << setw(8) << (group + k)->data.state[choice1 - 1]  << "|" << endl;
	}
	for (int j = 0; j < 43; j++)
	{
		cout << "_";
		if (j == 5 || j == 20 || j == 33 || j == 42)
			cout << "|";
	}
	cout << "\n\nEnter group number: ";
	cin >> choice2;
	while (choice2 < 1 || choice2 > NUMGRP)
	{
		cout << "Please enter a number between 1 and " << NUMGRP << ": ";
		cin >> choice2;
	}
	for (int i = 0; i < 36; i++)
		cout << "_";
	
	cout << left << setw(9) << "\nGroup |" << setw(10) << "Project |" << "Status\t    |\n";
	for (int i = 0; i < 34; i++)
	{
		cout << "_";
		if (i == 5 || i == 14 || i == 33)
			cout << "|";
	}
	cout << endl;
	for (int j = 0; j < (group + (choice2 -1))->data.numPro; j++)
	{
		if ((group + (choice2 - 1))->data.subDate[j] == "\0")
				(group + (choice2 - 1))->data.state[j] = "Not yet submitted";
		else if ((group + (choice2 - 1))->data.subDate[j] <= (group + (choice2 - 1))->data.subDeadline[j])
			(group + (choice2 - 1))->data.state[j] = "On time";
		else if ((group + (choice2 - 1))->data.subDate[j] > (group + (choice2 - 1))->data.subDeadline[j])
				(group + (choice2 - 1))->data.state[j] = "Late";
		if (j == 0)
		{
			cout << left << setw(6) << choice2 << "| " << setw(8) << j + 1 << "| ";
			cout << setw(18) << (group + (choice2 - 1))->data.state[j] << "|" << endl;
		}
		else
		{
			cout << left << setw(6) << " " << "| " << setw(8) << j + 1 << "| ";
			cout << setw(18) << (group + (choice2 - 1))->data.state[j] << "|" << endl;
		}
	}
		for (int i = 0; i < 34; i++)
	{
		cout << "_";
		if (i == 5 || i == 14 || i == 33)
			cout << "|";
	}
	cout << "\n\nEnter to return to main menu ";
	cin.get();
	cin.get();
}

void overallStat(Troy *group)
{
	char choice;
	fstream outputStatistic;
	
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << "Do you want to watch statistic ";
	cout << "to a to specific date or to current time (C/S)? ";
	cin >> choice;

	while (toupper(choice) != 'C' && toupper(choice) != 'S')
	{
		cout << "Please enter either \"C\" or \"S\": ";
		cin >> choice;
	}
	if (toupper(choice) == 'C')
	{
		for (int i = 0; i < 30; i++)
			cout << "_";
		for (int j = 0; j < (group->data.numPro * 12); j++)
			cout << "_";
		cout << endl;
		cout << left << setw(7) << "Group |" << setw(23) << " Student's name        | ";
		for (int k = 0; k < group->data.numPro; k++)
			cout << "Project " << k + 1 << " | ";
		cout << endl;
		for (int l = 0; l < 29; l++)
		{
			cout << "_";
			if (l == 5 || l == 28)
				cout << "|";
		}
		for (int m = 0; m < group->data.numPro; m++)
		cout << "___________|";
		cout << endl;
		for (int i = 0; i < NUMGRP; i++)
		{
			cout << left << setw(6) << i + 1 << "| " << setw(22) << (group + i)->name[0] << "| ";
			for (int j = 0; j < group->data.numPro; j++)
			{
				if ((group + i)->data.subDate[j] ==  "\0")
					(group + i)->data.state[j] = "NotYetSub";
				else if ((group + i)->data.subDate[j] <= (group + i)->data.subDeadline[j])
					(group + i)->data.state[j] = "On time";
				else if ((group + i)->data.subDate[j] > (group + i)->data.subDeadline[j])
					(group + i)->data.state[j] = "Late";
				cout << left << setw(10) << (group + i)->data.state[j] << "| ";
			}
			cout << endl;
			for (int k = 1; k < (group + i)->numStu; k++)
			{
				cout << left << setw(6) << " " << "| " << setw(22) << (group + i)->name[k] << "|";
				for (int i = 0; i < group->data.numPro; i++)
					cout << "           |";
				cout << endl;
			}
			for (int i = 0; i < 29; i++)
			{
				cout << "_";
				if (i == 5 || i == 28)
					cout << "|";
			}
			for (int i = 0; i < group->data.numPro; i++)
				cout << "___________|";
			cout << endl;
		}
		
		outputStatistic.open("Overall statistic.txt", ios::out);
		
		for (int i = 0; i < 30; i++)
			outputStatistic << "_";
		for (int j = 0; j < (group->data.numPro * 12); j++)
			outputStatistic << "_";
		outputStatistic << endl;
		outputStatistic << left << setw(7) << "Group |" << setw(23) << " Student's name        | ";
		for (int k = 0; k < group->data.numPro; k++)
			outputStatistic << "Project " << k + 1 << " | ";
		outputStatistic << endl;
		for (int l = 0; l < 29; l++)
		{
			outputStatistic << "_";
			if (l == 5 || l == 28)
				outputStatistic << "|";
		}
		for (int m = 0; m < group->data.numPro; m++)
		outputStatistic << "___________|";
		outputStatistic << endl;
		for (int i = 0; i < NUMGRP; i++)
		{
			outputStatistic << left << setw(6) << i + 1 << "| " << setw(22) << (group + i)->name[0] << "| ";
			for (int j = 0; j < group->data.numPro; j++)
			{
				if ((group + i)->data.subDate[j] ==  "\0")
					(group + i)->data.state[j] = "NotYetSub";
				else if ((group + i)->data.subDate[j] <= (group + i)->data.subDeadline[j])
					(group + i)->data.state[j] = "On time";
				else if ((group + i)->data.subDate[j] > (group + i)->data.subDeadline[j])
					(group + i)->data.state[j] = "Late";
				outputStatistic << left << setw(10) << (group + i)->data.state[j] << "| ";
			}
			outputStatistic << endl;
			for (int k = 1; k < (group + i)->numStu; k++)
			{
				outputStatistic << left << setw(6) << " " << "| " << setw(22) << (group + i)->name[k] << "|";
				for (int i = 0; i < group->data.numPro; i++)
					outputStatistic << "           |";
				outputStatistic << endl;
			}
			for (int i = 0; i < 29; i++)
			{
				outputStatistic << "_";
				if (i == 5 || i == 28)
					outputStatistic << "|";
			}
			for (int i = 0; i < group->data.numPro; i++)
				outputStatistic << "___________|";
			outputStatistic << endl;
		}
	}
	else
	{	
		cin.ignore();
		string speTime;
		
		cout << "Enter specific time you want to check (yyyy-mm-d): ";
		getline(cin, speTime);
		
		cout << left << setw(8) << "\nGroup" << "Status\n";
		for (int i = 0; i < NUMGRP; i++)
		{
			cout << left << setw(8) << i + 1;
			for (int j = 0; j < group->data.numPro; j++)
			{
				if (group->data.subDeadline[j] <= speTime)
				{
					if ((group + i)->data.subDate[j] ==  "\0")
						(group + i)->data.state[j] = "NotYetSub";
					else if ((group + i)->data.subDate[j] <= (group + i)->data.subDeadline[j])
						(group + i)->data.state[j] = "On time";
					else if ((group + i)->data.subDate[j] > (group + i)->data.subDeadline[j])
						(group + i)->data.state[j] = "Late";
					cout << (group + i)->data.state[j] << "  ";
				}
			}
			cout << endl;
		}
		
		outputStatistic.open("Overall statistic.txt", ios::out);
		
		outputStatistic << left << setw(8) << "\nGroup" << "Status\n";
		for (int i = 0; i < NUMGRP; i++)
		{
			outputStatistic << left << setw(8) << i + 1;
			for (int j = 0; j < group->data.numPro; j++)
			{
				if (group->data.subDeadline[j] <= speTime)
				{
					if ((group + i)->data.subDate[j] ==  "\0")
						(group + i)->data.state[j] = "NotYetSub";
					else if ((group + i)->data.subDate[j] <= (group + i)->data.subDeadline[j])
						(group + i)->data.state[j] = "On time";
					else if ((group + i)->data.subDate[j] > (group + i)->data.subDeadline[j])
						(group + i)->data.state[j] = "Late";
					outputStatistic << (group + i)->data.state[j] << "  ";
				}
			}
			outputStatistic << endl;
		}
	}
	if (outputStatistic)
		cout << "\nYour data has been successfully saved!";
	outputStatistic.close();
	cout << "\nEnter to return to main menu ";
	cin.get();
	cin.get();
}

void findIncompleteGroup(Troy *group)
{
	cout << "\t\t+++Course CS255 - Computer Science II+++\n\n";
	cout << left << setw(8) << "Group" << "Late project\n";
	for (int i = 0; i < NUMGRP; i++)
	{
		cout << left << setw(8) << i + 1;
		for (int j = 0; j < group->data.numPro; j++)
		{
			if ((group + i)->data.subDate[j] == "\0")
				(group + i)->data.state[j] = " ";
			else if ((group + i)->data.subDate[j] > (group + i)->data.subDeadline[j])
				(group + i)->data.state[j] = "Late";
			if ((group + i)->data.state[j] == "Late")
			{
				cout << j + 1 << " ";
			}
		}
		cout << endl;
	}
	cout << "\nEnter to return to main menu ";
	cin.get();
	cin.get();
}
