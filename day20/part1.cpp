#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#define RIGHT true
#define LEFT false
#define SIZE 144

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

unsigned long elab (string filename);


class Tile {
	public:
		string id;
		char matrix[10][10];
		vector<string> boundaries;
		
		string rightLeft(bool right) {
			string tbound = "";
			int col = 0;
			if (right) {col = 9;}
			for (int x = 0; x < 10; x ++) {
				tbound += matrix[x][col];
			}
			return tbound;
		}	
		
		void flip() {
			char new_matrix[10][10];
			for (unsigned int row = 0; row < 10; row++) {
				for (unsigned int col = 0; col < 10; col++) {
					new_matrix[row][col] = matrix[row][9-col];
				}
				
			}
			copyMatrix(new_matrix);
			return;
		}
		
		void rotate90() {
			char new_matrix[10][10];
			for (unsigned int row = 0; row < 10; row++) {
				for (unsigned int col = 0; col < 10; col++) {
					new_matrix[col][9-row] = matrix[row][col];
				}
			}
			copyMatrix(new_matrix);
			return;
		}
	private:
		void copyMatrix(char new_matrix[10][10]) {
			for (unsigned int row = 0; row < 10; row++) {
				for (unsigned int col = 0; col < 10; col++) {
					matrix[row][col] = new_matrix[row][col];
				}
			}
		return;
		}

};

bool check(Tile tile1, Tile tile2);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

bool check(Tile tile1, Tile tile2) {
	if (tile1.rightLeft(RIGHT) == tile2.rightLeft(LEFT)) {
		return true;
	}
	return false;
}

unsigned long elab(string filename) {
	ifstream file(filename);

	string temp;
	int row;
	int nTile = 0;
	Tile tiles[SIZE];
	
	while (getline(file,temp)){;
		if (temp != "") {
			if (temp.substr(0,1) == "T") {
				tiles[nTile].id = temp.substr(5,4);
				row = 0;
			} else {
				for (unsigned int i = 0; i < temp.length(); i++) {
					tiles[nTile].matrix[row][i] = temp[i];
				}
				row ++;
			}
		} else {
			nTile ++;
		}
	}
	
	unsigned long result = 1;
	int count = 0;
	bool found;
	for (unsigned int t1 = 0; t1 < SIZE; t1++) {
		for(unsigned int t2 = t1+1; t2 < SIZE; t2++) {
			found = false;
			
			for (unsigned int i1 = 0; i1 < 8; i1++){				
				for (unsigned int i2 = 0; i2 < 8; i2++){
					found = check(tiles[t1],tiles[t2]);
					if (found){break;}
					if(i2%4 == 0) {
						tiles[t2].flip();
					} else {
						tiles[t2].rotate90();
					}
				}
				if (found){break;}
				
				if (i1%4 == 0) {
					tiles[t1].flip();
				} else {
					tiles[t1].rotate90();
				}
				
			}
			if (found) {
				tiles[t1].boundaries.push_back(tiles[t2].id);
				tiles[t2].boundaries.push_back(tiles[t1].id);
			}
		}
		if (tiles[t1].boundaries.size() == 2) {
			result *= atol(tiles[t1].id.c_str());
			count ++;
			if (count == 4) {
				break;
			}
		}
		
	}
	return result;
}
