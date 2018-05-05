#pragma once
#pragma once
#ifndef HAZARDUNITS_H
#define HAZARDUNITS_H
#include"complete.h"
class HazardUnitS
{
public:
	HazardUnitS();
	~HazardUnitS();
	int isStall(unsigned int RsD, unsigned int RtE, unsigned int RtD, unsigned int MemtoRegE, unsigned int branch,
		unsigned int RegWriteE, unsigned int WriteRegE)
	{
		int lwstall = ((RsD == RtE) || (RtD == RtE)) && MemtoRegE;
		int branchstall =
			((branch) && (RegWriteE) && ((WriteRegE == RsD) || (WriteRegE == RtD)));//if the data is still not out of the alu
		return lwstall || branchstall;
	}
private:

};

HazardUnitS::HazardUnitS()
{

}

HazardUnitS::~HazardUnitS()
{

}
#endif