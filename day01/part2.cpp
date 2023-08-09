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

int elab (string filename) {
	ifstream file(filename);

	int num_lines = count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	int line[num_lines];

	string temp;

	for (int i = 0; i < num_lines+1; i++) {
		getline(file,temp);
		line[i] = atoi(temp.c_str());	
	}
	file.close();

	for (int i1 = 0; i1 < num_lines; i1++) {
		for (int i2 = 0; i2 < num_lines; i2++) {
			for (int i3 = 0; i3 < num_lines; i3++) {
				if ( line[i1] + line[i2] + line[i3]  == 2020 ) {
					return (line[i1] * line[i2] * line[i3]);	
				}
			}
		}
	}
	return 0;
}

