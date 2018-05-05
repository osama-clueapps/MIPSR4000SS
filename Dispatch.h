#ifndef DISPATCH_H
#define DISPATCH_H
#include "instCU.h"
#include <queue>
class Dispatch
{
public:
	struct inst {
		unsigned int instruction;
		int instNum;
	};
	Dispatch();
	~Dispatch();
	void inputData(unsigned int inst1, int instNum1, unsigned int inst2, int instNum2)
	{
		if (inst1 != 0)
		{
			inst i;
			i.instruction = inst1;
			i.instNum = instNum1;
			insts.push(i);
		}
		if (inst2 != 0)
		{
			inst i;
			i.instruction = inst2;
			i.instNum = instNum2;
			insts.push(i);
		}
	};
	void outputData(int num)
	{
		if (insts.size() == 0)
		{
			inst1 = 0;
			inst2 = 0;
			instNum1 = -1;
			instNum2 = -1;
			return;
		}
		if (num == 0)
			return;
		unsigned int inst1_val, inst2_val;
		if (num == 1)
		{
			inst1_val = insts.front().instruction;
			inst1 = inst1_val;
			instNum1 = insts.front().instNum;
			insts.pop();
			return;
		}
		inst1_val = insts.front().instruction;
		inst1 = inst1_val;
		instNum1 = insts.front().instNum;
		insts.pop();
		if (insts.size() == 0)
		{
			inst2 = 0;
			instNum2 = -1;
			return;
		}
		inst2_val = insts.front().instruction;
		instCU cu1, cu2;
		cu1.setinst(inst1_val);
		cu2.setinst(inst2_val);
		if (!dependent(cu1, cu2))
		{
			inst2 = inst2_val;
			instNum2 = insts.front().instNum;
			insts.pop();
		}
		else
		{
			inst2 = 0;
			instNum2 = -1;
		}
	}
	unsigned int inst1, inst2;
	int instNum1, instNum2;
private:
	queue<inst> insts;
	bool dependent(instCU cu1, instCU cu2)
	{
		if ((cu1.MemtoReg || cu1.MemWrite) && (cu2.MemtoReg || cu2.MemWrite))//interconnecting memory accessing
			return true;
		if (cu1.RegWrite&&cu2.RegWrite)//dependecies
		{
			int write1, write2;
			write1 = cu1.RegDst ? cu1.RdE : cu1.RtD;
			write2 = cu2.RegDst ? cu2.RdE : cu2.RtD;
			if (cu1.RsD == write2 || cu2.RsD == write1)
				return true;
			if (cu1.RegDst&&cu1.RtD == write2)
				return true;
			if (cu2.RegDst&&cu2.RtD == write1)
				return true;
		}
		if ((cu1.branch || cu1.jump || cu1.jumpr) && (cu2.branch || cu2.jump || cu2.jumpr))//interconnecting branches or jumps
			return true;
		return false;
	}
};

Dispatch::Dispatch()
{

}

Dispatch::~Dispatch()
{
}
#endif