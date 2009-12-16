{

   // rootlogon.C for dNdeta 
   // Andre S. Yoon (Dec 04 2009)
   // common style is collected here

   //Error handeling
   gStyle->SetErrorX(0); // remove horizontal error bar
   
   //Opt style
   gStyle->SetOptFit(1); 
   gStyle->SetOptStat(0);                                                                                                                                   
   gStyle->SetOptTitle(0);

   //Canvas style
   gStyle->SetCanvasColor(0);
   gStyle->SetCanvasBorderMode(0);
   gStyle->SetCanvasBorderSize(0);

   // Pad style
   gStyle->SetPadTickX(1);
   gStyle->SetPadTickY(1);
   //gStyle->SetPadLeftMargin(0.18); 
   gStyle->SetPadLeftMargin(0.21);    
   gStyle->SetPadRightMargin(0.04); 
   gStyle->SetPadTopMargin(0.05); 
   gStyle->SetPadBottomMargin(0.145); 

   // Frame style
   gStyle->SetFrameLineWidth(2.0);  

   // Font options - 22, 

   // Label style
   gStyle->SetLabelFont(42,"XYZ");
   //gStyle->SetLabelSize(0.045,"XYZ");
   //gStyle->SetLabelSize(0.055,"XYZ");  
   gStyle->SetLabelSize(0.059,"XYZ"); 
   //gStyle->SetLabelOffset(0.01,"X");
   //gStyle->SetLabelOffset(0.02,"X");
   
   //gStyle->SetLabelOffset(0.02,"Y");
   //gStyle->SetLabelOffset(0.001,"X"); 
   gStyle->SetLabelOffset(0.015,"Y");

   // Title style
   gStyle->SetTitleFont(62,"XYZ");
   gStyle->SetTitleColor(0);
   gStyle->SetTitleBorderSize(0);
   gStyle->SetTitleXSize(.050); 
   gStyle->SetTitleYSize(.050); 
   //gStyle->SetTitleXOffset(1.2);
   gStyle->SetTitleXOffset(1.3); 
   //gStyle->SetTitleYOffset(1.7);
   gStyle->SetTitleYOffset(2.1);
   gStyle->SetTitleColor(1,"XYZ");

   /*
   gStyle->SetPadFrameFillStyle(0); 
   gStyle->SetPadFrameBorderMode(0); 
   gStyle->SetPadFrameFillStyle(0); 
   gStyle->SetPadFrameBorderMode(0); 
   */
}
