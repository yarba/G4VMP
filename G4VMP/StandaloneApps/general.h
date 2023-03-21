#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <list>

#include <math.h>
#include <vector>

#include "Rtypes.h"
#include "TROOT.h"
#include "TRint.h"
#include "TObject.h"
#include "TFile.h"
#include "TH1D.h"
#include "TProfile.h"
#include "TCanvas.h"
// --> #include "TPad.h"
#include "TStyle.h"
#include "TGraph.h"
#include "TLine.h"
#include "TArrow.h"

// --> LQ1 --> std::string file_dir_global = "/lustre1/g4/yarba_j/g4vmp-study";
std::string file_dir_global = "/wclustre/g4v/yarba_j/g4vmp-study";

std::string file_dir_local  = "";
std::string model           = "";
std::string beam            = "";
std::string secondary       = "";
TFile*      file            = 0;

bool LogX=false;
bool LogY=false;
