#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <cmath>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map;

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
	string temp;
	int value;
	
	int nset = 0;
	int eset = 0;
	int nway = 1;
	int eway = 10;
	
	int tempway;
	
	
	while (getline(file,temp)){
		value = atoi( temp.substr(1,temp.length()-1).c_str());
		switch(temp[0]){
		case 'F':
			nset += nway*value;
			eset += eway*value;
			break;
		case 'N':
			nway += value;
			break;
		case 'S':
			nway -= value;
			break;
		case 'E':
			eway += value;
			break;
		case 'W':
			eway -= value;
			break;
		case 'L':
			value = 360-value;
		case 'R':
			switch(value) {
			case 90:
				tempway = nway;
				nway = eway * -1;
				eway = tempway;
				break;
			case 180:
				nway *= -1;
				eway *= -1;
				break;
			case 270:
				tempway = nway;
				nway = eway;
				eway = tempway * -1;
				break;
			}
			break;
		}
	}
	
	file.close();
	
	return abs(nset)+abs(eset);
}
