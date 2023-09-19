#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout; using std::string; using std::ifstream; using std::getline;

unsigned long elab (string filename);

int main(int argc, char**argv) {
	unsigned long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

unsigned long elab(string filename) {
	ifstream file(filename);
	string temp;
	string toElab;
	
	
	unsigned long op1;
	unsigned long op2;
	string tempOp;
	char op;
	
	unsigned long result = 0;

	while (getline(file,temp)){
		unsigned int indStart;
		unsigned int index = 0;
		temp = '(' + temp + ')';
		while (true) {
			if (temp[index] == '(') {
				indStart = index +1;
			}
			if (temp[index] == ')') {
				toElab = temp.substr(indStart,index-indStart)+' ';
				tempOp = "";
				op1 = 0;
				op2 = 0;
				for(unsigned int i = 0; i < toElab.length(); i++){
					if (toElab[i] == ' ') {
						if (op1 == 0) {
							op1 = atol(tempOp.c_str());
							tempOp = "";
						} else {
							op2 = atol(tempOp.c_str());
							tempOp = "";
							if (op == '*') {
								op1 = op1 * op2;
							} else {
								op1 = op1 + op2;
							}
						}
					} else if (toElab[i] >= '0' && toElab[i] <= '9') {
						tempOp += toElab[i];
					} else {
						op = toElab[i];
						i++;
					}
				}
				temp = temp.substr(0,indStart-1) + std::to_string(op1) + temp.substr(index+1);
				index = -1;
			}
			index ++;
			if (index > temp.length()) {
				break;
			}
		}
		result += atol(temp.c_str());
	}
	
	file.close();
	
	return result;
}
