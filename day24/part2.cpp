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
	int neigh[6][2] = { {1,1}, {2,0}, {1,-1}, {-1,-1}, {-2,0}, {-1,1} };
	
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
	set<pair<int,int>> next_blacks;
	set<pair<int,int>> to_check;
	unsigned int adj;
	for (unsigned day = 0; day < 100; day++){
		next_blacks.clear();
		to_check.clear();
		for(auto tile:blacks) {
			adj = 0;
			for(unsigned int i = 0; i < 6; i++) {
				coords = make_pair(tile.first+neigh[i][0],tile.second+neigh[i][1]);
				if(blacks.find(coords) != blacks.end()) {
					adj++;
				} else {
					to_check.insert(coords);			
				}
			}
			if(adj == 1 || adj == 2) {
				next_blacks.insert(coords);
			}
		}
		
		for(auto tile:to_check) {
			adj = 0;
			for(unsigned int i = 0; i < 6; i++) {
				coords = make_pair(tile.first+neigh[i][0],tile.second+neigh[i][1]);
				if(blacks.find(coords) != blacks.end()) {
					adj++;
				}
			}
			if(adj == 2) {
				next_blacks.insert(coords);
			}
		}
		blacks = next_blacks;
	}
	
	return blacks.size();
}
