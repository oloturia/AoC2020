#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout; using std::string; using std::ifstream; using std::getline;

long elab (string filename);

int main(int argc, char**argv) {
	long solution;
	
	if (argc >= 2 ) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

long elab(string filename) {
	ifstream file(filename);

	string temp;

	int a = 0;
	int b = 0;
	int c = 0;
	int d = 0;
	int e_x = 0;
	int e_y = 0;

	long counta = 0;
	long countb = 0;
	long countc = 0;
	long countd = 0;
	long counte = 0;

	while (getline(file,temp)) {
		if (temp[a%temp.length()] == '#'){
			counta ++;
		}
		if (temp[b%temp.length()] == '#'){
			countb ++;
		}
		if (temp[c%temp.length()] == '#'){
			countc ++;
		}
		if (temp[d%temp.length()] == '#') {
			countd ++;
		}
		if (e_y%2 == 0) {
			if (temp[e_x%temp.length()] == '#') {
				
				counte ++;
			}
			e_x += 1;
		}
		a +=1;
		b +=3;
		c +=5;
		d +=7;
		e_y += 1;
	}
	
	file.close();
	return counta*countb*countc*countd*counte;
}
