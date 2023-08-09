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
	int count = 0;
	bool newPass = true;
	map<string,bool> test;
	string params[] = {"byr","iyr","eyr","hgt","hcl","ecl","pid"};
	
	while(std::getline(file,temp)) {			
			if (newPass) {
				if (test["byr"] && test["iyr"] && test["eyr"] && test["hgt"] && test["hcl"] && test["ecl"] && test["pid"]) {
					count ++;
				}
				test = {{"byr",false},{"iyr",false},{"eyr",false},{"hgt",false},{"hcl",false},{"ecl",false},{"pid",false}};
				newPass = false;
			}
					
			if (temp == "") {
				newPass = true;
			} else {
				for(int i = 0; i < 7; i++) {
					if (temp.find(params[i]) != string::npos) {	
						test[params[i]] = true;
					}
				}
			}
	}

	
	
	file.close();
	
	return count;
}
