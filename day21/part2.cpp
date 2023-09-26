#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <set>
#include <algorithm>
 
using std::cout; using std::string; using std::ifstream; using std::getline; using std::map; using std::set; using std::multimap;
 
string elab (string filename);
void parseLine(string line);
map<string,set<string>> allergens;


int main(int argc, char**argv) {
	string solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}
 
void parseLine(string line) {
	set<string> templine;
	string tempname = "";
	unsigned int index = 0;
	
	while (line[index] != '(') {
		if (line[index] == ' ') {
			templine.insert(tempname);
			tempname = "";
		} else {
			tempname = tempname + line[index];
		}
		index ++;
	}
	
	index += 10;
	set<string> prevline;
	tempname = "";
	
	while (index < line.length() ) {
		if(line[index] == ',' || line[index] == ')') {
			if ( allergens[tempname].empty() ) {
				allergens[tempname] = templine;
			} else {
				prevline = allergens[tempname];
				allergens[tempname].clear();
				set_intersection(prevline.begin(), prevline.end(), templine.begin(), templine.end(), inserter( allergens[tempname], allergens[tempname].begin() ) );
			}
			tempname = "";
			index ++;
		} else {
			tempname = tempname + line[index];
		}
		index ++;
	}
}
 
string elab(string filename) {
	ifstream file(filename);
	string temp;
 
	while (getline(file,temp)){;
		parseLine(temp);
	}
	
	file.close();

	unsigned int n_allergens =  allergens.size();
	unsigned int n_found = 0;
	set<string> tempallergens;
	string stem;

	map<string,string> found_allergens;
	
	while(n_allergens != n_found) {
		for (auto it1 = allergens.begin(); it1 != allergens.end(); ++it1) {		
			if (it1->second.size() == 1) {
				n_found ++;
				for(auto itb = it1->second.begin(); itb != it1->second.end(); ++itb) {
					stem = *itb;
					found_allergens[it1->first] = *itb;
				}
				for (auto it2 = allergens.begin(); it2 != allergens.end(); ++it2) {
					tempallergens.clear();
					for (auto it3 = it2->second.begin(); it3 != it2->second.end(); ++it3) {
						if( *it3 != stem ) {
							tempallergens.insert(*it3);
						}
					}
					it2->second = tempallergens;
				}
			}
		}
	}
	
	string result = "";
	for(auto it = found_allergens.begin(); it != found_allergens.end(); ++it) {
		result = result + it->second + ",";
	}
	result = result.substr(0,result.length()-1)+'.';
	return result;
}
