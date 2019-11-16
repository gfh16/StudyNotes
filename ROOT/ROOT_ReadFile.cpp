//______________________________________________________________________________
////////////////////////////////////////////////////////////////////////////////
// Read data from a file
===========
1.ifstream
===========
ifstream infile("input.txt");
while(1)   // while(infile.good()){}
{
      infile>>var1>>var2>>var3>>var4>>var5>>var6;  //var1...可以是任何类型变量
      if (!infile.good() || infile.eof())  break;
      ...
      ...
}
infile.Close();

/*******************************************************************************
 * Notes: It is an infinite loop which will run till a break statement
 * is issued explicitly. 只要是非零的整数（正数、负数皆可），true, 所得结果都和 1 相同；
 * 0 则不执行循环
 *******************************************************************************/
//______________________________________________________________________________


//______________________________________________________________________________
=====================================================
2. void open(const char *filename, ios::openmode mode)
=====================================================
ifstream infile;
infile.open("input.txt",ios::app);

/*******************************************************************************
 * ios::app  追加模式。所有写入都追加到文件的末尾。
 *******************************************************************************/


================
3. TFile
================
TFile * filein = new TFile("test.root");
TFile filein("test.root")


===============
4. FILE
================
FILE * FileOut = fopen(Form("output/PulserCali_%s.dat", FileTag3.c_str()),"w");
fprintf(FileOut,"# itel  icsi \n");
fflush(FileOut); // 需要加上这句！！！ 否则由于缓存问题，内容不被写入
