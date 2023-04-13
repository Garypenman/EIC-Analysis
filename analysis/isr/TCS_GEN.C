// modified from
// https://github.com/eic/eicsmeardetectors#analyze-the-tree
// https://github.com/eic/eic-smear/blob/master/scripts/read.cxx
// couldn't really find any other examples

{
  // load eic smear libraries
  gSystem->Load("libeicsmear");

// read in root file output from eic after passing epic text file to iT
TFile *myFile = new TFile("/w/work5/home/garyp/eic/EpiC/rootfiles/18.t.1000.root"); //truth
//TFile *myfile = new TFile("TCS_gen_18x275m_s800.root"); 
TTree *mc= (TTree*)myFile->Get("EICTree"); // get the tree from the root file

// set up input event  buffer
erhic::EventMC* inEvent(NULL);
mc->SetBranchAddress("event",&inEvent);

TLorentzVector q, q_prime, eIn, pIn, eOut, gamma, pOut, gammaStar, decayLepton1, decayLepton2, missing, inv, t;
Double_t pmom, emom, mp, t1, l2_mom, l1_mom, miss_mass;
float decayLepton1_pT, decayLepton1_eta, decayLepton2_pT, decayLepton2_eta, proton_eta, gamma_eta, proton_theta, dL1_theta, dL2_theta, electron_eta, Q2, Q2_prime, xb;
//cout<<"here"<<endl;
mp = 0.938; // mass of proton

// histograms
///////////////////////////////////////////////////////
TH1D *h0_1_gen = new TH1D("h0_1_gen","#eta_{e^{-}}",50,-10,0);
h0_1_gen->GetXaxis()->SetTitle("#eta_{e^{-}}");
h0_1_gen->GetYaxis()->SetTitle("Counts");

TH1D *h0_2_gen = new TH1D("h0_2_gen","#eta_{#gamma*}",50,-10,10);
h0_2_gen->GetXaxis()->SetTitle("#eta_{#gamma*}");
h0_2_gen->GetYaxis()->SetTitle("Counts");

TH1D *h3_gen = new TH1D("h3_gen","#eta_{p'}",50,6.2,8.4);
h3_gen->GetXaxis()->SetTitle("#eta_{p'}");
h3_gen->GetYaxis()->SetTitle("Counts");

TH1D *h4_gen = new TH1D("h4_gen", "Q^{2}", 50, 0, 50);
h4_gen->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
h4_gen->GetYaxis()->SetTitle("Counts L=10 fb^{-1}");

TH1D *h5_gen = new TH1D("h5_gen", "x_{B} (#tau)", 50, 0, 0.02);
h5_gen->GetXaxis()->SetTitle("x_{B} (#tau)");
h5_gen->GetYaxis()->SetTitle("Counts L=10 fb^{-1}");

TH1D *h6_gen = new TH1D("h6_gen", "Q^{2}'", 50, 2, 20);
h6_gen->GetXaxis()->SetTitle("Q^{2}' (GeV^{2})");
h6_gen->GetYaxis()->SetTitle("Counts L=10 fb^{-1}");

TH1D *h10_gen = new TH1D("h10_gen", "-t", 50 ,0, 1);
h10_gen->GetXaxis()->SetTitle("-t (GeV^{2})");
h10_gen->GetYaxis()->SetTitle("Counts L=10 fb^{-1}");


TH2D *h7_gen = new TH2D("h7_gen", "-t vs x_{B}", 50,  0, 0.02, 50, 0, 1);
h7_gen->GetYaxis()->SetTitle("-t (GeV^{2})");
h7_gen->GetXaxis()->SetTitle("x_{B}");

TH2D *h2_gen = new TH2D("h2_gen", "Q'^{2} vs x_{B}", 50, 0, 0.02, 50, 2, 20);
h2_gen->GetXaxis()->SetTitle("x_{B}");
h2_gen->GetYaxis()->SetTitle("Q'^{2} (GeV^{2})");

TH2D *h9_gen= new TH2D("h9_gen","Q'^{2} vs -t", 50, 0, 1, 50, 2, 20);
h9_gen->GetYaxis()->SetTitle("Q'^{2} (GeV^{2})");
h9_gen->GetXaxis()->SetTitle("-t (GeV^{2})");

TH1D *h13 = new TH1D("h13", "Phi", 100, -7, 7);

TH1D *eIn_hist = new TH1D("eIn_hist", "eIn", 2000, -50, 50);
TH1D *head_pOut_hist = new TH1D("head_pOut_hist", "head_pOut", 2000, -30, 300);
TH1D *inv_hist = new TH1D("inv_hist", "inv", 2000, -100, 100);
TH1D *mm = new TH1D("mm", "missing_mass", 2000, -10, 10);


//final state angle plots
//
TH1D *prot_theta_gen = new TH1D("prot_theta_gen", "Scattered Proton Theta", 50, -180, 180);
TH1D *dl1_theta_gen = new TH1D("dl1_theta_gen", "Electron Theta", 50, -180, 180);
TH1D *dl2_theta_gen = new TH1D("dl2_theta_gen", "Positron Theta", 50, -180, 180);
TH1D *dl1_eta_gen = new TH1D("dl1_eta_gen", "Electron eta", 50, -10, 10);
TH1D *dl2_eta_gen = new TH1D("dl2_eta_gen", "Positron eta", 50, -10, 10);
TH1D *dl1_P_gen = new TH1D("dl1_P_gen", "Electron Momentum", 50, -10, 30);
TH1D *dl2_P_gen = new TH1D("dl2_P_gen", "Positron Momentum", 50, -10, 30);
TH1D *P_P_gen = new TH1D("P_P_gen_gen", "Scattered Proton  Momentum", 50, 200, 300);
  
//////////////////////////////////////////////////////
// event loop
for(long iEvent=0; iEvent < mc->GetEntries(); iEvent++){
    if(mc->GetEntry(iEvent) <=0) break;
    //paricle loop
    for(int particle=0; particle<inEvent->GetNTracks(); particle++){
      const Particle* inParticle = inEvent->GetTrack(particle);
      if(inParticle == NULL) continue;
      // functions to get particle info:
      // https://eic.github.io/doxygen/db/db19/erhic_2ParticleMC_8h_source.html

      //cout << "on particle inc " << particle
      	 //  << " particle index " << inParticle->GetIndex()
      	 //  << " parent index " << inParticle->GetParentIndex()
      	//   << " no of children " << inParticle->GetNChildren() << endl;
    //  cout << "PID " << inParticle->GetPdgCode() << endl;
// 1= BEAM E
//2 = BEAM P 
//3 = SCATTERED E
// 4 = REAL PHOTON (PARENT IS ELECTRON)
// 5 = VIRTUAL PHOTON (PARENT IS PROTON)
// 6 = SCATTERED PROTON
//7 = DECAY ELECTRON
//8 = DECAY POSITRON
  // loop through the particles and fille the histos for each type
     
      // beam electron
     if(inParticle->GetIndex()==1 && inParticle->GetPdgCode()==11){
       emom = (sqrt(pow(inParticle->GetPx(),2)+pow(inParticle->GetPy(),2)+pow(inParticle->GetPz(),2)));
       eIn.SetPxPyPzE(inParticle->GetPx(), inParticle->GetPy(), inParticle->GetPz(), emom);
     }// beam electron

     // beam proton
     if(inParticle->GetIndex()==2 && inParticle->GetPdgCode()==2212){
       pmom = (sqrt(pow(inParticle->GetPx(),2)+pow(inParticle->GetPy(),2)+pow(inParticle->GetPz(),2)));
       pIn.SetPxPyPzE(inParticle->GetPx(), inParticle->GetPy(), inParticle->GetPz(), (sqrt((mp*mp) + (pmom*pmom))));
     }// beam proton

     // Scattered electron
     //if(inParticle->GetIndex()==3 && inParticle->GetPdgCode()==11){
     //}// scattered electron

     // real photon
     //if(inParticle->GetIndex()==4 && inParticle->GetPdgCode()==22){
     //}// real photon

     // virtual photon 
     //if(inParticle->GetIndex()==5 && inParticle->GetPdgCode()==22){
     //}// virtual photon
 
     // scattered proton
     if(inParticle->GetIndex()==6 && inParticle->GetPdgCode()==2212){
       pmom = (sqrt(pow(inParticle->GetPx(),2)+pow(inParticle->GetPy(),2)+pow(inParticle->GetPz(),2)));
       pOut.SetPxPyPzE(inParticle->GetPx(), inParticle->GetPy(), inParticle->GetPz(), (sqrt((mp*mp) + (pmom*pmom))));
     }// scattered proton

   // decay electron
     if(inParticle->GetIndex()==7 && inParticle->GetPdgCode()==11){
       l1_mom = (sqrt(pow(inParticle->GetPx(),2)+pow(inParticle->GetPy(),2)+pow(inParticle->GetPz(),2)));
       decayLepton1.SetPxPyPzE(inParticle->GetPx(), inParticle->GetPy(), inParticle->GetPz(),l1_mom);//tinymass
     }// scattered proton

   // decay positron
     if(inParticle->GetIndex()==8 && inParticle->GetPdgCode()==-11){
       l2_mom = (sqrt(pow(inParticle->GetPx(),2)+pow(inParticle->GetPy(),2)+pow(inParticle->GetPz(),2)));
       decayLepton2.SetPxPyPzE(inParticle->GetPx(), inParticle->GetPy(), inParticle->GetPz(),l2_mom);//tinymass
     }// scattered proton

    inv = decayLepton1 + decayLepton2;
    missing = (eIn + pIn - pOut - inv); //scattered electron
    q  = (eIn - missing); //initial - scattered electron 4 mom for electron = initial photon
    q_prime = inv;
    miss_mass = missing.M2();

    gamma_eta = inv.Eta();
    electron_eta = missing.Eta();
    decayLepton1_eta = decayLepton1.Eta();
    dL1_theta = decayLepton1.Phi();
    decayLepton2_eta = decayLepton2.Eta();
    dL2_theta = decayLepton2.Phi();
    proton_eta = pOut.Eta();
    proton_theta = pOut.Phi();

//cout<<"here"<<endl;

    Q2=-1*q.M2();
    Q2_prime = 1*q_prime.M2();
    float s = (pIn+q).M2();
    xb=Q2_prime/(s-(mp*mp));
    t = (pOut - pIn);
    t1 = -1*t.M2();


     TVector3 lep_plane = ((decayLepton1.Vect()).Cross(decayLepton2.Vect()));
     TVector3 had_plane = ((q.Vect()).Cross(pOut.Vect())); //cross product of q vector and p' gives vector describing hadronic plane

 //Calculating Phi - angle between leptonic and hadronic plane
    double Phi;
    double sign = ( lep_plane.Unit() ).Cross( had_plane.Unit() ).Dot( (q.Vect()).Unit() );
    sign = fabs(sign);

    double sinb2 = ( ( lep_plane.Unit()).Cross( had_plane.Unit() ) ).Mag();
    double cosb2 = ( lep_plane.Unit() ).Dot( had_plane.Unit() );

    Phi = atan2(sign*sinb2, cosb2);
    //if( Phi < 0. ) Phi = Phi + 2.*TMath::Pi(); //negative direction redefined as 50-360

 }//particle loop

if(Q2_prime<20 && Q2_prime > 2 && t1 > 0 && t1 < 1 && xb > 0 && xb < 0.02){  //if(Q2_prime < 12.25){
	eIn_hist->Fill(eIn.P());
 	head_pOut_hist->Fill(pOut.P());
 	inv_hist -> Fill(inv.M());
	h2_gen->Fill(xb,Q2_prime);
 	h7_gen->Fill(xb,t1);
 	h9_gen->Fill(t1,Q2_prime);

    	h4_gen->Fill(Q2);
    	h5_gen->Fill(xb);
    	h10_gen->Fill(t1);
    	h6_gen->Fill(Q2_prime);


    	h0_1_gen->Fill(electron_eta); //commented out for now and replaced with the geometry hist above to get a look at the roman pots geometry and see where the beam is as a visual/sense check
    	h0_2_gen->Fill(gamma_eta);
    	h3_gen->Fill(proton_eta);
    	mm->Fill(miss_mass);
P_P_gen->Fill(pOut.P());
prot_theta_gen->Fill(180*TMath::Pi()*proton_theta);
dl1_theta_gen->Fill(180*TMath::Pi()*dL1_theta);
dl1_eta_gen->Fill(decayLepton1_eta);
dl1_P_gen->Fill(decayLepton1.P());
dl2_theta_gen->Fill(180*TMath::Pi()*dL2_theta);
dl2_eta_gen->Fill(decayLepton2_eta);
dl2_P_gen->Fill(decayLepton2.P());



    }  
 // if(xb<0.1 && xb>0.0025 && Q2_prime > 2 && Q2_prime < 12.25 && t1 < 1 && t1 > 0 )h13->Fill(Phi);
}// event loop
TCanvas* c1 = new TCanvas("c1","",2000,1000); // Create canvas
c1->cd();
//gPad->SetLogy();
h10_gen->Sumw2();
h10_gen->Draw("he");
TCanvas* c14 = new TCanvas("c14", "", 2000, 1000);//canvas for final state plots

c14->cd();
//gStyle->SetOptStat(1111);
c14->Divide(3,3);
c14->cd(1);
prot_theta_gen->Draw();
c14->cd(2);
h3_gen->Draw();
c14->cd(3);
P_P_gen->Draw();
c14->cd(4);
dl1_theta_gen->Draw();
c14->cd(5);
dl1_eta_gen->Draw();
c14->cd(6);
dl1_P_gen->Draw();
c14->cd(7);
dl2_theta_gen->Draw();
c14->cd(8);
dl2_eta_gen->Draw();
c14->cd(9);
dl2_P_gen->Draw();
//c14->Print("/home/kayleighg/Documents/ECCE/ROOTFILES/Plots/18X275_high_acc_hel_minus_1M/18x275_allfinalstate_GEN.pdf");

//TFile outfile1("/home/kayleighg/Documents/ECCE/ROOTFILES/GEN_final_states.root","RECREATE");

//prot_theta_gen->Write();
//h3_gen->Write();
//P_P_gen->Write();
//dl1_theta_gen->Write();
//dl1_eta_gen->Write();
//dl1_P_gen->Write();
//dl2_theta_gen->Write();
//dl2_eta_gen->Write();
//dl2_P_gen->Write();

//outfile1.Close();

//TFile outfile("/home/kayleighg/Documents/ECCE/ROOTFILES/Gen_hists_18x275_fixed_ranges.root", "RECREATE");

//h0_1_gen->Write();
//h0_2_gen->Write();
//h2_gen->Write();
//h3_gen->Write();
//h4_gen->Write();
//h5_gen->Write();
//h6_gen->Write();
//h7_gen->Write();
//h9_gen->Write();
//h10_gen->Write();
//mm->Write();
//eIn_hist->Write();
//head_pOut_hist->Write();
//inv_hist -> Write();
//c1->Print("/home/kayleighg/Documents/ECCE/ECCE_ANALYSIS_SCRIPTS/t_gen.pdf");
//outfile.Close();

}// macro end
/*
on particle inc 0 particle index 1 parent index 0 no of children 0
PID 11 BEAM E
on particle inc 1 particle index 2 parent index 0 no of children 0
PID 2212 BEAM P 
on particle inc 2 particle index 3 parent index 1 no of children 0
PID 11 SCATTERED E
on particle inc 3 particle index 4 parent index 1 no of children 2
PID 22 REAL PHOTON (PARENT IS ELECTRON)
on particle inc 4 particle index 5 parent index 2 no of children 2
PID 22 VIRTUAL PHOTON (PARENT IS PROTON)
on particle inc 5 particle index 6 parent index 2 no of children 0
PID 2212 SCATTERED PROTON
on particle inc 6 particle index 7 parent index 5 no of children 0
PID 11 DECAY ELECTRON
on particle inc 7 particle index 8 parent index 5 no of children 0
PID -11 DECAY POSITRON

 */



