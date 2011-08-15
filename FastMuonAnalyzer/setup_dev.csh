#!/bin/tcsh

#pushd $CMSSW_BASE/src
# New improvements for ECAL, HCAL and Muon Brem
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/Calorimetry/src/CalorimetryManager.cc
cvs co -r HEAD  UserCode/MuonBremDev/FastSimulation/Calorimetry/interface/CalorimetryManager.h

cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MaterialEffects/src/MaterialEffects.cc
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MaterialEffects/src/MuonBremsstrahlungSimulator.cc
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MaterialEffects/interface/MaterialEffects.h
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MaterialEffects/interface/MuonBremsstrahlungSimulator.h
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MaterialEffects/python/MaterialEffects_cfi.py
# new improvements of Muon chambers
cvs co -r HEAD UserCode/MuonBremDev/FastSimulation/MuonSimHitProducer/src/MuonSimHitProducer.cc 
cvs co -r HEAD  UserCode/MuonBremDev/FastSimulation/MuonSimHitProducer/interface/MuonSimHitProducer.h 
#cvs co -r  V00-02-00 UserCode/MuonSim_June01/FastSimulation/MaterialEffects/python/MaterialEffects_cfi.py


pushd $CMSSW_BASE/src

#Testing in CMSSW_4_4_0_pre8
cvs co  Configuration/Generator  
cvs co  FastSimulation/Calorimetry                       
cvs co  FastSimulation/Configuration                     
cvs co  FastSimulation/MaterialEffects                   
cvs co  FastSimulation/MuonSimHitProducer                
cvs co  FastSimulation/TrajectoryManager  
#Calorimetry improvements
cp UserCode/MuonBremDev/FastSimulation/Calorimetry/src/CalorimetryManager.cc FastSimulation/Calorimetry/src
cp UserCode/MuonBremDev/FastSimulation/Calorimetry/interface/CalorimetryManager.h FastSimulation/Calorimetry/interface

cp UserCode/MuonBremDev/FastSimulation/MaterialEffects/src/MaterialEffects.cc FastSimulation/MaterialEffects/src
cp UserCode/MuonBremDev/FastSimulation/MaterialEffects/src/MuonBremsstrahlungSimulator.cc FastSimulation/MaterialEffects/src
cp UserCode/MuonBremDev/FastSimulation/MaterialEffects/interface/MaterialEffects.h FastSimulation/MaterialEffects/interface
cp UserCode/MuonBremDev/FastSimulation/MaterialEffects/interface/MuonBremsstrahlungSimulator.h FastSimulation/MaterialEffects/interface
cp UserCode/MuonBremDev/FastSimulation/MaterialEffects/python/MaterialEffects_cfi.py FastSimulation/MaterialEffects/python

##Muon Chambers improvements
cp UserCode/MuonBremDev/FastSimulation/MuonSimHitProducer/src/MuonSimHitProducer.cc FastSimulation/MuonSimHitProducer/src
cp UserCode/MuonBremDev/FastSimulation/MuonSimHitProducer/interface/MuonSimHitProducer.h FastSimulation/MuonSimHitProducer/interface
#cp UserCode/MuonSim_June01/FastSimulation/MaterialEffects/python/MaterialEffects_cfi.py FastSimulation/MaterialEffects/python

#Analysis code for Tracker
cvs co -r V00-00-04 -d FastMuonBremAnalyzers/FastMuonAnalyzer  UserCode/FastMuonBremAnalyzers/FastMuonAnalyzer
cvs co -r V00-00-01 -d FastMuonBremAnalyzers/Photon_FastSim_Analyzer  UserCode/FastMuonBremAnalyzers/Photon_FastSim_Analyzer
# G4 Observer
#cvs co -r V00-00-01  -d  FastMuonBremAnalyzers/ElectronBremAnalysis UserCode/FastMuonBremAnalyzers/ElectronBremAnalysis
#scram build -c

#CPU timing tests
cvs co -d FastMuonBremAnalyzers/timing_cpu_test UserCode/FastMuonBremAnalyzers/timing_cpu_test/timing.cpp 





scramv1 b -j 4
popd
