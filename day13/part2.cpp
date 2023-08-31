#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <tuple>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector; using std::tuple; using std::make_tuple; using std::get;

unsigned long elab (string filename);
vector<tuple<int,int>> parseint (string original);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

vector<tuple<int,int>> parseint(string original, char separator){
	vector<tuple<int,int>> n_num;
	bool found;
	string temp = "";
	int index = 0;
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
				n_num.push_back( make_tuple( atoi( temp.c_str() ), index ) );
				temp = "";
			}
			if (original[i] == separator) {
				index ++;
			}
		}
	}
	if (found) {
		n_num.push_back( make_tuple (atoi( temp.c_str() ), index) );
	}
	return n_num;
}

unsigned long elab(string filename) {
	ifstream file(filename);
	string temp;
	unsigned long timestamp = 0;
	unsigned long interval;
	unsigned int index = 1;
	getline(file,temp);
	getline(file,temp);
	file.close();
	vector<tuple<int,int>> times = parseint(temp,',');	

	unsigned long int_start;
	bool found = false;
	interval = get<0>(times[0]);
	
	while(index < times.size()) {
		timestamp += interval;
		
		if ( ( timestamp + get<1>(times[index]) ) % get<0>(times[index])  == 0 ) {
			if (!found) {
				found = true;
				int_start = timestamp;
			} else {
				interval = timestamp - int_start;
				index ++;
				found = false;
				timestamp = int_start;
			}
		}
	}
	
	return timestamp;
}
