#ifndef __YJJECH_HH_
#define __YJJECH_HH_

#include <memory>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include "TTree.h"
#include "TLorentzVector.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "DataFormats/Common/interface/Handle.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "DelPanj/TreeMaker/interface/utils.h"
#include "DelPanj/TreeMaker/interface/muSelector.h"
#include "DelPanj/TreeMaker/interface/eSelector.h"
#include "pandolf/BTagSFUtil/src/BTagSFUtil.h" 

#include "DataFormats/PatCandidates/interface/Jet.h"

#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h"  // ADDED
#include "TMVA/Reader.h"

//Yun-Ju for jec
#include "DataFormats/PatCandidates/interface/JetCorrFactors.h"
#include "CondFormats/JetMETObjects/interface/JetResolution.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "PFJetSmearFactory.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"


using namespace std;
using namespace edm;
using namespace reco;


class YJJECHiggTree{


 public:
  explicit YJJECHiggTree(std::string name, TTree* tree, const edm::ParameterSet& cfg);
  virtual ~YJJECHiggTree();
  virtual void Fill(const edm::Event& iEvent, edm::EventSetup const& iSetup);
  void SetBranches();
  void Clear();
  int _nEvents;  ///< Number of processed events.
  int _nFailTrig;
  int _nCandidates;  ///< Number of H->ZZ->2l2j candidates found.
  int _nRejected; ///<Number of events rejected because any candidate all criteria (but mJJ and mLL)
  int _nPassed;//Number of events passed
  int _nJetEvtSave; 
  int _nSB;
  int _nPFinalHLTDoubleMu;
  int _nPFinalHLTDoubleEle;
  int _nPFinalHLTMu17TkMu8; 
  int _nFailMet;

  int SetJEC_C;

private:
  YJJECHiggTree();

  BTagSFUtil* btsfutiljp;
  void AddBranch(double* x, std::string name);
  void AddBranch(int* x, std::string name);
  void AddBranch(std::vector<double>*, std::string name);
  void AddBranch(std::vector<int>*, std::string name);
  void AddBranchArray(const int arraySize, double* x, std::string name);

  bool passLooseJetID(const pat::Jet* recJet);

  edm::InputTag hzzeejj_;
  edm::InputTag hzzmmjj_;
  edm::InputTag eleRhoIsoInputTag_;
  edm::InputTag muoRhoIsoInputTag_;
  eSelector e2012ID_;
  muSelector mu2012ID_;

  TTree* tree_;
  

  int EvtType_;
  int EvtLepType_;
  int n_pileup_;
  int n_pileup_true_;
  double genHmass_;

  int  HLTDoubleMu_;
  int HLTDoubleEle_;
  int HLTMu17TkMu8_;

  int theOneHNBtag_; 
  
  double theOnehiggsPt_;
  double theOnehiggsEta_;
  double theOnehiggsPhi_;
  double theOnehiggsM_;
  double theOnehiggsMRefit_;

  double theOneHzllPt_;
  double theOneHzllEta_;
  double theOneHzllPhi_;
  double theOneHzllM_;
  double theOneHzlldR_; // deltaR between two leptons

  double theOneHzjjPt_;
  double theOneHzjjEta_;
  double theOneHzjjPhi_;
  double theOneHzjjM_;
  double theOneHzjjMRefit_;
  double theOneHzjjdR_; // deltaR between two jets   


  //save hjet and hlep
  std::vector<double> HJetE_;
  std::vector<double> HJetPt_;
  std::vector<double> HJetEta_;
  std::vector<double> HJetPhi_;

  std::vector<double> HLeptonsE_;
  std::vector<double> HLeptonsPt_;
  std::vector<double> HLeptonsEta_;
  std::vector<double> HLeptonsPhi_;

  //save all jets 
  std::vector<double> JetPt_;
  std::vector<double> JetEta_;
  std::vector<double> JetPhi_;
  std::vector<double> JetEn_;
  std::vector<int> JetFromtheOneH_;
  std::vector<double> JetPUMVA_;

 

  // input for the angular likelihood 
  double heliLD_;
  double costhetaNT1_;
  double costhetaNT2_;
  double phiNT_;
  double phiNT1_;
  double costhetastarNT_;


  int OnlyMuon;


   virtual void endJob (void);


/// JES Stuff //////////////////////////////////
    ///////////////////////// JES Info /////////////////////////
    //JetCorrectorParameters totp;
    JetCorrectionUncertainty *uncGetter; 
    // I'm going to store modified copies here
    pat::Jet j1JEC,j2JEC;
    //const edm::EventSetup &iSetup;
    void ScaleJet(pat::Jet & dest, const pat::Jet * j,const int SetJEC);
  
};

#endif

