#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <cmath>
#define RIGHT true
#define LEFT false
#define TOP false
#define DOWN true
#define SIZE 144


using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

unsigned long elab (string filename);
const int side = std::sqrt(SIZE);


class Tile {
	public:
		string id;
		char matrix[10][10];
		vector<string> boundaries;
		bool mapped = false;
		
		
		string showLine(unsigned int line) {
			string tempLine;
			for(unsigned int x = 1; x < 9; x++) {
				tempLine = tempLine + matrix[line][x];
			}
			return tempLine;
		}
		
		string rightLeft(bool right) {
			string tbound = "";
			int col = 0;
			if (right) {col = 9;}
			for (int x = 0; x < 10; x ++) {
				tbound += matrix[x][col];
			}
			return tbound;
		}
		
		string topDown(bool top) {
		
			string tbound = "";
			int row = 0;
			if (top) {row = 9;}
			
			for (int x = 0; x < 10; x ++) {
				tbound += matrix[row][x];
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
bool orderTile(Tile* tile1, Tile* tile2, bool onlyFirst, bool topDown);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}


bool orderTile(Tile* tile1, Tile* tile2, bool onlyOne = false, bool topDown = false) {
	bool found = false;
	if (not onlyOne) {
		for (unsigned int i1 = 0; i1 <= 8; i1++) {
			for(unsigned int i2 = 0; i2 <= 8; i2++) {
				found = (tile1->rightLeft(RIGHT) == tile2->rightLeft(LEFT));
				if (found) {break;}
				if(i2%4 == 0) {
					tile1->flip();
					tile1->rotate90();
				} else {
					tile1->rotate90();
				}
			}
			if (found) {break;}
			
			if(i1%4 == 0) {
				tile2->flip();
				tile2->rotate90();
			} else {
				tile2->rotate90();
			}
		}
	} else {
		for (unsigned int i = 0; i <= 8; i++) {
			if(topDown) {
				found = (tile1->topDown(DOWN)  == tile2->topDown(TOP));
			} else {
				found = (tile1->rightLeft(RIGHT)  == tile2->rightLeft(LEFT));
			}
			if (found) {break;}
			if(i%4 == 0) {
				tile2->flip();
				tile2->rotate90();
			} else {
				tile2->rotate90();
			}
		}
		

	}
	return found;
}


unsigned long elab(string filename) {
	ifstream file(filename);

	string temp;
	int row;
	int col;
	int nTile = 0;
	Tile tiles[SIZE];
	Tile corners[4];
	Tile sides[(side-2)*4];
	
	
	while (getline(file,temp)){
		
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
	
	bool found;

	for (unsigned int t1 = 0; t1 < SIZE; t1++) {
		for(unsigned int t2 = 0; t2 < SIZE; t2++) {
			if(t1 == t2) {continue;}
			found = orderTile(&tiles[t2], &tiles[t1]);
			
			if (found) {
				tiles[t1].boundaries.push_back(tiles[t2].id);
			}
		}
	}
	
	Tile ordered[side][side];
	row = 0;
	col = 0;
	Tile corner;
	
	string line[side];
	string next_line[side];
	

	for(auto& t:tiles) {
		if (t.boundaries.size() == 2 && t.mapped == false) {
			t.mapped = true;
			corner = t;
			ordered[row][0] = t;
			line[0] = t.id;
			break;
		}
	}
	
	while(col < side -2) {
		for(auto& t:tiles) {
			if (t.boundaries.size() == 3 && t.mapped == false) {
				if(corner.boundaries[0] == t.id || corner.boundaries[1] == t.id) {
					t.boundaries.erase( find(t.boundaries.begin(), t.boundaries.end(), corner.id) );
					corner.boundaries.erase( find(corner.boundaries.begin(), corner.boundaries.end(), t.id) );
					next_line[col] = corner.boundaries[0];
					t.mapped = true;
					corner = t;
					col ++;
					ordered[row][col] = t;
					line[col] = t.id;
				}
			}
		}
	}
	
	for(auto& t:tiles) {
		if (t.boundaries.size() == 2 && t.mapped == false) {
			if (corner.boundaries[0] == t.id || corner.boundaries[1] == t.id || corner.boundaries[2] == t.id) {
				t.boundaries.erase( find(t.boundaries.begin(), t.boundaries.end(), corner.id) );
				corner.boundaries.erase( find(corner.boundaries.begin(), corner.boundaries.end(), t.id) );
				next_line[col] = corner.boundaries[0];
				next_line[col+1] = t.boundaries[0];
				t.mapped = true;
				ordered[row][col+1] = t;
				line[col+1] = t.id;
				break;
			}
		}
	}
		
		
	while (row < side -2) {
		for(auto& t:tiles) {
			if(t.mapped == false) {
				for (unsigned int sp = 0; sp < side; sp++) {
					if (find(t.boundaries.begin(), t.boundaries.end(), line[sp]) != t.boundaries.end())  {
						t.boundaries.erase( find(t.boundaries.begin(), t.boundaries.end(), line[sp]) );
					}
				}
			}
		}
		
		
		row ++;
		col = 0;
		for (unsigned int sp = 0; sp < side; sp++) {
			for(auto& t:tiles) {
				if (t.id == next_line[col] && t.mapped == false) {
					t.mapped = true;
					
					if (col +1 < side) {
						
						t.boundaries.erase( find(t.boundaries.begin(), t.boundaries.end(), next_line[col+1]) );
					}
					if (col -1 >= 0) {
						t.boundaries.erase( find(t.boundaries.begin(), t.boundaries.end(), ordered[row][col-1].id) );
						
					}
					ordered[row][col] = t;
					line[col] = t.id;
					
					next_line[col] = t.boundaries[0];
					col ++;
				}
			}
		}
		
	}

	for(auto& t:tiles) {
		col = 0;
		if(t.mapped == false) {
			for (unsigned int sp = 0; sp < side; sp++) {
				if (t.id == next_line[sp]) {
					ordered[row+1][sp] = t;
				}
			}
		}
	}
	
	orderTile(&ordered[0][0],&ordered[0][1]);
	
	for(unsigned int row = 0; row < side; row++) {
		if (row !=0) {
			orderTile(&ordered[row-1][0],&ordered[row][0],true,true);
			orderTile(&ordered[row][0],&ordered[row][1],true);			
		}
		for(unsigned int i = 1; i < side -1; i++) {
			orderTile(&ordered[row][i],&ordered[row][i+1],true);
		}
		
	}

	string defmap[96];
	int rowmap = 0;
	
	for (unsigned int y = 0; y < side; y++) {
		for (unsigned int x = 0; x < side; x++) {
			for(unsigned line = 0; line < 8; line++) {
				defmap[rowmap+line] += ordered[y][x].showLine(line+1);
			}
		}
		rowmap += 8;
	}
	
	unsigned long monsters = 0;
	unsigned long result = 0;
	const char cf = '#';
	
	for(unsigned int x = 0; x < 96; x++) {
		for(unsigned int y = 0; y < 96; y++){
			if (x < 96-2 && y < 96-19) {
				if (defmap[x+1][y] == cf && defmap[x+2][y+1] == cf && defmap[x+2][y+4] == cf && defmap[x+1][y+5] == cf && defmap[x+1][y+6] && defmap[x+2][y+7] == cf && defmap[x+2][y+10] == cf && defmap[x+1][y+11] == cf && defmap[x+1][y+12] == cf && defmap[x+2][y+13] == cf && defmap[x+2][y+16] == cf && defmap[x+1][y+17] == cf && defmap[x][y+18] == cf && defmap[x+1][y+18] == cf && defmap[x+1][y+19] == cf	) {
					monsters ++;
				}
			}
			if (defmap[x][y] == '#') {
				result ++;
			}
		}
	}

	result = result - (monsters*15);
	
	return result;
}
