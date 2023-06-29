void enemom(){

//abrir o ficheiro
TFile *input = new TFile("sndlhc_+volTarget_0.781e16_SNDG18_02a_01_000.gst.root","read");
TTree *tree = (TTree*)input->Get("gst");

//variaveis
int nf;
double Ev;
double Ef[32766]; //32766
int pdgf;
double El;
int nfp;
int nfn;

//std::cout << "nf " << nf << std::endl;

//associação da minha variavel com o ramo da ttree que estou interssado
tree -> SetBranchAddress("Ev",&Ev);
tree -> SetBranchAddress("Ef",&Ef);
tree -> SetBranchAddress("nf",&nf);
tree -> SetBranchAddress("pdgf",&pdgf);
tree -> SetBranchAddress("El",&El);
tree -> SetBranchAddress("nfn",&nfn);
tree -> SetBranchAddress("nfp",&nfp);


TH2D* h2d = new TH2D("h2d", ";Neutrino Energies(Gev);Hadrons+Leptons Energies(Gev)", 100, 0, 1000, 100, 0, 1000);

for(int iEntry = 0; 32766 >= iEntry ; ++iEntry){ // nao devia ser nf-1 ???
     
     tree->GetEntry(iEntry);
     std::cout << "nf " << nf << std::endl;
     
     double E_lep = El;
     double E_had = 0;

     for(int ihad=0; ihad < nf;ihad++){
        
        E_had += Ef[ihad]; 
     }

     //std::cout << "Os valores de Ev, E_lep, nf  e  são: " << Ev << ", " << E_lep << " e " << iEntry << std::endl;
   
   h2d->Fill(Ev,E_lep+E_had-0.938*(nfp+nfn));
 
 
 //std::cout << "Os valores de Ev, E_lep, nf  e  são: " << Ev << ", " << E_lep << " e " << iEntry << std::endl;
   
}
for(int iEntry = 0; nf >= iEntry ; ++iEntry){
int x;
tree->GetEntry(iEntry);
x=pdgf;
std::cout << "pdg part" << x <<" entrada " << iEntry << " neutrino "<< Ev << " leptao " << El << std::endl;
}


h2d->Draw("colz");

auto f1 = new TF1("f1","x",0,1000);
f1->Draw("same");

}
