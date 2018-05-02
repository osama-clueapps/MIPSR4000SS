#pragma once
#ifndef HAZARDUNIT_H
#define HAZARDUNIT_H
class HazardUnit
{
public:
	HazardUnit();
	~HazardUnit();
	int StallF = 0, StallD = 0, ForwardAD = 0, ForwardBD = 0, FlushE = 0, ForwardAE = 0,
		ForwardBE = 0, branchstall = 0, lwstall = 0;
	unsigned int RsD, RsE, RtD, RtE,
		MemtoRegE, branch, RegWriteE, MemWriteE, MemtoRegM,
		WriteRegM, WriteRegE, PCSrcD,
		WriteRegM2, WriteRegM3, RegWriteM, RegWriteM2, RegWriteM3, RegDstE, RdE,
		WriteRegW, RegWriteW;
	void updateData();
	void inputData(unsigned int RsD_in, unsigned int RsE_in, unsigned int RtD_in, unsigned int RtE_in, unsigned int MemtoRegE_in, unsigned int branch_in,
		unsigned int RegWriteE_in, unsigned int MemWriteE_in, unsigned int MemtoRegM_in, unsigned int WriteRegM_in,
		unsigned int PCSrcD_in, unsigned int WriteRegM2_in, unsigned int WriteRegM3_in, unsigned int RegWriteM_in,
		unsigned int RegWriteM2_in, unsigned int RegWriteM3_in, int RegDstE_in, int RdE_in, int WriteRegW_in,
		int RegWriteW_in,unsigned int WriteRegE_in);
private:

};

HazardUnit::HazardUnit()
{
	RsD == 0;
	RsE == 0;
	RtD == 0;
	RtE == 0;
	MemtoRegE == 0;
	branch == 0;
	RegWriteE == 0;
	MemWriteE == 0;
	MemtoRegM == 0;
	WriteRegM == 0;
	PCSrcD == 0;
	WriteRegM2 == 0;
	WriteRegM3 == 0;
	RegWriteM == 0;
	RegWriteM2 == 0;
	RegWriteM3 == 0;
	RegDstE = 0;
	RdE = 0;
	RegWriteW = 0;
	WriteRegW = 0;
}

HazardUnit::~HazardUnit()
{

}
void HazardUnit::inputData(unsigned int RsD_in, unsigned int RsE_in, unsigned int RtD_in, unsigned int RtE_in, unsigned int MemtoRegE_in, unsigned int branch_in,
	unsigned int RegWriteE_in, unsigned int MemWriteE_in, unsigned int MemtoRegM_in, unsigned int WriteRegM_in,
	unsigned int PCSrcD_in, unsigned int WriteRegM2_in, unsigned int WriteRegM3_in, unsigned int RegWriteM_in,
	unsigned int RegWriteM2_in, unsigned int RegWriteM3_in, int RegDstE_in, int RdE_in, int WriteRegW_in,
	int RegWriteW_in, unsigned int WriteRegE_in)
{
	RegDstE = RegDstE_in;
	RdE = RdE_in;
	RegWriteW = RegWriteW_in;
	WriteRegW = WriteRegW_in;
	RsD = RsD_in;
	RsE = RsE_in;
	RtD = RtD_in;
	RtE = RtE_in;
	MemtoRegE = MemtoRegE_in;
	branch = branch_in;
	RegWriteE = RegWriteE_in;
	MemWriteE = MemWriteE_in;
	MemtoRegM = MemtoRegM_in;
	WriteRegM = WriteRegM_in;
	PCSrcD = PCSrcD_in;
	WriteRegM2 = WriteRegM2_in;
	WriteRegM3 = WriteRegM3_in;
	RegWriteM = RegWriteM_in;
	RegWriteM2 = RegWriteM2_in;
	RegWriteM3 = RegWriteM3_in;
	WriteRegE = WriteRegE_in;
}
void HazardUnit::updateData()
{
	lwstall = ((RsD == RtE) || (RtD == RtE)) && MemtoRegE;
	branchstall =
		((branch) && (RegWriteE) && ((WriteRegE == RsD) ||(WriteRegE == RtD)))//if the data is still not out of the alu
		||
		((branch) && (MemtoRegM) && ((WriteRegM == RsD) ||(WriteRegM == RtD)));//if the data is still not out of the memory
	if (PCSrcD == 1)
		FlushE = 1;
	else
		FlushE = 0;
	StallF = lwstall || branchstall;
	StallD = lwstall || branchstall;
	if ((RsE != 0 && (RsE == WriteRegM)) && RegWriteM)
		ForwardAE = 2;
	else if ((RsE != 0 && (RsE == WriteRegW)) && RegWriteW)
	    ForwardAE = 1;
	else if ((RsE != 0 && (RsE == WriteRegM2)) && RegWriteM2)
		ForwardAE = 3;
	else if ((RsE != 0 && (RsE == WriteRegM3) && RegWriteM3))
		ForwardAE = 4;
	else
		ForwardAE = 0;
	if ((RtE != 0 && RtE == WriteRegM) && RegWriteM)
		ForwardBE = 2;
	else if ((RtE != 0 && RtE == WriteRegW) && RegWriteW)
		ForwardBE = 1;
	else if ((RtE != 0 && RtE == WriteRegM2) && RegWriteM2)
		ForwardBE = 3;
	else if ((RtE != 0 && RtE == WriteRegM3) && RegWriteM3)
		ForwardBE = 4;
	else
		ForwardBE = 0;
	if ((RsD != 0 && (RsD == WriteRegM)) && RegWriteM)
		ForwardAD = 2;
	else if ((RsD != 0 && (RsD == WriteRegW)) && RegWriteW)
		ForwardAD = 1;
	else if ((RsD != 0 && (RsD == WriteRegM2)) && RegWriteM2)
		ForwardAD = 3;
	else if ((RsD != 0 && (RsD == WriteRegM3) && RegWriteM3))
		ForwardAD = 4;
	else
		ForwardAD = 0;
	if ((RtD != 0 && RtD == WriteRegM) && RegWriteM)
		ForwardBD = 2;

	else if ((RtD != 0 && RtD == WriteRegM2) && RegWriteM2)
		ForwardBD = 3;
	else if ((RtD != 0 && (RtD == WriteRegW)) && RegWriteW)
		ForwardBD = 1;
	else if ((RtD != 0 && RtD == WriteRegM3) && RegWriteM3)
		ForwardBD = 4;
	else
		ForwardBD = 0;
	//WriteDataE = (ForwardBE == 0) ? buf3.RD2E : (ForwardBE == 1) ? ResultW : buf4.ALUOutM;
}
#endif