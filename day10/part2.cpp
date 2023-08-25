#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map;

long elab (string filename);

int main(int argc, char**argv) {
	long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

long elab(string filename) {
	ifstream file(filename);

	int num_lines = count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	map<int,unsigned long> line;
	string temp;
	int max = 0;
	unsigned long count;
	
	for (int i = 0; i < num_lines+1; i++) {
		getline(file,temp);
		line[atoi(temp.c_str())] = 0;
		if (max < atoi(temp.c_str()) ) {
			max = atoi(temp.c_str());
		}
	}
	file.close();
	line[0] = 1;
	
	line[max+3] = 0;

	for (int i1 = 1; i1 <= max+3; i1 ++) {
		if (line.find(i1) != line.end()) {
			count = 0;
			if (line.find(i1-1) != line.end()) {
				count += line[i1-1];
			}
			if (line.find(i1-2) != line.end()) {
				count += line[i1-2];
			}
			if (line.find(i1-3) != line.end()) {
				count += line[i1-3];
			}
			line[i1] = count;
		}
	}

	return line[max+3];
}
