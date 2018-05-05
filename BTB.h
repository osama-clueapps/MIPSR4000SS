#pragma once
#pragma once
#ifndef BTB_H
#define BTB_H
#include <vector>
using namespace std;
struct bt {
	unsigned int branchpc;
	unsigned int predictedPC;
	int predictedState;
	int Taken;
};
class BTB {

private:
	int branchPredict(int prev, bool taken)
	{
		if (prev == 0)
		{
			if (taken)
				return 0;
			else
				return 1;
		}
		else if (prev == 1)
		{
			if (taken)
				return 0;
			else
				return 2;
		}
		else if (prev == 2)
		{
			if (taken)
				return 1;
			else
				return 3;
		}
		else if (prev == 3)
		{
			if (taken)
				return 2;
			else
				return 3;
		}
	}
	int findPC(unsigned int pc) {
		for (int i = 0; i < predict.size(); i++)
			if (predict[i].branchpc == pc)
				return i;
		return -1;
	}
public:
	vector <bt> predict;
	BTB() {
		predict.resize(15);
	}
	void fillVector(vector < int> inst) {
		predict.resize(inst.size());
		for (int i = 0; i < inst.size(); i++) {
			if (inst[i] >> 26 == 0x4) {
				predict[i].branchpc = i * 4;
				predict[i].predictedState = 1;
			}
			else predict[i].branchpc = 3;
		}
	}
	bool isBranch(unsigned int pc) {
		for (int i = 0; i < predict.size(); i++)
			if (predict[i].branchpc == pc)
				return true;
		return false;
	}
	void update(unsigned int pc, bool taken) {
		int i = findPC(pc);
		if (i != -1)
			predict[i].predictedState = branchPredict(predict[i].predictedState, taken);
		//if (predict[i].predictedState == 0 || predict[i].predictedState == 1) {
		////predict[i].predictedPC =
		//}
		//else
		//	predict[i].predictedPC = predict[i].branchpc + 4;
	}
	bool TakenorNot(unsigned int pc) {
		if (pc % 4 == 0) {
			int i = findPC(pc);
			if (i != -1)
			{
				if (predict[i].predictedState == 0 || predict[i].predictedState == 1)
					return true;
				else
					return false;
			}
		}
		else return false;
	}
};

#endif