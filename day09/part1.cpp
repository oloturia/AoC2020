#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout; using std::string; using std::ifstream; using std::getline;

string elab (string filename);

int main(int argc, char**argv) {
	string solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	std::cout << solution << '\n';
}

string elab(string filename) {
	ifstream file(filename);
	string temp;
	long buffer[25];
	unsigned int fill = 0;
	bool started = false;
	bool found;

	while (getline(file,temp)){;
		if (started) {
			found = false;
			for (unsigned int i1 = 0; i1 < 25; i1 ++) {
				for (unsigned int i2 = 0; i2 < 25; i2 ++) {
					if (i1 == i2) {continue;}
					if (buffer[i1] + buffer[i2] == atoi(temp.c_str())) {
						found = true;
					}
				}
			}
			if (!found) {file.close();return temp;}
		}
		fill ++;
		if (fill == 25) {
			fill = 0;
			started = true;
		}
		buffer[fill] = atoi(temp.c_str());
		
	}
	
	file.close();
	
	return 0;
}
