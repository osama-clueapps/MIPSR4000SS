#ifndef BUFFER_3_H
#define BUFFER_3_H
class buffer_3
{
public:
	buffer_3();
	~buffer_3();
	bool flushed;
	unsigned int RegWriteD, MemtoRegD, MemWriteD, ALUControlD, ALUSrcD, RegDstD;
	unsigned int RegWriteE, MemtoRegE, MemWriteE, ALUControlE, ALUSrcE, RegDstE;
	unsigned int RD1D, RD2D, RsD, RtD, RdD, SignImmD;
	unsigned int RD1E, RD2E, RsE, RtE, RdE, SignImmE;
	void inputData(unsigned int RegWriteD, unsigned int MemtoRegD, unsigned int MemWriteD
		, unsigned int ALUControlD, unsigned int ALUSrcD, unsigned int RegDstD
		, unsigned int RD1D, unsigned int RD2D, unsigned int RsD, unsigned int RtD
		, unsigned int RdD, unsigned int SignImmD);
	void updateData();
	int inst_num = 0;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num = num;
		pc = p;
	}
	void flushE();
private:

};

buffer_3::buffer_3()
{
	flushE();
	flushed = false;
}

buffer_3::~buffer_3()
{
}
void buffer_3::inputData(unsigned int RegWriteD_in, unsigned int MemtoRegD_in, unsigned int MemWriteD_in
	, unsigned int ALUControlD_in, unsigned int ALUSrcD_in, unsigned int RegDstD_in
	, unsigned int RD1D_in, unsigned int RD2D_in, unsigned int RsD_in, unsigned int RtD_in
	, unsigned int RdD_in, unsigned int SignImmD_in)
{
	flushed = false;
	RegWriteD = RegWriteD_in;
	MemtoRegD = MemtoRegD_in;
	MemWriteD = MemWriteD_in;
	ALUControlD = ALUControlD_in;
	ALUSrcD = ALUSrcD_in;
	RegDstD = RegDstD_in;
	RD1D = RD1D_in;
	RD2D = RD2D_in;
	RsD = RsD_in;
	RtD = RtD_in;
	RdD = RdD_in;
	SignImmD = SignImmD_in;
}
void buffer_3::updateData()
{
	RegWriteE = RegWriteD;
	MemtoRegE = MemtoRegD;
	MemWriteE = MemWriteD;
	ALUControlE = ALUControlD;
	ALUSrcE = ALUSrcD;
	RegDstE = RegDstD;
	RD1E = RD1D;
	RD2E = RD2D;
	RsE = RsD;
	RtE = RtD;
	RdE = RdD;
	SignImmE = SignImmD;
}
void buffer_3::flushE()
{
	RegWriteE = 0;
	MemtoRegE = 0;
	MemWriteE = 0;
	ALUControlE = 0;
	ALUSrcE = 0;
	RegDstE = 0;
	RD1E = 0;
	RD2E = 0;
	RsE = 0;
	RtE = 0;
	RdE = 0;
	SignImmE = 0;
	flushed = true;
}
#endif