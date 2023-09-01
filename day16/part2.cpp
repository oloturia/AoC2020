#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <vector>

#define EL 20
#define RS 6

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map; using std::vector;

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
	map<int,int[4]> intervals;
	bool definitions = true;
	bool testing = false;
	bool valid;
	unsigned long result = 1;
	int line = 0;
	int test_value;
	int field;
	vector<int> y_tick;
	vector<int> temp_tick;
	vector<vector<int>> valid_tick;
	int stem[EL][EL];
	string temp_part;

	for (int i = 0 ; i < EL; i++) {
		temp_tick.push_back(0);
		for (int n = 0; n < EL; n++){
			stem[i][n] = 1;
		}
	}

	while (getline(file,temp)){
		if (temp == "") {
			definitions = false;
		}
		
		if (temp == "your ticket:") {
			getline(file,temp);
			temp_part == "";
			for (unsigned int i = 0; i <= temp.length(); i++) {
				if ( temp[i] == ',' || i == temp.length() ) {
					y_tick.push_back(atoi( temp_part.c_str() ) );
					temp_part = "";
				} else {
					temp_part += temp[i];
				}
			}
		}
		
		if (temp == "nearby tickets:") {
			testing = true;
			continue;
		}
		
		if (definitions) {
			temp_part =  temp.substr(temp.find(":")+2,temp.length()-temp.find(":")-2);
			intervals[line][0] = atoi( temp_part.substr(0,temp_part.find("-")).c_str()  );
			intervals[line][1] = atoi( temp_part.substr(temp_part.find("-")+1,temp_part.find("or")-3).c_str() );
			
			temp_part = temp.substr(temp.find(" or ")+4,temp.length()-temp.find(" or ")-4);
			intervals[line][2] = atoi( temp_part.substr(0,temp_part.find("-")).c_str() );
			intervals[line][3] = atoi( temp_part.substr(temp_part.find("-")+1,temp_part.length()-temp_part.find("-")-1).c_str() );
			line ++;
		}
		
		if (testing) {
			temp_part = "";
			field = 0;
			for (unsigned int i1 = 0; i1 <= temp.length(); i1++) {
				if ( temp[i1] == ',' || i1 == temp.length() ) {
					test_value = atoi(temp_part.c_str());
					temp_tick[field] = test_value;
					field ++;
					temp_part = "";
					valid = false;
					for(int i2 = 0; i2 < EL; i2++) {
						if ( (test_value >= intervals[i2][0] && test_value <= intervals[i2][1]) || (test_value >= intervals[i2][2] && test_value <= intervals[i2][3]) ){
							valid = true;
						}
					}
					if (!valid) {
						break;
					}
				} else {
					temp_part += temp[i1];
				}
			}
			if (valid) {
				valid_tick.push_back(temp_tick);
			}
		}	
	}

	file.close();	
	
	for (unsigned int i1 = 0; i1 < valid_tick.size(); i1++) {
		for(int i2 = 0; i2 < EL; i2++) {
			for(int i3 = 0; i3 < EL; i3++) {
				if (!( (valid_tick[i1][i2] >= intervals[i3][0] && valid_tick[i1][i2] <= intervals[i3][1]) || (valid_tick[i1][i2] >= intervals[i3][2] && valid_tick[i1][i2] <= intervals[i3][3]) )) {
					stem[i3][i2] = 0;
				}
			}
		}
	}
		
	
	int found;
	int n_found = 0;
	int columns[EL];
	
	while (n_found < EL) {
		for (int i1 = 0; i1 < EL; i1++) {
			found = -1;
			for (int i2 = 0; i2 < EL; i2++) {
				if ( stem[i1][i2] == 1 && found == -1) {
					found = i2;
				} else if (stem[i1][i2] == 1 && found >= 0) {
					found = -2;
				}
			}
			if (found >= 0) {
				n_found ++;
				for(int i3 = 0; i3 < EL; i3++) {
					stem[i3][found] = 0;
				}
				columns[found] = i1;
			}
		}
	}

	for (int i1 = 0; i1 < EL; i1++) {
		if (columns[i1] < RS) {
			result = result * y_tick[i1];
		}
	}
	return result;
}
