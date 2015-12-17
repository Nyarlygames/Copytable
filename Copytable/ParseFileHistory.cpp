#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <stdio.h>
#include <string.h>

#include <cstring>

const int MAX_CHARS_PER_LINE = 50000;
const int MAX_TOKENS_PER_LINE = 500;
const int MAX_SUBTOKENS_PER_LINE = 1000;
const int Max_mantis = 1000;
const char* const DELIMITER = "(";
const char* const SUB_DELIMITER = " ";


struct Mantis {
	int reg;
	std::string id;
	char* project;
	char* Reporter;
};
struct Mantis *Mantisdb;
int mantisnb = 0;
int newid = 0;
int curline = 0;

int main()
{
  // create a file-reading object
  ifstream fin;
  ofstream log ("log_tool.txt",ofstream::binary);
  ofstream convert ("convert.txt",ofstream::binary);
  Mantisdb = new Mantis[Max_mantis];
  
  fin.open("test.txt"); // open a file
 if (!fin.good()) 
    return 1; //exit if file not found
  
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
	//char date[3] = {};
	const char* dates[1] = {};
    fin.getline(buf, MAX_CHARS_PER_LINE);
    int n = 0; // a for-loop index
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
		for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
		{
			if (!token[n]) {
					break;
			}// no more tokens
		}
		while (n > 0) {
			if (token[n - 1][0] != '\t') {
				convert << endl << token[n - 1];
				newid = 1;
			}
			else {
				newid++;
				if (newid == 2) {
					//convert << token[n - 1] << "date";
					//strncpy(date, token[n - 1], 12);
					dates[0] = strtok(buf, " ");
					convert << dates[0];
				}
				else {
					convert << token[n - 1];
				}
			}
			n--;
		}
	}
	curline++;
//	cout << "Line : " << curline << " Text : " << buf << endl;
//	log << "Line : " << curline << " Text : " << buf << endl;
  }
  

  log.close();
  fin.close();
  convert.close();
  return 0;
}