#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout; using std::string; using std::ifstream; using std::getline;

int elab (std::string filename);

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
	bool found;

	while (getline(file,temp)){
		if (temp.length() > 0) {
			group = group + temp;	
		} else {
			for (u_int i1 = 0; i1 < group.length(); i1++) {
				found = false;
				for (u_int i2 = 0; i2 < no_dup.length(); i2++) {
					if (group[i1] == no_dup[i2]) {
						found = true;
						break;
					}
				}
				if (!found) {
					no_dup = no_dup + group[i1];
				}
			}
			total += no_dup.length();
			no_dup = "";
			group = "";
		}
	}
	
	file.close();
	
	return total;
}
