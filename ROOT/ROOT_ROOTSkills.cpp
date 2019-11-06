////////////////////////////////////////////////////////////////////////////////
///  This file introducing how to show the percentages of a program
////////////////////////////////////////////////////////////////////////////////
======================
1. 显示程序完成进度
======================
if(jentry%100000==0)
{
  std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
  std::cout << "   [";
  int printindex=0;
  for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
  for(; printindex<100; printindex+=5) std::cout << " ";
  std::cout << "]\r"; std::cout.flush();
}


======================
2. 显示程序完成进度
======================
#include <time.h>
for(Long64_t jentry=0; jentry<nentries; jentry++)
{
  if(jentry%100000==0)
  {
    double time_elapsed = (double)(clock() - fStartTime)/CLOCKS_PER_SEC;
    std::cout << "  Percentage = " << std::fixed << std::setprecision(1) << std::setw(5) << (100*double(jentry)/nentries) << " %";
    std::cout << "   [";
    int printindex=0;
    for(; printindex<int(100*double(jentry)/nentries); printindex+=5) std::cout << "=";
    for(; printindex<100; printindex+=5) std::cout << " ";
    std::cout << "]   " << "elapsed time " << std::setprecision(1) <<
    (time_elapsed<60 ? time_elapsed : (time_elapsed<3600 ? time_elapsed/60 : time_elapsed/3600)) <<
    (time_elapsed<60 ? " s; " : (time_elapsed<3600 ? " m; " : " h; "));
    if(jentry>0) {
    double time_remaining = (time_elapsed/jentry)*(nentries-jentry);
    std::cout << " estimated remaining time " << std::setprecision(1) <<
    (time_remaining<60 ? time_remaining : (time_remaining<3600 ? time_remaining/60 : time_remaining/3600)) <<
    (time_remaining<60 ? " s      " : (time_remaining<3600 ? " m      " : " h      "));
  }
  std::cout << "\r";
  std::cout.flush();
}


========================
3. 写手动GUI界面
========================
c1->Connect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)",0,0,"SetPoints(Int_t,Int_t,Int_t,TObject*)");
while(Index!=1)
{
  usleep(100);
  gClient->HandleInput();
}
c1->Disconnect("ProcessedEvent(Int_t,Int_t,Int_t,TObject*)");
