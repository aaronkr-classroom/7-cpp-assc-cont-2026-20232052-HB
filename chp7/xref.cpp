//xref.cpp
#include <iostream>
#include <string>	
#include <vector>	
#include <map>

#include "C:\Users\com316\Desktop\C++\6-cpp-library-algorithms-2026-20232052-HB\chp6\split_str.h"

using namespace std;

map<string, vector<int> > xref(
	istream& in,
	vector<string> find_words(const string&) = lib_split)
{
	string line;
	int line_num = 0;
	map < string, vector<int> > ret;

	while (getline(in, line)) {
		++line_num;

		vector<string> words = find_words(line);
		for (vector<string > ::const_iterator it = words.begin();
			it != words.end(); ++it) {
			ret[*it].push_back(line_num);
		}
	}
	return ret;
}

int main(void) {

	map < string, vector<int> > ret = xref(cin);
	
	//결과를 출력
	for (map<string, vector<int> >::const_iterator it = ret.begin();
		it != ret.end(); ++it) {

		cout << "\"" << it->first << "\" is on line(s): ";

		//이어서 하나 이상의 행 번호를 출력
		vector<int>::const_iterator line_it = it->second.begin();

		//해당 단어가 등장한 첫번째 행 번호를 출력
		cout << *line_it;
		++line_it;
		// 행 번호가 더 있으면 마저 출력
		while (line_it != it->second.end()) {
			cout << ", " << *line_it;
			++line_it;
		}
		// 각 단어를 다음 단어와 구분하려고 새로운 행을 출력
		cout << endl;

	}
	
	
	return 0;
}
