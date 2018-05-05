#ifndef BUFFER_1_H
#define BUFFER_1_H
class buffer_1
{
public:
	buffer_1();
	~buffer_1();
	unsigned int PC_in, PC_out;
	void inputData(unsigned int);
	void updateData();
	int inst_num = -1, inst_num_in = -1;
	unsigned int pc;
	void setInstNum(int num, unsigned int p)
	{
		inst_num_in = num;
		pc = p;
	}
private:

};

buffer_1::buffer_1()
{
	PC_in = 0;
	PC_out = 0;
}

buffer_1::~buffer_1()
{
}
void buffer_1::inputData(unsigned int PC)
{
	PC_in = PC;
}
void buffer_1::updateData()
{
	PC_out = PC_in;
	inst_num = inst_num_in;
}
#endif