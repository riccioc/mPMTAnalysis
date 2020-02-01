//////////////////////////////////////////////////////////
// Author: Ciro Riccio
// Date: Nov 8, 2019
//////////////////////////////////////////////////////////
#ifndef mPMTTreeReader_cxx
#define mPMTTreeReader_cxx

#include "mPMTTreeReader.hxx"
#include <TH1D.h>
#include <TH2D.h>
#include <TMath.h>

mPMTTreeReader::mPMTTreeReader(TString fname)
{
  if(fname.IsNull()){ 
    cerr << "Specify the input file name!" <<endl;
    exit(1);
  }
  infile = new TFile(fname.Data(),"OPEN");
  if (infile->IsZombie()) {
    // if we cannot open the file, print an error message and return immediatly
    cerr << "File not open!" <<endl;
    return;
  }
  infile->GetObject("Dome01_events",tree);

  Init(tree);
}

mPMTTreeReader::~mPMTTreeReader()
{
   if (!tree) return;
   delete tree->GetCurrentFile();
}

Int_t mPMTTreeReader::GetEntry(Long64_t entry)
{
   // Read contents of entry.
   if (!tree) return 0;
   return tree->GetEntry(entry);
}

Long64_t mPMTTreeReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!tree) return -5;
   Long64_t centry = tree->LoadTree(entry);
   if (centry < 0) return centry;
   if (tree->GetTreeNumber() != fCurrent) {
      fCurrent = tree->GetTreeNumber();
   }
   return centry;
}

void mPMTTreeReader::Init(TTree *tree)
{
   // Set branch addresses and branch pointers
   if (!tree) return;
   tree = tree;
   fCurrent = -1;
   tree->SetMakeClass(1);

   tree->SetBranchAddress("TS"  , &TS_nTS,     &b_TS  );
   tree->SetBranchAddress("CHAN", &CHAN_nCHAN, &b_CHAN);
   tree->SetBranchAddress("TIME", &TIME_nTIME, &b_TIME);
   tree->SetBranchAddress("TIHR", &TIHR_nTIHR, &b_TIHR);
   tree->SetBranchAddress("WIDT", &WIDT_nWIDT, &b_WIDT);
   tree->SetBranchAddress("WIHR", &WIHR_nWIHR, &b_WIHR);
   tree->SetBranchAddress("ENER", &ENER_nENER, &b_ENER);

}

void mPMTTreeReader::SetOutputFile(TString name){
  
  if(name.IsNull()){ 
    cerr << "Specify the output file name!" <<endl;
    exit(1);
  }
  outfile  = new TFile(name.Data(),"RECREATE");
  //outtree  = new TTree("mPMTEvents","mPMTEvents");
}

mPMTEventAnalyser mPMTTreeReader::GetPMTEvents(int channelID){

  Long64_t nentries = tree->GetEntriesFast();
  Long64_t nbytes = 0, nb = 0;
  
  mPMTEventAnalyser anaev;  
  //144167591/1000
  for (Long64_t jentry=0; jentry<nentries/1000;jentry++){

    nb = tree->GetEntry(jentry); nbytes += nb;

    //===== Create and fill event structure
    mPMTEventManager ev(jentry);
    ev.SetChannelID( CHAN_CHAN[0]  );
    ev.SetEnergy(    ENER_ENER[0]  );
    ev.SetUnixTime(  TS_TS[0]      );
    ev.SetTime28Bit( TIME_TIME[0]  );
    ev.SetTime5Bit(  TIHR_TIHR[0]  );
    ev.SetWidth(     WIDT_WIDT[0]  );
    ev.SetWidthHR(   WIHR_WIHR[0]  );
    if (CHAN_CHAN[0]==channelID){ 
      anaev.AddEvent(ev);
    }
  }   
  return anaev;
}

#endif

