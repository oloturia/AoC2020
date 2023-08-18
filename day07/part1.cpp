#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::count; using std::istreambuf_iterator; using std::vector;

int elab (string filename);

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

int elab(string filename) {
	ifstream file(filename);

	int num_lines = count(istreambuf_iterator<char>(file),istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	string line[num_lines];
	int pos;	

	string temp;
	vector<string> found;
	int found_index = 0;
	int next_index = 1;
	bool no_more = true;

	found.push_back("shiny gold");
	
	for (int i = 0; i < num_lines; i++) {
		getline(file,temp);
		line[i] = temp;	
	}
	file.close();
	
	while (no_more) {
		no_more = false;
		for (unsigned int i1 = found_index; i1 < found.size(); i1 ++) {
			for (int i2 = 0; i2 < num_lines; i2++) {
				pos = line[i2].find(found[i1]);
				if ( pos != -1 && pos != 0) {
					if (find(found.begin(),found.end(),line[i2].substr(0,line[i2].find("bags")-1) ) == found.end() ) {
						no_more = true;
						
						found.push_back(line[i2].substr(0,line[i2].find("bags")-1));

					}
				}
			}
		}
		found_index = next_index;
		next_index = found.size();
	}

	return found.size() -1;
}
