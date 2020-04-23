#ifndef ANALYSIS_HEADFILE
#define ANALYSIS_HEADFILE

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1F.h"
#include <iostream>
#include <vector>
#include "makeHists.h"
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include "TH2D.h"

using namespace std;
class Analysis{
    public:
        TTree *fChain;

        UInt_t          Rrun;
        UInt_t          RluminosityBlock;
        ULong64_t       Revent;
        Float_t         RElectron_pt[10];
        Float_t         RElectron_dxy[10];
        Float_t         RElectron_eta[10];
        Float_t         RElectron_deltaEtaSC[10];
        Float_t         RElectron_phi[10];
        Float_t         RElectron_mass[10];
        Bool_t          RElectron_convVeto[10];
        UChar_t         RElectron_lostHits[10];
        Int_t           RElectron_tightCharge[10];
        Float_t         RElectron_dz[10];
        Float_t         RElectron_sip3d[10];
        Float_t         RElectron_miniPFRelIso_all[10];
        Float_t         RElectron_mvaFall17V1Iso[10];
        Float_t         RElectron_mvaFall17V1noIso[10];
        Float_t         RElectron_eCorr[10];
        Float_t         RElectron_hoe[10];
        Float_t         RElectron_sieie[10];
        Float_t         RElectron_jetPtRelv2[10];
        Float_t         RElectron_jetRelIso[10];
        Float_t         RElectron_pfRelIso03_all[10];
        

        
        UInt_t          RnElectron;
        UInt_t          RnMuon;
        UInt_t          RnJet;

        Int_t           RElectron_jetIdx[10];
        Int_t           RMuon_jetIdx[10];

        Float_t         RMuon_pt[10];
        Float_t         RMuon_eta[10];
        Float_t         RMuon_dxy[10];
        Float_t         RMuon_dz[10];
        Float_t         RMuon_sip3d[10];
        Float_t         RMuon_ptErr[10];
        Float_t         RMuon_phi[10];
        Float_t         RMuon_mass[10];
        Float_t         RMuon_jetPtRelv2[10];
        Float_t         RMuon_jetRelIso[10];
        Bool_t          RMuon_looseId[10];
        Bool_t          RMuon_mediumId[10];
        Float_t         RMuon_pfRelIso03_all[10];
        Float_t         RMuon_eCorr[10];
        Float_t         RMuon_miniPFRelIso_all[10];
//        Float_t         RMuon


        Float_t         RJet_pt[30];
        Float_t         RJet_eta[30];
        Float_t         RJet_phi[30];
        Float_t         RJet_mass[30];


        //*************Analysis func******************//
        Analysis(const char* ifileName, const char* TypeName);
        virtual ~Analysis();
        virtual void  Initial(const char* RootName, int RootNumber);
//        virtual void  Eventgetentry(int Evtnumber);
        virtual void  Loop(const char* TypeName, const char *yearName);
        virtual void  End(int RootNumber);
        virtual void  Finish(int RootNumber);
        virtual void  Output();

        //**************Electron Selection****************//
        virtual bool electronIDVBS(int elIdx, string id_name);
        virtual float electronMvacut(float A, float B, float C, float pt);
        virtual bool ifpassElectronMVAID(int iel, string id_name);
        virtual bool isTriggerSavenoIso_v1(int iel);
        virtual bool passElectronIso(double cut_miniiso, double cut_ptratio, double cut_ptrel, int iel);

        //*****************Muon Selection*****************//
        virtual bool muonIDVBS(unsigned int imu, string id_name);
        virtual bool passMuonIso(double cut_miniiso, double cut_ptratio, double cut_ptrel, int imu);

        //******************Isolation func**************//
        virtual float getPtRel(int id, int idx);
        virtual float getPtRatio(int id, int idx);
        virtual float computePtRel(const TLorentzVector& lepp4, const TLorentzVector& jetp4);
        virtual bool passMultiIso(int id, int idx, float cutMiniIso, float cutPtRatio, float cutPtRel);

        makeHists *myhists;
        bool ifsavehists;


};
#endif


#ifdef ANALYSIS_SOURCE
Analysis::Analysis(const char* ifileName, const char* TypeName){
    myhists = new makeHists();
    TString histoname = (TString)TypeName + "_results.root";
    myhists->bookHists(histoname);
    ifsavehists = true;
}


void Analysis::End(int RootNumber){
    if(!fChain){
        cout<<"Big Error!!! No File loaded!!!"<<endl;
        return;
    }
    delete fChain->GetCurrentFile();
}

Analysis::~Analysis(){
}

void Analysis::Finish(int RootNumber){
    cout<<"Running "<<RootNumber<<"root file finished"<<endl;
    if(ifsavehists){
        myhists->saveHists();
        delete myhists;
    }
    cout<<"Running histogram saved"<<endl;
}

void Analysis::Output(){
    cout<<endl;
    cout<<endl;
}

void Analysis::Initial(const char* RootName, int RootNumber){
    TTree *tree = NULL;
    TFile *file = (TFile *)gROOT->GetListOfFiles()->FindObject(RootName);
    if(!file)
        file = new TFile(RootName);
    tree = (TTree *)gDirectory->Get("Events");
    if(tree == NULL)
        cout<<"No Such Tree!!!"<<endl;

    fChain = tree;

    fChain->SetBranchAddress("run",&Rrun);
    fChain->SetBranchAddress("luminosityBlock",&RluminosityBlock);
    fChain->SetBranchAddress("event",&Revent);
    fChain->SetBranchAddress("nElectron",&RnElectron);
    fChain->SetBranchAddress("Electron_pt",&RElectron_pt);
    fChain->SetBranchAddress("Electron_dxy",&RElectron_dxy);
    fChain->SetBranchAddress("Electron_eta",&RElectron_eta);
    fChain->SetBranchAddress("Electron_phi",&RElectron_phi);
    fChain->SetBranchAddress("Electron_mass",&RElectron_mass);
    fChain->SetBranchAddress("Electron_deltaEtaSC",&RElectron_deltaEtaSC);
    fChain->SetBranchAddress("Electron_convVeto",&RElectron_convVeto);
    fChain->SetBranchAddress("Electron_lostHits",&RElectron_lostHits);
    fChain->SetBranchAddress("Electron_tightCharge",&RElectron_tightCharge);
    fChain->SetBranchAddress("Electron_dz",&RElectron_dz);
    fChain->SetBranchAddress("Electron_sip3d",&RElectron_sip3d);
    fChain->SetBranchAddress("Electron_miniPFRelIso_all",&RElectron_miniPFRelIso_all);
    fChain->SetBranchAddress("Electron_jetIdx",&RElectron_jetIdx);
    fChain->SetBranchAddress("Electron_mvaFall17V1Iso",&RElectron_mvaFall17V1Iso);
    fChain->SetBranchAddress("Electron_mvaFall17V1noIso",&RElectron_mvaFall17V1noIso);
    fChain->SetBranchAddress("Electron_eCorr",&RElectron_eCorr);
    fChain->SetBranchAddress("Electron_hoe",&RElectron_hoe);
    fChain->SetBranchAddress("Electron_sieie",&RElectron_sieie);
    fChain->SetBranchAddress("Electron_jetPtRelv2",&RElectron_jetPtRelv2);
    fChain->SetBranchAddress("Electron_jetRelIso",&RElectron_jetRelIso);
    fChain->SetBranchAddress("Electron_pfRelIso03_all",&RElectron_pfRelIso03_all);

    fChain->SetBranchAddress("nMuon",&RnMuon);
    fChain->SetBranchAddress("Muon_jetIdx",&RMuon_jetIdx);
    fChain->SetBranchAddress("Muon_pt",&RMuon_pt);
    fChain->SetBranchAddress("Muon_eta",&RMuon_eta);
    fChain->SetBranchAddress("Muon_dxy",&RMuon_dxy);
    fChain->SetBranchAddress("Muon_dz",&RMuon_dz);
    fChain->SetBranchAddress("Muon_sip3d",&RMuon_sip3d);
    fChain->SetBranchAddress("Muon_ptErr",&RMuon_ptErr);
    fChain->SetBranchAddress("Muon_phi",&RMuon_phi);
    fChain->SetBranchAddress("Muon_mass",&RMuon_mass);
    fChain->SetBranchAddress("Muon_looseId",&RMuon_looseId);
    fChain->SetBranchAddress("Muon_mediumId",&RMuon_mediumId);
    fChain->SetBranchAddress("Muon_jetPtRelv2",&RMuon_jetPtRelv2);
    fChain->SetBranchAddress("Muon_miniPFRelIso_all",&RMuon_miniPFRelIso_all);
    fChain->SetBranchAddress("Muon_jetRelIso",&RMuon_jetRelIso);
    fChain->SetBranchAddress("Muon_pfRelIso03_all",&RMuon_pfRelIso03_all);
//    fChain->SetBranchAddress("Muon_eCorr",&RMuon_eCorr);




    fChain->SetBranchAddress("Jet_pt",&RJet_pt);
    fChain->SetBranchAddress("Jet_eta",&RJet_eta);
    fChain->SetBranchAddress("Jet_phi",&RJet_phi);
    fChain->SetBranchAddress("Jet_mass",&RJet_mass);
    fChain->SetBranchAddress("nJet",&RnJet);


}
#endif



