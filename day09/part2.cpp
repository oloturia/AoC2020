#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>

using std::cout; using std::vector; using std::string; using std::ifstream; using std::getline;

long elab (string filename);

int main(int argc, char**argv) {
	long solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

long elab(string filename) {
	ifstream file(filename);

	string temp;
	long buffer[25];
	unsigned int fill = 0;
	bool started = false;
	bool found;
	
	long numbercheck;
	vector<long> numbers;
	long temp_result;
	unsigned int index_1 = 0;
	unsigned int index_2 = 0;	
	
	long min = 0;
	long max = 0;
	while (getline(file,temp)){
		numbers.push_back( atoi(temp.c_str()) );
		if (started) {
			found = false;
			for (unsigned int i1 = 0; i1 < 25; i1 ++) {
				for (unsigned int i2 = 0; i2 < 25; i2 ++) {
					if (i1 == i2) {continue;}
					if (buffer[i1] + buffer[i2] == atoi(temp.c_str())) {
						found = true;
					}
				}
			}
			if (!found) {
				numbercheck = atoi(temp.c_str()); 
				break;
			}
		}
		fill ++;
		if (fill == 25) {
			fill = 0;
			started = true;
		}
		buffer[fill] = atoi(temp.c_str());
	}
	while(true) {
		temp_result = 0;
		for (unsigned int i = index_1; i <= index_2; i++) {
			temp_result += numbers[i];
		}
		if (temp_result < numbercheck) {
			index_2 ++;
		} else if (temp_result > numbercheck) {
			index_1 ++;
			index_2 = index_1;
		} else {
			file.close();
			min = numbers[index_1];
			for (unsigned int i = index_1; i <= index_2; i++){
				if (numbers[i] > max) {max = numbers[i];}
				if (numbers[i] < min) {min = numbers[i];}
			}
			return min+max;
		}
		
	}	
	file.close();
	return 0;
}
