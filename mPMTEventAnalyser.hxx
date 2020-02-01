//////////////////////////////////////////////////////////
// Author: Ciro Riccio
// Date: Nov 8, 2019
//////////////////////////////////////////////////////////
#ifndef __mPMTEventAnalyser_hh__
#define __mPMTEventAnalyser_hh__

#include <iostream>
#include <vector>
#include "mPMTEventManager.hxx"

using namespace std;

class mPMTEventAnalyser
{
public:
  mPMTEventAnalyser();
  ~mPMTEventAnalyser();
  mPMTEventManager* GetEvent(int evnum);
  void              AddEvent(mPMTEventManager &event);
  int               GetN();
  void              ClearEvents();

private:
  vector<mPMTEventManager> m_events;

};

#endif