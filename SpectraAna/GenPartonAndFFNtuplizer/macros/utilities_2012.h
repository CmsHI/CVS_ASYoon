




TH1D* HistIt(TGraphErrors* tg, double minx, bool verbose, TString name){

  /*
    - Convert TGraph to TH1D (varying x-axis) 
    - "minx" has to be given
  */

  int nbins = tg->GetN();
  const int nlines = nbins;

  double pt[nlines], xsec[nlines];
  double pterr[nlines], xsecerr[nlines];

  for(int i = 0; i<nbins; i++ ){
    tg->GetPoint(i,pt[i],xsec[i]);
    pterr[i] = tg->GetErrorX(i);
    xsecerr[i] = tg->GetErrorY(i);
  }

  double xbins[nlines+1];
  xbins[0] = minx;
  double dx = 0;
  double binbdry = 0;
  for(int k = 0; k<nbins; k++ ){
    if(verbose) cout<<" xaxis["<<k<<"] = "<<xbins[k]<<endl;
    dx = pt[k]-xbins[k];
    binbdry = pt[k]+dx;
    xbins[k+1] = binbdry;
  }
  xbins[nlines] = xbins[nlines-1] + 2.*dx;
  if(verbose) cout<<" xaxis["<<nlines<<"] = "<<xbins[nlines]<<endl;

  TH1D *h = new TH1D("","",nlines,xbins);

  for(int j = 0; j<nbins; j++ ){
    h->SetBinContent(j+1,xsec[j]);
    h->SetBinError(j+1,xsecerr[j]);
  }

  h->SetName(name.Data());
  if(verbose) cout<<"Histogram name = "<<h->GetName()<<endl;

  return h;
}

TH1D* HistIt(TGraphErrors* tg, TH1D* histC, TString name){

  /*
    - Convert TGraph to TH1D
    - Assuming predefined hist
  */

  TH1D *h = (TH1D*) histC->Clone("h");
  h->Reset();
  h->SetName(name.Data());

  int nbins = tg->GetN();
  const int nlines = nbins;

  double pt[nlines], xsec[nlines];
  double pterr[nlines], xsecerr[nlines];

  for(int i = 0; i<nbins; i++ ){
    tg->GetPoint(i,pt[i],xsec[i]);
    pterr[i] = tg->GetErrorX(i);
    xsecerr[i] = tg->GetErrorY(i);
    h->SetBinContent(i+1,xsec[i]);
    h->SetBinError(i+1,xsecerr[i]);
  }


  return h;
}

TH1D* HistItShift(TGraphErrors* tg, TH1D* histC, TString name){

  /*                                                                                                                                                                                                              
    - Convert TGraph to TH1D 
    - Assuming predefined hist
    - FindBin is used to match Xaxis
  */

  TH1D *h = (TH1D*) histC->Clone("h");
  h->Reset();
  h->SetName(name.Data());

  int nbins = tg->GetN();
  const int nlines = nbins;

  double pt[nlines], xsec[nlines];
  double pterr[nlines], xsecerr[nlines];

  for(int i = 0; i<nbins; i++ ){
    tg->GetPoint(i,pt[i],xsec[i]);
    pterr[i] = tg->GetErrorX(i);
    xsecerr[i] = tg->GetErrorY(i);

    int bin = h->GetXaxis()->FindBin(pt[i]);
    h->SetBinContent(bin,xsec[i]);
    h->SetBinError(bin,xsecerr[i]);
  }

  return h;
}


TGraphErrors* TgraphIt(TH1F* hist){

  TGraphErrors *tg;
  int nbins = hist->GetNbinsX();

  const int nlines = nbins;

  float pt[nlines], xsec[nlines];
  float pterr[nlines], xsecerr[nlines];

  for(int i = 0; i<nbins; i++ ){
    pt[i] = hist->GetBinCenter(i+1);
    xsec[i] = hist->GetBinContent(i+1);
    xsecerr[i] = hist->GetBinError(i+1);
    pterr[i] = 0;
  }

  tg = new TGraphErrors(nlines,pt,xsec,pterr,xsecerr);
  return tg;
}

TGraphErrors* TgraphIt(TH1D* hist){

  TGraphErrors *tg;
  int nbins = hist->GetNbinsX();

  const int nlines = nbins;

  float pt[nlines], xsec[nlines];
  float pterr[nlines], xsecerr[nlines];

  for(int i = 0; i<nbins; i++ ){
    pt[i] = hist->GetBinCenter(i+1);
    xsec[i] = hist->GetBinContent(i+1);
    xsecerr[i] = hist->GetBinError(i+1);
    pterr[i] = 0;
  }

  tg = new TGraphErrors(nlines,pt,xsec,pterr,xsecerr);
  return tg;
}

void makeMultiPanelCanvas(TCanvas*& canv,
                          const Int_t columns,
                          const Int_t rows,
                          const Float_t leftOffset,
                          const Float_t bottomOffset,
                          const Float_t leftMargin,
                          const Float_t bottomMargin,
                          const Float_t edge) {
  if (canv==0) {
    Error("makeMultiPanelCanvas","Got null canvas.");
    return;
  }
  canv->Clear();

  TPad* pad[columns][rows];

  Float_t Xlow[columns];
  Float_t Xup[columns];
  Float_t Ylow[rows];
  Float_t Yup[rows];
   Float_t PadWidth =
     (1.0-leftOffset)/((1.0/(1.0-leftMargin)) +
                       (1.0/(1.0-edge))+(Float_t)columns-2.0);
   Float_t PadHeight =
     (1.0-bottomOffset)/((1.0/(1.0-bottomMargin)) +
                         (1.0/(1.0-edge))+(Float_t)rows-2.0);
   Xlow[0] = leftOffset;
   Xup[0] = leftOffset + PadWidth/(1.0-leftMargin);
   Xup[columns-1] = 1;
   Xlow[columns-1] = 1.0-PadWidth/(1.0-edge);

   Yup[0] = 1;
   Ylow[0] = 1.0-PadHeight/(1.0-edge);
   Ylow[rows-1] = bottomOffset;
   Yup[rows-1] = bottomOffset + PadHeight/(1.0-bottomMargin);

   for(Int_t i=1;i<columns-1;i++) {
     Xlow[i] = Xup[0] + (i-1)*PadWidth;
     Xup[i] = Xup[0] + (i)*PadWidth;
   }
   Int_t ct = 0;
   for(Int_t i=rows-2;i>0;i--) {
     Ylow[i] = Yup[rows-1] + ct*PadHeight;
     Yup[i] = Yup[rows-1] + (ct+1)*PadHeight;
     ct++;
   }

   TString padName;
   for(Int_t i=0;i<columns;i++) {
     for(Int_t j=0;j<rows;j++) {
       canv->cd();
       padName = Form("p_%d_%d",i,j);
       pad[i][j] = new TPad(padName.Data(),padName.Data(),
                            Xlow[i],Ylow[j],Xup[i],Yup[j]);
       if(i==0) pad[i][j]->SetLeftMargin(leftMargin);
       else pad[i][j]->SetLeftMargin(0);

       if(i==(columns-1)) pad[i][j]->SetRightMargin(edge);
       else pad[i][j]->SetRightMargin(0);

       if(j==0) pad[i][j]->SetTopMargin(edge);
       else pad[i][j]->SetTopMargin(0);

       if(j==(rows-1)) pad[i][j]->SetBottomMargin(bottomMargin);
       else pad[i][j]->SetBottomMargin(0);

       pad[i][j]->Draw();
       pad[i][j]->cd();
       pad[i][j]->SetNumber(columns*j+i+1);
     }
   }
}

