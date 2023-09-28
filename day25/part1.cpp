#include <iostream>
#include <fstream>
#include <algorithm>
#include <set>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::set;

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
	unsigned long cardkey;
	unsigned long doorkey;
	
	getline(file,temp);
	cardkey = atol(temp.c_str());
	getline(file,temp);
	doorkey = atol(temp.c_str());
	file.close();
	
	unsigned long subjectcard = 1;
	unsigned long subjectdoor = 1;
	unsigned long loopcard = 0;
	unsigned long loopdoor = 0;
	
	
	while(subjectcard != cardkey) {
		subjectcard = (subjectcard*7)%20201227;
		loopcard ++;
		
	}
	while(subjectdoor != doorkey) {
		subjectdoor = (subjectdoor*7)%20201227;
		loopdoor ++;
	}
	
	unsigned long privatekey = 1;
	
	for(unsigned int i = 0; i < loopcard; i++) {
		privatekey = (subjectdoor*privatekey)%20201227;
	}
	
	return privatekey;
}
