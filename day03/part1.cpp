#include <iostream>
#include <fstream>
#include <algorithm>

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

	
	int x = 0;
	int count = 0;
	while (getline(file,temp)) {
		if (temp[x%temp.length()] == '#'){
			count ++;
		}
		x +=3;
	}
	file.close();
	
	return count;
}
