#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <math.h>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map;

unsigned long elab (string filename);
int *toBin(int number);
long toDec(int bin[35]);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

int *toBin(int number, int toFill[35]) {
	for (int i = 35; i >= 0; i--) {
			if(pow(2,i) <= number) {
				toFill[i] = 1;
				number -= pow(2,i);
			} else {
				toFill[i] = 0;
			}
	}
	return toFill;
}

long toDec(int bin[35]) {
	long temp_decimal = 0;
	for (int i = 35; i >= 0; i--) {
		temp_decimal += pow(2,i) * bin[i];
	}
	return temp_decimal;
}

unsigned long elab(string filename) {
	ifstream file(filename);

	string temp;
	string mask;
	map<long,unsigned long> memloc;
	int temp_memloc[35];
	unsigned long value;
	
	unsigned long total = 0;
	int x_count;
	int x_mask[35];
	int x_temp;
	
	while (getline(file,temp)){;
		if (temp.substr(0,4) == "mask") {
			x_count = 0;
			mask = temp.substr(7,36);
			for (unsigned int i = 0; i < mask.length(); i++) {
				if (mask[i] == 'X') {
					x_count ++;
				}
			}
		} else {
			value = atoi(temp.substr(temp.find('=')+2,temp.length()-temp.find('=')+3).c_str());
			for (int x = 0; x <= pow(2,x_count); x++) {
				toBin(x,x_mask);
				x_temp = 0;	
				toBin(atoi(temp.substr(4,temp.find(']')-4).c_str()),temp_memloc);
				for (int i = 35; i >= 0; i--) {
					if (mask[35-i] == 'X') {
						temp_memloc[i] = x_mask[x_temp];
						x_temp ++;
					} else if (mask[35-i] == '1') {
						temp_memloc[i] = 1;
					}
				}
				memloc[toDec(temp_memloc)] = value;			
			}

		}
	}
	
	file.close();
	
	map<long,unsigned long>::iterator it = memloc.begin();
	while (it != memloc.end()) {
		total += it->second;
		it ++;
	}
	
	return total;
}
