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
	cout << solution << '\n';
}

int elab(string filename) {
	ifstream file(filename);
	string temp;
	map<int,int*> directions;
	int tempdir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
	directions[0] = tempdir[0];
	directions[180] = tempdir[1];	
	directions[90] = tempdir[2];	
	directions[270] = tempdir[3];
	int facing = 90;
	int nset = 0;
	int eset = 0;
	int value;
	
	while (getline(file,temp)){
		value = atoi( temp.substr(1,temp.length()-1).c_str());
		switch(temp[0]) {
		case 'F':
			nset += directions[facing][0]*value;
			eset += directions[facing][1]*value;
			break;
		case 'R':
			facing += value;
			facing = facing % 360;
			break;
		case 'L':
			facing -= value;
			if (facing < 0) { facing = 360+facing; }
			break;
		case 'N':
			nset += value;
			break;
		case 'S':
			nset -= value;
			break;
		case 'E':
			eset += value;
			break;
		case 'W':
			eset -= value;
			break;
		}
		
	}
	
	file.close();
	
	return abs(nset)+abs(eset);
}
