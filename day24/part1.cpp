#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>


using std::cout; using std::string; using std::ifstream; using std::getline; using std::set; using std::pair; using std::make_pair;

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
	set<pair<int,int>> blacks;
	int targetx;
	int targety;
	pair<int,int> coords;
	
	while (getline(file,temp)){
		targetx = 0;
		targety = 0;

		for(unsigned int i = 0; i < temp.length(); i++) {
			if(temp[i] == 'n'){
				i++;
				targety++;
				if (temp[i] == 'e') {
					targetx++;
				} else if (temp[i] == 'w') {
					targetx--;
				}
			} else if (temp[i] == 's') {
				i++;
				targety--;
				if (temp[i] == 'e') {
					targetx++;
				} else if (temp[i] == 'w') {
					targetx--;
				}
			} else if (temp[i] == 'e') {
				targetx+=2;
			} else if (temp[i] == 'w') {
				targetx-=2;
			}	
		}
		coords = make_pair(targetx,targety);
		if(blacks.find(coords) == blacks.end()) {
			blacks.insert(coords);
		} else {
			blacks.erase(coords);
		}

	}
	
	file.close();
	
	return blacks.size();
}
