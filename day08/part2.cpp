#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

int elab (string filename);

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
	unsigned int cursor = 0;
	int acc = 0;
	vector<unsigned int> visited;
	//int num_lines = count(istreambuf_iterator<char>(file),istreambuf_iterator<char>(),'\n');
	//file.clear();
	//file.seekg(0);
	vector<string> line;
	int changed = -1;
		
	while(getline(file,temp)) {
		line.push_back(temp);
		if ( (temp.substr(0,3) == "jmp" || temp.substr(0,3) == "nop") && changed == -1)  {changed = line.size();}
			
	}	
	file.close();
	while (true){
		if (line[cursor].substr(0,3) == "nop") {
			if (cursor == changed) {
				cursor += atoi(line[cursor].substr(4,temp.length()-4).c_str());
			} else {
				cursor ++;
			}
		} else if (line[cursor].substr(0,3) == "acc") {
			//cout << atoi(line[cursor].substr(4,temp.length()-4).c_str()) << '\n';
			acc += atoi(line[cursor].substr(4,temp.length()-4).c_str());
			cursor ++;
		} else if (line[cursor].substr(0,3) == "jmp") {
			if (cursor == changed) {
				cursor ++;
			} else {
				cursor += atoi(line[cursor].substr(4,temp.length()-4).c_str());
			}
		}
		if (std::find(visited.begin(),visited.end(),cursor) != visited.end()) {
			cursor = 0;
			acc = 0;
			visited.clear();
			changed ++;
			while (!(line[changed].substr(0,3) == "jmp" || line[changed].substr(0,3) == "nop")) { changed ++;}
		}
		visited.push_back(cursor);
		if (cursor >= line.size()) {
			break;		
		}
	}
	return acc;
}
