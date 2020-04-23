#ifndef MAKEHISTS_HEADFILE
#define MAKEHISTS_HEADFILE
#include <iostream>
#include "TTree.h"

class TH1D;
class TH2D;
class TH2F;
class TH3F;
class TFile;
class TProfile;
class TProfile2D;
class makeHists{
    public:
        TFile *hf;

        TH1D *plot_aaa;

        void bookHists(const char* fName);
        void saveHists();
};
#endif
