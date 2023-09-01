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
	map<int,int[4]> intervals;
	bool definitions = true;
	bool testing = false;
	bool valid;
	int result = 0;
	int line = 0;
	int test_value;
	string temp_part;

	while (getline(file,temp)){
		if (temp == "") {
			definitions = false;
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
			for (unsigned int i1 = 0; i1 <= temp.length(); i1++) {
				if ( temp[i1] == ',' || i1 == temp.length() ) {
					test_value = atoi(temp_part.c_str());
					temp_part = "";
					valid = false;
					for(int i2 = 0; i2 < line; i2++) {
						if ( (test_value >= intervals[i2][0] && test_value <= intervals[i2][1]) || (test_value >= intervals[i2][2] && test_value <= intervals[i2][3]) ){
							valid = true;
						}
					}
					if (!valid) {
						result += test_value;
					}
				} else {
					temp_part += temp[i1];
				}
			}
		}	
	}
	
	file.close();
	
	return result;
}
