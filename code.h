#pragma once
#pragma once
#ifndef CODE_H
#define CODE_H
#include <string>
#include <vector>
using namespace std;

class Code {

public:
	string wordinst;
	int numinst;
	unsigned int pc;

	Code() {

	}

	void setDetails(string s, int ins, unsigned int p) {
		wordinst = s;
		numinst = ins;
		pc = p;
	}
};

#endif