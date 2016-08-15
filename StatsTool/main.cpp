#include <stdio.h>
#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std; 
ofstream	output("stats.html");

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if(from.empty())
        return;
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); 
    }
}

void	create_debug_curve(string	labels, int	nbunique, vector<string>	dates,vector<int>	totalopen,vector<int>	totalcreated,vector<int>	totalclosed, string	title, string	divname) {
	output << "google.charts.setOnLoadCallback(" << divname << ");\n";
	output << "function " << divname << "() { \n var datadate = google.visualization.arrayToDataTable([";
	output << labels;
	int i =0;
	while (i < nbunique-1){
		output << "['" << dates[i] << "', " << totalopen[i] << ", "  << totalcreated[i] << ", " << totalclosed[i] << "],\n";
		i++;
	}
	output << "['" << dates[i] << "', " << totalopen[i] << ", "  << totalcreated[i] << ", " << totalclosed[i] << "]\n";
	output << "]);";
	output << "var optionsdate = {\n";
	output << "explorer: {keepInBounds: true},\n";
	output << "hAxis: {titleTextStyle: {color: '#333'}},\n";
	output << "legend : {position: 'top', textStyle: {color: 'blue', fontSize: 16}},\n";
	output << "title : '" << title << "',\n";
    output << "vAxis: {minValue: 0}\n};\n";
	output << "var " << divname << " = new google.visualization.AreaChart(document.getElementById('" << divname << "'));\n";
	output << "" << divname << ".draw(datadate, optionsdate);}\n";
}

void	create_multiple_debug_curve(vector<string>	titles, int	nbtitles, int	nbunique, vector<string>	dates, vector< vector<int> >	progress, int	offsetstat, int offset, string	title, string	divname) {
	output << "google.charts.setOnLoadCallback(" << divname << ");\n";
	output << "function " << divname << "() { \n var datadate = google.visualization.arrayToDataTable([";
	output << "['Date', ";
	int i =0;
	while (i < nbtitles-1) {
		output << "'" << titles[i] << "', ";
		i++;
	}
	output << "'" << titles[i] << "'],";
	i=0;
	int y =0;
	while (i < nbunique-1){
		output << "['" << dates[i] << "', ";
		while (y < nbtitles-1) {
			output << progress[i][y*offset+offsetstat] << ", ";
			y++;
		}
		output << progress[i][y*offset+offsetstat] << "],\n";
		y=0;
		i++;
	}
	y=0;
	output << "['" << dates[i] << "', ";
	while (y < nbtitles-1) {
		output << progress[i][y*offset+offsetstat] << ", ";
		y++;
	}
	output << progress[i][y*offset+offsetstat] << "]\n";
	output << "]);";
	output << "var optionsdate = {\n";
	output << "explorer: {keepInBounds: true},\n";
	output << "hAxis: {titleTextStyle: {color: '#333'}},\n";
	output << "legend : {position: 'right', textStyle: {color: 'blue', fontSize: 10}},\n";
	output << "title : '" << title << "',\n";
    output << "vAxis: {minValue: 0}\n};\n";
	output << "var " << divname << " = new google.visualization.AreaChart(document.getElementById('" << divname << "'));\n";
	output << "" << divname << ".draw(datadate, optionsdate);}\n";
}

void	create_debug_pie(string	labels, int	nbunique, vector<string>	names,vector<int>	count, string	title, string divname) {
	output << "google.charts.setOnLoadCallback(" << divname << ");\n";
	output << "function " << divname << "() {\n";
    output << "var datapie = google.visualization.arrayToDataTable([\n";
	output << labels;
	int i = 0;
	while ( i < nbunique-1) {
		output << "['" << names[i] << "', " << count[i] << "],\n";
		i++;
	}
	output << "['" << names[i] << "', " << count[i] << "]\n";
	output << "]);\n";
    output << "var optionspie = {\n";
    output << "title: '" << title << "',\n";
	output << "legend : {position: 'right', textStyle: {color: 'blue', fontSize: 10}},\n";
    output << "sliceVisibilityThreshold: 0.01,\n";
    output << "is3D: true\n";
    output << "};\n";

    output << "var chartpie = new google.visualization.PieChart(document.getElementById('" << divname << "'));\n";

    output << "chartpie.draw(datapie, optionspie);\n";
	output << " }\n";
}

void	create_debug_bar_stacked(string	labels, int	nbunique, vector<string>	names,vector<int>	criticals, vector<int>	majors, vector<int>	minors, string	title, string divname) {
	output << "google.charts.setOnLoadCallback(" << divname << ");\n";
    output << "function " << divname << "() {\n";
    output << "var databar = google.visualization.arrayToDataTable([\n";
    output << labels;
	
	int i = 0;
	while ( i < nbunique-1) {
		output << "['" << names[i] << "', " << criticals[i] << ", " << majors[i] << ", " << minors[i] << "],\n";
		i++;
	}
		output << "['" << names[i] << "', " << criticals[i] << ", " << majors[i] << ", " << minors[i] << "]\n";
	output << "]);\n";

    output << "var optionsbar = {title: '" << title << "', isStacked: true, explorer: {}};\n";
	output << "var chartbar = new google.visualization.BarChart(document.getElementById('" << divname << "'));\n";
    output << "chartbar.draw(databar, optionsbar);\n";
	output << "}\n";
 }

void	create_debug_bar(string	labels, int	nbunique, vector<string>	names,vector<int>	criticals, vector<int>	majors, vector<int>	minors, string	title, string divname) {
	output << "google.charts.setOnLoadCallback(" << divname << ");\n";
    output << "function " << divname << "() {\n";
    output << "var databar = google.visualization.arrayToDataTable([\n";
    output << labels;
	
	int i = 0;
	while ( i < nbunique-1) {
		output << "['" << names[i] << "', " << criticals[i] << ", " << majors[i] << ", " << minors[i] << "],\n";
		i++;
	}
		output << "['" << names[i] << "', " << criticals[i] << ", " << majors[i] << ", " << minors[i] << "]\n";
	output << "]);\n";

	output << "var optionsbar = {title: '" << title << "', vAxis: {minValue: 0}, explorer: {}};\n";
	output << "var chartbar = new google.visualization.ColumnChart(document.getElementById('" << divname << "'));\n";
    output << "chartbar.draw(databar, optionsbar);\n";
	output << "}\n";
}

int main()
{
    ifstream	file("db.csv");
	ofstream	log("yolog.txt");
	ofstream	csv("stats.csv");
	
	int maxrows = 20000;
	int maxrowscsv = 20000;
	int maxcols = 50;
	int maxcolscsv = 50;
	int datatype = 1;;
	vector< string > labels(maxcols);
	string labassigned ="";
	string labcategory ="";
	string labdatesub = "";
	string labupdated = "";
	string labstatus = "";
	string labimpact = "";
	string labviewstat = "";
	string labtag = "";
	string labclose = "";
	string labresolved = "";
	string labreport = "";
	string labmaj = "";
	string labmin = "";
	string labblock = "";
	string labcrash = "";
	string labid = "";
	string basemin = "2000-01-01";

	cout << "Select database type: \n";
	cout << "1) Mantis english\n";
	cout << "2) Mantis french (focus/spiders/giants)\n";
	cout << "3) Mantis french (cyanide) \n";
	cout << "4) Openproject\n";
	cout << "5) (WIP) Jira\n";
	cin >> datatype;
	system("cls");

	

	int mode = 10;
	bool bmindate = 0;
	bool bclosed = 0;
	bool bresolved = 0;
	bool bmajor = 0;
	bool bcritique = 0;
	bool bminor = 0;
	while (mode == 10) {
		cout << "Select mode: \n";
		cout << "0 : Default (all impacts, all status)\n";
		cout << "1 : Minimum date";
		if (bmindate == 1) cout << "\t\t\t[Set : " << basemin << "]"; else cout << "\t\t\t[Not set]";
		cout << "\n2 : Remove minimum date";
		cout << "\n3 : (WIP) Add/remove closed";
		if (bclosed == 1) cout << "\t\t[Set]"; else cout << "\t\t[Not set]";
		cout << "\n4 : (WIP) Add/remove resolved";
		if (bresolved == 1) cout << "\t\t[Set]"; else cout << "\t\t[Not set]";
		cout << "\n5 : (WIP) Add/remove minors";
		if (bminor == 1) cout << "\t\t[Set]"; else cout << "\t\t[Not set]";
		cout << "\n6 : (WIP) Add/remove majors";
		if (bmajor == 1) cout << "\t\t[Set]"; else cout << "\t\t[Not set]";
		cout << "\n7 : (WIP) Add/remove criticals";
		if (bcritique == 1) cout << "\t\t[Set]"; else cout << "\t\t[Not set]";
		switch (datatype) {
		case 1 : 
			//Mantis english
			labassigned = "Assigned To";
			labcategory = "Category";
			labdatesub = "Date Submitted";
			labupdated = "Updated";
			labstatus = "Status";
			labimpact = "Severity";
			labviewstat = "View";
			labclose = "closed";
			labresolved = "resolved";
			labreport = "Reporter";
			labmaj = "major";
			labmin = "minor";
			labblock = "block";
			labcrash = "crash";
			labid = "Id";
			cout << "\n8 : Change database \t\t\t[Mantis - English]";
			break;
		case 2 :
			//Mantis french
			labassigned = "Assign";
			labcategory = "gorie";
			labdatesub = "Date de soumission";
			labupdated = "jour";
			labstatus = "Statut";
			labimpact = "Impact";
			labviewstat = "Afficher les statuts";
			labclose = "ferm";
			labresolved = "solu";
			labreport = "Rapporteur";
			labmaj = "majeur";
			labmin = "mineur";
			labblock = "bloquant";
			labcrash = "critique";
			labid = "Identifiant";
			cout << "\n8 : Change database \t\t\t[Mantis - French (focus/spiders/giants)]";
			break;
		case 3 :
			//Mantis french cyanide
			labassigned = "Assign";
			labcategory = "gorie";
			labdatesub = "Date de soumission";
			labupdated = "jour";
			labstatus = "tat";
			labimpact = "Impact";
			labviewstat = "Afficher";
			labclose = "ferm";
			labresolved = "solu";
			labreport = "Rapporteur";
			labmaj = "majeur";
			labmin = "mineur";
			labblock = "bloquant";
			labcrash = "critique";
			labid = "Identifiant";
			cout << "\n8 : Change database \t\t\t[Mantis - French (cyanide)]";
			break;
		case 4 :
			//Openproject
			labassigned = "Assignee";
			labcategory = "Category";
			labdatesub = "Created on";
			labupdated = "Updated on";
			labstatus = "Status";
			labimpact = "Impact";
			labviewstat = "LOLOL";
			labreport = "Author";
			labtag = "Tags";
			labclose = "closed";
			labresolved = "resolved";
			labmaj = "Majeur";
			labmin = "Mineur";
			labblock = "Bloquant";
			labcrash = "Critique";
			labid = "ID";
			cout << "\n8 : Change database \t\t\t[Openproject]";
			break;
		case 5 :
			//jira
			cout << "\n8 : Change database \t\t\t[(WIP) Jira]";
			break;
		default : 
			cout << "\n8 : Change database \t\t\t[Unrecognized]";
			datatype = -1;
			break;
		};
		cout << "\n9 : Launch script with set parameters\n";
		cin >> mode;
		cout << "\n";

		switch (mode) {
		case 0 : 
			basemin = "2000-01-01";
			bclosed = 0;
			bresolved = 0;
			bminor = 0;
			bmajor = 0;
			bcritique = 0;
			mode = 0;
			break;
		case 1 :
			bmindate = 1;
			cout << "Set minimum date : (YYYY-MM-DD)\n";
			cin >> basemin;
			mode = 10;
			break;
		case 2 :
			bmindate = 0;
			basemin = "2000-01-01";
			mode = 10;
			break;
		case 3 :
			bclosed = !bclosed;
			mode = 10;
			break;
		case 4 :
			bresolved = !bresolved;
			mode = 10;
			break;
		case 5 :
			bminor = !bminor;
			mode = 10;
			break;
		case 6 :
			bmajor = !bmajor;
			mode = 10;
			break;
		case 7 :
			bcritique = !bcritique;
			mode = 10;
			break;
		case 8:
			cout << "Select database type: \n";
			cout << "1) Mantis english\n";
			cout << "2) Mantis french (focus/spiders/giants)\n";
			cout << "3) Mantis french (cyanide) \n";
			cout << "4) Openproject\n";
			cout << "5) (WIP) Jira\n";
			cin >> datatype;
			mode = 10;
			break;
		case 9:
			mode = 0;
			break;
		default :
			mode = 10;
			break;
		}
		system("cls");
	}
	
	if (datatype == -1) {
		return(0);
	}


	// ----------------------------------------------------------------------------------------------------------- get labels ----------------------------------------------------------------------------------------------------------- //
	string head;
	getline(file, head); 
    stringstream   lineStream(head);
    string         cell;
	int cols = 0;
	while(getline(lineStream, cell, ',')){
		labels[cols] = cell;
		cols++;
	}
	
	// ----------------------------------------------------------------------------------------------------------- get values from csv ----------------------------------------------------------------------------------------------------------- //
	maxcols = --cols;
	cols = 0;
	vector< vector<string> > csvextract(maxrows, vector<string>(maxcols+1));
	string	value;
	int rows = 0;
	bool iscommaloop = false;
	
	cout << "Extracting CSV : started\n";
	while ( file.good() )
	{
		getline( file, value, ',' );
		if ((((value.size() > 1) && (value[0] == '"') && (value[value.size()-1] != '"'))  || ((value.size() > 2) && (value[0] == '"') && (value[value.size()-1] == '"') && (value[value.size()-2] == '"'))) && (cols == maxcols) ) {
			if (std::count(value.begin(), value.end(), '"') % 2 == 0) {
				csvextract[rows][cols] = value.substr(0,value.find_last_of('\n'));
				rows++;
				cols = 0;
				csvextract[rows][cols] = value.substr(value.find_last_of('\n')+1);
				cols++;
			}
			else {
				iscommaloop = true;
				string extendnewline;
				while (iscommaloop) {
					getline( file, extendnewline, '\n' );
					value.append("\n");
					value.append(extendnewline);
					if (((extendnewline.size() > 2) && (extendnewline[extendnewline.size()-1] == '"') && (extendnewline[extendnewline.size()-2] != '"')) || ((extendnewline.size() > 3) && (extendnewline[extendnewline.size()-1] == '"') && (extendnewline[extendnewline.size()-2] == '"') && (extendnewline[extendnewline.size()-3] == '"')))
						iscommaloop = false;
				}
				csvextract[rows][cols] = value;
				rows++;
				cols = 0;
			}
		}
		else {
			// ----------------------------------------------------------------------------------------------------------- handle comma inside cell ----------------------------------------------------------------------------------------------------------- //
			if ((((value.size() > 1) && (value[0] == '"') && (value[value.size()-1] != '"')) || ((value.size() == 1) && (value[0] == '"')) || ((value.size() > 2) && (value[0] == '"') && (value[value.size()-1] == '"') && (value[value.size()-2] == '"'))) && (cols != maxcols) ) {

				if ((std::count(value.begin(), value.end(), '"') % 2 != 0) && (value.size() > 0)) {
					iscommaloop = true;
					string extendcomma;
					string checknext;
					while (iscommaloop) {
						getline( file, extendcomma, '"' );
						value.append(",");
						// failed SUB
						try 
						{ 
							value.append(extendcomma);
					    } 
						catch ( const std::bad_alloc & ) 
						{ 
							log << "Unsupported symbol at row : " << rows+2 << " cols : " << cols+1 << "\n After : " << checknext << value <<"\n";
							return (-1);
						} 
						getline( file, checknext, ',' );
						if (((std::count(checknext.begin(), checknext.end(), '"') % 2) == 0)) {
							value.append("\"");
							iscommaloop = false;
						}
						else {
							value.append("\"");
							value.append(checknext);
						}
					}
				}
			}
			// ----------------------------------------------------------------------------------------------------------- handle end of line ----------------------------------------------------------------------------------------------------------- //
			if ((value.size() > 1) && (value.find_last_of('\n') != string::npos) && (cols == maxcols)) {
				csvextract[rows][cols] = value.substr(0,value.find_last_of('\n'));
				rows++;
				cols = 0;
				csvextract[rows][cols] = value.substr(value.find_last_of('\n')+1);
			}
			// default
			else {
				csvextract[rows][cols] = value;
			}
			cols++;
		}
		if (((rows % 100) == 0) && (cols == 1)) {
			cout << "Extracting CSV : " << rows << " extracted\n";
		}
	}
	maxrows = --rows;
	cout << "Extracting CSV : " << maxrows << " done\n";
	rows=0;
	cols=0;
	string mindate = "3000-01-01";
	string lastmin = basemin;
	int labelsearch = 0;
	int date = -1;
	int status = -1;
	int updated = -1;
	int category = -1;
	int assigned = -1;
	int impact = -1;
	int reporter = -1;
	int id = -1;
	while (labelsearch <= maxcols) {
		if ((labels[labelsearch].find(labdatesub) != string::npos) && (labels[labelsearch].find(labupdated) == string::npos)){
			cout << "Found date at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			date = labelsearch;
		}
		if ((labels[labelsearch].find(labupdated) != string::npos) ){
			cout << "Found update at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			updated = labelsearch;
		}
		if ((labels[labelsearch].find(labstatus) != string::npos) && (labels[labelsearch].find(labviewstat) == string::npos) ){
			cout << "Found status at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			status = labelsearch;
		}
		if ((labels[labelsearch].find(labcategory) != string::npos) ){
			cout << "Found category at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			category = labelsearch;
		}
		if ((labels[labelsearch].find(labassigned) != string::npos) ){
			cout << "Found assigned at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			assigned = labelsearch;
		}
		if ((labels[labelsearch].find(labimpact) != string::npos) ){
			cout << "Found impact at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			impact = labelsearch;
		}
		if ((labels[labelsearch].find(labreport) != string::npos) ){
			cout << "Found report at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			reporter = labelsearch;
		}
		if ((labels[labelsearch].find(labid) != string::npos) ){
			cout << "Found id at column : " << labelsearch << " Named : " << labels[labelsearch] << "\n";
			id = labelsearch;
		}
		labelsearch++;
	}
	int nbunique = 0;
	int rows2 = 0;
	vector< string > dates(maxrows+1);
	vector< int > dmajor(maxrows+1); //dIMPACT = impact changes each day
	vector< int > dminor(maxrows+1);
	vector< int > dcritique(maxrows+1);
	vector< int > dmajorclose(maxrows+1); //dIMPACTclose = closed impact each day
	vector< int > dminorclose(maxrows+1);
	vector< int > dcritiqueclose(maxrows+1);
	vector< int > dmajorcreate(maxrows+1); // dIMPACTcreate = created impact each day
	vector< int > dminorcreate(maxrows+1);
	vector< int > dcritiquecreate(maxrows+1);
	vector< int > closed(maxrows+1); // closed tickets each day
	vector< int > open(maxrows+1); // opened tickets each day
	cout << "Getting/sorting unique dates : started\n";
	rows = 0;
	if ((date != -1) && (csvextract[rows][date].size() > 0) && ((csvextract[rows][date][2] == '/') || (csvextract[rows][date][2] == '-'))) {	
		while (rows <= maxrows) {
			string temp = csvextract[rows][date].substr(0,10);
			csvextract[rows][date] ="";
			csvextract[rows][date] = temp.substr(6,4);
			csvextract[rows][date].append("-");
			csvextract[rows][date].append(temp.substr(3,2));
			csvextract[rows][date].append("-");
			csvextract[rows][date].append(temp.substr(0,2));	
			rows++;
		}
		rows = 0;
	}
	else if (csvextract[rows][date].size() > 10) {
		while (rows <= maxrows) {
			string temp = csvextract[rows][date].substr(0,10);
			csvextract[rows][date] ="";
			csvextract[rows][date] = temp.substr(6,4);
			csvextract[rows][date].append("-");
			csvextract[rows][date].append(temp.substr(3,2));
			csvextract[rows][date].append("-");
			csvextract[rows][date].append(temp.substr(0,2));	
			rows++;
		}
		rows = 0;
	}
	if ((updated != -1) && (csvextract[rows][updated].size() > 0) && ((csvextract[rows][updated][2] == '/') || (csvextract[rows][updated][2] == '-'))) {	
		while (rows <= maxrows) {
			string temp2 = csvextract[rows][updated].substr(0,10);
			csvextract[rows][updated] = "";
			csvextract[rows][updated] = temp2.substr(6,4);
			csvextract[rows][updated].append("-");
			csvextract[rows][updated].append(temp2.substr(3,2));
			csvextract[rows][updated].append("-");
			csvextract[rows][updated].append(temp2.substr(0,2));
			rows++;
		}
		rows = 0;
	}
	else if (csvextract[rows][updated].size() > 10) {
		while (rows <= maxrows) {
			string temp2 = csvextract[rows][updated].substr(0,10);
			csvextract[rows][updated] = "";
			csvextract[rows][updated] = temp2.substr(6,4);
			csvextract[rows][updated].append("-");
			csvextract[rows][updated].append(temp2.substr(3,2));
			csvextract[rows][updated].append("-");
			csvextract[rows][updated].append(temp2.substr(0,2));
			rows++;
		}
		rows = 0;
	}
	rows = 0;
	// ----------------------------------------------------------------------------------------------------------- get min dates ----------------------------------------------------------------------------------------------------------- //
	while (rows2 <= maxrows) {
		while (rows <= maxrows) {
			if ((csvextract[rows][date] < mindate) && (csvextract[rows][date] > lastmin)){
				mindate = csvextract[rows][date];
			}
			if ((csvextract[rows][updated] < mindate) && (csvextract[rows][updated] > lastmin)) { 
				mindate = csvextract[rows][updated];
			}
			rows++;
		}
		if (lastmin != mindate) {
			dates[nbunique] = mindate;
			lastmin = mindate;
			mindate = "3000-01-01";
			nbunique++;
		}
		else {
			cout << "Getting/sorting unique dates : " << rows2 << " / " << maxrows << " treated, " << nbunique << " maximum unique dates found.\n";
			rows2 = maxrows;
		}
		if ((rows2 % 50) == 0) {
			cout << "Getting/sorting unique dates : " << rows2 << " / " << maxrows << " treated, " << nbunique << " unique dates found.\n";
		}
		rows=0;
		rows2++;
	}
	cout << "Getting/sorting unique dates : done\n";
	nbunique--;

	
	int rowsname=0;
	int rowscat=0;
	int rowsreport=0;
	int divider=100;
	if (maxrows < divider)
		divider = 1;
	rows2 = 0;
	vector< string > categories(maxrows+1);
	vector< int > catcount(maxrows+1); // cout = number of tickets for each category
	vector< int > catcrit(maxrows+1); // impact = all tickets for each category and impact
	vector< int > catmaj(maxrows+1);
	vector< int > catmin(maxrows+1);
	vector< int > catopencount(maxrows+1); // openimpact = open tickets for each category and impact
	vector< int > catopencrit(maxrows+1);
	vector< int > catopenmaj(maxrows+1);
	vector< int > catopenmin(maxrows+1);
	int nbuniquecat=0; // number of categories
	bool isuniquecat = true;
	vector< string > names(maxrows+1);
	vector< int > namescount(maxrows+1);
	vector< int > namescrit(maxrows+1);
	vector< int > namesmaj(maxrows+1);
	vector< int > namesmin(maxrows+1);
	vector< int > namesopencount(maxrows+1);
	vector< int > namesopencrit(maxrows+1);
	vector< int > namesopenmaj(maxrows+1);
	vector< int > namesopenmin(maxrows+1);
	int nbuniquename=0;
	bool isuniquename = true;
	vector< string > reporters(maxrows+1);
	vector< int > reporterscount(maxrows+1);
	vector< int > reporterscrit(maxrows+1);
	vector< int > reportersmaj(maxrows+1);
	vector< int > reportersmin(maxrows+1);
	vector< int > reportersopencount(maxrows+1);
	vector< int > reportersopencrit(maxrows+1);
	vector< int > reportersopenmaj(maxrows+1);
	vector< int > reportersopenmin(maxrows+1);
	int nbuniquereporter=0;
	bool isuniquereporter = true;
	cout << "Getting unique names & categories : started\n";
	// ----------------------------------------------------------------------------------------------------------- get cat & counts ----------------------------------------------------------------------------------------------------------- //
	while (rows2 <= maxrows) {
		while ((rowscat < nbuniquecat) && (isuniquecat != false)){
			if (csvextract[rows2][category] == categories[rowscat]) {
				isuniquecat = false;
				catcount[rowscat]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					catopencount[rowscat]++;
				if (csvextract[rows2][impact].find(labmaj) != string::npos) {
					catmaj[rowscat]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						catopenmaj[rowscat]++;
				}
				else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock) != string::npos)){
					catcrit[rowscat]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						catopencrit[rowscat]++;
				}
				else{
					catmin[rowscat]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						catopenmin[rowscat]++;
				}
			}
			rowscat++;
		}
		if (isuniquecat) {
			categories[nbuniquecat] = csvextract[rows2][category];
			catcount[nbuniquecat] = 1;
			if (csvextract[rows2][status].find(labclose) == string::npos)
				catopencount[rowscat]++;
			if (csvextract[rows2][impact].find(labmaj) != string::npos){
				catmaj[nbuniquecat]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					catopenmaj[rowscat]++;
			}
			else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock)!= string::npos)){
				catcrit[nbuniquecat]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					catopencrit[rowscat]++;
			}
			else{
				catmin[nbuniquecat]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					catopenmin[rowscat]++;
			}
			nbuniquecat++;
		}
		// ----------------------------------------------------------------------------------------------------------- get assigned & counts ----------------------------------------------------------------------------------------------------------- //
		while ((rowsname < nbuniquename) && (isuniquename != false)){
			if (csvextract[rows2][assigned] == names[rowsname]) {
				isuniquename = false;
				namescount[rowsname]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					namesopencount[rowsname]++;
				if (csvextract[rows2][impact].find(labmaj) != string::npos){
					namesmaj[rowsname]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						namesopenmaj[rowsname]++;
				}
				else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock)!= string::npos)){
					namescrit[rowsname]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						namesopencrit[rowsname]++;
				}
				else{
					namesmin[rowsname]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						namesopenmin[rowsname]++;
				}
			}
			rowsname++;
		}
		if (isuniquename) {
			names[nbuniquename] = csvextract[rows2][assigned];
			namescount[nbuniquename] = 1;
			if (csvextract[rows2][status].find(labclose) == string::npos)
				namesopencount[rowsname]++;
			if (csvextract[rows2][impact].find(labmaj) != string::npos){
				namesmaj[nbuniquename]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					namesopenmaj[rowsname]++;
			}
			else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock)!= string::npos)){
				namescrit[nbuniquename]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					namesopencrit[rowsname]++;
			}
			else{
				namesmin[nbuniquename]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					namesopenmin[rowsname]++;
			}
			nbuniquename++;
		}
		// ----------------------------------------------------------------------------------------------------------- get reporters & counts ----------------------------------------------------------------------------------------------------------- //
		while ((rowsreport < nbuniquereporter) && (isuniquereporter != false)){
			if (csvextract[rows2][reporter] == reporters[rowsreport]) {
				isuniquereporter = false;
				reporterscount[rowsreport]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					reportersopencount[rowsreport]++;
				if (csvextract[rows2][impact].find(labmaj) != string::npos){
					reportersmaj[rowsreport]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						reportersopenmaj[rowsreport]++;
				}
				else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock)!= string::npos)){
					reporterscrit[rowsreport]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						reportersopencrit[rowsreport]++;
				}
				else{
					reportersmin[rowsreport]++;
					if (csvextract[rows2][status].find(labclose) == string::npos)
						reportersopenmin[rowsreport]++;
				}
			}
			rowsreport++;
		}
		if (isuniquereporter) {
			reporters[nbuniquereporter] = csvextract[rows2][reporter];
			reporterscount[nbuniquereporter] = 1;
			if (csvextract[rows2][status].find(labclose) == string::npos)
				reportersopencount[rowsreport]++;
			if (csvextract[rows2][impact].find(labmaj) != string::npos){
				reportersmaj[nbuniquename]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					reportersopenmaj[rowsreport]++;
			}
			else if ((csvextract[rows2][impact].find(labcrash) != string::npos) || (csvextract[rows2][impact].find(labblock)!= string::npos)){
				reporterscrit[nbuniquename]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					reportersopencrit[rowsreport]++;
			}
			else{
				reportersmin[nbuniquereporter]++;
				if (csvextract[rows2][status].find(labclose) == string::npos)
					reportersopenmin[rowsreport]++;
			}
			nbuniquereporter++;
		}
		rowscat=0;
		rowsname=0;
		rowsreport=0;
		rows2++;
		isuniquename = true;
		isuniquecat = true;
		isuniquereporter = true;
		if ((rows2 % (maxrows/divider)) == 0) {
			cout << "Getting unique names & categories : " << rows2 << " / " << maxrows << " treated, " << nbuniquename << " unique assignation found, " << nbuniquecat << " unique categories found, " << nbuniquereporter << " unique reporters found.\n";
		}
	}
	cout << "Getting unique names & categories: done\n";
	
	// ----------------------------------------------------------------------------------------------------------- setting "nones" ----------------------------------------------------------------------------------------------------------- //

	
	rows=0;
	int rowsdate=0;
	
	vector< vector<int> > categoryprogress(nbunique+1, vector<int>(nbuniquecat*21)); 
	vector< vector<int> > reportersprogress(nbunique+1, vector<int>(nbuniquereporter*21));
	vector< vector<int> > assignprogress(nbunique+1, vector<int>(nbuniquename*21));// 1:created, 2 close, 3 open, 4 crit, 5 maj, 6 min, 7 total created, 8 total closed, 9 total open, 10 total crit, 11 total maj, 12 total min, 13 open crit, 14 open maj, 15 openmin, 16 closedcrit, 17closedmaj, 18closedmin, 19 totalopen crit, 20 totalopen maj, 21totalopen min
	//vector< vector<int> > statusprogress(nbunique, vector<int>(3)); // 1:open, 2 resolved, 3 close, 4 total open, total resolved, total close. Not worth it / already existing ?
	int offset = 21;
	int offsetcreated = 0;
	int offsetclosed = 1;
	int offsetopen = 2;
	int offsetcrit = 3;
	int offsetmaj = 4;
	int offsetmin = 5;
	int offsettotalcreated = 6;
	int offsettotalclosed = 7;
	int offsettotalopen = 8;
	int offsettotalcrit = 9;
	int offsettotalmaj = 10;
	int offsettotalmin = 11;
	int offsetopencrit = 12;
	int offsetopenmaj = 13;
	int offsetopenmin = 14;
	int offsetclosedcrit = 15;
	int offsetclosedmaj = 16;
	int offsetclosedmin = 17;
	int offsettotalopencrit = 18;
	int offsettotalopenmaj = 19;
	int offsettotalopenmin = 20;

	int catidfound = -1;
	int reporteridfound = -1;
	int assignidfound = -1;
	int idfound = 0;

	cout << "Counting : started\n";
	// ----------------------------------------------------------------------------------------------------------- get dates count ----------------------------------------------------------------------------------------------------------- //
	while (rows <= maxrows) {
		while (rowsdate < nbunique) {

			while (idfound < nbuniquecat) {
				if (csvextract[rows][category] == categories[idfound]) {
					catidfound = idfound;
					idfound = nbuniquecat;
				}
				idfound++;
			}
			idfound = 0;
			while (idfound < nbuniquename) {
				if (csvextract[rows][assigned] == names[idfound]) {
					assignidfound = idfound;
					idfound = nbuniquename;
				}
				idfound++;
			}
			idfound = 0;
			while (idfound < nbuniquereporter) {
				if (csvextract[rows][reporter] == reporters[idfound]) {
					reporteridfound = idfound;
					idfound = nbuniquereporter;
				}
				idfound++;
			}
			if (csvextract[rows][date] == dates[rowsdate]) {
				open[rowsdate]++;
				categoryprogress[rowsdate][catidfound*offset+offsetopen]++;
				reportersprogress[rowsdate][reporteridfound*offset+offsetopen]++;
				assignprogress[rowsdate][assignidfound*offset+offsetopen]++;
				categoryprogress[rowsdate][catidfound*offset+offsetcreated]++;
				reportersprogress[rowsdate][reporteridfound*offset+offsetcreated]++;
				assignprogress[rowsdate][assignidfound*offset+offsetcreated]++;

				if (csvextract[rows][impact].find(labmaj) != string::npos) {
					dmajor[rowsdate]++;
					dmajorcreate[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetmaj]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetmaj]++;
					assignprogress[rowsdate][assignidfound*offset+offsetmaj]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopenmaj]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopenmaj]++;
					assignprogress[rowsdate][assignidfound*offset+offsetopenmaj]++;
				}
				else if ((csvextract[rows][impact].find(labcrash) != string::npos) || (csvextract[rows][impact].find(labblock) != string::npos)) {
					dcritique[rowsdate]++;
					dcritiquecreate[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetcrit]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetcrit]++;
					assignprogress[rowsdate][assignidfound*offset+offsetcrit]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopencrit]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopencrit]++;
					assignprogress[rowsdate][assignidfound*offset+offsetopencrit]++;
				}
				else {
					dminor[rowsdate]++;
					dminorcreate[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetmin]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetmin]++;
					assignprogress[rowsdate][assignidfound*offset+offsetmin]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopenmin]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopenmin]++;
					assignprogress[rowsdate][assignidfound*offset+offsetopenmin]++;
				}

			}
			if ((csvextract[rows][updated] == dates[rowsdate]) && (csvextract[rows][status].find(labclose) != string::npos)) {
				closed[rowsdate]++;
				categoryprogress[rowsdate][catidfound*offset+offsetclosed]++;
				reportersprogress[rowsdate][reporteridfound*offset+offsetclosed]++;
				assignprogress[rowsdate][assignidfound*offset+offsetclosed]++;
				categoryprogress[rowsdate][catidfound*offset+offsetopen]--;
				reportersprogress[rowsdate][reporteridfound*offset+offsetopen]--;
				assignprogress[rowsdate][assignidfound*offset+offsetopen]--;
				if (csvextract[rows][impact].find(labmaj) != string::npos) {
					dmajor[rowsdate]--;
					dmajorclose[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetclosedmaj]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetclosedmaj]++;
					assignprogress[rowsdate][assignidfound*offset+offsetclosedmaj]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopenmaj]--;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopenmaj]--;
					assignprogress[rowsdate][assignidfound*offset+offsetopenmaj]--;
				}
				else if ((csvextract[rows][impact].find(labcrash) != string::npos) || (csvextract[rows][impact].find(labblock) != string::npos)) {
					dcritique[rowsdate]--;
					dcritiqueclose[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetclosedcrit]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetclosedcrit]++;
					assignprogress[rowsdate][assignidfound*offset+offsetclosedcrit]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopencrit]--;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopencrit]--;
					assignprogress[rowsdate][assignidfound*offset+offsetopencrit]--;
				}
				else {
					dminor[rowsdate]--;
					dminorclose[rowsdate]++;
					categoryprogress[rowsdate][catidfound*offset+offsetclosedmin]++;
					reportersprogress[rowsdate][reporteridfound*offset+offsetclosedmin]++;
					assignprogress[rowsdate][assignidfound*offset+offsetclosedmin]++;
					categoryprogress[rowsdate][catidfound*offset+offsetopenmin]--;
					reportersprogress[rowsdate][reporteridfound*offset+offsetopenmin]--;
					assignprogress[rowsdate][assignidfound*offset+offsetopenmin]--;
				}
			}
			catidfound = -1;
			reporteridfound = -1;
			assignidfound = -1;
			idfound = 0;
			rowsdate++;
		}

		if ((rows % (maxrows/divider)) == 0) {
			int test = ((double)rows/(double)maxrows)*100;
			cout << "[" <<  test << "%] ";
			cout << "Counting : " << rows << " / " << maxrows << " treated\n";
		}
		rowsdate=0;
		rows++;
	}

	rows=0;
	while (rows < nbuniquecat) {
		if (categories[rows] == "") {
			categories[rows] = "None";
		}
		replaceAll(categories[rows], "'", "\\'");
		rows++;
	}
	rows=0;
	while (rows < nbuniquename) {
		if (names[rows] == "") {
			names[rows] = "None";
		}
		replaceAll(names[rows], "'", "\\'");
		rows++;
	}
	rows=0;
	while (rows < nbuniquereporter) {
		if (reporters[rows] == "") {
			reporters[rows] = "None";
		}
		replaceAll(reporters[rows], "'", "\\'");
		rows++;
	}

	cout << "Counting : aggregating data\n";

	vector< int > totalclosed(maxrows+1); // total closed tickets each day
	vector< int > totalopen(maxrows+1); // total open tickets each day
	vector< int > totalcreated(maxrows+1); // total created tickets each day
	vector< int > totalcrit(maxrows+1); // totalIMPACT = total open tickets by impact each day
	vector< int > totalmaj(maxrows+1);
	vector< int > totalmin(maxrows+1);
	vector< int > totalcritall(maxrows+1); // totalIMPACTall = total tickets by impact each day
	vector< int > totalmajall(maxrows+1);
	vector< int > totalminall(maxrows+1);
	vector< int > totalcritclose(maxrows+1); // totalIMPACTclose = total closed tickets by impact each day
	vector< int > totalmajclose(maxrows+1);
	vector< int > totalminclose(maxrows+1);
	totalcrit[0] = dcritique[0];
	totalmaj[0] = dmajor[0];
	totalmin[0] = dminor[0];
	totalcritall[0] = dcritique[0] + dcritiqueclose[0];
	totalmajall[0] = dmajor[0] + dmajorclose[0];
	totalminall[0] = dminor[0] + dminorclose[0];
	totalcritclose[0] = dcritiqueclose[0];
	totalmajclose[0] = dmajorclose[0];
	totalminclose[0] = dminorclose[0];
	totalclosed[0] = closed[0];
	totalcreated[0] = open[0];
	totalopen[0] = open[0] - closed[0];
	
	catidfound = 0;
	reporteridfound = 0;
	assignidfound = 0;
	
	while (reporteridfound < nbuniquereporter) {
		reportersprogress[0][reporteridfound*offset+offsettotalcreated]= reportersprogress[0][reporteridfound*offset+offsetcreated]; 
		reportersprogress[0][reporteridfound*offset+offsettotalclosed]= reportersprogress[0][reporteridfound*offset+offsetclosed]; 
		reportersprogress[0][reporteridfound*offset+offsettotalopen]= reportersprogress[0][reporteridfound*offset+offsetopen];

		reportersprogress[0][reporteridfound*offset+offsettotalcrit]= reportersprogress[0][reporteridfound*offset+offsetcrit]; 
		reportersprogress[0][reporteridfound*offset+offsettotalmaj]= reportersprogress[0][reporteridfound*offset+offsetmaj]; 
		reportersprogress[0][reporteridfound*offset+offsettotalmin]= reportersprogress[0][reporteridfound*offset+offsetmin]; 

		reportersprogress[0][reporteridfound*offset+offsettotalopencrit]= reportersprogress[0][reporteridfound*offset+offsetopencrit]; 
		reportersprogress[0][reporteridfound*offset+offsettotalopenmaj]= reportersprogress[0][reporteridfound*offset+offsetopenmaj]; 
		reportersprogress[0][reporteridfound*offset+offsettotalopenmin]= reportersprogress[0][reporteridfound*offset+offsetopenmin]; 
		reporteridfound++;
	}
	
	while (catidfound < nbuniquecat) {
		categoryprogress[0][catidfound*offset+offsettotalcreated]= categoryprogress[0][catidfound*offset+offsetcreated]; 
		categoryprogress[0][catidfound*offset+offsettotalclosed]= categoryprogress[0][catidfound*offset+offsetclosed]; 
		categoryprogress[0][catidfound*offset+offsettotalopen]= categoryprogress[0][catidfound*offset+offsetopen];

		categoryprogress[0][catidfound*offset+offsettotalcrit]= categoryprogress[0][catidfound*offset+offsetcrit]; 
		categoryprogress[0][catidfound*offset+offsettotalmaj]= categoryprogress[0][catidfound*offset+offsetmaj]; 
		categoryprogress[0][catidfound*offset+offsettotalmin]= categoryprogress[0][catidfound*offset+offsetmin]; 

		categoryprogress[0][catidfound*offset+offsettotalopencrit]= categoryprogress[0][catidfound*offset+offsetopencrit]; 
		categoryprogress[0][catidfound*offset+offsettotalopenmaj]= categoryprogress[0][catidfound*offset+offsetopenmaj]; 
		categoryprogress[0][catidfound*offset+offsettotalopenmin]= categoryprogress[0][catidfound*offset+offsetopenmin]; 
		catidfound++;
	}

	while (assignidfound < nbuniquename) {
		assignprogress[0][assignidfound*offset+offsettotalcreated]= assignprogress[0][assignidfound*offset+offsetcreated]; 
		assignprogress[0][assignidfound*offset+offsettotalclosed]= assignprogress[0][assignidfound*offset+offsetclosed]; 
		assignprogress[0][assignidfound*offset+offsettotalopen]= assignprogress[0][assignidfound*offset+offsetopen];

		assignprogress[0][assignidfound*offset+offsettotalcrit]= assignprogress[0][assignidfound*offset+offsetcrit]; 
		assignprogress[0][assignidfound*offset+offsettotalmaj]= assignprogress[0][assignidfound*offset+offsetmaj]; 
		assignprogress[0][assignidfound*offset+offsettotalmin]= assignprogress[0][assignidfound*offset+offsetmin]; 

		assignprogress[0][assignidfound*offset+offsettotalopencrit]= assignprogress[0][assignidfound*offset+offsetopencrit]; 
		assignprogress[0][assignidfound*offset+offsettotalopenmaj]= assignprogress[0][assignidfound*offset+offsetopenmaj]; 
		assignprogress[0][assignidfound*offset+offsettotalopenmin]= assignprogress[0][assignidfound*offset+offsetopenmin]; 
		assignidfound++;
	}
	rows = 1;
	assignidfound = 0;
	catidfound = 0;
	reporteridfound = 0;
	while (rows <= nbunique) {

		while (reporteridfound < nbuniquereporter) {
			reportersprogress[rows][reporteridfound*offset+offsettotalcreated]= reportersprogress[rows-1][reporteridfound*offset+offsettotalcreated] + reportersprogress[rows][reporteridfound*offset+offsetcreated]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalclosed]= reportersprogress[rows-1][reporteridfound*offset+offsettotalclosed] + reportersprogress[rows][reporteridfound*offset+offsetclosed]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalopen]= reportersprogress[rows-1][reporteridfound*offset+offsettotalopen] + reportersprogress[rows][reporteridfound*offset+offsetopen];

			reportersprogress[rows][reporteridfound*offset+offsettotalcrit]= reportersprogress[rows-1][reporteridfound*offset+offsettotalcrit] + reportersprogress[rows][reporteridfound*offset+offsetcrit]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalmaj]= reportersprogress[rows-1][reporteridfound*offset+offsettotalmaj] + reportersprogress[rows][reporteridfound*offset+offsetmaj]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalmin]= reportersprogress[rows-1][reporteridfound*offset+offsettotalmin] + reportersprogress[rows][reporteridfound*offset+offsetmin]; 

			reportersprogress[rows][reporteridfound*offset+offsettotalopencrit]= reportersprogress[rows-1][reporteridfound*offset+offsettotalopencrit] + reportersprogress[rows][reporteridfound*offset+offsetopencrit]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalopenmaj]= reportersprogress[rows-1][reporteridfound*offset+offsettotalopenmaj] + reportersprogress[rows][reporteridfound*offset+offsetopenmaj]; 
			reportersprogress[rows][reporteridfound*offset+offsettotalopenmin]= reportersprogress[rows-1][reporteridfound*offset+offsettotalopenmin] + reportersprogress[rows][reporteridfound*offset+offsetopenmin]; 
			reporteridfound++;
		}
			
		while (catidfound < nbuniquecat) {
			categoryprogress[rows][catidfound*offset+offsettotalcreated]= categoryprogress[rows-1][catidfound*offset+offsettotalcreated] + categoryprogress[rows][catidfound*offset+offsetcreated]; 
			categoryprogress[rows][catidfound*offset+offsettotalclosed]= categoryprogress[rows-1][catidfound*offset+offsettotalclosed] + categoryprogress[rows][catidfound*offset+offsetclosed]; 
			categoryprogress[rows][catidfound*offset+offsettotalopen]= categoryprogress[rows-1][catidfound*offset+offsettotalopen] + categoryprogress[rows][catidfound*offset+offsetopen];

			categoryprogress[rows][catidfound*offset+offsettotalcrit]= categoryprogress[rows-1][catidfound*offset+offsettotalcrit] + categoryprogress[rows][catidfound*offset+offsetcrit]; 
			categoryprogress[rows][catidfound*offset+offsettotalmaj]= categoryprogress[rows-1][catidfound*offset+offsettotalmaj] + categoryprogress[rows][catidfound*offset+offsetmaj]; 
			categoryprogress[rows][catidfound*offset+offsettotalmin]= categoryprogress[rows-1][catidfound*offset+offsettotalmin] + categoryprogress[rows][catidfound*offset+offsetmin]; 

			categoryprogress[rows][catidfound*offset+offsettotalopencrit]= categoryprogress[rows-1][catidfound*offset+offsettotalopencrit] + categoryprogress[rows][catidfound*offset+offsetopencrit]; 
			categoryprogress[rows][catidfound*offset+offsettotalopenmaj]= categoryprogress[rows-1][catidfound*offset+offsettotalopenmaj] + categoryprogress[rows][catidfound*offset+offsetopenmaj]; 
			categoryprogress[rows][catidfound*offset+offsettotalopenmin]= categoryprogress[rows-1][catidfound*offset+offsettotalopenmin] + categoryprogress[rows][catidfound*offset+offsetopenmin]; 
			catidfound++;
		}
			
		while (assignidfound < nbuniquename) {
			assignprogress[rows][assignidfound*offset+offsettotalcreated]= assignprogress[rows-1][assignidfound*offset+offsettotalcreated] + assignprogress[rows][assignidfound*offset+offsetcreated]; 
			assignprogress[rows][assignidfound*offset+offsettotalclosed]= assignprogress[rows-1][assignidfound*offset+offsettotalclosed] + assignprogress[rows][assignidfound*offset+offsetclosed]; 
			assignprogress[rows][assignidfound*offset+offsettotalopen]= assignprogress[rows-1][assignidfound*offset+offsettotalopen] + assignprogress[rows][assignidfound*offset+offsetopen];

			assignprogress[rows][assignidfound*offset+offsettotalcrit]= assignprogress[rows-1][assignidfound*offset+offsettotalcrit] + assignprogress[rows][assignidfound*offset+offsetcrit]; 
			assignprogress[rows][assignidfound*offset+offsettotalmaj]= assignprogress[rows-1][assignidfound*offset+offsettotalmaj] + assignprogress[rows][assignidfound*offset+offsetmaj]; 
			assignprogress[rows][assignidfound*offset+offsettotalmin]= assignprogress[rows-1][assignidfound*offset+offsettotalmin] + assignprogress[rows][assignidfound*offset+offsetmin]; 

			assignprogress[rows][assignidfound*offset+offsettotalopencrit]= assignprogress[rows-1][assignidfound*offset+offsettotalopencrit] + assignprogress[rows][assignidfound*offset+offsetopencrit]; 
			assignprogress[rows][assignidfound*offset+offsettotalopenmaj]= assignprogress[rows-1][assignidfound*offset+offsettotalopenmaj] + assignprogress[rows][assignidfound*offset+offsetopenmaj]; 
			assignprogress[rows][assignidfound*offset+offsettotalopenmin]= assignprogress[rows-1][assignidfound*offset+offsettotalopenmin] + assignprogress[rows][assignidfound*offset+offsetopenmin]; 
			assignidfound++;
		}
		assignidfound = 0;
		catidfound = 0;
		reporteridfound = 0;

		totalclosed[rows] = totalclosed[rows-1] + closed[rows];
		totalopen[rows] = open[rows] + totalopen[rows-1] - closed[rows];
		totalcreated[rows] = open[rows] + totalcreated[rows-1];

		totalcrit[rows] = totalcrit[rows-1] + dcritique[rows];
		totalmaj[rows] = totalmaj[rows-1] + dmajor[rows];
		totalmin[rows] = totalmin[rows-1] + dminor[rows];

		totalcritclose[rows] = totalcritclose[rows-1] + dcritiqueclose[rows];
		totalmajclose[rows] = totalmajclose[rows-1] + dmajorclose[rows];
		totalminclose[rows] = totalminclose[rows-1] + dminorclose[rows];

		totalcritall[rows] = totalcritall[rows-1] + dcritique[rows] + dcritiqueclose[rows];
		totalmajall[rows] = totalmajall[rows-1] + dmajor[rows] + dmajorclose[rows];
		totalminall[rows] = totalminall[rows-1] + dminor[rows] + dminorclose[rows];
		rows++;
	}
	cout << "Counting : done\n";
	cout << "Generating html : started\n";
	// ----------------------------------------------------------------------------------------------------------- html start ----------------------------------------------------------------------------------------------------------- //
	output << "<html><head><script type=\"text/javascript\" src=\"https://www.gstatic.com/charts/loader.js\"></script><script type=\"text/javascript\">\n";
	output << "google.charts.load('current', {'packages':['corechart', 'bar']});\n";
	create_debug_curve((string) "['Date', 'Open', 'New', 'Closed'],", nbunique, dates, totalopen, totalcreated, totalclosed, "Debug curve", "chartdate_div");
	cout << "Generating html : debug curve done\n";
	
	create_debug_curve((string) "['Date', 'Critiques', 'Majors', 'Minors'],", nbunique, dates, totalcrit, totalmaj, totalmin, "Open impact curves", "chartimpact_div");
	cout << "Generating html : impacts curve done\n";
	
	create_debug_curve((string) "['Dates', 'Criticals', 'Majors', 'Minors'],", nbunique, dates, totalcritall, totalmajall, totalminall, "Total impacts curve", "chartdatebar_div");
	cout << "Generating html : total impacts curve done\n";	
	
	create_multiple_debug_curve(categories, nbuniquecat, nbunique, dates, categoryprogress, offsettotalopen, offset, "Categories open curves", "chartcattotal_div");
	cout << "Generating html : categories total open tickets curve done\n";
	
	create_multiple_debug_curve(reporters, nbuniquereporter, nbunique, dates, reportersprogress, offsettotalopen, offset, "Reporter open curves", "chartreporttotal_div");
	cout << "Generating html : reporters total open tickets curve done\n";
	
	create_multiple_debug_curve(names, nbuniquename, nbunique, dates, assignprogress, offsettotalopen, offset, "Assignation open curves", "chartnametotal_div");
	cout << "Generating html : assigned total open tickets curve done\n";
	
	
	create_multiple_debug_curve(reporters, nbuniquereporter, nbunique, dates, reportersprogress, offsettotalcrit, offset, "Reporter critical curves", "chartreporttotalcrit_div");
	cout << "Generating html : reporters total critical tickets curve done\n";
	create_multiple_debug_curve(reporters, nbuniquereporter, nbunique, dates, reportersprogress, offsettotalmaj, offset, "Reporter major curves", "chartreporttotalmaj_div");
	cout << "Generating html : reporters total major tickets curve done\n";
	create_multiple_debug_curve(reporters, nbuniquereporter, nbunique, dates, reportersprogress, offsettotalmin, offset, "Reporter minor curves", "chartreporttotalmin_div");
	cout << "Generating html : reporters total minor tickets curve done\n";

	create_debug_pie((string) "['Names', 'Tickets count'],", nbuniquename, names, namescount, "Assignation distribution", "chartnames_div");
	cout << "Generating html : assigned pie done\n";

	create_debug_pie((string) "['Names', 'Tickets count'],", nbuniquereporter, reporters, reporterscount, "Reporters distribution", "chartreporters_div");
	cout << "Generating html : reporters pie done\n";

	create_debug_pie((string) "['Categories', 'Tickets count'],", nbuniquecat, categories, catcount, "Categories distribution", "chartcat_div");
	cout << "Generating html : category pie done\n";
	
	create_debug_bar_stacked((string) "['Categories', 'Criticals', 'Majors', 'Minors'],", nbuniquecat, categories, catcrit, catmaj, catmin, "Categories by impact", "chartcatbar_div");
	cout << "Generating html : category bars done\n";
		
	create_debug_bar((string) "['Reporter', 'Criticals', 'Majors', 'Minors'],", nbuniquereporter, reporters, reporterscrit, reportersmaj, reportersmin, "Impacts by reporters", "chartreporterbar_div");
	cout << "Generating html : reporters bar done\n";

	output << "\n</script></head><body>\n";
	output << "<div id=\"chartdate_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartimpact_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartdatebar_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartnames_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporters_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartcat_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartcatbar_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporterbar_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartcattotal_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporttotal_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartnametotal_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporttotalcrit_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporttotalmaj_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<div id=\"chartreporttotalmin_div\" style=\"width: 900px; height: 500px;\"></div>\n";
	output << "<body></html>";
	cout << "Generating html : done\n";
	
	// ----------------------------------------------------------------------------------------------------------- csv start ----------------------------------------------------------------------------------------------------------- //
	cout << "Generating csv : started\n";
	rows = 0;
	cols = 0;
	while (rows < nbuniquename + nbunique + nbuniquecat + nbuniquereporter + 4/*nbunique+nbuniquename+nbuniquecat+nbuniquereporter+nbunique+5*/) {
		while (cols <= maxcolscsv) {
	// ----------------------------------------------------------------------------------------------------------- dates ----------------------------------------------------------------------------------------------------------- //
			if (rows < nbunique+1) {
				if (rows == 0) {
					if (cols == 0) {
						cout << "Generating csv : debug curve\n";
						csv << "Dates,";
					}
					else if (cols == 1)
						csv << "Opened,";
					else if (cols == 2)
						csv << "Closed,";
					else if (cols == 3)
						csv << "Total Created,";
					else if (cols == 4)
						csv << "Total Opened,";
					else if (cols == 5)
						csv << "Total Closed,";
					else if (cols == 6)
						csv << "Criticals,";
					else if (cols == 7)
						csv << "Majors,";
					else if (cols == 8)
						csv << "Minors,";
					else if (cols == 9)
						csv << "Total open Criticals,";
					else if (cols == 10)
						csv << "Total open Majors,";
					else if (cols == 11)
						csv << "Total open Minors,";
					else if (cols == 12)
						csv << "Total closed Criticals,";
					else if (cols == 13)
						csv << "Total closed Majors,";
					else if (cols == 14)
						csv << "Total closed Minors,";
					else if (cols == 15)
						csv << "Created Criticals,";
					else if (cols == 16)
						csv << "Created Majors,";
					else if (cols == 17)
						csv << "Created Minors,";
					else if (cols == 18)
						csv << "Total Criticals,";
					else if (cols == 19)
						csv << "Total Majors,";
					else if (cols == 20)
						csv << "Total Minors,";
					else
						csv << ",";
				}
				else {
					if (cols == 0)
						csv << dates[rows-1] << ",";
					else if (cols == 1)
						csv << open[rows-1] << ",";
					else if (cols == 2)
						csv << closed[rows-1] << ",";
					else if (cols == 3)
						csv << totalcreated[rows-1] << ",";
					else if (cols == 4)
						csv << totalopen[rows-1] << ",";
					else if (cols == 5)
						csv << totalclosed[rows-1] << ",";
					else if (cols == 6)
						csv << dcritique[rows-1] << ",";
					else if (cols == 7)
						csv << dmajor[rows-1] << ",";
					else if (cols == 8)
						csv << dminor[rows-1] << ",";
					else if (cols == 9)
						csv << totalcrit[rows-1] << ",";
					else if (cols == 10)
						csv << totalmaj[rows-1] << ",";
					else if (cols == 11)
						csv << totalmin[rows-1] << ",";
					else if (cols == 12)
						csv << totalcritclose[rows-1] << ",";
					else if (cols == 13)
						csv << totalmajclose[rows-1] << ",";
					else if (cols == 14)
						csv << totalminclose[rows-1] << ",";
					else if (cols == 15)
						csv << dcritiquecreate[rows-1] << ",";
					else if (cols == 16)
						csv << dmajorcreate[rows-1] << ",";
					else if (cols == 17)
						csv << dminorcreate[rows-1] << ",";
					else if (cols == 18)
						csv << totalcritall[rows-1] << ",";
					else if (cols == 19)
						csv << totalmajall[rows-1] << ",";
					else if (cols == 20)
						csv << totalminall[rows-1] << ",";
					else
						csv << ",";
				}
			}
		// ----------------------------------------------------------------------------------------------------------- names ----------------------------------------------------------------------------------------------------------- //
			if ((rows >= nbunique+1) && (rows < nbuniquename + nbunique + 2)) {
				if (rows == nbunique+1) {
					if (cols == 0) {
						csv << "Assign name,";
						cout << "Generating csv : debug curve done\n";
						cout << "Generating csv : assignee stats\n";
					}
					else if (cols == 1)
						csv << "Count,";
					else if (cols == 2)
						csv << "Criticals,";
					else if (cols == 3)
						csv << "Majors,";
					else if (cols == 4)
						csv << "Minors,";
					else if (cols == 5)
						csv << "Open Criticals,";
					else if (cols == 6)
						csv << "Open Majors,";
					else if (cols == 7)
						csv << "Open Minors,";
					else if (cols == 8)
						csv << "Open count,";
					else
						csv << ",";
				}
				else {
					if (cols == 0)
						csv << names[rows-nbunique-2] << ",";
					else if (cols == 1)
						csv << namescount[rows-nbunique-2] << ",";
					else if (cols == 2)
						csv << namescrit[rows-nbunique-2] << ",";
					else if (cols == 3)
						csv << namesmaj[rows-nbunique-2] << ",";
					else if (cols == 4)
						csv << namesmin[rows-nbunique-2] << ",";
					else if (cols == 5)
						csv << namesopencrit[rows-nbunique-2] << ",";
					else if (cols == 6)
						csv << namesopenmaj[rows-nbunique-2] << ",";
					else if (cols == 7)
						csv << namesopenmin[rows-nbunique-2] << ",";
					else if (cols == 8)
						csv << namesopencount[rows-nbunique-2] << ",";
					else
						csv << ",";
				}
			}
		// ----------------------------------------------------------------------------------------------------------- categories ----------------------------------------------------------------------------------------------------------- //
			if ((rows >= nbuniquename + nbunique + 2) && (rows < nbuniquename + nbunique + nbuniquecat + 3)) {
				if (rows == nbuniquename + nbunique + 2) {
					if (cols == 0) {
						cout << "Generating csv : assignee stats done\n";
						cout << "Generating csv : categories stats\n";
						csv << "Category,";
					}
					else if (cols == 1)
						csv << "Count,";
					else if (cols == 2)
						csv << "Criticals,";
					else if (cols == 3)
						csv << "Majors,";
					else if (cols == 4)
						csv << "Minors,";
					else if (cols == 5)
						csv << "Open Criticals,";
					else if (cols == 6)
						csv << "Open Majors,";
					else if (cols == 7)
						csv << "Open Minors,";
					else if (cols == 8)
						csv << "Open count,";
					else
						csv << ",";
				}
				else {
					if (cols == 0)
						csv << categories[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 1)
						csv << catcount[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 2)
						csv << catcrit[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 3)
						csv << catmaj[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 4)
						csv << catmin[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 5)
						csv << catopencrit[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 6)
						csv << catopenmaj[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 7)
						csv << catopenmin[rows-nbunique-nbuniquename-3] << ",";
					else if (cols == 8)
						csv << catopencount[rows-nbunique-nbuniquename-3] << ",";
					else
						csv << ",";
				}
			}		
			// ----------------------------------------------------------------------------------------------------------- reporters ----------------------------------------------------------------------------------------------------------- //
			if ((rows >= nbuniquename + nbunique + nbuniquecat + 3) && (rows < nbuniquename + nbunique + nbuniquecat + nbuniquereporter + 4)) {
				if (rows == nbuniquename + nbunique + nbuniquecat + 3) {
					if (cols == 0) {	
						cout << "Generating csv : categories stats done\n";
						cout << "Generating csv : reporters stats\n";
						csv << "Reporter,";
					}
					else if (cols == 1)
						csv << "Count,";
					else if (cols == 2)
						csv << "Criticals,";
					else if (cols == 3)
						csv << "Majors,";
					else if (cols == 4)
						csv << "Minors,";
					else if (cols == 5)
						csv << "Open Criticals,";
					else if (cols == 6)
						csv << "Open Majors,";
					else if (cols == 7)
						csv << "Open Minors,";
					else if (cols == 8)
						csv << "Open count,";
					else
						csv << ",";
				}
				else {
					if (cols == 0)
						csv << reporters[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 1)
						csv << reporterscount[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 2)
						csv << reporterscrit[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 3)
						csv << reportersmaj[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 4)
						csv << reportersmin[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 5)
						csv << reportersopencrit[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 6)
						csv << reportersopenmaj[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 7)
						csv << reportersopenmin[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else if (cols == 8)
						csv << reporterscount[rows-nbunique-nbuniquename-nbuniquecat-4] << ",";
					else
						csv << ",";
				}
			}	
			cols++;
		}
		csv << "\n";
		cols = 0;
		rows++;
	}
	cout << "Generating csv : reporters stats done\n";
	cout << "Generating csv : reporters curve\n";
	int i = 0;
	int y = 0;
	int internalrow = 0;
	while (i < nbuniquereporter) {
		while (internalrow < nbunique) {
			while (y < maxcolscsv) {
				if (internalrow == 0) {
					if (y == 0){
						cout << "Generating csv : reporters curve - " << reporters[i] << "\n";
						csv << reporters[i] << ",";
					}
					else if (y == 1)
						csv << "Created,";
					else if (y == 2)
						csv << "Closed,";
					else if (y == 3)
						csv << "Opened,";
					else if (y == 4)
						csv << "Criticals,";
					else if (y == 5)
						csv << "Majors,";
					else if (y == 6)
						csv << "Minors,";
					else if (y == 7)
						csv << "Total created,";
					else if (y == 8)
						csv << "Total closed,";
					else if (y == 9)
						csv << "Total open,";
					else if (y == 10)
						csv << "Total criticals,";
					else if (y == 11)
						csv << "Total majors,";
					else if (y == 12)
						csv << "Total minors,";
					else if (y == 13) 
						csv << "Open criticals,";
					else if (y == 14)
						csv << "Open majors,";
					else if (y == 15)
						csv << "Open minors,";
					else if (y == 16)
						csv << "Closed criticals,";
					else if (y == 17)
						csv << "Closed majors,";
					else if (y == 18)
						csv << "Closed minors,";
					else if (y == 19)
						csv << "Total open criticals,";
					else if (y == 20)
						csv << "Total open majors,";
					else if (y == 21)
						csv << "Total open minors,";
					else
						csv << ",";
				}
				else {
					if (y == 0)
						csv << dates[internalrow] << ",";
					else if (y == 1)
						csv << reportersprogress[internalrow][i*offset+offsetcreated] << ",";
					else if (y == 2)
						csv << reportersprogress[internalrow][i*offset+offsetclosed] << ",";
					else if (y == 3)
						csv << reportersprogress[internalrow][i*offset+offsetopen] << ",";
					else if (y == 4)
						csv << reportersprogress[internalrow][i*offset+offsetcrit] << ",";
					else if (y == 5)
						csv << reportersprogress[internalrow][i*offset+offsetmaj] << ",";
					else if (y == 6)
						csv << reportersprogress[internalrow][i*offset+offsetmin] << ",";
					else if (y == 7)
						csv << reportersprogress[internalrow][i*offset+offsettotalcreated] << ",";
					else if (y == 8)
						csv << reportersprogress[internalrow][i*offset+offsettotalclosed] << ",";
					else if (y == 9)
						csv << reportersprogress[internalrow][i*offset+offsettotalopen] << ",";
					else if (y == 10)
						csv << reportersprogress[internalrow][i*offset+offsettotalcrit] << ",";
					else if (y == 11)
						csv << reportersprogress[internalrow][i*offset+offsettotalmaj] << ",";
					else if (y == 12)
						csv << reportersprogress[internalrow][i*offset+offsettotalmin] << ",";
					else if (y == 13)
						csv << reportersprogress[internalrow][i*offset+offsetopencrit] << ",";
					else if (y == 14)
						csv << reportersprogress[internalrow][i*offset+offsetopenmaj] << ",";
					else if (y == 15)
						csv << reportersprogress[internalrow][i*offset+offsetopenmin] << ",";
					else if (y == 16)
						csv << reportersprogress[internalrow][i*offset+offsetclosedcrit] << ",";
					else if (y == 17)
						csv << reportersprogress[internalrow][i*offset+offsetclosedmaj] << ",";
					else if (y == 18)
						csv << reportersprogress[internalrow][i*offset+offsetclosedmin] << ",";
					else if (y == 19)
						csv << reportersprogress[internalrow][i*offset+offsettotalopencrit] << ",";
					else if (y == 20)
						csv << reportersprogress[internalrow][i*offset+offsettotalopenmaj] << ",";
					else if (y == 21)
						csv << reportersprogress[internalrow][i*offset+offsettotalopenmin] << ",";
					else
						csv << ",";
				}
				y++;
			}
			csv << "\n";
			internalrow++;
			y = 0;
		}
		cout << "Generating csv : reporters curve - " << reporters[i] << " done\n";
		internalrow = 0;
		i++;
	}
	cout << "Generating csv : reporters curve done\n";
	cout << "Generating csv : categories curve\n";
	i = 0;
	y = 0;
	internalrow = 0;
	while (i < nbuniquecat) {
		while (internalrow < nbunique) {
			while (y < maxcolscsv) {
				if (internalrow == 0) {
					if (y == 0) {
						cout << "Generating csv : categories curve - " << categories[i] << "\n";
						csv << categories[i] << ",";
					}
					else if (y == 1)
						csv << "Created,";
					else if (y == 2)
						csv << "Closed,";
					else if (y == 3)
						csv << "Opened,";
					else if (y == 4)
						csv << "Criticals,";
					else if (y == 5)
						csv << "Majors,";
					else if (y == 6)
						csv << "Minors,";
					else if (y == 7)
						csv << "Total created,";
					else if (y == 8)
						csv << "Total closed,";
					else if (y == 9)
						csv << "Total open,";
					else if (y == 10)
						csv << "Total criticals,";
					else if (y == 11)
						csv << "Total majors,";
					else if (y == 12)
						csv << "Total minors,";
					else if (y == 13) 
						csv << "Open criticals,";
					else if (y == 14)
						csv << "Open majors,";
					else if (y == 15)
						csv << "Open minors,";
					else if (y == 16)
						csv << "Closed criticals,";
					else if (y == 17)
						csv << "Closed majors,";
					else if (y == 18)
						csv << "Closed minors,";
					else if (y == 19)
						csv << "Total open criticals,";
					else if (y == 20)
						csv << "Total open majors,";
					else if (y == 21)
						csv << "Total open minors,";
					else
						csv << ",";
				}
				else {
					if (y == 0)
						csv << dates[internalrow] << ",";
					else if (y == 1)
						csv << categoryprogress[internalrow][i*offset+offsetcreated] << ",";
					else if (y == 2)
						csv << categoryprogress[internalrow][i*offset+offsetclosed] << ",";
					else if (y == 3)
						csv << categoryprogress[internalrow][i*offset+offsetopen] << ",";
					else if (y == 4)
						csv << categoryprogress[internalrow][i*offset+offsetcrit] << ",";
					else if (y == 5)
						csv << categoryprogress[internalrow][i*offset+offsetmaj] << ",";
					else if (y == 6)
						csv << categoryprogress[internalrow][i*offset+offsetmin] << ",";
					else if (y == 7)
						csv << categoryprogress[internalrow][i*offset+offsettotalcreated] << ",";
					else if (y == 8)
						csv << categoryprogress[internalrow][i*offset+offsettotalclosed] << ",";
					else if (y == 9)
						csv << categoryprogress[internalrow][i*offset+offsettotalopen] << ",";
					else if (y == 10)
						csv << categoryprogress[internalrow][i*offset+offsettotalcrit] << ",";
					else if (y == 11)
						csv << categoryprogress[internalrow][i*offset+offsettotalmaj] << ",";
					else if (y == 12)
						csv << categoryprogress[internalrow][i*offset+offsettotalmin] << ",";
					else if (y == 13)
						csv << categoryprogress[internalrow][i*offset+offsetopencrit] << ",";
					else if (y == 14)
						csv << categoryprogress[internalrow][i*offset+offsetopenmaj] << ",";
					else if (y == 15)
						csv << categoryprogress[internalrow][i*offset+offsetopenmin] << ",";
					else if (y == 16)
						csv << categoryprogress[internalrow][i*offset+offsetclosedcrit] << ",";
					else if (y == 17)
						csv << categoryprogress[internalrow][i*offset+offsetclosedmaj] << ",";
					else if (y == 18)
						csv << categoryprogress[internalrow][i*offset+offsetclosedmin] << ",";
					else if (y == 19)
						csv << categoryprogress[internalrow][i*offset+offsettotalopencrit] << ",";
					else if (y == 20)
						csv << categoryprogress[internalrow][i*offset+offsettotalopenmaj] << ",";
					else if (y == 21)
						csv << categoryprogress[internalrow][i*offset+offsettotalopenmin] << ",";
					else
						csv << ",";
				}
				y++;
			}
			csv << "\n";
			internalrow++;
			y = 0;
		}
		internalrow = 0;
		cout << "Generating csv : categories curve - " << categories[i] << " done\n";
		i++;
	}
	cout << "Generating csv : categories curve done\n";
	cout << "Generating csv : assignees curve\n";
	i = 0;
	y = 0;
	internalrow = 0;
	while (i < nbuniquename) {
		while (internalrow < nbunique) {
			while (y < maxcolscsv) {
				if (internalrow == 0) {
					if (y == 0) {
						cout << "Generating csv : assignees curve - " << names[i] << "\n";
						csv << names[i] << ",";
					}
					else if (y == 1)
						csv << "Created,";
					else if (y == 2)
						csv << "Closed,";
					else if (y == 3)
						csv << "Opened,";
					else if (y == 4)
						csv << "Criticals,";
					else if (y == 5)
						csv << "Majors,";
					else if (y == 6)
						csv << "Minors,";
					else if (y == 7)
						csv << "Total created,";
					else if (y == 8)
						csv << "Total closed,";
					else if (y == 9)
						csv << "Total open,";
					else if (y == 10)
						csv << "Total criticals,";
					else if (y == 11)
						csv << "Total majors,";
					else if (y == 12)
						csv << "Total minors,";
					else if (y == 13) 
						csv << "Open criticals,";
					else if (y == 14)
						csv << "Open majors,";
					else if (y == 15)
						csv << "Open minors,";
					else if (y == 16)
						csv << "Closed criticals,";
					else if (y == 17)
						csv << "Closed majors,";
					else if (y == 18)
						csv << "Closed minors,";
					else if (y == 19)
						csv << "Total open criticals,";
					else if (y == 20)
						csv << "Total open majors,";
					else if (y == 21)
						csv << "Total open minors,";
					else
						csv << ",";
				}
				else {
					if (y == 0)
						csv << dates[internalrow] << ",";
					else if (y == 1)
						csv << assignprogress[internalrow][i*offset+offsetcreated] << ",";
					else if (y == 2)
						csv << assignprogress[internalrow][i*offset+offsetclosed] << ",";
					else if (y == 3)
						csv << assignprogress[internalrow][i*offset+offsetopen] << ",";
					else if (y == 4)
						csv << assignprogress[internalrow][i*offset+offsetcrit] << ",";
					else if (y == 5)
						csv << assignprogress[internalrow][i*offset+offsetmaj] << ",";
					else if (y == 6)
						csv << assignprogress[internalrow][i*offset+offsetmin] << ",";
					else if (y == 7)
						csv << assignprogress[internalrow][i*offset+offsettotalcreated] << ",";
					else if (y == 8)
						csv << assignprogress[internalrow][i*offset+offsettotalclosed] << ",";
					else if (y == 9)
						csv << assignprogress[internalrow][i*offset+offsettotalopen] << ",";
					else if (y == 10)
						csv << assignprogress[internalrow][i*offset+offsettotalcrit] << ",";
					else if (y == 11)
						csv << assignprogress[internalrow][i*offset+offsettotalmaj] << ",";
					else if (y == 12)
						csv << assignprogress[internalrow][i*offset+offsettotalmin] << ",";
					else if (y == 13)
						csv << assignprogress[internalrow][i*offset+offsetopencrit] << ",";
					else if (y == 14)
						csv << assignprogress[internalrow][i*offset+offsetopenmaj] << ",";
					else if (y == 15)
						csv << assignprogress[internalrow][i*offset+offsetopenmin] << ",";
					else if (y == 16)
						csv << assignprogress[internalrow][i*offset+offsetclosedcrit] << ",";
					else if (y == 17)
						csv << assignprogress[internalrow][i*offset+offsetclosedmaj] << ",";
					else if (y == 18)
						csv << assignprogress[internalrow][i*offset+offsetclosedmin] << ",";
					else if (y == 19)
						csv << assignprogress[internalrow][i*offset+offsettotalopencrit] << ",";
					else if (y == 20)
						csv << assignprogress[internalrow][i*offset+offsettotalopenmaj] << ",";
					else if (y == 21)
						csv << assignprogress[internalrow][i*offset+offsettotalopenmin] << ",";
					else
						csv << ",";
				}
				y++;
			}
			csv << "\n";
			internalrow++;
			y = 0;
		}
		internalrow = 0;
		cout << "Generating csv : assignees curve - " << names[i] << " done\n";
		i++;
	}
	cout << "Generating csv : assignees curve done\n";
	log << "tout s'est bien passé ! : D";
	cout << "Generating csv : done\n";
	cout << "Exiting...\n";
}