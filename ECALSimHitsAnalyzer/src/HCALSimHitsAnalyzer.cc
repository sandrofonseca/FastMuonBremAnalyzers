// -*- C++ -*-
//
// Package:    HCALSimHitsAnalyzer
// Class:      HCALSimHitsAnalyzer
// 
/**\class HCALSimHitsAnalyzer HCALSimHitsAnalyzer.cc FastMuonBremAnalyzers/HCALSimHitsAnalyzer/src/HCALSimHitsAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Sandro Fonseca De Souza,32 4-C14,+41227674949,
//         Created:  Thu Aug 18 11:16:07 CEST 2011
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FastMuonBremAnalyzers/ECALSimHitsAnalyzer/interface/HCALSimHitsAnalyzer.h" 

#include "SimDataFormats/CaloHit/interface/PCaloHit.h"
#include "SimDataFormats/CaloHit/interface/PCaloHitContainer.h"
#include "DataFormats/HcalDetId/interface/HcalDetId.h"
#include "DataFormats/HcalRecHit/interface/HcalCalibRecHit.h"
#include "DataFormats/HcalRecHit/interface/HcalRecHitCollections.h"

#include "FWCore/Framework/interface/ESHandle.h"
#include "Geometry/CommonDetUnit/interface/GeomDet.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "FastSimulation/Event/interface/FSimEvent.h"
#include "FastSimulation/Event/interface/FSimTrack.h"
#include "FastSimulation/Event/interface/FSimVertex.h"
#include "FastSimulation/Particle/interface/ParticleTable.h"

#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"

//
HCALSimHitsAnalyzer::HCALSimHitsAnalyzer(const edm::ParameterSet& iConfig)
{   

     inputTagFamosSimHits_ = iConfig.getParameter<InputTag>("famosSimHitsLabel");
     verbose_ = iConfig.getUntrackedParameter<bool>("verbose",false);
     inputmaxEnergy = iConfig.getUntrackedParameter<double>("hmaxEnergy");
     inputBinEnergy = iConfig.getUntrackedParameter<double>("hBimEnergy");
 
}

///////////////////////////////////////////////////////////////////////////////////////
HCALSimHitsAnalyzer::~HCALSimHitsAnalyzer()
{;}
///////////////////////////////////////////////////////////////////

// ------------ method called once each job just before starting event loop  ------------
void 
HCALSimHitsAnalyzer::beginJob()
{
  std::cout<<" Starting!!" << std::endl;

  edm::Service<TFileService> fs;  
  h_run    = fs->make<TH1F>( "run"  , "run", 100,  0., 1. );
  h_events   = fs->make<TH1F>( "events" , "events" , 100, 0. , 10000 );
  h_id   = fs->make<TH1F>( "id" , "id" , 100, 838939000., 838940000 );
  h_EMDeposit = fs->make<TH1F>( "EMDeposit" , "EMDeposit" , inputBinEnergy , 0., inputmaxEnergy );
}

// ------------ method called for each event  ------------
void
HCALSimHitsAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   run =  iEvent.id().run();
   evt =  iEvent.id().event();
   
 if(verbose_) std::cout << "Run: " << run << " Event: " << evt << std::endl;

   numberOfEvents++;
  if ( numberOfEvents%500 == 0 )
    cout << " --- Processed " << numberOfEvents << " events" << endl;

  h_run ->Fill(run);
  h_events->Fill(evt);

  //  using namespace edm;

 typedef std::pair<double, unsigned> hitSimID;
 typedef std::list< std::pair<double, unsigned> >::iterator ITM;
 std::vector< std::list <hitSimID> > caloHitsHcalID(62000);
 std::vector<double> caloHitsHcalTotE(62000,0.0);

// Get the SimTrack collection from the event
 //  Handle<SimTrackContainer> simTracks;
//   event.getByLabel(theSimTrackLabel,simTracks);
//   SimTrackContainer::const_iterator simTrack;
//   nsimu =  simTracks->size();

//http://cmslxr.fnal.gov/lxr/source/Validation/HcalHits/src/HcalSimHitsValidation.cc#200

// //getting the PCAloHit
Handle<edm::PCaloHitContainer> pcalohits;
iEvent.getByLabel(inputTagFamosSimHits_,pcalohits);

PCaloHitContainer::const_iterator it = pcalohits.product()->begin();
PCaloHitContainer::const_iterator itend  = pcalohits.product()->end();


//  //loop on the PCaloHit from g4SimHits Calorimetry
  for(;it!=itend;++it)
 {
 
 HcalDetId detid(it->id());
  if(verbose_){
         std::cout <<" "<< " " << detid.rawId()
                   << " Energy EM:  " << it->energy() 
                   << "ID:  " << detid.hashed_index() 
                   << " trackId=" 
                   << it->geantTrackId() 
	           << std::endl;
      }
           
           if(it->energy() > 0.0) {
             std::pair<double, unsigned> phitsimid
               = make_pair(it->energy(),it->geantTrackId());
             caloHitsHcalID[detid.hashed_index()].push_back(phitsimid);
             caloHitsHcalTotE[detid.hashed_index()]
             += it->energy();
             id =  detid.hashed_index();
             EMDeposit = caloHitsHcalTotE[detid.hashed_index()];
             
              h_id->Fill(id);
	      h_EMDeposit->Fill(EMDeposit);
             
              // if(verbose_) std::cout<<" Det ID:" << id << " EMDeposit: " <<  EMDeposit << std::endl;
            } 
	   
   }

}

 

// ------------ method called once each job just after ending the event loop  ------------
void 
HCALSimHitsAnalyzer::endJob() 
{ 

}

// ------------ method called when starting to processes a run  ------------
void 
HCALSimHitsAnalyzer::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
void 
HCALSimHitsAnalyzer::endRun(edm::Run const&, edm::EventSetup const&)
{

}



//define this as a plug-in
DEFINE_FWK_MODULE(HCALSimHitsAnalyzer);
