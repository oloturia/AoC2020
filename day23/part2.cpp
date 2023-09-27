#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::map; using std::to_string;

unsigned long elab (string filename);

struct Cup {
	unsigned long next;
};

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
	map<unsigned long,Cup> cups;
	unsigned long num;
	unsigned long index = 0;
	unsigned long maxind = 0;
	
	while (getline(file,temp)){;
		for(unsigned long i = 0; i < 9; i++) {
			num = temp[i] - 48;
			if (num > maxind) {
				maxind = num;
			}
			if (index == 0) {
				index = num;
			}
			if (i < 8) {
				cups[num].next = temp[i+1] - 48;
			}
		}
	}
	file.close();
	
	cups[num].next = maxind+1;
	for(unsigned long i = maxind+1; i < 1000000; i++) {
		cups[i].next = i+1;
	}
	cups[1000000].next = index;
	maxind = 1000000;
	
	unsigned long first;
	unsigned long mid;
	unsigned long last;
	unsigned long destination;
	unsigned long temp_d;

	for(unsigned long mv = 0; mv < 10000000; mv++) {
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
	unsigned long solution;
	solution = cups[1].next * cups[cups[1].next].next;
	
	return solution;
}
