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
	unsigned long loc;
	unsigned long locend;
	bool found;
	
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
				loc = temp.find("byr");
				if ( loc != string::npos) {
					if (atoi(temp.substr(loc+4,4).c_str()) >= 1920 && atoi(temp.substr(loc+4,4).c_str()) <= 2002) {
						test["byr"] = true;
					}
				}
				
				loc = temp.find("iyr");
				if (loc != string::npos) {
					if (atoi(temp.substr(loc+4,4).c_str()) >= 2010 && atoi(temp.substr(loc+4,4).c_str()) <= 2020) {
						test["iyr"] = true;
					}
				}				
				loc = temp.find("eyr");
				if (loc != string::npos) {
					if (atoi(temp.substr(loc+4,4).c_str()) >= 2020 && atoi(temp.substr(loc+4,4).c_str()) <= 2030) {
						test["eyr"] = true;
					}
				}
				loc = temp.find("hgt");
				if (loc != string::npos) {
					locend = temp.substr(loc+4).find("cm");					
					if (locend != string::npos) {
						if (atoi(temp.substr(loc+4,locend).c_str()) >= 150 && atoi(temp.substr(loc+4,locend).c_str()) <= 193) {
							test["hgt"] = true;
						}
					} else {
						locend = temp.substr(loc+4).find("in");
						if (locend != string::npos) {
							if (atoi(temp.substr(loc+4,locend).c_str()) >= 59 && atoi(temp.substr(loc+4,locend).c_str()) <= 76) {
								test["hgt"] = true;
							}
						}
						
					}
				}
				loc = temp.find("hcl");
				if (loc != string::npos) {
					if (temp[loc+4] == '#') {
						found = true;
						for (unsigned int i = loc+5; i < loc+11; i++) {
							if (!((temp[i] >= '0' && temp[i] <='9')||(temp[i] >= 'a' && temp[i] <= 'f'))){								
								found = false;
							}
						}
						if (found) {
							test["hcl"] = true;							
						} 
					}
				}
				
				loc = temp.find("ecl");
				
				if (loc != string::npos) {
					if (temp.substr(loc+4,3) == "amb" || temp.substr(loc+4,3) == "blu" || temp.substr(loc+4,3) == "brn" ||temp.substr(loc+4,3) == "gry" || temp.substr(loc+4,3)  == "grn" || temp.substr(loc+4,3) == "hzl" || temp.substr(loc+4,3) == "oth") {
						test["ecl"] = true;
					}
				}
				
				loc = temp.find("pid");
				if (loc != string::npos) {
					found = true;
					for (unsigned int i = loc+4; i < loc+13; i++) {
						if ((temp[i] < '0' || temp[i] > '9')) {
							found = false;
							break;
						}					
					}
					
					if (temp[loc+13] != ' ' && loc+13 != temp.length())  {
						found = false;
					}
					if (found) {
						test["pid"] = true;
						
					}
				}
			}
	}
	
	file.close();
	return count;
}
