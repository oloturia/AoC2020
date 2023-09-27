#include <iostream>
#include <fstream>
#include <algorithm>
#include <deque>
#include <set>

using std::cout; using std::string; using std::ifstream; using std::getline; using std::deque; using std::set;
int elab (string filename);
bool combat (deque<int>players[2]);

int main(int argc, char**argv) {
	int solution;
	if (argc >= 2) {
		solution =  elab(argv[1]);
	} else {
		solution = elab("input");
	}
	cout << solution << '\n';
}

bool combat (deque<int> players[2]) {
	unsigned int ply1;
	unsigned int ply2;
	set<deque<int>> history[2];
	deque<int> recursive[2];
	deque<int> initial[2];
	
	initial[0] = players[0];
	initial[1] = players[1];
	
	history[0].insert(players[0]);
	history[1].insert(players[1]);
	
	while (players[0].size() > 0 && players[1].size() > 0) {
		ply1 = players[0].front();
		ply2 = players[1].front();
		
		players[0].pop_front();
		players[1].pop_front();		
		
		if (players[0].size() >= ply1 && players[1].size() >= ply2) {
			for(auto rp1 = players[0].begin(); rp1 < players[0].begin()+ply1; ++rp1) {
				recursive[0].push_back(*rp1);
			}
			for(auto rp2 = players[1].begin(); rp2 < players[1].begin()+ply2; ++rp2) {
				recursive[1].push_back(*rp2);
			}
			if(combat(recursive)){
				players[0].push_back(ply1);
				players[0].push_back(ply2);
			} else {
				players[1].push_back(ply2);
				players[1].push_back(ply1);
			}
			recursive[0].clear();
			recursive[1].clear();
		} else if (ply1 > ply2) {
			players[0].push_back(ply1);
			players[0].push_back(ply2);
		} else {
			players[1].push_back(ply2);
			players[1].push_back(ply1);
		}
		
		if( history[0].find(players[0]) != history[0].end() && history[1].find(players[1]) != history[1].end() ) {
			return true;
		} else {
			history[0].insert(players[0]);
			history[1].insert(players[1]);
		}		
	}
		
	if (players[0].size() == 0) {
		return false;
	} 
	return true;
}
	

int elab(string filename) {
	ifstream file(filename);

	string temp;
	deque<int> players[2];
	unsigned int second = 0;
	
	while (getline(file,temp)){;
		if(temp == "") {
			second = 1;
			getline(file,temp);
		} else if (temp.substr(0,1) != "P") {
			players[0+second].push_back( atoi(temp.c_str()) );
		}
	}
	file.close();
	unsigned int ply1;
	unsigned int ply2;
	deque<int> recursive[2];
	
	while (players[0].size() > 0 && players[1].size() > 0) {
		ply1 = players[0].front();
		ply2 = players[1].front();
		
		players[0].pop_front();
		players[1].pop_front();
		
		if (players[0].size() >= ply1 && players[1].size() >= ply2) {
			for(auto rp1 = players[0].begin(); rp1 < players[0].begin()+ply1; ++rp1) {
				recursive[0].push_back(*rp1);
			}
			for(auto rp2 = players[1].begin(); rp2 < players[1].begin()+ply2; ++rp2) {
				recursive[1].push_back(*rp2);
			}
			if(combat(recursive)){
				players[0].push_back(ply1);
				players[0].push_back(ply2);
			} else {
				players[1].push_back(ply2);
				players[1].push_back(ply1);
			}
			recursive[0].clear();
			recursive[1].clear();				
		} else if (ply1 > ply2) {
			players[0].push_back(ply1);
			players[0].push_back(ply2);
		} else {
			players[1].push_back(ply2);
			players[1].push_back(ply1);
		}
	}
		
	int won_12 = 0;
	if (players[0].size() == 0) {
		won_12 = 1;
	}
	
	unsigned int result = 0;
	unsigned int value;
	unsigned int size_w = players[won_12].size();	
	for(unsigned int i = 0; i < size_w; i++) {
		value = players[won_12].back();
		result += (i+1)*value;
		players[won_12].pop_back();
	}

	return result;
}
