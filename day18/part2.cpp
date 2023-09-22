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
	
	int opInd;
	unsigned int startInd;
	unsigned int indElab;
	
	string tempOp;
	
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
				toElab = temp.substr(indStart,index-indStart);
				op1 = 0;
				op2 = 0;
				indElab = 0;
				startInd = 0;
				while(true) {
					if(toElab[indElab] == '+') {
						tempOp = "";
						opInd = indElab;
						indElab -=2 ;
						while (toElab[indElab] >= '0' && toElab[indElab] <= '9') {
							tempOp = toElab[indElab] + tempOp;
							if (indElab == 0) {
								indElab = 0;
								break;
							}
							indElab --;
						}
						startInd = indElab;
						op1 = atol(tempOp.c_str());
						tempOp = "";
						indElab = opInd +2;
						while (toElab[indElab] >= '0' && toElab[indElab] <= '9') {
							tempOp = tempOp + toElab[indElab];
							indElab ++;
							if (indElab > toElab.length()) {
								indElab = toElab.length();
								break;
							}
						}						
						op2 = atol(tempOp.c_str());
						op1 = op1+op2;
						if (startInd == 0) {
							toElab = std::to_string(op1) + toElab.substr(indElab);
						} else {
							toElab = toElab.substr(0,startInd+1) + std::to_string(op1) + toElab.substr(indElab);
						}
						indElab = 0;
						
					} else {
						indElab ++;
						if (indElab > toElab.length() ) {
							break;
						}
					}
				}
				op1 = 0;
				op2 = 0;
				indElab = 0;
				startInd = 0;
				while(true) {
					if(toElab[indElab] == '*') {
						tempOp = "";
						opInd = indElab;
						indElab -=2 ;
						while (toElab[indElab] >= '0' && toElab[indElab] <= '9') {
							tempOp = toElab[indElab] + tempOp;
							if (indElab == 0) {
								indElab = 0;
								break;
							}
							indElab --;
						}
						startInd = indElab;
						op1 = atol(tempOp.c_str());
						tempOp = "";
						indElab = opInd +2;
						while (toElab[indElab] >= '0' && toElab[indElab] <= '9') {
							tempOp = tempOp + toElab[indElab];
							indElab ++;
							if (indElab > toElab.length()) {
								indElab = toElab.length();
								break;
							}
						}						
						op2 = atol(tempOp.c_str());
						op1 = op1*op2;
												
						if (startInd == 0) {
							toElab = std::to_string(op1) + toElab.substr(indElab);
						} else {
							toElab = toElab.substr(0,startInd+1) + std::to_string(op1) + toElab.substr(indElab);
						}
						indElab = 0;
						
					} else {
						indElab ++;
						if (indElab > toElab.length() ) {
							break;
						}
					}
				}
				temp = temp.substr(0,indStart-1) + toElab + temp.substr(index+1);
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
