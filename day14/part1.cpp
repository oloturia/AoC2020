#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <math.h>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map;

unsigned long elab (string filename);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

unsigned long elab(string filename) {
	ifstream file(filename);

	string temp;
	string mask;
	map<string,unsigned long> memloc;
	unsigned long value;
	int temp_value[35];
	unsigned long temp_decimal;
	unsigned long total = 0;
	
	while (getline(file,temp)){;
		if (temp.substr(0,4) == "mask") {
			mask = temp.substr(7,36);
		} else {
			value = atoi( temp.substr(temp.find('=')+2,temp.length()-temp.find('=')+3).c_str() );
			for (int i = 35; i >= 0; i--) {
				
				if (pow(2,i) <= value) {
					temp_value[i] = 1;
					value -= pow(2,i);
				} else {
					temp_value[i] = 0;
				}
				
				if (mask[35-i] == '0') {
					temp_value[i] = 0;
				} else if (mask[35-i] == '1') {
					temp_value[i] = 1;
				}
			}
		
			temp_decimal = 0;
			for (int i = 35; i >= 0; i--) {
				temp_decimal += pow(2,i) * temp_value[i];
			}
			
			memloc[temp.substr(4,temp.find(']')-4)] = temp_decimal;
		}
	}
	
	file.close();
	
	map<string,unsigned long>::iterator it = memloc.begin();
	while (it != memloc.end()) {
		total += it->second;
		it ++;
	}
	
	return total;
}
