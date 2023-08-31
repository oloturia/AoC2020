#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout; using std::string; using std::ifstream; using std::getline;

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

	/*int num_lines = count(istreambuf_iterator<char>(file),istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	int line[num_lines];
	*/
	string temp;
	/*
	for (int i = 0; i < num_lines+1; i++) {
		getline(file,temp);
		line[i] = atoi(temp.c_str());	
	}
	*/
	while (getline(file,temp)){;
		
	}
	
	file.close();
	
	return 0;
}
