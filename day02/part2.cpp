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

int elab(std::string filename) {
	ifstream file(filename);
	string test;
	string password;
	string temp;
	string delimeter_1 = "-";
	string delimeter_2 = ":";
	
	int total = 0;
	
	
	while (getline(file, temp)) {
		int pos1 = atoi(temp.substr(0, temp.find(delimeter_1)).c_str());
		int pos2 = atoi(temp.substr(temp.find(delimeter_1)+1, temp.find(" ")-temp.find(delimeter_1)).c_str());
		test = temp.substr(temp.find(delimeter_2)-1,1).c_str();
		string password = temp.substr(temp.find(delimeter_2)+2,temp.length()).c_str();
		int count = 0;
		if (password[pos1-1] == test[0]) {
			count ++;
		}
		if (password[pos2-1] == test[0]) {
			count ++;
		}
		if (count == 1) {
			total ++;
		}
	}
	file.close();
	return total;
}
