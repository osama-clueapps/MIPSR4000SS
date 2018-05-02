#ifndef BUFFER_4_H
#define BUFFER_4_H
class buffer_4
{
public:
	buffer_4();
	~buffer_4();
	unsigned int RegWriteE, MemtoRegE, MemWriteE;
	unsigned int RegWriteM, MemtoRegM, MemWriteM;
	unsigned int ALUOutE, WriteDataE, WriteRegE;
	unsigned int ALUOutM, WriteDataM, WriteRegM;
	void inputData(unsigned int RegWriteE, unsigned int MemtoRegE, unsigned int MemWriteE
		, unsigned int ALUOutE, unsigned int WriteDataE, unsigned int WriteRegE);
	void updateData();
	int inst_num = 0;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num = num;
		pc = p;
	}
private:

};

buffer_4::buffer_4()
{
	RegWriteM = 0;
	MemtoRegM = 0;
	MemWriteM = 0;
	ALUOutM = 0;
	WriteDataM = 0;
	WriteRegM = 0;
}

buffer_4::~buffer_4()
{
}
void buffer_4::inputData(unsigned int RegWriteE_in, unsigned int MemtoRegE_in, unsigned int MemWriteE_in
	, unsigned int ALUOutE_in, unsigned int WriteDataE_in, unsigned int WriteRegE_in)
{
	RegWriteE = RegWriteE_in;
	MemtoRegE = MemtoRegE_in;
	MemWriteE = MemWriteE_in;
	ALUOutE = ALUOutE_in;
	WriteDataE = WriteDataE_in;
	WriteRegE = WriteRegE_in;
}
void buffer_4::updateData()
{
	RegWriteM = RegWriteE;
	MemtoRegM = MemtoRegE;
	MemWriteM = MemWriteE;
	ALUOutM = ALUOutE;
	WriteDataM = WriteDataE;
	WriteRegM = WriteRegE;
}
#endif