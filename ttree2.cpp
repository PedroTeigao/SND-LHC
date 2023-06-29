void ttree2(){

//abrir o ficheiro
TFile *input = new TFile("sndlhc_+volTarget_0.781e16_SNDG18_02a_01_000.gst.root","read");

TTree *tree = (TTree*)input->Get("gst");

int entradas = tree -> GetEntries();

// da o numero de entrada do gst 
cout << entradas << endl;

double variavel;

int variavel2;

//associação da minha variavel com o ramo da ttree que estou interssado
tree -> SetBranchAddress("Ev",&variavel);
tree -> SetBranchAddress("neu",&variavel2);

 TH1F *histo = new TH1F("histo","Histogram title;x title;y title",100,0,5000 );
 TH1F *histo2 = new TH1F("histo2","Histogram title;x title;y title",100,0,5000 );


for (int iEntry = 0; entradas>= iEntry ; ++iEntry) {
   // Load dos dados para uma dada entrada da arvore
   tree->GetEntry(iEntry);
  
    // Now, `variable` is set to the value of the branch
   // "gst" na entrada da arvore `iEntry`
  
  // avalia a minha condição-neste caso o valor absoluto do neutriono dp eletrao
  if(fabs(variavel2)==12){
  histo -> Fill(variavel); 
  } 
   histo2->Fill(variavel);
  
  // printf("%f\n", variavel);
}


//cor do hitograma 1
 histo->SetLineColor(kRed);
    
    histo2->Draw();
    histo->Draw("same");
    

//input -> Close(); mata os dados 
}
