


void PlotCentDistUsingYKTable(){

  TFile *f1 = new TFile("/Users/andreyoon/Research/pbpbSpectra/hi2011/root_files/data/hydjetBass_44x_cent_ntuples_dec192011.root");

  TNtuple *nt_hftowers = (TNtuple*) f1->Get("postEvtCentDist/nt_hftowers");

  string bin = "0";

  double edge[40] = {3610.07,3129.23,2757.6,2443.6,2160.04,1928.63,1730.1,1547.79,1382.21,1232.02,1092.89,968.524,857.347,755.897,659.172,576.598,499.89,433.515,372.682,317.755,268.925,226.91,190.069,156.552,128.77,105.005,85.1869,67.1869,53.3646,42.6393,33.7168,26.5969,20.873,15.9455,11.9324,8.54856,5.90016,3.79686,2.03625,0};

  for(int i = 0; i < 40 ; ++i){
    bin += Form("+ (hftowers > %f)",edge[i]);

    //if(i==0) bin += Form("(hftowers > %f)",edge[i]);
    //else bin += Form("+ (hftowers > %f)",edge[i]);
  }

  cout<<bin<<endl;
  nt_hftowers->SetAlias("bin",bin.data());
  nt_hftowers->Draw("bin");

}
