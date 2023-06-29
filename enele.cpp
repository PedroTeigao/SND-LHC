void enele(){

//abrir o ficheiro
TFile *input = new TFile("sndlhc_+volTarget_0.781e16_SNDG18_02a_01_000.gst.root","read");
TTree *tree = (TTree*)input->Get("gst");

int entradas = tree -> GetEntries();
// da o numero de entrada do gst 
cout << entradas << endl;

double Ev;

int neu;

//associação da minha variavel com o ramo da ttree que estou interssado
tree -> SetBranchAddress("Ev",&Ev);
tree -> SetBranchAddress("neu",&neu);

 //mudar o tituolo da geito
TH1F *histo = new TH1F("histo",";Energy(Gev); N Events",100,0,2500 );
TH1F *histo2 = new TH1F("histo2",";Energy(Gev); N Events",100,0,2500 );
TH1F *histo3 = new TH1F("histo3",";Energy(Gev); N Events",100,0,2500 ); 
TH1F *histo4 = new TH1F("histo4",";Energy(Gev); N Events",100,0,2500 );


for (int iEntry = 0; entradas>= iEntry ; ++iEntry) {
   // Load dos dados para uma dada entrada da arvore
   tree->GetEntry(iEntry);
    // Now, `variable` is set to the value of the branch
    // "gst" na entrada da arvore `iEntry`
    // avalia a minha condição-neste caso o valor absoluto do neutriono dp eletrao
  
  
  
  // na seguinte secção vamos impor as condiçoes de modo a completar os graficos para o eletrao, muao e taU

  
  //neutrino do eletrao
  if(fabs(neu)==12){
  histo2 -> Fill(Ev); 
  } 
  
  //neutrino do muao
  if(fabs(neu)==14){
  histo3 -> Fill(Ev); 
  } 

  //neutrino do tau
  if(fabs(neu)==16){
  histo -> Fill(Ev); 
  } 
  histo->Fill(Ev);

}

//cor do hitograma 1
 histo ->SetLineColor(kBlack);// cores kRed , kGreen+2 , kViolet
 histo2->SetLineColor(kRed);// cores kRed , kGreen+2 , kViolet
 histo3->SetLineColor(kGreen+2);// cores kRed , kGreen+2 , kViolet
 histo4->SetLineColor(kViolet);// cores kRed , kGreen+2 , kViolet
  
histo->Scale(0.0125); 
histo2->Scale(0.0125); 
histo3->Scale(0.0125);
histo4->Scale(0.0125);

//histo->Integral();

cout << histo->Integral() << endl;
cout << histo2->Integral() << endl;
cout << histo3->Integral() << endl;
cout << histo4->Integral() << endl;

    histo->Draw("hist");
    histo2->Draw("samehist");
    histo3->Draw("samehist");
    histo4->Draw("samehist");
//input -> Close(); mata os dados 



TLegend *legend = new TLegend(0.7, 0.7, 0.9, 0.9);
   legend->AddEntry(histo, "Total", "l");
   legend->AddEntry(histo2, "Electron", "l");
   legend->AddEntry(histo3, "Muon", "l");
   legend->AddEntry(histo4, "Tau", "l");
   legend->Draw();

}

