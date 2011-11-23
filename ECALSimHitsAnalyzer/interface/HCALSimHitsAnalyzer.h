
#ifndef ExclusiveDijetsAnalysis_EventData_h
#define ExclusiveDijetsAnalysis_EventData_h

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "TH1.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
//
// class declaration
#include <map>

class ParameterSet;

 using namespace edm;
 using namespace std;

class HCALSimHitsAnalyzer : public edm::EDAnalyzer {
   public:
      explicit HCALSimHitsAnalyzer(const edm::ParameterSet&);
      ~HCALSimHitsAnalyzer();

     
   private:
      virtual void beginJob() ;
      virtual void analyze(const edm::Event&, const edm::EventSetup&);
      virtual void endJob() ;

      virtual void beginRun(edm::Run const&, edm::EventSetup const&);
      virtual void endRun(edm::Run const&, edm::EventSetup const&);
     
      InputTag    inputTagFamosSimHits_;
      InputTag    inputTagEcalRecHitsEB_;
      InputTag    inputTagEcalRecHitsEE_;
      bool   verbose_;
      double  EMDeposit;
      int run,id;
      int evt;
      int numberOfEvents;
      double inputmaxEnergy, inputBinEnergy;

      // TTree *theTree;
        TH1F * h_run, * h_events, * h_id,* h_EMDeposit;


      // map<std::string,TH1F*> histContainer_; 
  

      // ----------member data ---------------------------
};
#endif
