#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

int elab (string filename);
vector<int> parseint (string original);

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

vector<int> parseint(string original){
	vector<int> n_num;
	bool found;
	string temp = "";
	for (unsigned int i = 0; i < original.length(); i++) {
	
		if (original[i] >= '0' && original[i] <= '9'){
			
			if (!found) {
				temp = original[i];
				found = true;
			} else {
				temp += original[i];
			}
		} else {
			if (found) {
				found = false;
				n_num.push_back( atoi( temp.c_str() ) );
				temp = "";
			}
		}
	}
	if (found) {
		n_num.push_back( atoi( temp.c_str() ) );
	}
	return n_num;
}

int elab(string filename) {
	ifstream file(filename);
	string temp;
	
	getline(file,temp);
	int timestamp = atoi(temp.c_str());
	getline(file,temp);
	file.close();
	
	vector<int> times = parseint(temp);

	int	smallest_interval = -1;
	int index = 0;
	for (unsigned int i = 0; i < times.size(); i++) {
		if (smallest_interval == -1 || smallest_interval > times[i] - (timestamp % times[i])) {
			smallest_interval = times[i] - (timestamp % times[i]);
			index = times[i];
		}
	}
	
	return index*smallest_interval;
}
