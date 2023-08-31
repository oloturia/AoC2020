#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map;

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
	

	map<int,int> spoken;
	getline(file,temp);
	file.close();
	string temp_number;
	unsigned long turn = 0;
	int last;
	int next;
	
	for (unsigned int i = 0; i < temp.length(); i++) {
			if (temp[i] == ',') {
				last = atoi(temp_number.c_str());
				spoken[last] = turn;
				temp_number = "";
				turn ++;
			} else {
				temp_number += temp[i];
			}
	}
	
	
	int r_ind = temp.length();
	while(temp[r_ind] != ',') {
		r_ind --;
	}
	
	last = atoi( temp.substr(r_ind+1,temp.length()-r_ind+1).c_str() );
		
	for (unsigned int i = turn; i < 2019; i ++) {
		if(spoken.find(last) != spoken.end()) {
			next = i - spoken[last];
			spoken[last] = i;
			last = next;
		} else {
			spoken[last] = i;
			last = 0;
		}
	}
	return last;
}
