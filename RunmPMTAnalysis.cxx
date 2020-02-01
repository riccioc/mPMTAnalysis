//////////////////////////////////////////////////////////
// Author: Ciro Riccio
// Date: Nov 8, 2019
//////////////////////////////////////////////////////////

#include "mPMTTreeReader.cxx"
#include <unistd.h>
#include <vector>
#include <TCanvas.h>

using namespace std;

int main(int argc, char *argv[])
{ 
  TString infilename;
  TString outfilename;

  int opt;
  while((opt=getopt(argc, argv, "i:o:h")) != -1){
    switch(opt){
      case 'i':
        infilename = optarg;
        break;
      case 'o': 
        outfilename = optarg;
        break;  
      case '?': 
        cerr << "USAGE: " 
             << argv[0] << " Mandatory options:" << endl
             << "-i : \tset input file" << endl
             << "-o : \tset output file name" << endl;
        exit(1);
        break;                  
      case 'h': //help 
        cerr << "USAGE: " 
             << argv[0] << " Mandatory options:" << endl
             << "-i : \tset input file" << endl
             << "-o : \tset output file name" << endl;
        return 0;
        break;       
      default:
        break;
    }
  }

  //=== Initialise mPMTTreeReader
  mPMTTreeReader* t = new mPMTTreeReader(infilename.Data());

  cout<< " Start file analysis" <<endl;
  
  vector<mPMTEventAnalyser> evana;

  for (int ipmt = 0; ipmt < 19; ++ipmt)
  {
    evana.push_back(t->GetPMTEvents(ipmt));
  }

  cout<< " Start coincidences " <<endl;

  TFile* outfile  = new TFile(outfilename.Data(),"RECREATE");

  TH2D* h = new TH2D("h","h",19,0,19,19,0,19);
  TH2D* h3 = new TH2D("h3","h3",19,0,19,1000,-100,100);
  
  int count=0;
  for (int ipmt = 0; ipmt < 19; ++ipmt)
  {
    for (int jpmt = 0; jpmt < 19; ++jpmt)
    {
      for (int iev = 0; iev < evana[ipmt].GetN(); ++iev)
      {
        mPMTEventManager* eventipmt = evana[ipmt].GetEvent(iev);
        for (int jev = 0; jev < evana[jpmt].GetN(); ++jev)
        {
          mPMTEventManager* eventjpmt = evana[jpmt].GetEvent(jev);
          if(ipmt!=jpmt && ipmt>jpmt){
            if(eventipmt->GetUnixTime() == eventjpmt->GetUnixTime()){
              if((eventipmt->GetTime() - eventjpmt->GetTime()<1e3) /*&& (eventipmt->GetTime() - eventjpmt->GetTime()!=0)*/){
                count++;
                h3->Fill(ipmt,eventipmt->GetTime() - eventjpmt->GetTime());
                
                h->Fill(ipmt,jpmt);
                cout << count << " " << ipmt << " GetEvId " << eventipmt->GetEvId() << "  " << jpmt << "  " << eventjpmt->GetEvId() << " Unixtime " << eventipmt->GetUnixTime() << " " << eventjpmt->GetUnixTime() << " Time " << eventipmt->GetTime() << "  " << eventjpmt->GetTime() <<endl;
              }
            }
          }
        }
      }
    }
  }
  cout << " count " << count <<endl;

  for (int i = 0; i < 19; ++i)
  {
    cout << " GetN " << i << "  " << evana[i].GetN() <<endl;
  } 

  outfile->cd();
  h->Write();
  h3->Write();
  //c->Print("test.pdf");
  cout<< " End analysis " <<endl;
  outfile->Close();

  return 0;  

}
