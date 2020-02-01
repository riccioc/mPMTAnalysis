//////////////////////////////////////////////////////////
// Author: Ciro Riccio
// Date: Nov 8, 2019
//////////////////////////////////////////////////////////
#ifndef mPMTTreeReader_hxx
#define mPMTTreeReader_hxx

#include "mPMTEventManager.hxx"
#include "mPMTEventAnalyser.hxx"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <cstdlib>
#include <iostream>


using namespace std;
// Header file for the classes stored in the TTree if any.

class mPMTTreeReader {
public:
   Int_t           fCurrent; //!current Tree number in a TChain

   // Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           TS_nTS;
   UInt_t          TS_TS[1];       //[nTS]
   Int_t           CHAN_nCHAN;
   UInt_t          CHAN_CHAN[1];   //[nCHAN]
   Int_t           TIME_nTIME;
   UInt_t          TIME_TIME[1];   //Step of 5 ns 
   Int_t           TIHR_nTIHR;
   UInt_t          TIHR_TIHR[1];   //Step of 5/18 ps
   Int_t           WIDT_nWIDT;
   UInt_t          WIDT_WIDT[1];   //[nWIDT]
   Int_t           WIHR_nWIHR;
   UInt_t          WIHR_WIHR[1];   //[nWIHR]
   Int_t           ENER_nENER;
   UInt_t          ENER_ENER[1];   //[nENER]

   // List of branches
   TBranch        *b_TS;   //!
   TBranch        *b_CHAN;   //!
   TBranch        *b_TIME;   //!
   TBranch        *b_TIHR;   //!
   TBranch        *b_WIDT;   //!
   TBranch        *b_WIHR;   //!
   TBranch        *b_ENER;   //!

   mPMTTreeReader(TString fname);
   virtual ~mPMTTreeReader();
   virtual Int_t     GetEntry(Long64_t entry);
   virtual Long64_t  LoadTree(Long64_t entry);
   virtual void      Init(TTree *tree);
   virtual void      SetOutputFile(TString name);
   mPMTEventAnalyser GetPMTEvents(int channelID);

 private: 
   TTree          *tree;   
   TFile          *infile;
   TFile          *outfile;
   TTree          *outtree;

};

#endif


