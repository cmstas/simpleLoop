#define ANALYSIS_SOURCE
#include "Analysis.h"
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include "TMath.h"
#include "TH1D.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TLorentzVector.h"
#include "Math/LorentzVector.h"
#include "Math/Point3D.h"
#include "Math/VectorUtil.h"
#include "TH3F.h"
#include <TRandom3.h>
#include <TMinuit.h>
#include <TApplication.h>
#include "TEnv.h"
#include <TComplex.h>
#include <TGraph.h>
#include <TProfile.h>
#include <TProfile2D.h>
#include <iomanip>

using namespace std;

void Analysis::Loop(const char* TypeName, const char* yearName){
    bool isData = false;
    bool isMC = false;

    TString InputName = TString(TypeName);
    if(InputName == "sig")   isData = true;
    else if(InputName == "MC")   isMC = true;


    if(fChain == 0) return;
    Int_t Nentries = fChain->GetEntries();

    Double_t weight;
    if(isData)
        cout<<"start looping data : "<<Nentries<<" events "<<endl;
    else
        cout<<"start loopoing MC  : "<<Nentries<<" events "<<endl;

    for(int ii = 0 ; ii < Nentries ; ii ++){
        fChain->GetEntry(ii,0);
        for(int jj = 0 ; jj < RnElectron ; jj ++){
            electronIDVBS(jj,"2017_tight");
        }

    }

}
