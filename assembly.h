#pragma once
#pragma once
#ifndef ASSEMBLY_H
#define ASSEMBLY_H
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

class assembly {

private:

	bool getOpcode(string s, int &opcode, int &funct, char &type) {

		funct = -1;
		if (s == "ADD") {
			opcode = 0;
			funct = 32;
			type = 'R';
		}
		else if (s == "ADDI") {
			opcode = 8;
			type = 'I';
		}
		else if (s == "LW") {
			opcode = 0x23;
			type = 'I';
		}
		else if (s == "SW") {
			opcode = 0x2b;
			type = 'I';
		}
		else if (s == "JAL") {
			opcode = 3;
			type = 'J';
		}
		else if (s == "J") {
			opcode = 2;
			type = 'J';
		}
		else if (s == "JR") {
			opcode = 0;
			funct = 8;
			type = 'R';
		}
		//pseudoinstruction ask about it
		else if (s == "BLE") {
			opcode = 4;
			type = 'I';
		}
		else if (s == "XOR") {
			opcode = 0;
			funct = 38;
			type = 'R';
		}
		else if (s == "SLT") {
			opcode = 0;
			funct = 42;
			type = 'R';
		}
		else return false;

		return true;
	}

	bool split(string s, string &name, int &rs, int &rt, int &rd, int &imm) {

		int i = s.find(" ");
		/*	if (i == string::npos)*/
		/*return false;*/

		int j = s.find(",");
		int j1 = s.find(",", j + 1);
		name = s.substr(0, i);

		if (j != string::npos) {
			rd = atoi((s.substr(i + 1, j)).c_str());
			/*	if (rd > 15 || rd<0)*/
			/*	return false;*/
		}

		else if (name != "JR") {
			imm = atoi((s.substr(i + 1)).c_str());
			//	cout << "%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%		" << imm << endl;
				return true;
		}
		else {
			rs = atoi((s.substr(i + 1)).c_str());
			/*if (rs > 15 || rs<0)
			return false;*/
			rd = 0;
			rt = 0;
				return true;
		}

		if (j1 != string::npos) {

			rs = atoi((s.substr(j + 1, j1)).c_str());
			rt = atoi((s.substr(j1 + 1)).c_str());
			imm = rt;
			/*if (rs > 15 || rs < 0)
			return false;*/
			/*	if (rt > 15 || rt < 0)
			return false;*/
		}

		else {
			int k = s.find("(");
			int k1 = s.find(")");

			/*if (k == string::npos || k1 == string::npos)
			return false;*/


			rt = rd;
			imm = atoi((s.substr(j + 1, k)).c_str());
			rs = atoi((s.substr(k + 1, k1)).c_str());

			//if (rt > 15 || rt < 0)
			////	return false;
			//if (rs > 15 || rs < 0)
			//return false;
		}
		return true;
	}

	bool parseASM(string s, int &inst) {

		int opcode, funct, rs, rt, rd, imm;
		string name;
		char type;


		if (!split(s, name, rs, rt, rd, imm)) {
			cout << "UNKNOWN INSTRUCTION: SYNTAX ERROR" << endl;
			//return false;
		}

		if (!getOpcode(name, opcode, funct, type)) {
			cout << "UNKNOWN INSTRUCTION: SYNTAX ERROR" << endl;
			//return false;
		}


		if (type == 'R') {
			cout << "opcode:" << hex << opcode << endl << "rs: " << rs << endl << "rt: " << rt << endl << "rd: " << rd << endl << "imm: " << imm << endl;
			rs = rs << 21;
			rt = rt << 16;
			rd = rd << 11;

			opcode = opcode << 26;
			inst = opcode | rs | rt | rd | funct;
		}
		else if (type == 'I') {

			if (opcode != 0x4) {
				rt = rd;
			}
			else {
				rt = rs;
				rs = rd;

			}

			cout << "opcode:" << hex << opcode << endl << "rs: " << dec << rs << endl << "rt: " << rt << endl << "rd: " << rd << endl << "imm: " << imm << endl;
			opcode = opcode << 26;	rs = rs << 21;
			rt = rt << 16;
			cout << "I:    " << hex << rs << "      " << rt << endl;

			inst = opcode | rs | rt | (imm & 0x0000ffff);
		}
		else if (type == 'J') {
			opcode = opcode << 26;
			inst = opcode | imm;
			//cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&		" << inst << endl;
		}

		return true;

	}

	void convertASM() {

		inst.clear();
		inst.resize(instructions.size());
		cout << instructions.size() << endl;
		for (int i = 0; i < instructions.size(); i++)
			parseASM(instructions[i], inst[i]);
		inst.push_back(0);
	}

	bool allspace(string l)
	{
		for (int x = 0; x < l.length(); x++)
		{
			if (l[x] != ' ')
				return false;

		}
	};

	bool check()
	{
		ifstream myReadFile;
		myReadFile.open(fn);
		string inst;
		string l;
		int i;
		//flag = true;
		string arr[3];

		if (myReadFile.is_open()) {
			while (!myReadFile.eof()) {

				arr[0] = ""; arr[1] = ""; arr[2] = "";
				myReadFile >> inst;
				i = 0;
				if (inst == "ADD" || inst == "XOR" || inst == "SLT")
				{
					getline(myReadFile, l);
					for (int x = 0; x < l.length(); x++)
					{
						if (l[x] != ',')
							arr[i] += l[x];
						else
							i++;
					}
					//cout << arr[0] << arr[1] << arr[2] << endl;
					if ((l == ""))
						//flag = false;
						return false;
					else if (allspace(l))
						//flag = false;
						return false;
					else if (!((stoi(arr[0]) <= 15) && (stoi(arr[1]) <= 15) && (stoi(arr[2]) <= 15)))
					{
						//flag = false;
						return false;
						cout << "add" << endl;
					}
					//else
					//flag = true;
				}
				else if (inst == "ADDI")
				{
					string x; bool b = true;
					getline(myReadFile, l);
					for (int x = 0; x < l.length(); x++)
					{
						if ((l[x] != ','))
							arr[i] += l[x];
						else
							i++;
					}
					x = arr[2];
					//cout << "x=" <<x;
					//cout << "Xvals" << endl;
					//for (int a = 0; a < x.length(); a++)
					//{
					//	//cout << x[a]<<endl;
					//	if (/*x[a] != ' ' ||*/ !(isdigit(x[a]))) {
					//		b = false;
					//		
					//	} 

					//}
					//cout <<"b="<< b;
					if ((l == ""))
						//	flag = false;
						return false;
					else if (allspace(l))
						//flag = false;
						return false;
					else if (!((stoi(arr[0]) <= 15) && (stoi(arr[1]) <= 15) /*&& (b)*/))
					{
						//flag = false;
						return false;
						cout << "addi" << endl;;
					}

				}
				else if ((inst == "LW") || (inst == "SW"))
				{
					getline(myReadFile, l);
					for (int x = 0; x < l.length() - 1; x++)
					{
						if (l[x] != ',' && l[x] != '(')
							arr[i] += l[x];
						else
							i++;
					}
					if ((l == ""))
						//flag = false;
						return false;
					else if (allspace(l))
						//flag = false;
						return false;
					else if (!((stoi(arr[0]) <= 15) && ((stoi(arr[1])) % 4 == 0) && (stoi(arr[2]) <= 15)))
						//	flag = false;
						return false;
				}
				else if (inst == "JR")
				{
					//cout << "in";
					getline(myReadFile, l);
					//cout << l;
					if ((l == ""))
						//	flag = false;
						return false;
					else if (allspace(l))
						//	flag = false;
						return false;
					else if (stoi(l)>15)
						//flag = false;
						return false;
				}
				else if (inst == "J")
				{

					getline(myReadFile, l);
					//cout << l;

					if ((l == ""))
						//flag = false;
						return false;
					else if (allspace(l))
						//flag = false;
						return false;
				}


				else if (inst == "BLE")
				{
					getline(myReadFile, l);
					for (int x = 0; x < l.length(); x++)
					{
						if (l[x] != ',' && l[x] != '(')
							arr[i] += l[x];
						else
							i++;
					}
					cout << arr[0] << "?" << arr[1] << "?" << arr[2] << "?" << endl;
					if ((l == ""))
						//flag = false;
						return false;
					else if (allspace(l))
						//flag = false;
						return false;
					else if (!((stoi(arr[0]) <= 15) && (stoi(arr[0]) <= 15) && (arr[2] != "")))
						//flag = false;
						return false;

				}


			}return true;
		}

		myReadFile.close();
	}

	void removeSpaces(string &s) {
		int m = s.find(' ');
		int n;
		if (m < 5)
			n = s.find(' ', m + 1);
		while (n != string::npos) {
			s.erase(n);
			n = s.find(' ', m + 1);
		}
	}

	void readASM() {
		ifstream inp;
		inp.open(fn);
		string s;
		if (inp.is_open()) {


			while (!inp.eof()) {
				getline(inp, s);
				cout << s << endl;
				removeSpaces(s);
				cout << s << endl;
				instructions.push_back(s);

				//getline(inp, s);
			}
		}

		inp.close();
	}

public:
	string fn;
	vector <string> instructions;
	vector <int> inst;
	bool valid;

	assembly(string filename) {
		fn = filename;
		if (check()) {
			valid = true;
			readASM();
			convertASM();
		}
		else
			valid = false;

	}

	assembly() {
		fn = "";
	}

	bool readFile(string filename) {
		fn = filename;
		if (check()) {
			readASM();
			convertASM();
			//for (int i = 0; i < inst.size(); i++)
			//cout << (unsigned)inst[i] << endl;
			valid = true;
			return true;
		}
		else
			valid = false;
		return false;
	}


};

#endif