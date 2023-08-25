#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

int elab (string filename);

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

int elab(string filename) {
	ifstream file(filename);

	int num_lines = count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	vector<int> line;
	string temp;
	int jolt = 0;
	int sum_1 = 0;
	int sum_3 = 0;
	int max = 0;
	
	for (int i = 0; i < num_lines+1; i++) {
		getline(file,temp);
		line.push_back( atoi(temp.c_str()) );
		if (max < atoi(temp.c_str()) ) {
			max = atoi(temp.c_str());
		}
	}
	file.close();
	
	while (jolt != max+3) {
		if (std::find(line.begin(),line.end(),jolt+1) != line.end()) {
			jolt +=1;
			sum_1 ++;
		} else {
			jolt +=3;
			sum_3 ++;
		}
	}
	
	return sum_1*sum_3;
}
