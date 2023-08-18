#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::count; using std::istreambuf_iterator; using std::vector;

int num_lines = 0;
int elab (string filename);
void contains(string search, string* line, int temp_total);
int total = 0;

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

void contains(string search, string* line, int temp_total) {
	int temp_spaces;
	int i3;
	int number;
	int prev_res = temp_total;
	total += temp_total;
	for (int i1 = 0; i1 < num_lines; i1++) {
		if (line[i1].substr(0,line[i1].find("bags")-1) == search) {
			if (line[i1].substr(line[i1].find("bags"),line[i1].length()) == "bags contain no other bags.") {
				return;
			} else {
				for (unsigned int i2 = 0; i2 < line[i1].length(); i2++) {
					if (line[i1][i2] >= '1' && line[i1][i2] <= '9') {
						temp_spaces = 0;
						i3 = i2+1;
						while(temp_spaces != 2){
							i3 ++;
							if(line[i1][i3] == ' ') {								
								temp_spaces +=1;
							}
						}
						number = line[i1][i2]-'0';
						temp_total += number * prev_res;
						contains(line[i1].substr(i2+2,i3-i2-2),line,number*prev_res);
						i2 = i3;
					}
				}
				return;
			}		
		}
	}
}

int elab(string filename) {
	ifstream file(filename);
	num_lines = count(istreambuf_iterator<char>(file),istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	string line[num_lines];	

	string temp;

	for (int i = 0; i < num_lines; i++) {
		getline(file,temp);
		line[i] = temp;	
	}
	file.close();
	contains("shiny gold",line,1);

	return total-1;
}
