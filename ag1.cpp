void ag1(){

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

//massa do muao e velocidade da luz;

double mmuao = 0.1057;
//double c = 299792458;

//Energia


double Ev;
double Ef[32766]; //32766
int pdgf;
double El;
int nfp;
int nfn;
bool cc;
int neu;

//Set do adresses
tree -> SetBranchAddress("neu",&neu);
tree -> SetBranchAddress("cc",&cc);
tree -> SetBranchAddress("Ev",&Ev);
tree -> SetBranchAddress("Ef",&Ef);
tree -> SetBranchAddress("pdgf",&pdgf);
tree -> SetBranchAddress("El",&El);
tree -> SetBranchAddress("nfn",&nfn);
tree -> SetBranchAddress("nfp",&nfp);
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

int i=tree -> GetEntries();

TH2D* h2d = new TH2D("h2d", ";Energy of the Lepton (Gev/c);Energy Momentum of the JetGev/c)", 300, 0 , 0, 300, 0 , 0);

//princher ptot x,y,z
for(int ientry = 0; i >= ientry ; ++ientry){
    
    tree->GetEntry(ientry);
    if((fabs(neu)==14) && (cc == true)){
    
    //dame o momento total para os jatos
    double ptotz=0;
    double ptoty=0;
    double ptotx=0;
    
    //modulos dos leptoes e neutrao
    double modv = sqrt(pxv*pxv+pyv*pyv+pzv*pzv);
    double modl = sqrt(pxl*pxl+pyl*pyl+pzl*pzl);

    double pmx; //modulo calculado para x
    double pmy; // modulo calculad para y

    double teta;
    double phi;
    
    /*
    \\variaveis primeira tentetiva
    double c;
    double pmx; //modulo calculado para x
    double pmy; // modulo calculad para y
    */
    
    //momento trnaverse variables 

    double pj;
    double pjv;
    double pjt;

    double pl;
    double plv;
    double plt;

    double E_jet = 0;
    double E_l=0;
    double E_v = 0;

     for(int ia=0; ia < nf;ia++){
        
        E_jet += Ef[ia]; 
     }


     for(int ihad=0; ihad < nf ;ihad++){
        ptotz += pzf[ihad]; 
        ptotx += pxf[ihad];
        ptoty += pyf[ihad];
     }


    double modj=sqrt(ptotx*ptotx+ptoty*ptoty+ptotz*ptotz);
   
    
    double a1=(pxv*pxl + pyv*pyl + pzv*pzl)/(sqrt(pxv*pxv+pyv*pyv+pzv*pzv)*sqrt(pxl*pxl+pyl*pyl+pzl*pzl));
    double a2= (pxv*ptotx + pyv*ptoty + pzv*ptotz)/(sqrt(pxv*pxv+pyv*pyv+pzv*pzv)*sqrt(ptotx*ptotx+ptoty*ptoty+ptotz*ptotz));
    
    teta = acos(a1);
    phi= acos (a2);

    //std::cout << "a1= " << a1 <<" a2= " << a2 << std::endl;

    pjt = abs(modj*sin(phi));
    pjv = abs(modj*cos(phi));


    pl =abs(pjt/sin(teta));
    plv = abs(pl*cos(teta));
    plt = abs(pl*sin(teta));
    
    E_l = sqrt(mmuao*mmuao + pl*pl);
    E_v = sqrt((plv+pjv)*(plv+pjv));//assumindo massa do neutrino despresavel
    
    //para a energia
    //h2d->Fill(Ev , E_jet+E_l-0.938*(nfp+nfn));

    //para a o memento na direção do neutrino
    //h2d->Fill(modl,pl);

    h2d -> Fill(El,E_l);

    }
}
auto f1 = new TF1("f1","x",-200,5000);


h2d->Draw("colz");
f1->Draw("same");
}

// coisas que reparei que o valor de pmy e pmx é muito maoires que o que deveria dar não sei porque???