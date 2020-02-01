//////////////////////////////////////////////////////////
//
//  A container with subset of necessary event 
//  information for mPMT analysis
//
//
//  Created:  Wed Jan 15 2020    
//  Modified: 
//
/////////////////////////////////////////////////////////

#ifndef __mPMTEventManager_hh__
#define __mPMTEventManager_hh__

#include <TROOT.h>
#include <iostream>

using namespace std;

class mPMTEventManager{

 public:
 mPMTEventManager(Long64_t evid){//Unique event id
  m_evid              = evid;
  m_channelID         = -1; 
  m_unixtime          = -1;
  m_time28bit         = -1;
  m_time5bit          = -1;
  m_width             = -1;
  m_widthhr           = -1;
  m_energy            = -999.0;
}
  ~mPMTEventManager(){;}

  //Set/Get methods
  Long64_t GetEvId(){ return m_evid; }

  void SetChannelID(int val){ m_channelID = val; }
  int GetChannelID(){ return m_channelID; }

  void SetEnergy(int val){ m_energy = val; }
  double GetEnergy(){ return m_energy; }  

  void SetUnixTime(int val){ m_unixtime = val; }
  ULong64_t GetUnixTime(){ return m_unixtime; }  

  void SetTime28Bit(int val){ m_time28bit = val; }
  ULong64_t GetTime28Bit(){ return m_time28bit; } 

  void SetTime5Bit(int val){ m_time5bit = val; }
  ULong64_t GetTime5Bit(){ return m_time5bit; } 

  void SetWidth(int val){ m_width = val; }
  ULong64_t GetWidth(){ return m_width; } 

  void SetWidthHR(int val){ m_widthhr = val; }
  ULong64_t GetWidthHR(){ return m_widthhr; } 

  ULong64_t GetTOT(){ return m_width*5000 - m_widthhr*227; } 
  ULong64_t GetTime(){ return m_time28bit*5000 + m_time5bit*227; } 
     
  void Print(){

    cout<<"  Event ID             "<<  m_evid         <<endl
        <<"  Channel ID           "<<  GetChannelID() <<endl
        <<"  Unixtime             "<<  GetUnixTime()  <<endl
        <<"  Time 28Bit           "<<  GetTime28Bit() <<endl
        <<"  Time 5Bit            "<<  GetTime5Bit()  <<endl
        <<"  Width                "<<  GetWidth()     <<endl
        <<"  Width HR             "<<  GetWidthHR()   <<endl
        <<"  Time over Threshold  "<<  GetTOT()       <<endl
        <<"  Time 28Bit+Time 5Bit "<<  GetTime()      <<endl;
  }
 
private: 
  Long64_t m_evid;       //unique event id
  int m_channelID;       
  ULong64_t m_unixtime; 
  ULong64_t m_time28bit; 
  ULong64_t m_time5bit;  
  ULong64_t m_width; 
  ULong64_t m_widthhr;  
  double m_energy;  

};

#endif
