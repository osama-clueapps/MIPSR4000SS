#include<iostream>
#include<string>
#include"instCU.h"
#include"buffer_1.h"
#include"buffer_2.h"
#include"buffer_3.h"
#include"buffer_4.h"
#include"buffer_5.h"
#include"buffer_6.h"
#include"buffer_7.h"
#include"dmem.h"
#include"imem.h"
#include"RegFile.h"
#include "HazardUnit.h"
#include <fstream>
#include"assembly.h"
#include "code.h"
#include "BTB.h"
#include"complete.h"
#include"Dispatch.h"
#include"HazardUnitS.h"
using namespace std;
void datapath(assembly f);
void ALU(int a, int b, int ALU_CT, int &result, int &z);
void PC(unsigned int pcin, unsigned int &pcout, bool en);
void print1();
void print2();
void print3();
void print4();
void print5();
void print5_1();
void print6();
void print7();
void IF();
void EXStage();
void RFStage();
void muxforALUs();
void FlushUnit();
void intersectingStalls();
void handlePC();
unsigned int inst1 = 0, inst2 = 0;
int clk = 0, rst;
//buffers
buffer_1 buf1;
buffer_2 buf2a, buf2b;
buffer_3 buf3;
buffer_4 buf4;
buffer_5 buf5;
buffer_6 buf6;
buffer_7 buf7;
//instdec and CU
instCU cu;
//PC
unsigned int pcin = 0, pcout = -4;
unsigned int pcofbranch = -1;
//IM
imem im;
//RegFile
RegFile rf;
unsigned int comp = 0, PCSrcD = 0;
int PCBranchD = 0, PCJump;
int c1 = 0, c2 = 0, rd1 = 0, rd2 = 0;
//ALU
int SrcAE = 0, SrcBE = 0, aluoutE, z, WriteDataE, WriteRegE;
//BTB
BTB b;
//Dmem
dmem dm;
int ResultW = 0;
unsigned int ReadDataM2 = 0;
int Pbfailedt = 0, Pbfailednt = 0;
unsigned int bpc;
vector <Code> code;
ofstream target;
assembly a;
HazardUnit h;
Dispatch d;
HazardUnitS hs;

int stall1 = 0, stall2 = 0;

instCU cu1, cu2;
buffer_3 buf3a, buf3b;
int rd1a, rd2a, rd1b, rd2b;
HazardUnit h1, h2;
int c1a, c1b, c2a, c2b;
unsigned int inst1D, inst2D;
complete c;
unsigned int pcout1 = -8, pcin1 = -8, pcout2 = -4, pcin2 = -4;
buffer_1 buf1a, buf1b;
buffer_7 buf7a, buf7b, buf7c;
int comp1, comp2;
int PCSrcDA, PCSrcDB, PCBranchDA, PCBranchDB;
int Pbfailednt1, Pbfailedt1, Pbfailednt2, Pbfailedt2, pcofbranch1, pcofbranch2, PCJumpA, PCJumpB;
int SrcAE1, SrcBE1, SrcAE2, SrcBE2;
int WriteDataE1, WriteDataE2, WriteRegE1, WriteRegE2, aluoutE1, aluoutE2;

void dp()
{
	if (clk > 2)
	{
		d.inputData(buf2a.instD, buf2a.inst_num, buf2b.instD, buf2b.inst_num);
		d.outputData(2);
	}
	cu1.setinst(d.inst1);
	cu2.setinst(d.inst2);
	WriteRegE1 = (buf3a.RegDstE == 0) ? buf3a.RtE : buf3a.RdE;
	WriteRegE2 = (buf3b.RegDstE == 0) ? buf3b.RtE : buf3b.RdE;
	h1.inputData(cu1.RsD, buf3a.RsE, cu1.RtD, buf3a.RtE, buf3a.MemtoRegE, cu1.branch,
		buf3a.RegWriteE, buf3a.MemtoRegE, buf4.MemtoRegM, buf4.WriteRegM,
		PCSrcDA, buf5.WriteRegM2, buf6.WriteRegM3, buf4.RegWriteM, 
		buf5.RegWriteM2, buf6.RegWriteM3, buf3a.RegDstE, buf3a.RdE,
		buf7.WriteRegW, buf7.RegWriteW,WriteRegE1);
	h2.inputData(cu2.RsD, buf3.RsE, cu2.RtD, buf3b.RtE, buf3b.MemtoRegE, cu2.branch,
		buf3b.RegWriteE, buf3b.MemtoRegE, buf4.MemtoRegM, buf4.WriteRegM,
		PCSrcDB, buf5.WriteRegM2, buf6.WriteRegM3, buf4.RegWriteM,
		buf5.RegWriteM2, buf6.RegWriteM3, buf3b.RegDstE, buf3b.RdE,
		buf7.WriteRegW, buf7.RegWriteW, WriteRegE2);
	h1.updateData();
	h2.updateData();
	handlePC();
	//IF
	IF();
	//IF2
	im.IF2(buf1a.PC_out, inst1);
	im.IF2(buf1b.PC_out, inst2);
	if (!h1.StallD && !stall1)
		buf2a.inputData(inst1, pcout1 + 4);
	if (!h2.StallD && !stall2)
		buf2b.inputData(inst2, pcout2 + 4);
	if (clk > 1)
	{
		buf2a.setInstNum(buf1a.inst_num, buf1a.pc);
		buf2b.setInstNum(buf1b.inst_num, buf1b.pc);
	}
	
	//Dispatch
	
	//
	c.insert(buf7a.inst_num, buf7a.ReadDataW, buf7a.RegWriteW, buf7a.MemtoRegW, buf7a.ALUOutW, buf7a.WriteRegW);
	c.insert(buf7b.inst_num, buf7b.ReadDataW, buf7b.RegWriteW, buf7b.MemtoRegW, buf7b.ALUOutW, buf7b.WriteRegW);
	c.insert(buf7c.inst_num, buf7c.ReadDataW, buf7c.RegWriteW, buf7c.MemtoRegW, buf7c.ALUOutW, buf7c.WriteRegW);
	EXStage();
	while (c.getnext())
	{
		unsigned int WriteReg, ReadData, MemtoReg, RegWrite, Aluout;
		c.next(ReadData, RegWrite, MemtoReg, Aluout, WriteReg);
		ResultW = (MemtoReg == 1) ? ReadData: Aluout;
		if(RegWrite)
			rf.writeRegFile(WriteReg, ResultW);
	}
	RFStage();
	print2();
	
	
	//RF
	/*rf.readRegFile(cu.A1, cu.A2, rd1, rd2);
	buf3.inputData(cu.RegWrite, cu.MemtoReg, cu.MemWrite, cu.aluctrl, cu.alusrc, cu.RegDst, rd1, rd2, cu.RsD, cu.RtD, cu.RdE, cu.Iimm);
	switch (h.ForwardBD)
	{
	case 0: c2 = rd2;
		break;
	case 2: c2 = buf4.ALUOutM;
		break;
	case 3: c2 = buf5.ALUOutM2;
		break;
	case 4: c2 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h.ForwardAD)
	{
	case 0: c1 = rd1;
		break;
	case 2: c1 = buf4.ALUOutM;
		break;
	case 3: c1 = buf5.ALUOutM2;
		break;
	case 4: c1 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h.ForwardAE)
	{
	case 0: SrcAE = rd1;
		break;
	case 1: SrcAE = ResultW;
		break;
	case 2: SrcAE = buf4.ALUOutM;
		break;
	case 3: SrcAE = buf5.ALUOutM2;
		break;
	case 4: SrcAE = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h.ForwardBE)
	{
	case 0: WriteDataE = rd2;
		break;
	case 1: WriteDataE = ResultW;
		break;
	case 2: WriteDataE = buf4.ALUOutM;
		break;
	case 3: WriteDataE = buf5.ALUOutM2;
		break;
	case 4: WriteDataE = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	SrcBE = (buf3.ALUSrcE == 0) ? WriteDataE : buf3.SignImmE;
	comp = (c1 <= c2) ? 1 : 0;
	PCSrcD = (cu.jump << 1 || (cu.branch && comp));
	target << "PCBRANCH BEFORE " << dec << cu.Iimm << endl;
	PCBranchD = cu.Iimm * 4;
	//BTB
	if (cu.branch) {
		if (b.TakenorNot(pcofbranch) == 1 && PCSrcD == 0) {
			Pbfailednt = 1;
			Pbfailedt = 0;
		}
		else if (b.TakenorNot(pcofbranch) == 0 && PCSrcD == 1) {
			Pbfailedt = 1;
			Pbfailednt = 0;
		}
		else if (b.TakenorNot(pcofbranch) == PCSrcD) {
			Pbfailedt = 0;
			Pbfailednt = 0;
		}
		//pcout = pcofbranch + 4;
		target << "BRANCHING THINGS " << endl;

		target << "Pbfailednt: " << Pbfailednt << endl;
		target << "Pbfailedt: " << Pbfailedt << endl;
		b.update(pcofbranch, PCSrcD);

	}
	else {
		Pbfailedt = 0;
		Pbfailednt = 0;
	}
	PCJump = ((pcout >> 28) << 28) | (cu.Jimm << 2);
	print4();
	if (clk > 2)
		buf3.setInstNum(buf2a.inst_num - 1, buf2a.pc);
	target << "--------------------------------------------------" << endl << endl;
	//EX
	ALU(SrcAE, SrcBE, buf3.ALUControlE, aluoutE, z);
	buf4.inputData(buf3.RegWriteE, buf3.MemtoRegE, buf3.MemWriteE, aluoutE, WriteDataE, WriteRegE);*/
	print5();
	buf5.inputData(buf4.RegWriteM, buf4.MemtoRegM, buf4.MemWriteM, buf4.ALUOutM, buf4.WriteDataM, buf4.WriteRegM);
	target << "--------------------------------------------------" << endl << endl;
	//DF
	dm.DF1();
	print5_1();
	if (clk > 4)
		buf5.setInstNum(buf4.inst_num, buf4.pc);
	target << "--------------------------------------------------" << endl << endl;
	//DS
	dm.DF2(buf5.ALUOutM2, buf5.MemWriteM2, buf5.WriteDataM2, ReadDataM2);
	buf6.inputData(buf5.RegWriteM2, ReadDataM2, buf5.MemtoRegM2, buf5.ALUOutM2, buf5.WriteRegM2);
	print6();
	if (clk > 5)
		buf6.setInstNum(buf5.inst_num, buf5.pc);
	target << "--------------------------------------------------" << endl << endl;
	//TC
	dm.TC();
	buf7c.inputData(buf6.RegWriteM3, buf6.ReadDataM3, buf6.MemtoRegM3, buf6.ALUOutM3, buf6.WriteRegM3);
	print7();
	if (clk > 6)
		buf7c.setInstNum(buf6.inst_num, buf6.pc);
	target << "--------------------------------------------------" << endl << endl;
	//Buffers update
	FlushUnit();
	buf1a.updateData();
	buf1b.updateData();

	buf2a.updateData();
	buf2b.updateData();
	buf3a.updateData();
	buf3b.updateData();
	buf4.updateData();
	buf5.updateData();
	buf6.updateData();
	buf7a.updateData();
	buf7b.updateData();
	buf7c.updateData();
}
int main() {
	assembly file;
	if (file.readFile("test2.txt")) {
		cout << "processing... " << endl;
		datapath(file);
	}
	else
		cout << "error file" << endl;
	system("Pause");
	return 0;
}
void ALU(int a, int b, int ALU_CT, int &result, int &z) {

	switch (ALU_CT) {
	case 0:
		result = a & b;
		break;
	case 1:
		result = a - b;
		break;
	case 2:
		result = a + b;
		break;
	case 4:
		result = a ^ b;
		break;
	case 6:
		result = a - b;
		break;
	default:
		result = result;
	}
	if (result == 0) z = 1;
}
void PC(unsigned int pcin, unsigned int & pcout, bool en)
{
	if (en)
		pcout = pcin;
}
void datapath(assembly f)
{
	a = f;
	unsigned int inst = 0;
	for (int i = 0; i < f.inst.size(); i++)
	{
		im.WriteInst(i * 4, f.inst[i]);
		cout << f.inst[i] << endl;
	}
	target.open("target.txt");
	b.fillVector(f.inst);
	buf1b.PC_out = -4;
	buf1a.PC_out = -4;

	while (clk<19)
	{
		if (true) {

			clk++;
			dp();
		}
	}
	for (int i = 0; i < 16; i++)
	{
		cout << dec << i << "\t" <<dec<< rf.file[i]<<endl;
	}
}
void print1()
{
	target << "\t\t\t\t\t\t\t Cycle " << clk << endl;
	target << "IF stage: " << endl;
	target << "PCSrcD: " << PCSrcD << endl;
	target << "PC: " << pcout << endl;
	target << "PCBRANCHD !!!!!!!!  " << dec << PCBranchD << endl;
	target << "StallF: " << h.StallF << endl;
	target << "--------------------------------------------------" << endl << endl;
}
void print2()
{
	target << "WB stage: " << endl;
	target << "MemtoRegW: " << buf7.MemtoRegW << endl;
	target << "ALUOutW: " << buf7.ALUOutW << endl;
	target << "ReadDataW: " << buf7.ReadDataW << endl;
	target << "RegWriteW: " << buf7.RegWriteW << endl;
	target << "WriteRegW: " << buf7.WriteRegW << endl;
	target << "ResultW: " << ResultW << endl;
	target << "====================================================================" << endl << endl;
}
void print3()
{
	target << "IS stage: " << endl;
	target << "Instruction: " << hex << inst1 << endl;
	target << "StallD: " << h.StallD << endl;
	target << "PCSrc: " << dec << PCSrcD << endl;
	target << "--------------------------------------------------" << endl << endl;
}
void print4()
{
	target << "RF stage: " << endl;
	target << "ForwardAD " << h.ForwardAD << endl;
	target << "ForwardBD " << h.ForwardBD << endl;
	target << "FlushE: " << h.FlushE << endl;
	target << "InstructionD: " << hex << buf2a.instD << endl;
	target << "c1: " << c1 << endl;
	target << "c2: " << c2 << endl;
	target << "A1: " << cu.A1 << endl;
	target << "A2: " << cu.A2 << endl;
	target << "RD1: " << rd1 << endl;
	target << "RD2: " << rd2 << endl;
	target << "RegWriteD: " << cu.RegWrite << endl;
	target << "MemtoRegD: " << cu.MemtoReg << endl;
	target << "MemWriteD: " << cu.MemWrite << endl;
	target << "ALUControlD: " << cu.aluctrl << endl;
	target << "ALUSrc: " << cu.alusrc << endl;
	target << "RegDstD: " << cu.RegDst << endl;
	target << "JumpD: " << cu.jump << endl;
	target << "BranchD: " << cu.branch << endl;
	target << "RsD: " << cu.RsD << endl;
	target << "RtD: " << cu.RtD << endl;
	target << "RdE: " << cu.RdE << endl;
	target << "I-imm: " << cu.Iimm << endl;
	target << "J-imm: " << cu.Jimm << endl;
}
void print5()
{
	target << "EX stage: " << endl;
	target << "RegDstE: " << buf3.RegDstE << endl;
	target << "ALUSrcE: " << buf3.ALUSrcE << endl;
	target << "ALUControlE: " << buf3.ALUControlE << endl;
	target << "SrcAE: " << SrcAE << endl;
	target << "SrcBE: " << SrcBE << endl;
	target << "ALUResult: " << aluoutE << endl;
	target << "RegWriteE: " << buf3.RegWriteE << endl;
	target << "MemtoRegE: " << buf3.MemtoRegE << endl;
	target << "MemWriteE: " << buf3.MemWriteE << endl;
	target << "WriteDataE: " << WriteDataE << endl;
	target << "WriteRegE: " << WriteRegE << endl;
	target << "buf3.RsE: " << buf3.RsE << endl;
	target << "Buf4.WriteregM: " << buf4.WriteRegM << endl;
	target << "Buf5.WriteRegM2: " << buf5.WriteRegM2 << endl;
	target << "Buf6.WriteRegM3: " << buf6.WriteRegM3 << endl;
	target << "Buf7.WriteRegW: " << buf7.WriteRegW << endl;
	target << "FA: " << h.ForwardAE << endl;
	target << "FB: " << h.ForwardBE << endl;
}
void print5_1()
{
	target << "DF stage: " << endl;
	target << "RegWriteM: " << buf4.RegWriteM << endl;
	target << "MemtoRegM: " << buf4.MemtoRegM << endl;
	target << "MemWriteM: " << buf4.MemWriteM << endl;
	target << "ALUOutM: " << buf4.ALUOutM << endl;
	target << "WriteDataM: " << buf4.WriteDataM << endl;
	target << "WriteRegM: " << buf4.WriteRegM << endl;
}
void print6()
{
	target << "DS stage: " << endl;
	target << "RegWriteM2: " << buf5.RegWriteM2 << endl;
	target << "MemtoRegM2: " << buf5.MemtoRegM2 << endl;
	target << "MemWriteM2: " << buf5.MemWriteM2 << endl;
	target << "ALUOutM2: " << buf5.ALUOutM2 << endl;
	target << "WriteDataM2: " << buf5.WriteDataM2 << endl;
	target << "WriteRegM2: " << buf5.WriteRegM2 << endl;
	target << "ReadDataM2: " << ReadDataM2 << endl;
}
void print7()
{
	target << "TC stage: " << endl;
	target << "RegWriteM3: " << buf6.RegWriteM3 << endl;
	target << "MemtoRegM3: " << buf6.MemtoRegM3 << endl;
	target << "ALUOutM3: " << buf6.ALUOutM2 << endl;
	target << "WriteRegM3: " << buf6.WriteRegM3 << endl;
	target << "ReadDataM3: " << buf6.ReadDataM3 << endl;
}
void IF()
{
	PC(pcin1, pcout1, !h1.StallF&&!stall1&&!h2.StallF && !stall2);
	PC(pcin1+4, pcout2, !h1.StallF && !stall1 && !h2.StallF && !stall2);
	im.IF1();
	if (clk == 1)
		pcout1 = 0;
	buf1a.setInstNum(pcout1/4, pcout1);
	buf1a.inputData(pcout1);
	buf1b.setInstNum(pcout2/4, pcout2);
	buf1b.inputData(pcout2);
	print1();
}
void RFStage()
{
	rf.readRegFile(cu1.A1, cu1.A2, rd1a, rd2a);
	rf.readRegFile(cu2.A1, cu2.A2, rd1b, rd2b);
	if (clk>2)
	{
		//if (d.inst != 0)
			buf3a.setInstNum(d.instNum1, buf2a.pc);
		//if (d.inst2 != 0)
			buf3b.setInstNum(d.instNum2, buf2b.pc);
	}
	buf3a.inputData(cu1.RegWrite, cu1.MemtoReg, cu1.MemWrite, cu1.aluctrl, cu1.alusrc, cu1.RegDst, rd1a, rd2a, cu1.RsD, cu1.RtD, cu1.RdE, cu1.Iimm);
	buf3b.inputData(cu2.RegWrite, cu2.MemtoReg, cu2.MemWrite, cu2.aluctrl, cu2.alusrc, cu2.RegDst, rd1b, rd2b, cu2.RsD, cu2.RtD, cu2.RdE, cu2.Iimm);
	switch (h1.ForwardBD)
	{
	case 0: c1b = c.isComp(cu1.A2) ? c.find(cu1.A2) : rd2a;
		break;
	case 2: c1b = buf4.ALUOutM;
		break;
	case 3: c1b = buf5.ALUOutM2;
		break;
	case 4: c1b = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h1.ForwardAD)
	{
	case 0: c1a = c.isComp(cu1.A1) ? c.find(cu1.A1) : rd1a;
		break;
	case 2: c1a = buf4.ALUOutM;
		break;
	case 3: c1a = buf5.ALUOutM2;
		break;
	case 4: c1a = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h2.ForwardBD)
	{
	case 0: c2b = c.isComp(cu2.A2) ? c.find(cu2.A2) : rd2b;
		break;
	case 2: c2b = buf4.ALUOutM;
		break;
	case 3: c2b = buf5.ALUOutM2;
		break;
	case 4: c2b = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h2.ForwardAD)
	{
	case 0: c2a = c.isComp(cu2.A1) ? c.find(cu2.A1) : rd1b;
		break;
	case 2: c2a = buf4.ALUOutM;
		break;
	case 3: c2a = buf5.ALUOutM2;
		break;
	case 4: c2a = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	comp1 = (c1a <= c2a) ? 1 : 0;
	comp2 = (c1b <= c2b) ? 1 : 0;
	PCSrcDA = (cu1.jump << 1 || (cu1.branch && comp1));
	PCSrcDB = (cu2.jump << 1 || (cu2.branch && comp2));
	h1.updatePCSrc(PCSrcDA);
	h2.updatePCSrc(PCSrcDB);
	PCBranchDA = cu1.Iimm * 4;
	PCBranchDB = cu2.Iimm * 4;
	if (cu1.branch) {
		if (b.TakenorNot(pcofbranch1) == 1 && PCSrcDA == 0) {
			Pbfailednt1 = 1;
			Pbfailedt1 = 0;
		}
		else if (b.TakenorNot(pcofbranch1) == 0 && PCSrcDA == 1) {
			Pbfailedt1 = 1;
			Pbfailednt1 = 0;
		}
		else if (b.TakenorNot(pcofbranch1) == PCSrcDA) {
			Pbfailedt1 = 0;
			Pbfailednt1 = 0;
		}

		b.update(pcofbranch1, PCSrcDA);

	}
	else {
		Pbfailedt1 = 0;
		Pbfailednt1 = 0;
	}
	if (cu2.branch) {
		if (b.TakenorNot(pcofbranch2) == 1 && PCSrcDB == 0) {
			Pbfailednt2 = 1;
			Pbfailedt2 = 0;
		}
		else if (b.TakenorNot(pcofbranch2) == 0 && PCSrcDB == 1) {
			Pbfailedt2 = 1;
			Pbfailednt2 = 0;
		}
		else if (b.TakenorNot(pcofbranch2) == PCSrcDB) {
			Pbfailedt2 = 0;
			Pbfailednt2 = 0;
		}
		b.update(pcofbranch2, PCSrcDB);
	}
	else {
		Pbfailedt2 = 0;
		Pbfailednt2 = 0;
	}
	PCJumpA = ((pcout1 >> 28) << 28) | (cu1.Jimm << 2);
	PCJumpB = ((pcout2 >> 28) << 28) | (cu2.Jimm << 2);
}
void EXStage() {
	
	muxforALUs();
	ALU(SrcAE1, SrcBE1, buf3a.ALUControlE, aluoutE1, z);
	ALU(SrcAE2, SrcBE2, buf3b.ALUControlE, aluoutE2, z);

	if (buf3a.MemtoRegE || buf3a.MemWriteE)
	{
		buf7a.clr();
		buf4.inputData(buf3a.RegWriteE, buf3a.MemtoRegE, buf3a.MemWriteE, aluoutE1, WriteDataE1, WriteRegE1);
		if (clk > 3)
			buf4.setInstNum(buf3a.inst_num,buf3a.pc);
	}
	else
	{
		buf7a.inputData(buf3a.RegWriteE, 0, buf3a.MemtoRegE, aluoutE1, WriteRegE1);
		if (clk > 3)
			buf7a.setInstNum(buf3a.inst_num,buf3a.pc);
	}

	if (buf3b.MemtoRegE || buf3b.MemWriteE)
	{
		buf7b.clr();
		buf4.inputData(buf3b.RegWriteE, buf3b.MemtoRegE, buf3b.MemWriteE, aluoutE2, WriteDataE2, WriteRegE2);
		if (clk > 3)
			buf4.setInstNum(buf3b.inst_num, buf3b.pc);
	}
	else
	{
		buf7b.inputData(buf3b.RegWriteE, 0, buf3b.MemtoRegE, aluoutE2, WriteRegE2);
		if (clk > 3)
			buf7b.setInstNum(buf3b.inst_num, buf3b.pc);
	}
	if (!(buf3a.MemtoRegE || buf3a.MemWriteE) && !(buf3b.MemtoRegE || buf3b.MemWriteE))
	{
		buf4.clr();
	}

}
void muxforALUs()
{

	switch (h1.ForwardAE)
	{
	case 1:
	case 0:
		SrcAE1 = c.isComp(buf3a.RsE) ? c.find(buf3a.RsE) : buf3a.RD1E;
		break;
	case 2: SrcAE1 = buf4.ALUOutM;
		break;
	case 3: SrcAE1 = buf5.ALUOutM2;
		break;
	case 4: SrcAE1 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h1.ForwardBE)
	{
	case 0:
	case 1:
		WriteDataE1 = c.isComp(buf3a.RtE) ? c.find(buf3a.RtE) : buf3a.RD2E;
		break;
	case 2: WriteDataE1 = buf4.ALUOutM;
		break;
	case 3: WriteDataE1 = buf5.ALUOutM2;
		break;
	case 4: WriteDataE1 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h2.ForwardAE)
	{
	case 0:
	case 1:
		SrcAE2 = c.isComp(buf3b.RsE) ? c.find(buf3b.RsE) : buf3b.RD1E;
		break;
	case 2: SrcAE2 = buf4.ALUOutM;
		break;
	case 3: SrcAE2 = buf5.ALUOutM2;
		break;
	case 4: SrcAE2 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}
	switch (h2.ForwardBE)
	{
	case 0:
	case 1:
		WriteDataE2 = c.isComp(buf3b.RtE) ? c.find(buf3b.RtE) : buf3b.RD2E;
		break;
	case 2: WriteDataE2 = buf4.ALUOutM;
		break;
	case 3: WriteDataE2 = buf5.ALUOutM2;
		break;
	case 4: WriteDataE2 = (buf6.MemtoRegM3) ? buf6.ReadDataM3 : buf6.ALUOutM3;
		break;
	default:
		break;
	}

	WriteRegE1 = (buf3a.RegDstE == 0) ? buf3a.RtE : buf3a.RdE;
	WriteRegE2 = (buf3b.RegDstE == 0) ? buf3b.RtE : buf3b.RdE;
	SrcBE1 = (buf3a.ALUSrcE == 0) ? WriteDataE1 : buf3a.SignImmE;
	SrcBE2 = (buf3b.ALUSrcE == 0) ? WriteDataE2 : buf3b.SignImmE;
}
void FlushUnit()
{
	if (h1.FlushE)
	{
		buf3a.flushE();
		buf2a.clr();
		buf3b.flushE();
		buf2b.clr();
	}
	if (h2.FlushE)
	{
		buf3b.flushE();
		buf2b.clr();
		buf2a.clr();
	}
}
void intersectingStalls()
{
	stall1 = hs.isStall(cu1.RsD, buf3b.RtE, cu1.RtD, buf3b.MemtoRegE, cu1.branch, buf3b.RegWriteE, WriteRegE2);
	stall2 = hs.isStall(cu2.RsD, buf3a.RtE, cu2.RtD, buf3a.MemtoRegE, cu2.branch, buf3a.RegWriteE, WriteRegE2);
}
void handlePC()
{
	instCU cb;
	if (b.isBranch(pcout1)) {
		pcofbranch = pcout1;
		cb.setinst(a.inst[(pcout1) / 4]);
		PCBranchD = cb.Iimm * 4;
	}
	else if (b.isBranch(pcout2)) {
		pcofbranch = pcout2;
		cb.setinst(a.inst[(pcout2) / 4]);
		PCBranchD = cb.Iimm * 4;
	}
	if (Pbfailednt) {
		pcin1 = pcofbranch + 4;
		pcin2 = pcofbranch + 8;
	}
	if (Pbfailedt) {
		pcin1 = PCBranchD + pcofbranch + 4;
		pcin2 = pcin1 + 4;
	}
	else if (Pbfailedt == 0 && Pbfailednt == 0) {
		pcin1 = pcout1 + 8;
		pcin2 = pcout2 + 8;
	}
	if (cu1.jump) {
		pcin1 = PCJumpA;
		pcin2 = pcin1 + 4;
	}
	if (cu2.jump) {
		pcin1 = PCJumpB;
		pcin2 = pcin1 + 4;
	}
	if (cu1.jumpr) {
		pcin1 = rf.file[15];
		pcin2 = pcin1 + 4;
	}
	if (cu2.jumpr) {
		pcin1 = rf.file[15];
		pcin2 = pcin1 + 4;
	}
	if (b.TakenorNot(pcofbranch) == 1 && pcout / 4 < (a.inst.size()) && (a.inst[pcout / 4] >> 26 == 0x4))
	{
		pcin1 = PCBranchD + 4 + pcout;
		pcin2 = pcin1 + 4;
	}
}