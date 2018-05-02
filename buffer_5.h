#ifndef BUFFER_5_H
#define BUFFER_5_H
class buffer_5
{
public:
	buffer_5();
	~buffer_5();
	unsigned int RegWriteM, MemtoRegM, MemWriteM;
	unsigned int RegWriteM2, MemtoRegM2, MemWriteM2;
	unsigned int ALUOutM, WriteDataM, WriteRegM;
	unsigned int ALUOutM2, WriteDataM2, WriteRegM2;
	void inputData(unsigned int RegWriteM, unsigned int MemtoRegM, unsigned int MemWriteM
		, unsigned int ALUOutM, unsigned int WriteDataM, unsigned int WriteRegM);
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

buffer_5::buffer_5()
{
	RegWriteM2 = 0;
	MemtoRegM2 = 0;
	MemWriteM2 = 0;
	ALUOutM2 = 0;
	WriteDataM2 = 0;
	WriteRegM2 = 0;
}

buffer_5::~buffer_5()
{
}
void buffer_5::inputData(unsigned int RegWriteM_in, unsigned int MemtoRegM_in, unsigned int MemWriteM_in
	, unsigned int ALUOutM_in, unsigned int WriteDataM_in, unsigned int WriteRegM_in)
{
	RegWriteM = RegWriteM_in;
	MemtoRegM = MemtoRegM_in;
	MemWriteM = MemWriteM_in;
	ALUOutM = ALUOutM_in;
	WriteDataM = WriteDataM_in;
	WriteRegM = WriteRegM_in;
}
void buffer_5::updateData()
{
	RegWriteM2 = RegWriteM;
	MemtoRegM2 = MemtoRegM;
	MemWriteM2 = MemWriteM;
	ALUOutM2 = ALUOutM;
	WriteDataM2 = WriteDataM;
	WriteRegM2 = WriteRegM;
}
#endif