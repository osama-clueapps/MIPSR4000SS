#ifndef DISPATCH_H
#define DISPATCH_H
#include "instCU.h"
#include <queue>
class Dispatch
{
public:
	Dispatch();
	~Dispatch();
	void inputData(unsigned int inst1, unsigned int inst2)
	{
		insts.push(inst1);
		insts.push(inst2);
	};
	void outputData()
	{
		unsigned int inst1_val, inst2_val;
		inst1_val = insts.back();
		insts.pop();
		inst2_val = insts.back();
		instCU cu1,cu2;
		cu1.setinst(inst1_val);
		cu2.setinst(inst2_val);
		inst1 = inst1_val;
		if (!dependent(cu1, cu2))
		{
			inst2 = inst2_val;
			insts.pop();
		}		
	}
	unsigned int inst1, inst2;
private:
	queue<unsigned int> insts;
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
