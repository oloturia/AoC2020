#include <iostream>
#include <fstream>
#include <algorithm>

int elab(std::string filename);

int main(int argc, char**argv) {
	int solution;
	if (sizeof(argv)/sizeof(*argv) > 1 ) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

int elab(std::string filename) {
	std::ifstream file(filename);

	int num_lines = count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	int line[num_lines];
	
	std::string temp;

	for (int i = 0; i < num_lines+1; i++) {
		std::getline(file,temp);
		line[i] = atoi(temp.c_str());	
	}
	file.close();

	for (int i1 = 0; i1 < num_lines; i1++) {
		for (int i2 = 0; i2 < num_lines; i2++) {
			if ( line[i1] + line[i2] == 2020 ) {
				return (line[i1] * line[i2]);
			}
		}
	}
	return 0;
}

