//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb  3 16:06:03 2023 by ROOT version 6.22/03
// from TTree EICTree/my EIC tree
// found on file: /w/work5/home/garyp/eic/EpiC/rootfiles/18.t.1000.root
//////////////////////////////////////////////////////////
#pragma once

#ifndef EICAnalyser_h
#define EICAnalyser_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TRef.h>
// Headers needed by this particular selector


class EICAnalyser : public TSelector {
public :
   TTreeReader     fReader;  //!the tree reader
   TTree          *fChain = 0;   //!pointer to the analyzed TTree or TChain

   // Readers to access the data (delete the ones you do not need).
   TTreeReaderValue<unsigned int> fUniqueID = {fReader, "fUniqueID"};
   TTreeReaderValue<unsigned int> fBits = {fReader, "fBits"};
   TTreeReaderValue<Double32_t> x = {fReader, "x"};
   TTreeReaderValue<Double32_t> QSquared = {fReader, "QSquared"};
   TTreeReaderValue<Double32_t> y = {fReader, "y"};
   TTreeReaderValue<Double32_t> WSquared = {fReader, "WSquared"};
   TTreeReaderValue<Double32_t> nu = {fReader, "nu"};
   TTreeReaderValue<Double32_t> yJB = {fReader, "yJB"};
   TTreeReaderValue<Double32_t> QSquaredJB = {fReader, "QSquaredJB"};
   TTreeReaderValue<Double32_t> xJB = {fReader, "xJB"};
   TTreeReaderValue<Double32_t> WSquaredJB = {fReader, "WSquaredJB"};
   TTreeReaderValue<Double32_t> yDA = {fReader, "yDA"};
   TTreeReaderValue<Double32_t> QSquaredDA = {fReader, "QSquaredDA"};
   TTreeReaderValue<Double32_t> xDA = {fReader, "xDA"};
   TTreeReaderValue<Double32_t> WSquaredDA = {fReader, "WSquaredDA"};
   TTreeReaderValue<Int_t> number = {fReader, "number"};
   TTreeReaderValue<Int_t> process = {fReader, "process"};
   TTreeReaderValue<Int_t> nTracks = {fReader, "nTracks"};
   TTreeReaderValue<Double32_t> ELeptonInNucl = {fReader, "ELeptonInNucl"};
   TTreeReaderValue<Double32_t> ELeptonOutNucl = {fReader, "ELeptonOutNucl"};
   TTreeReaderArray<unsigned int> particles_fUniqueID = {fReader, "particles.fUniqueID"};
   TTreeReaderArray<unsigned int> particles_fBits = {fReader, "particles.fBits"};
   TTreeReaderArray<unsigned short> particles_I = {fReader, "particles.I"};
   TTreeReaderArray<Int_t> particles_KS = {fReader, "particles.KS"};
   TTreeReaderArray<Int_t> particles_id = {fReader, "particles.id"};
   TTreeReaderArray<unsigned short> particles_orig = {fReader, "particles.orig"};
   TTreeReaderArray<unsigned short> particles_orig1 = {fReader, "particles.orig1"};
   TTreeReaderArray<unsigned short> particles_daughter = {fReader, "particles.daughter"};
   TTreeReaderArray<unsigned short> particles_ldaughter = {fReader, "particles.ldaughter"};
   TTreeReaderArray<Double_t> particles_px = {fReader, "particles.px"};
   TTreeReaderArray<Double_t> particles_py = {fReader, "particles.py"};
   TTreeReaderArray<Double_t> particles_pz = {fReader, "particles.pz"};
   TTreeReaderArray<Double32_t> particles_E = {fReader, "particles.E"};
   TTreeReaderArray<Double32_t> particles_m = {fReader, "particles.m"};
   TTreeReaderArray<Double32_t> particles_pt = {fReader, "particles.pt"};
   TTreeReaderArray<Double_t> particles_xv = {fReader, "particles.xv"};
   TTreeReaderArray<Double_t> particles_yv = {fReader, "particles.yv"};
   TTreeReaderArray<Double_t> particles_zv = {fReader, "particles.zv"};
   TTreeReaderArray<Int_t> particles_parentId = {fReader, "particles.parentId"};
   TTreeReaderArray<Double32_t> particles_p = {fReader, "particles.p"};
   TTreeReaderArray<Double32_t> particles_theta = {fReader, "particles.theta"};
   TTreeReaderArray<Double32_t> particles_phi = {fReader, "particles.phi"};
   TTreeReaderArray<Double32_t> particles_rapidity = {fReader, "particles.rapidity"};
   TTreeReaderArray<Double32_t> particles_eta = {fReader, "particles.eta"};
   TTreeReaderArray<Double32_t> particles_z = {fReader, "particles.z"};
   TTreeReaderArray<Double32_t> particles_xFeynman = {fReader, "particles.xFeynman"};
   TTreeReaderArray<Double32_t> particles_thetaGamma = {fReader, "particles.thetaGamma"};
   TTreeReaderArray<Double32_t> particles_ptVsGamma = {fReader, "particles.ptVsGamma"};
   TTreeReaderArray<Double32_t> particles_thetaGammaHCM = {fReader, "particles.thetaGammaHCM"};
   TTreeReaderArray<Double32_t> particles_ptVsGammaHCM = {fReader, "particles.ptVsGammaHCM"};
   TTreeReaderArray<Double32_t> particles_phiPrf = {fReader, "particles.phiPrf"};
   TTreeReaderArray<TRef> particles_event = {fReader, "particles.event"};


   EICAnalyser(TTree * /*tree*/ =0) { }
   virtual ~EICAnalyser() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   virtual Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { fReader.SetEntry(entry); return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();

   ClassDef(EICAnalyser,0);

};

#endif

#ifdef EICAnalyser_cxx
void EICAnalyser::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the reader is initialized.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   fReader.SetTree(tree);
}

Bool_t EICAnalyser::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}


#endif // #ifdef EICAnalyser_cxx
