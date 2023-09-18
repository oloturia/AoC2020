#include <iostream>
#include <fstream>
#include <algorithm>
#include <tuple>
#include <map>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::tuple; using std::map; using std::vector; using std::get;

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
	map<tuple<int,int,int,int>,bool> space;
	map<tuple<int,int,int,int>,bool> to_check;
	map<tuple<int,int,int,int>,bool> next_matrix;
	tuple<int,int,int,int> parameter;
	int row = 0;

	while (getline(file,temp)){
		for (unsigned int col = 0; col < temp.length(); col++) {
			if (temp[col] == '#') {
				space[{row,col,0,0}] = true;
			}
		}
		row ++;
		
	}
	
	file.close();
	
	map<tuple<int,int,int,int>,bool>::iterator it;

	
	int count_on;	
	int final_count;

	for (int cycle = 0; cycle < 6; cycle++) {
		final_count = 0;
		it = space.begin();
		while( it != space.end() ) {
			count_on = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						for (int w = -1; w <= 1; w++) {
							if (x == 0 && y == 0 && z == 0 && w == 0) { continue;}
							parameter = {get<0>(it->first)+x, get<1>(it->first)+y, get<2>(it->first)+z, get<3>(it->first)+w};
							if (space.find(parameter) == space.end()) {
								to_check[parameter] = true;
							} else {
								count_on ++;
							}
						}
					}
				}
			}
			if (count_on == 2 || count_on == 3) {
				next_matrix[{get<0>(it->first), get<1>(it->first), get<2>(it->first), get<3>(it->first)}] = true;
				final_count ++;
			}
			++it;
		}
		it = to_check.begin();
		while( it != to_check.end()) {
			count_on = 0;
			for (int x = -1; x <= 1; x++) {
				for (int y = -1; y <= 1; y++) {
					for (int z = -1; z <= 1; z++) {
						for (int w = -1; w <=1; w++) {
							if (x == 0 && y == 0 && z == 0 && w == 0) { continue;}
							parameter = {get<0>(it->first)+x, get<1>(it->first)+y, get<2>(it->first)+z, get<3>(it->first)+w};
							if (space.find(parameter) != space.end()) {
								count_on ++;
							}
						}
					}
				}
			}
			if (count_on == 3) {
				next_matrix[{get<0>(it->first), get<1>(it->first), get<2>(it->first), get<3>(it->first)}] = true;
				final_count ++;
			}
			++it;
		}

		space = next_matrix;
		to_check.clear();
		next_matrix.clear();
	
	}
	
	return final_count;
}
