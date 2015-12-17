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
const char* const DELIMITER = "";
const char* const SUB_DELIMITER = " ";

std::string str;
char *version;

struct Mantis {
	int reg;
	std::string id;
	char* project;
	char* Reporter;
};
struct Mantis *Mantisdb;
int mantisnb = 0;
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
    fin.getline(buf, MAX_CHARS_PER_LINE);
    int n = 0; // a for-loop index
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
  //  token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        if (!token[n]) {
				break;
				
		}// no more tokens
      }
		  while (n >= 0) {
			  /*
			  str = buf;
			  // IF ID = NEW MANTIS

			std::size_t found_item = str.find("</");
			  if (found_item!=std::string::npos) {
				 //	cout << "first 'item' found at: " << curline << " char : " << found_item << " mantisnb" << mantisnb << '\n';
						 size_t found_item2 = str.find("/>");
						// cout << found_item2<<endl;
						//	  cout << "curline : " << curline << " str : " << str.c_str() << endl;
								
				  if (found_item2!=std::string::npos) {
						 		log << "second 'item' found at: " << curline <<" char1 : " << found_item << " char : " << found_item2 << " " << '\n';
								  str_class1 = str.substr(found_item2+2, found_item - found_item2-2);
								//cout << "classstuff : " << str.c_str() <<  endl;
								 // cout << "	goodstr : " << str_class1.c_str() << " length : " << str_class1.length()<< endl;
								convert << str_class1.c_str() << "\t";
							//	cout << str_class1.c_str() << endl;
								
								size_t found_item3 = str_class1.find("a");
								
						  if (found_item3!=std::string::npos) {
										  size_t found_id = str_class1.find("00");
										  if (found_id!=std::string::npos) {
											cout << "first 'iditem' found at: " << str.c_str() << " char : " << found_id << " mantisnb : "<<mantisnb  << '\n';
												  curline = 0;
															//	cout << "second 'id' found at: " << curline <<" char1 : " << found_id << " char : " << found_id2 << " " << '\n';
												 // cout << "ITEM2 : " << found_item3 <<endl;
												  str_id = str_class1.substr(found_id, found_item3 - found_id);
																//cout << str_id.c_str() ;
															//	log << "id : " << str_id.c_str() <<  endl;
																//convert << str_id.c_str();

																	cout << "realid : " <<str_id.c_str() << " mantisnb" <<mantisnb <<  endl;
																	convert << str_id.c_str() << endl;
																	mantisnb++;
																	cout << str_id.c_str() << endl;
														  }
						  }
				  }
			  }*/
		  n--;
		}
		  
	}
	curline++;
	cout << "Line : " << curline << " Text : " << buf << endl;
	log << "Line : " << curline << " Text : " << buf << endl;
  }
  

  log.close();
  fin.close();
  convert.close();
  return 0;
}