#include<fstream>
#include<iostream>
#include<string>
#include<sstream>  
#include<algorithm>
using namespace std;

/*******************************************

Igor Alyeksyeyenko, ia22016

F21. Create program to read given text file containing correct C++ code. Count how many if, for and while commands are in given C++ program in input file. Program in input file does not contain comments.

Program created: 2023/02/06

*******************************************/

//trim empty spaces(and tabs) from the beginning of a string
string trimStart(string s)
{
	while (s[0] == ' ' || s[0] == '\t')
	{
		s.erase(0, 1);
	}

	return s;
}

//find the amount of commands(if/while/for) exist in a given string
//returns how many of them were found
int findCommands(string line)
{
	int commandCount = 0;

	//get rid of all strings inside line as they can contain fake if/while/for commands
	int position = line.find('"');
	while (position != -1)
	{
		line.erase(position, line.find('"', position + 1) - position + 1);
		position = line.find('"');
	}

	//turn the line into a stream to read it by a split character(;)
	stringstream lineStream(line);
	string segment;//split piece of the line
	//separate the line into pieces that end in semicolons
	//program can have an if/while/for at the end of a line and still be valid
	//since a line can contain an entire definition of if/while/for
	//they will end in either a semicolon or a closing brace '}'
	//replace all closing braces with semicolons for easier splitting
	replace(line.begin(), line.end(), '}', ';');

	while (getline(lineStream, segment, ';'))
	{
		segment = trimStart(segment);//get rid of leading spaces
		//check if each piece starts with if/for/while
		//as at this point it is guaranteed to start with those if they exist
		//else if is checked as well because it contains a valid if command(else on it's own is not an if command)
		if (segment.rfind("if", 0) == 0 || segment.rfind("else if", 0) == 0 || segment.rfind("for", 0) == 0 || segment.rfind("while", 0) == 0)
			commandCount++;
	}

	return commandCount;
}

int main() {
	cout << "Enter file name: ";
	string fileName;
	cin >> fileName;

	//file containing the code
	fstream codeFile(fileName, ios::in);
	//buffer for storing lines from file
	string codeLine = "";
	int commandCount = 0;
	//loop until the entire file is read, line by line
	while (getline(codeFile, codeLine))
	{
		commandCount += findCommands(codeLine);
	}

	//close file since reading has finished
	codeFile.close();

	cout << "Total number of if/for/while commands is: " << commandCount<<endl;

	return 0;
}