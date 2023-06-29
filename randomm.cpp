void randomm(){

TFile *input = new TFile("sndlhc_+volTarget_0.781e16_SNDG18_02a_01_000.gst.root","read");
TTree *tree = (TTree*)input->Get("gst");
TRandom3 * r = new TRandom3();
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

TH2D* h2d = new TH2D("h2d", ";Momentum of the Lepton (Gev/c);Reconstructed Momentum of the JetGev/c)", 300, 0 , 5, 300, 0 , 20);
TH1F* histo = new TH1F("Histo"," ;(Ev-Ev')/Ev;",100,-10,10);

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
    
    teta = acos(a1);// fazer a incerteza do angulo phi
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
    //h2d-> Fill((Ev-(E_jet+E_l-0.938*(nfp+nfn)))/Ev);
    
    
    //variaveis ramdom
    double vf=0;
    double w=0;
    
    
  
      
         double valv= r->Gaus();
         double valv1 = valv*vf;
       
    
         double E_jet1 = E_jet + valv1*E_jet;
    
         double ptotz1 = ptotz + valv1*ptotz; 
         double ptotx1= ptotx + valv1*ptotx;
         double ptoty1 = ptoty + valv1*ptoty;
    
         double modj1=sqrt(ptotx1*ptotx1+ptoty1*ptoty1+ptotz1*ptotz1);
    
         double a11= a1; ;//variar o angulo
         double a22= a2;
         double teta1 = acos(a11) + valv*w*(3.1415926/180) ;
         double phi1= acos (a22) + valv*w*(3.1415926/180);
    
         double pjt1 = abs(modj1*sin(phi1));
         double pjv1 = abs(modj1*cos(phi1));
    
         double pl1 =abs(pjt1/sin(teta1));
         double plv1 = abs(pl1*cos(teta1));
         double plt1 = abs(pl1*sin(teta1));
    
         double E_l1 = sqrt(mmuao*mmuao + pl1*pl1);
         double E_v1 = sqrt((plv1+pjv1)*(plv1+pjv1));//assumindo massa do neutrino despresavel
    
         histo -> Fill((Ev-(E_jet1+E_l1-0.938*(nfp+nfn)))/Ev);
    
    
    }
}
auto f1 = new TF1("f1","x",-200,5000);


histo->Draw("colz");
//f1->Draw("same");
}
