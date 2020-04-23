#include "makeHists.h"

#include "TH1D.h"
#include "TH2D.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TFile.h"
#include "TProfile.h"
#include "TProfile2D.h"
#include "TMath.h"
#include "TTree.h"
#include <vector>


using namespace std;
void makeHists::bookHists(const char* fName){
    hf = new TFile(fName, "RECREATE");
    plot_aaa = new TH1D("plot_aaa","plot_aaa",100,0,100);
    plot_aaa->Sumw2();
}

void makeHists::saveHists(){
    hf->cd();
    hf->Write();
    cout<<"histogram write"<<endl;
    hf->Close();
}
