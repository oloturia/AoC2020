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
	std::cout << solution << '\n';
}

int elab(string filename) {
	ifstream file(filename);
	string temp;
	int total = 0;
	string group;
	string no_dup;
	string partial;
	bool first = true;
	bool found;

	while (getline(file,temp)){
		if (first) {
			first = false;
			total += no_dup.length() - partial.length();
			no_dup = temp;
			partial = "";
		} else {
			if (temp.length() == 0) {
				first = true;
			} else {
				for (unsigned int i1 = 0; i1 < no_dup.length(); i1++) {
					found = false;
					for (unsigned int i2 = 0; i2 < temp.length(); i2++) {
						if (no_dup[i1] == temp[i2]) {
							found = true;
						}
					}
					if (!found) {
						for (unsigned int i3 = 0; i3 < partial.length(); i3++) {
							if (partial[i3] == no_dup[i1]) {
								found = true;
							}
						}
						if (!found) {
							partial = partial + no_dup[i1];
						}
					}
				}
			}
		}
	}
	
	file.close();
	
	return total;
}
