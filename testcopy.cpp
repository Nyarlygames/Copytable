
#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;
using std::ofstream;
#include <stdio.h>
#include <string.h>

#include <cstring>

const int MAX_CHARS_PER_LINE = 1024;
const int MAX_TOKENS_PER_LINE = 500;
const int MAX_SUBTOKENS_PER_LINE = 1000;
const int Max_mantis = 1000;
const char* const DELIMITER = "\n";
const char* const SUB_DELIMITER = ">";
std::string str;
std::string str_class1;
std::string str_id;
char *version;

struct Mantis {
	int reg;
	std::string id;
	char* project;
	char* Reporter;
	char* assigned_to;
	char* priority;
	char* severity;
	char* reproducibility;
	char* status;
	char* resolution;
	char* category;
	char* date_submit;
	char* updated;
	char* summary;
	char* description;
	char* steps;
	char* add_info;
	int nb_comment;
	char* fixed_in;
	char* moscow;
	char* player_link;
	char* version;
};
struct Mantis Mantis1;
struct Mantis Mantis0;
struct Mantis TempMantis;
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
  
  fin.open("test3.txt"); // open a file
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
    
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        if (!token[n]) {
				break;
				
		}// no more tokens
      }
	  int maxdesc = n; 
		  while (maxdesc >= 0) {
			  str = buf;
			  // IF ID = NEW MANTIS
			  size_t found_id = str.find("bug_id=");
			  if (found_id!=std::string::npos) {
			//	cout << "first 'id' found at: " << str.c_str() << " char : " << found_id << " mantisnb : "<<mantisnb  << '\n';
					  curline = 0;
						 size_t found_id2 = str.find("\">");
						  if (found_id2!=std::string::npos) {
								//	cout << "second 'id' found at: " << curline <<" char1 : " << found_id << " char : " << found_id2 << " " << '\n';
									str_id = str.substr(found_id+7, found_id2 - found_id - 7);
								
										cout << "id : " << str_id.c_str() << " mantisnb"<<mantisnb <<  endl;
								//	log << "id : " << str_id.c_str() <<  endl;
									//convert << str_id.c_str();
							  if (mantisnb >=0) {
								  if (strcmp(str.c_str(),Mantisdb[mantisnb].id.c_str())) {
								  }
									Mantisdb[mantisnb].id = str_id.c_str();
									Mantisdb[mantisnb].reg = mantisnb;
									mantisnb++;
								}
								  else {
cout<< "test";								  }
							  }
						  }

			  }
			std::size_t found_item = str.find("td>  class=\"center\">");
			  if (found_item!=std::string::npos) {
				//  	cout << "first 'item' found at: " << curline << " char : " << found_item << " mantisnb" << mantisnb << '\n';
						 size_t found_item2 = str.find("</");
						//	  cout << "curline : " << curline << " str : " << str.c_str() << endl;
						  if (found_item2!=std::string::npos) {
								//	cout << "second 'id' found at: " << curline <<" char1 : " << found_id << " char : " << found_id2 << " " << '\n';
									str_class1 = str.substr(found_item+7, found_item2 - found_item - 7);
								//	cout << "classstuff : " << str_class1.c_str() <<  endl;
							//		log << "	classstuff : " << str_class1.c_str() <<  endl;
						  }
				  curline++;
			  }
		  maxdesc--;
		}
		  convert<< endl;
	  
	  /*
    token2[0] = strtok(buf2, SUB_DELIMITER); // first token
	  int m = 1;
      for ( m = 1; m < MAX_SUBTOKENS_PER_LINE; m++){
		  
        token2[m] = strtok(0, SUB_DELIMITER); // subsequent token
        if (!token2[m]) {
				break;
				
		}// no more tokens
		  id2++;
	}
	  
	  for (int maxdesc2 = 0; maxdesc2 < m; maxdesc2++) {
		  cout <<" penislol2 : " << id2 << " "<<token2[maxdesc2] << " "<< m <<endl;
	  }
	  log << endl;
    }*/
/*	if (n>=1){
			cout <<token[0] << "	" << token[1] << endl;
		if (strcmp(token[0], "<tr class=")){
			cout <<"class" << endl;
			log <<"test : " << token[0] << endl;
		}
		else if (strcmp(token[0], "<td><a href=")){
			cout <<"href" << endl;
			log <<"test : " << token[0] << endl;
		}
		else{
			cout <<"autres" << endl;
			log <<"test2 : " << token[0] << endl;
		}
		}
	else {
		cout << "n : "<< n << "penislol : "<< id << " " << token[0]<< endl;
	}*/
	}
	
  }
  
  /*
  Mantis0.id = 0;
 Mantis0.project = "Project";
 Mantis0.Reporter = "Reported";
 Mantis0.assigned_to = "Assigned to";
 Mantis0.priority = "Priority";
 Mantis0.severity = "Severity";
 Mantis0.reproducibility="Reproducibility";
 Mantis0.status="Status";
 Mantis0.resolution ="Resolution";
 Mantis0.category="Category";
 Mantis0.date_submit="Submit";
 Mantis0.updated="Updated";
 Mantis0.summary="Summary";
 Mantis0.description="Description";
 Mantis0.steps="Steps to reproduce";
 Mantis0.add_info="Additionnal info";
 Mantis0.nb_comment =0;
 Mantis0.fixed_in="Fixed in version";
 Mantis0.moscow="MosCow";
 Mantis0.player_link="Player occurence";
 Mantis0.version="Version";
  Mantis1.id = 1;
 Mantis1.project = "Mordheim";
 Mantis1.Reporter = "Paul";
 Mantis1.assigned_to = "Rf-Edgy";
 Mantis1.priority = "High";
 Mantis1.severity = "Major";
 Mantis1.reproducibility="Always";
 Mantis1.status="new";
 Mantis1.resolution ="open";
 Mantis1.category="Gameplay";
 Mantis1.date_submit="10-12-2015";
 Mantis1.updated="10-12-2015";
 Mantis1.summary="test item mantis";
 Mantis1.description="test desc item mantis";
 Mantis1.steps="test step item mantis";
 Mantis1.add_info="test add info item mantis";
 Mantis1.nb_comment =0;
 Mantis1.fixed_in="0.0.0.0";
 Mantis1.moscow="Must";
 Mantis1.player_link="http://test.com";
 Mantis1.version="0.1.1.1";
  mantisnb = 2;
 Mantisdb = new Mantis[mantisnb];
 Mantisdb[0] = Mantis0;
 Mantisdb[1] = Mantis1;
  for (int idmantis = 0; idmantis < mantisnb; idmantis++) {  
	log << Mantisdb[idmantis].id << "	" <<  Mantisdb[idmantis].project << "	" <<  Mantisdb[idmantis].Reporter << "	";
	log <<  Mantisdb[idmantis].assigned_to << "	" << Mantisdb[idmantis].priority << "	"  << Mantisdb[idmantis].severity << "	";
	log << Mantisdb[idmantis].reproducibility << "	"  << Mantisdb[idmantis].status << "	"  << Mantisdb[idmantis].resolution << "	"  << Mantisdb[idmantis].category << "	";
	log << Mantisdb[idmantis].date_submit << "	"  << Mantisdb[idmantis].updated << "	"  << Mantisdb[idmantis].summary << "	"; 
	log << Mantisdb[idmantis].description << "	"  << Mantisdb[idmantis].steps << "	"  << Mantisdb[idmantis].add_info << "	"; 
	log << Mantisdb[idmantis].nb_comment << "	"  << Mantisdb[idmantis].fixed_in << "	"  << Mantisdb[idmantis].moscow  << "	"; 
	log << Mantisdb[idmantis].player_link << "	"  << Mantisdb[idmantis].summary << Mantisdb[idmantis].date_submit << "	"  << Mantisdb[idmantis].version << endl;
	cout << Mantisdb[idmantis].id << "	" <<  Mantisdb[idmantis].project << "	" <<  Mantisdb[idmantis].Reporter << "	";
	cout <<  Mantisdb[idmantis].assigned_to << "	" << Mantisdb[idmantis].priority << "	"  << Mantisdb[idmantis].severity << "	";
	cout << Mantisdb[idmantis].reproducibility << "	"  << Mantisdb[idmantis].status << "	"  << Mantisdb[idmantis].resolution << "	"  << Mantisdb[idmantis].category << "	";
	cout << Mantisdb[idmantis].date_submit << "	"  << Mantisdb[idmantis].updated << "	"  << Mantisdb[idmantis].summary << "	"; 
	cout << Mantisdb[idmantis].description << "	"  << Mantisdb[idmantis].steps << "	"  << Mantisdb[idmantis].add_info << "	"; 
	cout << Mantisdb[idmantis].nb_comment << "	"  << Mantisdb[idmantis].fixed_in << "	"  << Mantisdb[idmantis].moscow  << "	"; 
	cout << Mantisdb[idmantis].player_link << "	"  << Mantisdb[idmantis].summary << Mantisdb[idmantis].date_submit << "	"  << Mantisdb[idmantis].version << endl;
  }*/
  
  log.close();
  fin.close();
  convert.close();
  return 0;
}