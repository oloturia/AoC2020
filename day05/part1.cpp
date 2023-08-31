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
	cout << solution << '\n';
}

int elab(string filename) {
	ifstream file(filename);
	string temp;

	int cpos;
	int rpos;
	int maxpos = 0;
	
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
		
		if (maxpos < cpos*8+rpos) {
			maxpos = cpos*8+rpos;
		}
	}
	
	file.close();
	
	return maxpos;
}
