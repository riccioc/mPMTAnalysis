#ifndef mPMTEventAnalyser_cxx
#define mPMTEventAnalyser_cxx

#include "mPMTEventAnalyser.hxx"

using namespace std;

mPMTEventAnalyser::mPMTEventAnalyser()
{}

mPMTEventAnalyser::~mPMTEventAnalyser()
{}

//=====  GetN -- get number of events stored
int mPMTEventAnalyser::GetN(){ return (int)m_events.size(); }

void mPMTEventAnalyser::AddEvent(mPMTEventManager &event){ m_events.push_back(event); }

void mPMTEventAnalyser::ClearEvents(){ m_events.clear(); }

//=====  GetEvent 
mPMTEventManager* mPMTEventAnalyser::GetEvent(int evnum){

  if(m_events.empty() || evnum>=this->GetN()){
    
    cerr<<"No events are found in "<<endl;
    return NULL;
  }

  return &m_events[evnum];

}

#endif
