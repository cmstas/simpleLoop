#include "Analysis.h"

using namespace std;

bool Analysis::electronIDVBS(int iel, string id_name){
    int id_level;
    if     (id_name == "2017_tight")   id_level = 1;
    else if(id_name == "2017 loose")   id_level = 2;
    else{
        cout<<"wrong input id name"<<endl;
        return 0;
    }
    switch(id_level){
        case(1):
            if(RElectron_pt[iel] <= 10) return false;
            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            if(!isTriggerSavenoIso_v1(iel)) return false;
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 2.5) return false;
            if(!RElectron_convVeto[iel]) return false;
            if((int)(RElectron_lostHits[iel]) > 1) return false;
            if(fabs(RElectron_dxy[iel]) > 0.05) return false;
            if(fabs(RElectron_dz[iel]) >= 0.1) return false;
            if(!ifpassElectronMVAID(iel, "2017_veto_noiso")) return false;
            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            if((int)(RElectron_lostHits[iel]) > 0) return false; //SS_innerlayers
            if(RElectron_tightCharge[iel] == 0 || RElectron_tightCharge[iel] == 1) return false;
            if(fabs(RElectron_sip3d[iel] ) > 4) return false;
            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            if(!ifpassElectronMVAID(iel, "2017")) return false;
            if(!passElectronIso(0.07,0.78,8.0,iel)) return false;
            cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            return true;
            break;
            
        case(2):
            if(RElectron_pt[iel] <= 10) return false;
            if(!isTriggerSavenoIso_v1(iel)) return false;
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 2.5) return false;
            if(!RElectron_convVeto[iel]) return false;
            if((int)(RElectron_lostHits[iel]) > 1) return false;
            if(fabs(RElectron_dxy[iel]) > 0.05) return false;
            if(fabs(RElectron_dz[iel]) >= 0.1) return false;
            if(!ifpassElectronMVAID(iel, "2017_veto_noiso")) return false;
            if((int)(RElectron_lostHits[iel]) > 0) return false; //SS_innerlayers
            if(RElectron_tightCharge[iel] == 0) return false;
            if(fabs(RElectron_sip3d[iel] ) >= 4) return false;
            if(!ifpassElectronMVAID(iel, "2017SS_fo_looseMVA_noiso_v6")) return false;
            if(RElectron_miniPFRelIso_all[iel] >= 0.4) return false;
            return true;
            break;
    }
    cout<<"Error in ElectronSelection.C : should not see this message!!!!!!!"<<endl;
    return 0;
}

float Analysis::electronMvacut(float A, float B, float C, float pt){
    if(pt < 10) return C;
    if(pt > 25) return B;
    else return (A + (B-A) /15 * (pt-10));
}


bool Analysis::ifpassElectronMVAID(int iel, string id_name){
    int id_level;
    if     (id_name == "2017")                    id_level = 1;
    else if(id_name == "2017_veto_noiso")         id_level = 2;
    else if(id_name == "2017SS_fo_looseMVA_noiso_v6") id_level = 3;
    else{
        cout<<"wrong input id name from ElectronSelection.C!!!!!"<<endl;
        return 0;
    }
    switch(id_level){
        case(1):
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) < 0.8){
                if( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(0.2,0.68,0.2,RElectron_pt[iel]) ) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) >= 0.8 && fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) <= 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(0.1,0.475,0.1,RElectron_pt[iel]) ) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.1,0.32,-0.1,RElectron_pt[iel]) ) return false;
            }
            return true;
            break;
        case(2):
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) < 0.8){
                if(RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.788,-0.64,0.488,RElectron_pt[iel])) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) >= 0.8 && fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) <= 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.85,-0.775,-0.045,RElectron_pt[iel]) ) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.81,-0.733,0.176,RElectron_pt[iel]) ) return false;
            }
            return true;
            break;
        case(3):
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) < 0.8){
                if(RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.93,-0.887,-0.135,RElectron_pt[iel])) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) >= 0.8 && fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) <= 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.93,-0.89,-0.417,RElectron_pt[iel]) ) return false;
            }
            if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 1.479){
                if ( RElectron_mvaFall17V1noIso[iel] <= electronMvacut(-0.942,-0.91,-0.470,RElectron_pt[iel]) ) return false;
            }
            return true;
            break;

    }
    cout<<"wrong !!!!!!!should not see this message!!!! from ElectronSelection.C"<<endl;
    return 0;
}

bool Analysis::isTriggerSavenoIso_v1(int iel){
    if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) <= 1.479){
        if(RElectron_sieie[iel] >= 0.011) return false;
        if(RElectron_hoe[iel] >= 0.08) return false;
    }else if(fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) > 1.479 &&
            fabs(RElectron_eta[iel] + RElectron_deltaEtaSC[iel]) < 2.5){
        if(RElectron_sieie[iel] >= 0.031) return false;
        if(RElectron_hoe[iel] >= 0.08) return false;
    }
    return true;
}

bool Analysis::passElectronIso(double cut_miniiso, double cut_ptratio, double cut_ptrel, int iel){
    double val_miniiso = RElectron_miniPFRelIso_all[iel];
    double val_ptratio = 1/(RElectron_jetRelIso[iel]+1);
    double val_ptrel = RElectron_jetPtRelv2[iel];
    return (val_miniiso < cut_miniiso && ((val_ptratio > cut_ptratio) || (val_ptrel > cut_ptrel)));
}
