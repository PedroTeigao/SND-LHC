void valv(){

//abrir o ficheiro
TFile *input = new TFile("sndlhc_+volTarget_0.781e16_SNDG18_02a_01_000.gst.root","read");
TTree *tree = (TTree*)input->Get("gst");


//definir variaveis
int nf;

//momento do neutrino
double pxv;
double pyv;
double pzv;

//momento do leptao
double pxl;
double pyl;
double pzl;

// momentos do elemento do jato 

double pxf[100000];
double pyf[100000];
double pzf[100000];


//Set do adresses

tree -> SetBranchAddress("nf",&nf);
tree -> SetBranchAddress("pxv",&pxv);
tree -> SetBranchAddress("pyv",&pyv);
tree -> SetBranchAddress("pzv",&pzv);
tree -> SetBranchAddress("pxl",&pxl);
tree -> SetBranchAddress("pyl",&pyl);
tree -> SetBranchAddress("pzl",&pzl);
tree -> SetBranchAddress("pxf",&pxf);
tree -> SetBranchAddress("pyf",&pyf);
tree -> SetBranchAddress("pzf",&pzf);

//criação do histogrma 

int i=tree -> GetEntries();

TH2D* h2d = new TH2D("h2d", ";Momento em x do leptao ;Momento em x do jatos", 400, -4,4 , 400, -4, 4);

//preencher o histograma


//momento em z
for(int iEntry = 0; i >= iEntry ; ++iEntry){ 
     
     tree->GetEntry(iEntry);
     double ptot=0;

     for(int ihad=0; ihad < nf ;ihad++){
        
        ptot += pxf[ihad]; 
     }

     
   h2d->Fill(pxl,ptot);
 
 }

 auto f1 = new TF1("f1","-x",-200,5000);


h2d->Draw("colz");
f1->Draw("same");
}