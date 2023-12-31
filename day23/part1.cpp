#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map; using std::to_string;

string elab (string filename);

struct Cup {
	unsigned int next;
};

int main(int argc, char**argv) {
	string solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

string elab(string filename) {
	ifstream file(filename);
	string temp;
	map<int,Cup> cups;
	unsigned int num;
	unsigned int index = 0;
	unsigned int maxind = 0;
	
	while (getline(file,temp)){;
		for(unsigned int i = 0; i < 9; i++) {
			num = temp[i] - 48;
			if (num > maxind) {
				maxind = num;
			}
			if (index == 0) {
				index = num;
			}
			if (i < 8) {
				cups[num].next = temp[i+1] - 48;
			} else {
				cups[num].next = temp[0] - 48;
			}

		}
	}
	file.close();

	unsigned int first;
	unsigned int mid;
	unsigned int last;
	unsigned int destination;
	unsigned int temp_d;
	
	for(unsigned int mv = 0; mv < 100; mv++) {		
		first = cups[index].next;
		mid = cups[first].next;
		last = cups[mid].next;
		cups[index].next = cups[last].next;

		destination = index - 1;
		if (destination == 0) {destination = maxind;}	
		while(destination == first || destination == mid || destination == last) {
			destination --;
			if (destination == 0) {destination = maxind;}
		}
		
		temp_d = cups[destination].next;		
		cups[destination].next = first;
		cups[last].next = temp_d;	
		index = cups[index].next;
	}
	string solution;
	unsigned int index_zero = 1;
	while(cups[index_zero].next != 1) {
		solution = solution + to_string(cups[index_zero].next);
		index_zero = cups[index_zero].next;
	}
	
	return solution;
}
