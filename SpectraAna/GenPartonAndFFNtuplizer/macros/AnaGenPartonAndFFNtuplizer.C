
#include <iostream>

#include "TFile.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TNtuple.h"
#include "TMath.h"
#include "TString.h"
#include "TClonesArray.h"
#include "TTree.h"
#include "TSystem.h"
#include "TRandom2.h"

#include "GenParticleInfo.h"
#include "SpectraStudyTreeClass.h"

// 0. dN/dET of jet for a given eta range (e.g. |eta|<1.0), given sample
// 1. dN/dpT of all tracks for a given eta range , given sample
// 2. FF(jet et, trk pt, parton flavor) for a given eta range, given sample
// 3. Commissioning Plots: pTHat distribution, 

// Histograms 
TH1F *dPtHat;
TH1F *dNevtMinPtHat;
TH1F *dNJetdEt;
TH1F *dPar1stFracLogQ;

TH2F *dNJetdEtdPtHat;
TH2F *dNJetdEtdPtHat_FF;
TH2F *dNTrkdPtdPtHat;
TH2F *dNAllTrkdPtdPtHat;

TH2F *dNTrkdPtdJetEt;
TH2F *dNTrkdZdJetEt;

TH3F *dNTrkdPtdPtHatdJetEt;
TH3F *dNTrkdZdPtHatdJetEt;

TH2F *dNTrkdPtdPhi; // to calculate v2
TH2F *dNAllTrkdPtdPhi; // 

vector<TH1D*> hFF;

// Variables
const int LARGE_N = 100000;

vector<double> etBins, ptBins, ptHatBins;
vector<double> etFFBins, zBins, dphiBins;

//const double ETBINS[19] ={0., 10., 20.,30.,40.,50.,60.,70.,80.,90.,100.,120.,140.,160.,200.,250.,300.,500.,825.};
//const int bins = sizeof(ETBINS)/sizeof(double) - 1;

bool saveFF = false;
bool lightRAA = true; // save only histograms needed for RAA

//------------------------------------
void prepareHist();
void saveHistRoot();
float applyCos(float phi);
double getPathL(double phi, double a, double b);
double getPar1stLinearPathL(double pathL, double a, double b);
//------------------------------------


void AnaGenPartonAndFFNtuplizer(bool save=false){

   // variables
   bool debug = false;

   bool applyQ = true;

   double fractQ = 0.3;
   double constQ = 30.0;   // 10, 20, 30
   double fractLogQ = 0.1;
   double fractLogQ_P2 = 1;  // 1 = does nothing
   
   fractQ = -1;
   constQ = -1;
   fractLogQ = 2.0;
   fractLogQ_P2 = 1;

   bool fixedFracLogQ = false;
   double fractLogQ_low = 1.5;
   double fractLogQ_hig = 2.5;

   bool phiDepELoss = false;
   double ellipse_a = 5.0;  // short path length
   double ellipse_b = 10.0; // long path length

   TString infdir = "/net/hisrv0001/home/y_alive/scratch1/ana/jetquenching/pythia";
   //TString infile = "spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v3_VariedN.root";

   //TString infdir = "/net/hisrv0001/home/y_alive/scratch1/ana/jetquenching/pythia/proq20";    
   TString infile = "spectAnaGEN_March26_PtAll_Ntot400K_proq20_FullExt_Large_VariedN";
   //TString infile = "spectAnaGEN_March26_PtAll_numEvents5000_proq20_FullExt_v5_VariedN";

   //TString infdir = "/net/hisrv0001/home/y_alive/cmssw_new/CMSSW_443_JetQuenchingAna/src/SpectraAna/GenPartonAndFFNtuplizer/test";
   //TString infile = "spectAnaGEN_numEvent500.root";


   TString outdir = "./root_output";
   TString outfile;
   outfile.Append(Form("ANA_%s",infile.Data()));
   if(applyQ) {
      outfile.Append("_jetQ");
      if(fractQ>0) outfile.Append(Form("_fract%1.2f",fractQ));
      if(constQ>0) outfile.Append(Form("_const%1.2f",constQ));
      if(fractLogQ>0) {
	 if(!fixedFracLogQ) {  // if parameter is not fixed
	    outfile.Append(Form("_fractLog%1.2fto%1.2f",fractLogQ_low,fractLogQ_hig));
	 }else{
	    outfile.Append(Form("_fractLog%1.2f",fractLogQ));
	 }
	 if(fractLogQ_P2!=1) outfile.Append(Form("_sp%1.2f",fractLogQ_P2));
      }
      if(phiDepELoss){
	 outfile.Append(Form("_phidep_a%1.2f_b%1.2f",ellipse_a,ellipse_b));
      }
   }
   
   cout<<"Check Parameters = "<<outfile.Data()<<endl;


   TFile *f1 = TFile::Open(Form("%s/%s.root",infdir.Data(),infile.Data()));

   if(!f1) {
      Error("<Input File Reading>","File is NULL");
      return;
   }
   

   f1->cd("genSpectAna");
   TTree *nt = (TTree*) f1->FindObjectAny("SpectraStudyTree");
   if(!nt) {
      Error("<Input Tree Reading>","Tree is NULL");
      return;
   }

   gSystem->Load("/net/hisrv0001/home/y_alive/cmssw_new/CMSSW_443_JetQuenchingAna/lib/slc5_amd64_gcc434/pluginSpectraAnaGenPartonAndFFNtuplizer.so");

   SpectraStudyTreeClass stree;

   TClonesArray *asstrk = new TClonesArray("GenParticleInfo");
   TClonesArray *alltrk = new TClonesArray("GenParticleInfo");

   nt->SetBranchAddress("fPthat",&stree.fPthat);
   nt->SetBranchAddress("fCrossx",&stree.fCrossx);
   nt->SetBranchAddress("isMinPtHat",&stree.isMinPtHat);
   nt->SetBranchAddress("nNumEvt",&stree.nNumEvt);

   nt->SetBranchAddress("nJets",&stree.nJets);
   nt->SetBranchAddress("nTrks",stree.nTrks);
   nt->SetBranchAddress("fJPt",stree.fJPt);
   nt->SetBranchAddress("fJEt",stree.fJEt);
   nt->SetBranchAddress("fJEta",stree.fJEta);
   nt->SetBranchAddress("fJPhi",stree.fJPhi);

   nt->SetBranchAddress("AssParticles",&asstrk);
   nt->SetBranchAddress("AllParticles",&alltrk);

   // prepare histograms
   prepareHist();

   int totN = 0;

   for (int i=0;i<nt->GetEntries();i++){

      nt->GetEntry(i);
      
      float nevt = (float) stree.nNumEvt;

      if (i%5000==0) {
	 cout<<"Cross-section = "<<stree.fCrossx<<" pTHat = "<<stree.fPthat
	     <<" number of events = "<<nevt
	     <<" number of jets = "<<stree.nJets<<" number of total tracks = "<<alltrk->GetEntriesFast()<<endl;
      }

      int ntotTrk = 0;
      dPtHat->Fill(stree.fPthat);
      
      /* Event-by-event Quenching Parameter Determination */
      double pFracQ = 0.0;
      if(fixedFracLogQ){
	 pFracQ = fractLogQ;
      }else{
	 pFracQ = gRandom->Uniform(fractLogQ_low,fractLogQ_hig);
      }
      dPar1stFracLogQ->Fill(gRandom->Uniform(fractLogQ_low,fractLogQ_hig));

      
      // 0. Parton/Jet and Associated Tracks ------------------------------------
      for (int j=0; j<stree.nJets; ++j) {

	 float jet  = stree.fJEt[j];
	 float jpt  = stree.fJPt[j];
	 float jeta = stree.fJEta[j];
	 float jphi = stree.fJPhi[j];
	 int ntrk = stree.nTrks[j];

	 // Without this cut, slightly more fragmented tracks in 4-5 GeV/c 
	 if(fabs(jeta)>2.0) continue; // eta cut 

	 if(debug) {
	    cout<<" Found Jet (et,pt,  eta,phi) = ("<<jet<<","<<jpt<<",  "<<jeta<<","<<jphi
		<<") with "<<ntrk<<" associated charged tracks"<<endl;
	 }

	 // Apply quenching scenarios
	 double pathLength = 0.0;
	 double pPhiFracQ = 0.0;

	 if(applyQ){
	    if(fractQ>0){
	       /* fractional eloss: */
	       jet = jet*(1. - fractQ);
	    }else if(constQ>0){
	       /* constant eloss: */
	       jet = jet - constQ; 
	    }else if(fractLogQ>0){
	       /* e-dependent fractional eloss: */
	       jet = jet*(1. - pFracQ*(log(fractLogQ_P2*jet)/jet));
	    }else if(phiDepELoss && fractLogQ>0){
	       pathLength = getPathL(jphi,ellipse_a,ellipse_b);
	       pPhiFracQ = getPar1stLinearPathL(pathLength,ellipse_a,ellipse_b);
	       jet = jet*(1. - pPhiFracQ*(log(fractLogQ_P2*jet)/jet));
	    }
	    if(jet<0) continue;  // THIS IS IMPORTANT --> JUSTIFIED?
	 } // end of apply jetQ


	 // HIST FILLING 
	 dNJetdEt->Fill(jet,stree.fCrossx);
	 dNJetdEtdPtHat->Fill(jet,stree.fPthat,stree.fCrossx); 
	 dNJetdEtdPtHat_FF->Fill(jet,stree.fPthat,stree.fCrossx);
	 
	 // associated track loop 
	 for (int k=0; k<ntrk; ++k) {

	    GenParticleInfo *AssParticles = (GenParticleInfo*)asstrk->At(ntotTrk);  
	    ntotTrk++;  // ntotTrk = sum of ntrk_{i}
	    
	    float trkpt  = AssParticles->fPt;
	    float trketa = AssParticles->fEta;
	    float trkphi = AssParticles->fPhi;

	    float trkz = (jet>0) ? trkpt/jet : 100.0;

	    if(fabs(trketa)>1.0) continue; // eta cut

	    if(debug) {
	       cout<<"    Associated Tracks (pt,eta,phi) = ("<<trkpt<<","<<trketa<<","<<trkphi
		   <<") and z = trkpt/jetet = "<<trkpt/jpt<<endl; 
	    }


	    // HIST FILLING
	    dNTrkdPtdPtHat->Fill(trkpt,stree.fPthat,stree.fCrossx);  // weighted by cross section
	    dNTrkdPtdJetEt->Fill(trkpt,jpt,stree.fCrossx);
	    dNTrkdZdJetEt->Fill(trkz,jpt,stree.fCrossx);
	    dNTrkdPtdPhi->Fill(trkpt,trkphi,stree.fCrossx*(1.+applyCos(trkphi))); // ARTIFICAL V2

	    dNTrkdPtdPtHatdJetEt->Fill(trkpt,stree.fPthat,jpt,stree.fCrossx);
	    dNTrkdZdPtHatdJetEt->Fill(trkz,stree.fPthat,jpt,stree.fCrossx);
	    
	    //ntotTrk++;
	 } // end of tracks

      } // end of nJets


      // 1. All Charged Tracks ----------------------------------------
      for (int l=0; l<alltrk->GetEntriesFast(); ++l) {
	 GenParticleInfo *AllParticles = (GenParticleInfo*)alltrk->At(l);

	 float alltrkpt  = AllParticles->fPt;
	 float alltrketa = AllParticles->fEta;
	 float alltrkphi = AllParticles->fPhi;


	 if(fabs(alltrketa)>1.0) continue; // eta cut     

	 // HIST FILLING
	 dNAllTrkdPtdPtHat->Fill(alltrkpt,stree.fPthat,stree.fCrossx);
	 dNAllTrkdPtdPhi->Fill(alltrkpt,alltrkphi,stree.fCrossx);

      }


      if(stree.isMinPtHat==1) dNevtMinPtHat->Fill(1.1);
      totN++;

   } // end of all entries

   cout<<"Number of events = "<<totN<<endl;

   // Fragmentation Function Generator
   if(saveFF){
      for(int j=0;j<dNTrkdPtdPtHatdJetEt->GetNbinsZ();j++){
	 
	 //double dsigma = hdjetet_ff->GetBinContent(j+1);
	 //if(dsigma<1E-22) continue; // no jet ET bins 
	 double etmin = dNTrkdPtdPtHatdJetEt->GetZaxis()->GetBinLowEdge(j+1);
	 double etmax = dNTrkdPtdPtHatdJetEt->GetZaxis()->GetBinUpEdge(j+1);
	 
	 // Fragmentation Function (Be carefull not [j+1,j+2]) 
	 TH1D *hddtrkdpt_ff = (TH1D*) dNTrkdPtdPtHatdJetEt->ProjectionX("",0,-1,j+1,j+1,"e");
	 hddtrkdpt_ff->SetName(Form("hddTrkdPt_FF_et%1.0fto%1.0f",etmin,etmax));
	 hFF.push_back(hddtrkdpt_ff);
      }
   }

   // Save histograms in a root file
   if(save){
      cout<<"Output file = "<<Form("%s/%s.root",outdir.Data(),outfile.Data())<<endl;
      TFile *outputFile = new TFile(Form("%s/%s.root",outdir.Data(),outfile.Data()),"recreate");
      saveHistRoot();
   }

}


void prepareHist(){

   TH1::SetDefaultSumw2();
   TH2::SetDefaultSumw2();
   TH3::SetDefaultSumw2();

   const double small = 1e-3;

   // ptHat bins
   double pthb;
   for(pthb = 0; pthb < 1400-small; pthb += 5) ptHatBins.push_back(pthb);
   ptHatBins.push_back(1400);

   // et bins
   double etb;
   //for(etb = 0; etb < 1400-small; etb += 1) etBins.push_back(etb);
   //etBins.push_back(1400);

   for(etb =    0; etb <   10-small; etb +=  1.0) etBins.push_back(etb);
   for(etb =   10; etb <   30-small; etb +=  1.0) etBins.push_back(etb);
   for(etb =   30; etb <   50-small; etb +=  1.0) etBins.push_back(etb);
   for(etb =   50; etb <  100-small; etb +=  2.0) etBins.push_back(etb);
   for(etb =  100; etb <  300-small; etb +=  4.0) etBins.push_back(etb);
   for(etb =  300; etb <  500-small; etb +=  8.0) etBins.push_back(etb);
   for(etb =  500; etb < 1400-small; etb += 10.0) etBins.push_back(etb);
   etBins.push_back(1400);
   

   // et bins for defining FF
   double etffb;
   //for(etffb = 0; etffb < 1400-small; etffb += 25) etFFBins.push_back(etffb);
   //etFFBins.push_back(1400);

   for(etffb =    0; etffb <   10-small; etffb +=  1.0) etFFBins.push_back(etffb);
   for(etffb =   10; etffb <   30-small; etffb +=  1.0) etFFBins.push_back(etffb);
   for(etffb =   30; etffb <   50-small; etffb +=  1.0) etFFBins.push_back(etffb);
   for(etffb =   50; etffb <  100-small; etffb +=  2.0) etFFBins.push_back(etffb);
   for(etffb =  100; etffb <  300-small; etffb +=  4.0) etFFBins.push_back(etffb);
   for(etffb =  300; etffb <  500-small; etffb +=  8.0) etFFBins.push_back(etffb);
   for(etffb =  500; etffb < 1400-small; etffb += 10.0) etFFBins.push_back(etffb);
   etFFBins.push_back(1400);
   

   // z bins
   //zBins
   double zb;
   //for(zb = 0; zb < 1.5-small; zb += 0.0075) zBins.push_back(zb);
   //zBins.push_back(1.5);

   for(zb =   0; zb < 0.1-small; zb += 0.005) zBins.push_back(zb);         
   for(zb = 0.1; zb < 0.2-small; zb += 0.010) zBins.push_back(zb);
   for(zb = 0.2; zb < 0.5-small; zb += 0.025) zBins.push_back(zb);
   for(zb = 0.5; zb < 1.4-small; zb += 0.05) zBins.push_back(zb);
   zBins.push_back(1.4);   

   // pt bins
   double ptb;

   // simple rebinning possible with a rebinning facto n = 2, 3, 6 !
   for(ptb =   0  ; ptb <   1.2-small; ptb +=  0.05) ptBins.push_back(ptb); // 24 bins
   for(ptb =   1.2; ptb <   2.4-small; ptb +=  0.1 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =   2.4; ptb <   7.2-small; ptb +=  0.4 ) ptBins.push_back(ptb); // 12 bins
   for(ptb =   7.2; ptb <  14.4-small; ptb +=  1.2 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  14.4; ptb <  28.8-small; ptb +=  2.4 ) ptBins.push_back(ptb); // 6 bins 
   for(ptb =  28.8; ptb <  48.0-small; ptb +=  3.2 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  48.0; ptb <  86.4-small; ptb +=  6.4 ) ptBins.push_back(ptb); // 6 bins
   for(ptb =  86.4; ptb < 189.6-small; ptb +=  8.6 ) ptBins.push_back(ptb); // 6 bins
   for(ptb = 189.6; ptb < 396.0-small; ptb +=  17.2) ptBins.push_back(ptb); // 12 bins  
   for(ptb = 396.0; ptb <1221.6-small; ptb +=  34.4) ptBins.push_back(ptb); // 24 bins
   ptBins.push_back(1221.6);


   // phi bins
   double dphib;

   for(dphib = -3.2; dphib < 3.2-small; dphib += 0.05) dphiBins.push_back(dphib);
   dphiBins.push_back(3.2);

   // 1D      
   dPtHat = new TH1F("dPtHat","#hat{q} with no weight", ptHatBins.size()-1, &ptHatBins[0]);   
   dNevtMinPtHat = new TH1F("dNevtMinPtHat","Number of processed events in the min pt_hat sample",10,0.0,10.0); 

   dNJetdEt = new TH1F("dNJetdEt","Parton/Jet E_{T}; E_{T} (GeV)",etBins.size()-1, &etBins[0]);

   dPar1stFracLogQ = new TH1F("dPar1stFracLogQ","Jet Quenching Parameter Distribution; PAR1",100, 0.0, 5.0);

   // 2D
   dNJetdEtdPtHat = new TH2F("dNJetdEtdPtHat","Parton/Jet E_{T} vs #hat{q}; E_{T} (GeV); #hat{q} (GeV)", 
			  etBins.size()-1, &etBins[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNTrkdPtdPtHat = new TH2F("dNTrkdPtdPtHat","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
			     ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNAllTrkdPtdPtHat = new TH2F("dNAllTrkdPtdPtHat","Charged particle p_{T} vs #hat{q}; p_{T} (GeV/c); #hat{q} (GeV)",
				ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0]);
   
   dNJetdEtdPtHat_FF = new TH2F("dNJetdEtdPtHat_FF","Parton/Jet E_{T} vs #hat{q}; E_{T} (GeV); #hat{q} (GeV)",
				etFFBins.size()-1, &etFFBins[0], ptHatBins.size()-1, &ptHatBins[0]);

   dNTrkdPtdJetEt = new TH2F("dNTrkdPtdJetEt","p_{T} vs Jet E_{T};p_{T} (GeV/c);Jet E_{T} (GeV)",
			     ptBins.size()-1, &ptBins[0], etFFBins.size()-1, &etFFBins[0]);

   dNTrkdZdJetEt = new TH2F("dNTrkdZdJetEt","z vs Jet E_{T}; z=p_{T}/E_{T}; Jet E_{T} (GeV)",
			    zBins.size()-1, &zBins[0], etFFBins.size()-1, &etFFBins[0]);

   dNTrkdPtdPhi = new TH2F("dNTrkdPtdPhi","p_{T} vs #Delta#phi; p_{T} (GeV/c); #Delta#phi (rad)",
			   ptBins.size()-1, &ptBins[0], dphiBins.size()-1, &dphiBins[0]);
   
   dNAllTrkdPtdPhi = new TH2F("dNAllTrkdPtdPhi","p_{T} vs #Delta#phi; p_{T} (GeV/c); #Delta#phi (rad)",
			      ptBins.size()-1, &ptBins[0], dphiBins.size()-1, &dphiBins[0]);

   // 3D
   dNTrkdPtdPtHatdJetEt = new TH3F("dNTrkdPtdPtHatdJetEt",
				   "Charged particle p_{T} vs #hat{q} vs Jet E_{T} (GeV); p_{T} (GeV/c);#hat{q} (GeV);Jet E_{T} (GeV)",
				   ptBins.size()-1, &ptBins[0], ptHatBins.size()-1, &ptHatBins[0], etFFBins.size()-1, &etFFBins[0]);
   
   dNTrkdZdPtHatdJetEt = new TH3F("dNTrkdZdPtHatdJetEt",
                                   "Charged particle Z vs #hat{q} vs Jet E_{T} (GeV); z=p_{T}/E_{T};#hat{q} (GeV);Jet E_{T} (GeV)",
				  zBins.size()-1, &zBins[0], ptHatBins.size()-1, &ptHatBins[0], etFFBins.size()-1, &etFFBins[0]);
   
}


void saveHistRoot(){


   if(!lightRAA) dPtHat->Write();
   dNevtMinPtHat->Write();
   dNJetdEt->Write();
   dPar1stFracLogQ->Write();

   if(!lightRAA){
      dNJetdEtdPtHat->Write();
      dNJetdEtdPtHat_FF->Write();
      dNAllTrkdPtdPtHat->Write();
   }
   dNTrkdPtdPtHat->Write();

   dNTrkdPtdJetEt->Write();
   if(!lightRAA) dNTrkdZdJetEt->Write();

   dNTrkdPtdPtHatdJetEt->Write();
   if(!lightRAA) dNTrkdZdPtHatdJetEt->Write();

   dNTrkdPtdPhi->Write();
   dNAllTrkdPtdPhi->Write();

   if(saveFF){
      for(int s=0; s<hFF.size(); s++){
	 hFF[s]->Write();
      }
   }
}



float applyCos(float phi){
   
   return cos(2.*phi);

}

double getPathL(double phi, double a, double b){
   return a*b/TMath::Sqrt( pow(a*sin(phi),2) + pow(b*cos(phi),2) );
}

/*
double getPar1stPhi(double pathL, double a, double b){
   return getPar1stLinearPathL(pathL,a,b);
}
*/

double getPar1stLinearPathL(double pathL, double a, double b){

   // short path length --> p1stMin (e.g. 0.1)
   // long  path length --> p1stMax (e.g. 3.1)
   double p1stMin = 0.1;
   double p1stMax = 3.1;
   
   double c1 = (p1stMax-p1stMin)/(b-a);
   double c2 = p1stMin + a*(p1stMax-p1stMin)/(b-a);
   double par1 =  -1.*c1*pathL + c2;

   return par1;
}

