#include <iostream>
#include <fstream>
#include <algorithm>


int elab (std::string filename);

int main(int argc, char**argv) {
	int solution;
	if (sizeof(argv)/sizeof(*argv) > 1 ) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

int elab(std::string filename) {
	std::ifstream file(filename);
	std::string test;
	std::string password;
	std::string temp;
	std::string delimeter_1 = "-";
	std::string delimeter_2 = ":";
	
	int total = 0;
	
	
	while (std::getline(file, temp)) {
		int mincount = atoi(temp.substr(0, temp.find(delimeter_1)).c_str());
		int maxcount = atoi(temp.substr(temp.find(delimeter_1)+1, temp.find(" ")-temp.find(delimeter_1)).c_str());
		test = temp.substr(temp.find(delimeter_2)-1,1).c_str();
		std::string password = temp.substr(temp.find(delimeter_2)+2,temp.length()).c_str();
		int count = 0;
		for(u_int i = 0;i < password.length(); i++) {
			if (password[i] == test[0]) {
				count ++;
			}
		}
		if (count >= mincount && count <= maxcount) {
			total ++;
		}
	}
	file.close();
	return total;
}
