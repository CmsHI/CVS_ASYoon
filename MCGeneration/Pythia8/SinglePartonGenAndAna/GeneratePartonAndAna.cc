//-------------------------------------------------------------------------------------
//  August 17 2010 Andre S. Yoon
//
//  This code generates partons (qqbar or gg) with a specific energy, which is 
//  hadronized subsequently in PYTHIA. (see main21.cc) And then the hadronized 
//  particles are analyzed in the following way.
//
//  When fine bin option is set to true, histogram is filled only for fine bins, which
//  is located at the center of each large bin with a much smaller bin size. This is 
//  because as the bin size gets extremely large, the bin size efffect gets also very
//  large. If the original bin size is comparable to the fine bin size, the result 
//  should converge. However, as the bin width gets smaller, more statistics is required
//  to have a similar statistics it would have acquired otherwise 
// 
//  eg) eWidth = 1E6 eWidthFine = 0.5 for one bin pictorially
//
//      |------//------|--|-----//------| 
//                     |--|               Small bin
//      |-------------------------------| Big Bin
//
//  example) $make GeneratePartonAndAna
//           $./GeneratePartonAndAna.exe    
//
//  *Development note*
//   - currently, only one histogram is filled, but this can be improved to several
//     histograms with different particle X (photons, neutrionos, electrons)
//   - move from raw energy to a variable z, where z = e_particle/e_parton (aug 31 2010)
//-------------------------------------------------------------------------------------

#include "Pythia.h"
using namespace Pythia8;


std::vector<double> eBins;
std::vector<double> eHist;

// for initialization of "histogram"
/*
static double eMin   =  0;
static double eMax   =  1.1E11;
//static double eWidth =  1.1E8;
static double eWidth =  2.2E8; 
static double eWidthFine = 2E6; // fine bin option
const int nBins = 500; // (int) (eMax-eMin)/eWidth;
const bool fineBinOption = false;
*/

const bool fineBinOption = false; 

static double pEnergy = 1E11; // intial parton energy
static double zMin  = 0;
static double zMax  = 1.1;
static double zWidth = 0.002;
static double zWidthFine = 2E-6;

const int nBins = 550; // make sure number of bins is int

double eEntries[nBins], eEntriesErr[nBins];

ofstream outputF1;

//-------------------------------------------------------------------------------------
//void histograming(vector<double> bins, double pE);
void histograming(vector<double> bins, double pE, bool fineBin);
void fillPartons(int type, int id, double ee, Event& event, ParticleData& pdt, Rndm& rndm);
//-------------------------------------------------------------------------------------


int main() {

  // Pick kind of events to generate:        
  // 1 = q qbar, 2 = g g.               
  int type = 1;

  // Pick parton flavor
  // 1 = d, 2 = u, 3 = s, 4 = c, 5 = b, 6 = t 
  int id = 2;

  // Pick particle type for FF 
  // proton - 2212, electron - 11, photon - 22, neutrino(e) - 12
  // if wpid = 0, all finaal state  particles
  int wpid = 2212;
  //int wpid = 0;

  // Set typical energy per parton. 
  double ee = pEnergy;

  // Set number of events to generate and to list. 
  //int nEvent = 3000000;
  int nEvent = 1000;
  int nList = 1;
  int nEventCounter = 0;
  bool debugLog = false;  
  bool saveOutput = true;

  // Generator; shorthand for event and particleData. 
  Pythia pythia;
  Event& event      = pythia.event;
  ParticleData& pdt = pythia.particleData;

  // Key requirement: switch off ProcessLevel, and thereby also PartonLevel. 
  pythia.readString("ProcessLevel:all = off");

  // Optionally switch off decays. 
  //pythia.readString("HadronLevel:Decay = off"); 
  
  // Decay settings (cTau = 10 mm ?)

  // Provide printout of initial information. 
  pythia.settings.listChanged();

  // Initialize. 
  pythia.init();

  // Initialize histograms related
  //for(double e = eMin; e < eMax + eWidth/2; e += eWidth)
  for(double z = zMin; z < zMax + zWidth/2; z += zWidth)
     eBins.push_back(z);
  
  for(unsigned i=0;i<eBins.size()-1;i++)
    eEntries[i]=0., eEntriesErr[i]=0.; //intailize every "bin" with 0

  
  // Begin of event loop. 
  double dRdiv = 1.0; // dR divider for dividing q and qqbar (or gg)

  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
     //if (iEvent%(max(1,nEvent/20)) == 0) cout << " Now begin event "
     //<< iEvent << endl;
    
    if ((iEvent%10000) == 0) cout << " Now begin event "
				 << iEvent << endl;


    // set up parton gun
    fillPartons( type, id, ee, event, pdt, pythia.rndm);

    // Generate events. Quit if failure. => move on to next event if fails
    if (!pythia.next()) continue;

    // List first few events. 
    if (iEvent < nList) {
      event.list();
      // Also list junctions. 
      event.listJunctions();
    }

    // Pre-looping to select and collect parton info
    int nHardPart = 0;
    double phi = 0;
    double eta = 0;

    for (int i = 0; i < event.size(); ++i) {
      // Select parton once 
      int status_pre = event[i].statusAbs();
      int pid_pre = event[i].id();

      if(status_pre==23 && pid_pre>0 && nHardPart!=1) {
	phi = event[i].phi();
	eta = event[i].eta();
	nHardPart++;
	if(debugLog) cout<<" pid = "<<pid_pre<<" E = "<<event[i].e()<<" eta = "<<eta<<" phi = "<<phi<<endl;
      }
    }

    // Loop over all particles.
    Vec4 pVSumNear = - event[0].p();
    Vec4 pVSumAway = - event[1].p();
    
    double pSumNear = 0.; // sum of momentum of particle  near side
    double pSumAway= 0.;
    

    for (int i = 0; i < event.size(); ++i) { 
      int status = event[i].statusAbs();   
      int pid = event[i].id();
      double eCalc = event[i].eCalc(); // energy calculated from the mass and three-momentum

      // Find any unrecognized particle codes. 
      if (debugLog && (pid == 0 || !pdt.isParticle(id)))
        cout<<"Error! Unknown code id = "<<id<< "\n";

      // Find particles with E-p mismatch. 
      if (debugLog && (abs(eCalc/event[i].e() - 1.) > 1e-6)) 
	cout<< " e mismatch, i = "
	    <<i<<" e_nominal = "<<event[i].e() <<" e-from-p = "
	    <<eCalc<<" m-from-e " <<event[i].mCalc()<<"\n";
      
      // Study final-state particles. 
      if (event[i].isFinal()) {
	double dphi = fabs(event[i].phi() - phi);
	double deta = fabs(event[i].eta() - eta);
	double dR = sqrt(dphi*dphi + deta*deta);
	if(debugLog) cout<<" status = "<<status<<" y = "<<event[i].eta()
			 <<" phi = "<<event[i].phi()<<" dR = "<<dR
			 <<" energy = "<<event[i].e()<<endl;
	
	//double pMag = sqrt(event[i].px()*event[i].px() +
	//event[i].py()*event[i].py() +
	//event[i].pz()*event[i].pz());

	double pMag = event[i].e();
	double pZ = pMag/pEnergy;

	if(dR<dRdiv) {
	  pSumNear = pSumNear + pMag;
	  //if(wpid!=0 && abs(pid)==wpid) histograming(eBins,event[i].e(),fineBinOption);
	  //else if(wpid==0) histograming(eBins,event[i].e(),fineBinOption);
	  if(wpid!=0 && abs(pid)==wpid) histograming(eBins,pZ,fineBinOption);
          else if(wpid==0) histograming(eBins,pZ,fineBinOption);
	}else {
	  pSumAway = pSumAway + pMag;
	}

      }
    }

    if(debugLog) cout<<"Momentum sum near side = "<<pSumNear<<" away side = "<<pSumAway<<endl;
    nEventCounter++;
  }

  // Statistics
  pythia.statistics();
  cout<<"Number of effecitve events that are analyzed = "<<nEventCounter<<endl;

  // Print out and save in a output file
  if(saveOutput){
    char nameF1[200];
    if(fineBinOption)
       sprintf(nameF1,"./data_files/GPAA_ff_parton%d_particle%d_partonE%1.3e_fineBin%d_nEvent%d_zMin%1.2e_to_zMax%1.2e_zW%1.2e.out",
	       id,wpid,ee,fineBinOption,nEvent,zMin,zMax,zWidthFine);
    else
       sprintf(nameF1,"./data_files/GPAA_ff_parton%d_particle%d_partonE%1.3e_fineBin%d_nEvent%d_zMin%1.2e_to_zMax%1.2e_zW%1.2e.out",
	       id,wpid,ee,fineBinOption,nEvent,zMin,zMax,zWidth);
    
    outputF1.open(nameF1);
    for(unsigned i=0;i<eBins.size()-1;i++){
      
      // stat. err. calculation
      if(eEntries[i]!=0) eEntriesErr[i] = sqrt(eEntries[i]);
      
      // event normalization
      eEntries[i] = eEntries[i]/(double)nEventCounter;
      eEntriesErr[i] = eEntriesErr[i]/(double)nEventCounter;

      // divided by bin width
      if(fineBinOption)
	eEntries[i] = eEntries[i]/(double)zWidthFine, eEntriesErr[i] = eEntriesErr[i]/(double)zWidthFine;
      else 
	eEntries[i] = eEntries[i]/(double)zWidth, eEntriesErr[i] = eEntriesErr[i]/(double)zWidth;
      
      outputF1<<"      "<<0.5*(eBins[i]+eBins[i+1])
	      <<"      "<<eEntries[i]
	      <<"      "<<eEntriesErr[i]<<endl;
    }
    outputF1.close();
    cout<<"File: "<<nameF1<<" is created"<<endl;
  }

  // Done. 
  return 0;

}

/*
void histograming(vector<double> bins, double pE){

  for(unsigned i=0;i<bins.size()-1;i++){
    if(pE>=bins[i] && pE<bins[i+1]){
      eEntries[i] = eEntries[i] + 1.;
    } 
  }
}
*/

void histograming(vector<double> bins, double pE, bool fineBin){

  for(unsigned i=0;i<bins.size()-1;i++){
    if(pE>=bins[i] && pE<bins[i+1]){
      if(fineBin){ // note the bin center is not changed
	double binCenter = 0.5*(bins[i]+bins[i+1]);
	double binUpEdge = binCenter + zWidthFine;
	double binLowEdge = binCenter - zWidthFine;
	if(pE>=binLowEdge && pE<binUpEdge){
	  eEntries[i] = eEntries[i] + 1.;
	}
      }else{
	eEntries[i] = eEntries[i] + 1.;
      }
    }
  }

}

void fillPartons(int type, int id, double ee, Event& event, ParticleData& pdt, Rndm& rndm) {

  // Reset event record to allow for new event. 
  event.reset();

  // Information on a q qbar system, to be hadronized. 
  if (type == 1) {
    //int    id = 2;
    double mm = pdt.m0(id);
    double pp = sqrtpos(ee*ee - mm*mm);

    //event.append(  id, 23, 101,   0, 0., 0.,  pp, ee, mm);
    //event.append( -id, 23,   0, 101, 0., 0., -pp, ee, mm);

    // px, py=pz=0
    event.append(  id, 23, 101,   0, pp, 0.,  0., ee, mm);   
    event.append( -id, 23,   0, 101, -pp, 0., 0., ee, mm);  

    // px = py, pz = 0
    //event.append(  id, 23, 101,   0, pp*(1/sqrt(2)), pp*(1/sqrt(2)),  0., ee, mm);
    //event.append( -id, 23,   0, 101, -pp*(1/sqrt(2)), -pp*(1/sqrt(2)), 0., ee, mm);
    
    // px = pz, py =0
    //event.append(  id, 23, 101,   0, pp*(1/sqrt(2)), 0.,   pp*(1/sqrt(2)), ee, mm);
    //event.append( -id, 23,   0, 101, -pp*(1/sqrt(2)), 0., - pp*(1/sqrt(2)), ee, mm);


  // Information on a g g system, to be hadronized.
  } else if (type == 2) {
    event.append( 21, 23, 101, 102, 0., 0.,  ee, ee);
    event.append( 21, 23, 102, 101, 0., 0., -ee, ee);
  }

}
