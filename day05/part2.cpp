#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>

using std::cout; using std::string; using std::ifstream; using std::getline;

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

	
	int cpos;
	int rpos;
	
	int poslist[900];
	int index = 0;
	bool found;
	bool found_fr;
	bool found_bk;
	while (getline(file,temp)){
		cpos = 0;
		for (int i = 6; i >= 0; i--) {
			if (temp[i] == 'B') {
				cpos += pow(2,6-i);
			}
		}
		rpos = 0;
		for (int i = 9; i >= 7; i--) {
			if (temp[i] == 'R') {
				rpos += pow(2,9-i);
			}
		}
		poslist[index] = cpos*8 + rpos;
		index ++;
	}
	file.close();

	for (int i1 = 1; i1 < 900; i1++) {
		found = false;
		for (int i2 = 0 ; i2 < 900; i2++) {
			if (poslist[i2] == i1) {
				found = true;
			}
		}
		if (!found) {
			found_fr = false;
			for (int i2 = 0 ; i2 < 900; i2++) {
				if (poslist[i2] == i1+1) {
					found_fr = true;
				}
			}
			found_bk = false;
			for (int i2 = 0 ; i2 < 900; i2++) {
				if (poslist[i2] == i1-1) {
					found_bk = true;
				}
			}
			if (found_fr && found_bk) {
				return i1;
			}
		}				
		
	}
	return -1;
}
