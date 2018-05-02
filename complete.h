#include <map>
using namespace std;

class complete
{
	private:
		struct inst 
		{
			unsigned int ReadData, RegWrite, MemtoReg;
			unsigned int ALUOut, WriteReg;
		};
		inst i;  
	public:

		complete();
		void next(unsigned int &ReadDataWB, unsigned int &RegWriteWB, unsigned int &MemtoRegWB, unsigned int &ALUOutWB, unsigned int &WriteRegWB);
		bool getnext();
		void insert(int n, unsigned int ReadDataW, unsigned int RegWriteW, unsigned int MemtoRegW, unsigned int ALUOutW, unsigned int WriteRegW);
		map <int, inst> m;
		int n;
	


};

complete::complete()
{
	n=1;
	m.clear();
}
void complete:: insert(int instNum, unsigned int ReadDataW, unsigned int RegWriteW, unsigned int MemtoRegW, unsigned int ALUOutW, unsigned int WriteRegW)
{
	inst i;
	i.ReadData = ReadDataW;
	i.RegWrite = RegWriteW;
	i.MemtoReg = MemtoRegW;
	i.ALUOut = ALUOutW;
	i.WriteReg = WriteRegW;
	
	m[instNum] = i;
}
bool complete::getnext() 
{
	return(m.count(n));
}
void complete:: next(unsigned int &ReadDataWB, unsigned int &RegWriteWB, unsigned int &MemtoRegWB, unsigned int &ALUOutWB, unsigned int &WriteRegWB)
{
	inst i = m[n];
	ReadDataWB = i.ReadData;
	RegWriteWB = i.RegWrite;
	MemtoRegWB = i.MemtoReg;
	ALUOutWB = i.ALUOut;
	WriteRegWB = i.WriteReg;
	n++;
}
