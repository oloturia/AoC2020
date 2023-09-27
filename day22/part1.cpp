#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::deque;

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
	deque<int> players[2];
	unsigned int second = 0;
	
	while (getline(file,temp)){;
		if(temp == "") {
			second = 1;
			getline(file,temp);
		} else if (temp.substr(0,1) != "P") {
			players[0+second].push_back( atoi(temp.c_str()) );
		}
	}
	file.close();
	int ply1;
	int ply2;
	
	while (players[0].size() > 0 && players[1].size() > 0) {
		ply1 = players[0].front();
		ply2 = players[1].front();
		
		players[0].pop_front();
		players[1].pop_front();
		
		if (ply1 > ply2) {
			players[0].push_back(ply1);
			players[0].push_back(ply2);
		} else {
			players[1].push_back(ply2);
			players[1].push_back(ply1);
		}
	}
	
	int won_12 = 0;
	if (players[0].size() == 0) {
		won_12 = 1;
	}
	
	unsigned int result = 0;
	unsigned int value;
	unsigned int size_w = players[won_12].size();	
	for(unsigned int i = 0; i < size_w; i++) {
		value = players[won_12].back();
		result += (i+1)*value;
		players[won_12].pop_back();
	}

	return result;
}
