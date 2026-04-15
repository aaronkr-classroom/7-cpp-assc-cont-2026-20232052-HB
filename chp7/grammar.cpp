//grammar.cpp
#include <algorithm>	
#include <cstdlib>
#include <stdexcept>
#include <ctime>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "C:\Users\com316\Desktop\C++\6-cpp-library-algorithms-2026-20232052-HB\chp6\split_str.h"

using namespace std;

typedef vector<string> Rule;
typedef vector<Rule> Rule_collection;
typedef map<string, Rule_collection> Grammar;

Grammar read_grammar(const string& filename) {
	//aaron.kr에 있는 grammar .txt나 grammar-long.txt 필수
	Grammar ret;
	string line;

	ifstream grammar_file(filename);
	if (!grammar_file) {
		cerr << "Error opening file: " << filename << endl;
		throw runtime_error("Failed to open file.");

	}
	//입력 데이터를 읽음
	while (getline(grammar_file, line)) {
		vector<string> entry = lib_split(line);
		if (!entry.empty()) {
			ret[entry[0]].push_back(
				Rule(entry.begin() + 1, entry.end()));
		}
	}

}

//꺽쇠호<>있늕 ㅣ확인 함수
bool bracketed(const string& s){
	//<......> ? true : false;
	return s.size() > 1
		&& s[0] == '<'
		&& s[s.size() - 1] == '>';

}

//[0,n) 범위에서 임의 정수 하나를 반환
int nrand(int n) {
	//python의 random 모듈에서 같ㅇ은 함수
	if (n <= 0 || n > RAND_MAX)
		throw domain_error("nrand out of range!");

	const int bucket_size = RAND_MAX / n;
	int r;
	do r = rand() / bucket_size;
	while (r >= n);

	return r;
}

void gen_aux(const Grammar& g, const string& word,
	vector<string>& ret) {
	if (!bracketed(word)) ret.push_back(word);

	else { // <....> 있는 단어 (문법 규칙)
		// word와 연관된 규칙을 찾음
		Grammar::const_iterator it = g.find(word);
		if (it == g.end())
			throw logic_error("empty rule!");

		const Rule_collection& c = it->second;

		const Rule& r = c[nrand(c.size())];

		for (Rule::const_iterator i = r.begin();
			i != r.end(); i++) {
			gen_aux(g. * i, ret);
		}
	}
}

vector<string> gen_sent(const Grammar& g) {
	vector<string> ret;
	gen_aux(g, "<sentence>", ret);
	return ret;
}

int main(void) {

	srand(static_cast<unsigned int>(time(0)));

	cout << "choose a grammar file: \n"
		<< "1. grammar.txt\n"
		<< "2. grammar-long.txt\n"
		<< "3. enter 1 or 2: ";

		string choice;
		cin >> choice;
		string filename;
		if (choice == "1") {
			filename = "grammar.txt";
		}
		else if (choice == "2") {
			filename = "grammar-long.txt";
		}
		else {
			cout << " invalid choice chhose only 1 or 2!:" << endl;
			return 1;

		}

		Grammar grammar;
		try {
			grammar = read_grammar(filename);
		}
		catch (const runtime_error& e) {
			cerr << e.what() << endl;
			return 1;
		}
	vector<string> sentence = gen_sent(grammar);
	//첫번째 단어 출력
	vector<string>::const_iterator it = sentence.begin();
	if (!sentence.empty()) {
		cout << *it;	//반복자의 카리키는 값을 출력
		++it;			// 반복자를 이동시킴

		//공백과 함께 나머지 단어 출력

	}

	while (it != sentence.end()) {
		cout << " " << *it;
		++it;
	}

	cout << endl;

	return 0;
}
