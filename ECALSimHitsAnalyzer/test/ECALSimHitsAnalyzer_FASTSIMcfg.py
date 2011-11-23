import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
     #'file:/storage2/sfonseca/CMSSW/FastSim_std/CMSSW_4_2_0/src/SingleMuPt1000_cfi_py_GEN_FASTSIM_STD_HLT_VALIDATION_sameRD.root'
      'file:SingleMuPt1000_cfi_py_GEN_FASTSIM_HLT_VALIDATION_CaloHits.root'
    # 'file:SingleElectronPt1000_cfi_py_GEN_FASTSIM_HLT_VALIDATION_CaloHits.root'
    
    #'/store/relval/CMSSW_4_4_0_pre6/RelValSingleMuPt1000/GEN-SIM-DIGI-RAW-HLTDEBUG/START44_V2-v1/0026/1EF81E3E-49BB-E011-A495-002354EF3BE3.root' ## FULL SIM
  #  '/store/relval/CMSSW_4_4_0_pre7/RelValSingleMuPt100/GEN-SIM-DIGI-RECO/START44_V2_FastSim-v1/0147/50FE3EA4-1EBE-E011-913B-00261894387E.root'

#'file:/storage2/sfonseca/CMSSW/FastSim_std/CMSSW_4_2_0/src/SingleMuPt1000_cfi_py_GEN_FASTSIM_STD_HLT_VALIDATION_STD.root'
  
    )
)
process.TFileService = cms.Service("TFileService",
                       fileName = cms.string('CaloFastSim.root'),
                       #fileName = cms.string('CaloFastSim_std.root'),
                       #fileName = cms.string('CaloElectronFastSim.root'),           
                       closeFileFast = cms.untracked.bool(True)
       )

process.demo = cms.EDAnalyzer('ECALSimHitsAnalyzer',

       famosSimHitsLabel = cms.InputTag("famosSimHits","EcalHitsEB"),
##     famosSimHitsLabel = cms.InputTag("g4SimHits","EcalHitsEB"),#done!!!
   ##  famosSimHitsLabel = cms.InputTag("g4SimHits","EcalHitsEE"),#done!!!                         
     verbose = cms.untracked.bool(False),
    # verbose = cms.untracked.bool(True),                        
     hBimEnergy = cms.untracked.double(1000.0),                    
     hmaxEnergy = cms.untracked.double(1000.0),
)


process.p = cms.Path(process.demo)
