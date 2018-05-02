#pragma once
#pragma once
#ifndef RegFile_H
#define RegFile_H
#include <iostream>
using namespace std;
class RegFile {

public:
	int file[16];
	RegFile() {
		for (int i = 0; i<16; i++)
			file[i] = 0;
	}
	RegFile(int f[16]) {
		for (int i = 0; i < 16; i++)
			file[i] = f[i];
	}

	void readRegFile(int s1_addr, int s2_addr, int &s1_data, int &s2_data) {
		s1_data = file[s1_addr];
		s2_data = file[s2_addr];
	}

	void writeRegFile(int addr, int data) {
		file[addr] = data;
	}

	void jalRegFile(int pc) {
		file[15] = pc;
	}

	void print() {
		for (int i = 0; i < 16; i++)
			cout << i << "	" << file[i] << endl;
	}

};

#endif
