#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>
#include <set>
#include <regex>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map; using std::vector; using std::set;

int elab (string filename);
map<string,string> grammar;


int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}



int elab(string filename) {
	ifstream file(filename);

	string temp;
	string ruleDef;
	string leftPart;
	string regex = "0";
	unsigned int valid = 0;
	
	while (getline(file,temp)) {
		if (temp == "") {break;}
		ruleDef = temp.substr(0,temp.find(':'));
		leftPart = temp.substr(temp.find(':')+2);
		if (leftPart == "\"a\"") {
			grammar[ruleDef] = "a";
		} else if (leftPart == "\"b\"") {
			grammar[ruleDef] = "b";
		} else {
			grammar[ruleDef] = leftPart;
		}
	}

	bool found = true;
	string tr;
	unsigned int ir;
	unsigned int is;
	
	while(found) {
		found = false;
		for (unsigned int i = 0; i < regex.length(); i++) {
			if (regex[i] >= '0' && regex[i] <= '9'){
				found = true;
				is = i;
				ir = i;
				tr = "";
				while(regex[ir] >= '0' && regex[ir] <= '9'){
					tr = tr + regex[ir];
					ir ++;
					if (ir == regex.length() ) {
						break;
					}
				}
			}
			if (found){	break; }
		}
		if (found) {
			if (grammar[tr] == "a" || grammar[tr] == "b"){
				regex = regex.substr(0,is) + grammar[tr] + regex.substr(ir);
			} else {
				regex = regex.substr(0,is) + "(?:" + grammar[tr] + ")" + regex.substr(ir);
			}
		}
	}
	
	string regex_formatted = "";
	for (unsigned int i = 0; i < regex.length(); i++) {
		if(regex[i] != ' '){
			regex_formatted = regex_formatted + regex[i];
		}
	}

	std::regex re(regex_formatted);
	while (getline(file,temp)) {
		std::cmatch m;
		if (std::regex_match(temp.c_str(),m,re) ) {
			valid ++;
		}
	}
	file.close();
	return valid;
}
