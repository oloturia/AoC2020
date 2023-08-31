#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::vector;

int elab (string filename);
string check_boundary(int boundx, int boundy, vector<string> matrix);

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

string check_boundary(int boundx, int boundy, vector<string> mat) {
	char seat = mat[boundx][boundy];
	int offx;
	int offy;
	int count = 0;
	for (int ix = -1; ix <= 1; ix ++) {
		for (int iy = -1; iy <= 1; iy ++) {
			if (ix == 0 && iy == 0) {
				continue;
			}
			offx = ix;
			offy = iy;
			while (true) {
				if (boundx+offx < 0 || boundy+offy < 0 || boundx+offx >= mat.size() || boundy+offy >= mat[0].length()) {
					break;
				}
				if (mat[boundx+offx][boundy+offy] == '#') {
					count ++;
					break;
				}
				if (mat[boundx+offx][boundy+offy] == 'L') {
					break;
				}
				
				if (ix < 0) {
					offx --;
				} else if (ix > 0) {
					offx ++;
				}
				if (iy < 0) {
					offy --;
				} else if (iy > 0) {
					offy ++;
				}
				
			}
		}
	}
	if (count >= 5 && seat == '#') {
		return "L";
	}
	if (count == 0 && seat == 'L') {
		return "#";
	}
	return string( 1,seat);
}

int elab(string filename) {
	ifstream file(filename);

	int height = count(std::istreambuf_iterator<char>(file),std::istreambuf_iterator<char>(),'\n');
	file.clear();
	file.seekg(0);
	
	string temp;
	
	vector<string> matrix;
	vector<string> new_matrix;
	string new_line;
	
	int x = 0;
	while (getline(file,temp)){;
		matrix.push_back( temp );
		new_matrix.push_back("");
		x ++;
	}
	
	file.close();
	
	string status;
	bool moved = true;
	int width = matrix[0].length();
	int count;
	
	while (moved) {
		moved = false;
		count = 0;
		for (int ix = 0; ix < height; ix ++) {
			new_matrix[ix] = "";
			
			for (int iy = 0; iy < width; iy ++) {
				if (matrix[ix][iy] == '.') {
					new_matrix[ix].append(".");
					continue;
				}
				status = check_boundary(ix,iy,matrix);
				new_matrix[ix].append(status);
				
				if (status[0] != matrix[ix][iy]) {
					moved = true;
				}
				if (status == "#") {
					count ++;
				}
			}
		}
		
		for (int ix = 0; ix < height; ix ++) {
			matrix[ix] = new_matrix[ix];	
		}
		
	}

	
	
	return count;
}
