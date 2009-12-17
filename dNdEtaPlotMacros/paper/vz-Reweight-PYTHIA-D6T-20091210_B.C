{
//=========Macro generated from canvas: c9/
//=========  (Fri Dec 11 00:41:05 2009) by ROOT version5.22/00a
   gROOT->Reset();
   gROOT->ProcessLine(".x dndeta_rootlogon.C");
   TCanvas *MyCanvas = new TCanvas("c1", "c1",3,48,550,600);
   MyCanvas->Range(-28.6076,-0.01804519,22.02532,0.1022561);

   double msize = 1.2;

   int mcColor = 2;
   int dataColor = 1;

   TH1 *hvz1 = new TH1F("hvz1","",50,-20,20);
   hvz1->GetXaxis()->SetRange(0,45); // bin range!
   hvz1->SetMaximum(0.11);
   hvz1->SetBinContent(0,0.01672694);
   hvz1->SetBinContent(6,0.0004520796);
   hvz1->SetBinContent(7,0.0004520796);
   hvz1->SetBinContent(8,0.001356239);
   hvz1->SetBinContent(9,0.001356239);
   hvz1->SetBinContent(10,0.002260398);
   hvz1->SetBinContent(11,0.002712477);
   hvz1->SetBinContent(12,0.007685353);
   hvz1->SetBinContent(13,0.01356239);
   hvz1->SetBinContent(14,0.01717902);
   hvz1->SetBinContent(15,0.03345389);
   hvz1->SetBinContent(16,0.03254973);
   hvz1->SetBinContent(17,0.04837251);
   hvz1->SetBinContent(18,0.05696202);
   hvz1->SetBinContent(19,0.07414105);
   hvz1->SetBinContent(20,0.07640145);
   hvz1->SetBinContent(21,0.08544303);
   hvz1->SetBinContent(22,0.079566);
   hvz1->SetBinContent(23,0.08001808);
   hvz1->SetBinContent(24,0.07594936);
   hvz1->SetBinContent(25,0.0619349);
   hvz1->SetBinContent(26,0.06148282);
   hvz1->SetBinContent(27,0.04611212);
   hvz1->SetBinContent(28,0.03481013);
   hvz1->SetBinContent(29,0.03254973);
   hvz1->SetBinContent(30,0.02079566);
   hvz1->SetBinContent(31,0.01898734);
   hvz1->SetBinContent(32,0.005424955);
   hvz1->SetBinContent(33,0.006781193);
   hvz1->SetBinContent(34,0.001808318);
   hvz1->SetBinContent(35,0.0004520796);
   hvz1->SetBinContent(36,0.001808318);
   hvz1->SetBinContent(38,0.0004520796);
   hvz1->SetBinError(0,0.002749893);
   hvz1->SetBinError(6,0.0004520796);
   hvz1->SetBinError(7,0.0004520796);
   hvz1->SetBinError(8,0.0007830248);
   hvz1->SetBinError(9,0.0007830248);
   hvz1->SetBinError(10,0.001010881);
   hvz1->SetBinError(11,0.001107364);
   hvz1->SetBinError(12,0.001863972);
   hvz1->SetBinError(13,0.002476142);
   hvz1->SetBinError(14,0.002786806);
   hvz1->SetBinError(15,0.003888935);
   hvz1->SetBinError(16,0.003836022);
   hvz1->SetBinError(17,0.004676347);
   hvz1->SetBinError(18,0.005074581);
   hvz1->SetBinError(19,0.005789443);
   hvz1->SetBinError(20,0.005877034);
   hvz1->SetBinError(21,0.006215066);
   hvz1->SetBinError(22,0.005997513);
   hvz1->SetBinError(23,0.006014527);
   hvz1->SetBinError(24,0.005859621);
   hvz1->SetBinError(25,0.005291456);
   hvz1->SetBinError(26,0.005272108);
   hvz1->SetBinError(27,0.00456578);
   hvz1->SetBinError(28,0.003966982);
   hvz1->SetBinError(29,0.003836022);
   hvz1->SetBinError(30,0.003066153);
   hvz1->SetBinError(31,0.00292981);
   hvz1->SetBinError(32,0.00156605);
   hvz1->SetBinError(33,0.001750897);
   hvz1->SetBinError(34,0.0009041591);
   hvz1->SetBinError(35,0.0004520796);
   hvz1->SetBinError(36,0.0009041591);
   hvz1->SetBinError(38,0.0004520796);

   hvz1->SetLineColor(dataColor);
   hvz1->SetMarkerColor(dataColor);
   hvz1->SetMarkerStyle(20);
   hvz1->SetMarkerSize(msize);

   hvz1->GetYaxis()->SetNdivisions(405);
   
   hvz1->GetXaxis()->SetTitle("v_{z} (cm)");
   hvz1->GetYaxis()->SetTitle("Arbitrary normalization");
   hvz1->GetXaxis()->CenterTitle();
   hvz1->GetYaxis()->CenterTitle();
   hvz1->Draw("pz");

   
   TH1 *h2vz = new TH1F("h2vz","",50,-20,20);
   h2vz->SetBinContent(0,0.03038759);
   h2vz->SetBinContent(3,7.882643e-06);
   h2vz->SetBinContent(4,3.153057e-05);
   h2vz->SetBinContent(5,7.882643e-06);
   h2vz->SetBinContent(6,0.0001182396);
   h2vz->SetBinContent(7,0.0002680099);
   h2vz->SetBinContent(8,0.00068579);
   h2vz->SetBinContent(9,0.001474054);
   h2vz->SetBinContent(10,0.00217561);
   h2vz->SetBinContent(11,0.004335454);
   h2vz->SetBinContent(12,0.006645068);
   h2vz->SetBinContent(13,0.01127218);
   h2vz->SetBinContent(14,0.01624613);
   h2vz->SetBinContent(15,0.02495645);
   h2vz->SetBinContent(16,0.03518024);
   h2vz->SetBinContent(17,0.04374867);
   h2vz->SetBinContent(18,0.05717281);
   h2vz->SetBinContent(19,0.06686846);
   h2vz->SetBinContent(20,0.07651681);
   h2vz->SetBinContent(21,0.08328012);
   h2vz->SetBinContent(22,0.08476994);
   h2vz->SetBinContent(23,0.084565);
   h2vz->SetBinContent(24,0.07877914);
   h2vz->SetBinContent(25,0.06984022);
   h2vz->SetBinContent(26,0.05950607);
   h2vz->SetBinContent(27,0.0483679);
   h2vz->SetBinContent(28,0.03734796);
   h2vz->SetBinContent(29,0.02634379);
   h2vz->SetBinContent(30,0.01876069);
   h2vz->SetBinContent(31,0.01209197);
   h2vz->SetBinContent(32,0.008000883);
   h2vz->SetBinContent(33,0.004871474);
   h2vz->SetBinContent(34,0.002601272);
   h2vz->SetBinContent(35,0.001316401);
   h2vz->SetBinContent(36,0.0008513255);
   h2vz->SetBinContent(37,0.000331071);
   h2vz->SetBinContent(38,0.0001497702);
   h2vz->SetBinContent(39,7.094379e-05);
   h2vz->SetBinContent(40,3.941321e-05);
   h2vz->SetBinContent(41,1.576529e-05);
   h2vz->SetBinError(0,0.0004894226);
   h2vz->SetBinError(3,7.882643e-06);
   h2vz->SetBinError(4,1.576529e-05);
   h2vz->SetBinError(5,7.882643e-06);
   h2vz->SetBinError(6,3.052935e-05);
   h2vz->SetBinError(7,4.596331e-05);
   h2vz->SetBinError(8,7.35244e-05);
   h2vz->SetBinError(9,0.0001077935);
   h2vz->SetBinError(10,0.0001309563);
   h2vz->SetBinError(11,0.0001848644);
   h2vz->SetBinError(12,0.0002288683);
   h2vz->SetBinError(13,0.0002980848);
   h2vz->SetBinError(14,0.0003578581);
   h2vz->SetBinError(15,0.0004435344);
   h2vz->SetBinError(16,0.0005266054);
   h2vz->SetBinError(17,0.0005872437);
   h2vz->SetBinError(18,0.0006713217);
   h2vz->SetBinError(19,0.0007260167);
   h2vz->SetBinError(20,0.0007766304);
   h2vz->SetBinError(21,0.0008102268);
   h2vz->SetBinError(22,0.0008174419);
   h2vz->SetBinError(23,0.0008164531);
   h2vz->SetBinError(24,0.0007880278);
   h2vz->SetBinError(25,0.0007419741);
   h2vz->SetBinError(26,0.0006848833);
   h2vz->SetBinError(27,0.0006174681);
   h2vz->SetBinError(28,0.000542587);
   h2vz->SetBinError(29,0.0004556959);
   h2vz->SetBinError(30,0.0003845567);
   h2vz->SetBinError(31,0.0003087341);
   h2vz->SetBinError(32,0.0002511336);
   h2vz->SetBinError(33,0.0001959594);
   h2vz->SetBinError(34,0.0001431953);
   h2vz->SetBinError(35,0.0001018662);
   h2vz->SetBinError(36,8.191883e-05);
   h2vz->SetBinError(37,5.108537e-05);
   h2vz->SetBinError(38,3.435965e-05);
   h2vz->SetBinError(39,2.364793e-05);
   h2vz->SetBinError(40,1.762613e-05);
   h2vz->SetBinError(41,1.114774e-05);

   h2vz->SetFillColor(mcColor);
   h2vz->SetLineColor(mcColor);
   h2vz->SetLineStyle(0);
   h2vz->SetMarkerColor(mcColor);
   h2vz->SetMarkerStyle(25);
   h2vz->SetMarkerSize(msize);

   h2vz->GetXaxis()->SetTitle("v_z (cm)");
   h2vz->GetYaxis()->SetTitle("Arbitrary normalization");
   h2vz->Draw("same");

  

   //TLegend *leg = new TLegend(0.5782828,0.7473118,0.9772727,0.9462366,NULL,"brNDC");
   //TLegend *leg = new TLegend(0.6,0.77,0.998,0.94,NULL,"brNDC"); 
   TLegend *leg = new TLegend(0.64,0.76,1.0,0.88,NULL,"brNDC");
   leg->SetBorderSize(0);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(0);
   leg->SetFillStyle(0);

   TLegendEntry *entry=leg->AddEntry("hvz1","Run 123596","p");
   entry->SetLineColor(1);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(1);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(msize);

   entry=leg->AddEntry("h2vz","PYTHIA D6T","p");
   entry->SetLineColor(2);
   entry->SetLineWidth(1);
   entry->SetMarkerColor(2);
   entry->SetMarkerStyle(20);
   entry->SetMarkerSize(msize);
   leg->Draw();

   TLatex *tex = new TLatex(9.92,0.102,"CMS");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   tex = new TLatex(-19.,0.102,"(b)");
   tex->SetTextSize(0.04);
   tex->SetLineWidth(2);
   tex->Draw();

   MyCanvas->Print("Vz_PYTHIA_Run123596_B.eps");
   MyCanvas->Print("Vz_PYTHIA_Run123596_B.pdf");
   MyCanvas->Print("Vz_PYTHIA_Run123596_B.gif");

   /*
   c9->Modified();
   c9->cd();
   c9->SetSelected(c9);
   */
}
