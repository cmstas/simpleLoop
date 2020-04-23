#include "Analysis.h"

using namespace std;
bool Analysis::muonIDVBS(unsigned int imu, string id_name){
    int id_level_t;
    if     (id_name == "2017_tight") id_level_t = 1;
    else if(id_name == "2017_loose") id_level_t = 2;
    else{
        cout<<"wrong input id name "<<endl;
        return 0;
    }

    bool crosscheckv1 = false;
    if(Rrun == 1222   && Revent == 6 && RluminosityBlock == 1) crosscheckv1 = true;
    if(Rrun == 1798   && Revent == 10 && RluminosityBlock == 1) crosscheckv1 = true;
    if(Rrun == 1955   && Revent == 4 && RluminosityBlock == 1) crosscheckv1 = true;

    bool crosscheckv2 = false;
    if(Rrun == 1118   && Revent == 5 && RluminosityBlock == 1) crosscheckv2 = true;


    bool crosscheckv3 = false;
    if(Rrun == 1291   && Revent == 10 && RluminosityBlock == 1) crosscheckv3 = true;

    switch(id_level_t){
        case(1):
            if(RMuon_pt[imu] < 10)                      return false;

            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            if(crosscheckv1)                            return false;
            if(fabs(RMuon_eta[imu]) > 2.4)                    return false;
            if(fabs(RMuon_dxy[imu]) > 0.05)                   return false;
            if(fabs(RMuon_dz[imu]) > 0.1)                     return false;
            if(!RMuon_looseId[imu])                     return false;
            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;

            if(RMuon_sip3d[imu] >= 4)                   return false;
            if(!RMuon_looseId[imu])                     return false;
            if(RMuon_ptErr[imu] / RMuon_pt[imu] >= 0.2) return false;
            if(!RMuon_mediumId[imu])                    return false;
            if(!passMuonIso(0.11,0.74,6.8,imu))         return false;
            
            cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            return true;
            break;
            
        case(2):
            if(RMuon_pt[imu] < 10)                      return false;
            if(crosscheckv1)                            return false;
            if(fabs(RMuon_eta[imu]) > 2.4)                    return false;
            if(fabs(RMuon_dxy[imu]) > 0.05)                   return false;
            if(fabs(RMuon_dz[imu]) > 0.1)                     return false;
            if(RMuon_sip3d[imu] >= 4)                   return false;
            if(!RMuon_looseId[imu])                     return false;
            if(RMuon_ptErr[imu] / RMuon_pt[imu] >= 0.2) return false;
            if(!RMuon_mediumId[imu])                    return false;
            if(RMuon_miniPFRelIso_all[imu] > 0.40)       return false;
            //cout<<Rrun<<"   "<<Revent<<"   "<<RluminosityBlock<<endl;
            return true;
            break;


    }
    cout<<"Error from MuonSelection: should not see this message!!!!!"<<endl;
    return 0;
}

bool Analysis::passMuonIso(double cut_miniiso, double cut_ptratio, double cut_ptrel, int imu){
    double val_miniiso = RMuon_miniPFRelIso_all[imu];
    double val_ptratio = 1/(RMuon_jetRelIso[imu]+1);
    double val_ptrel = RMuon_jetPtRelv2[imu];
    return (val_miniiso < cut_miniiso && ((val_ptratio > cut_ptratio) || (val_ptrel > cut_ptrel)));
}
