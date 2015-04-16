#define MyAnalysis_cxx
// The class definition in MyAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.

// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// Root > T->Process("MyAnalysis.C")
// Root > T->Process("MyAnalysis.C","some options")
// Root > T->Process("MyAnalysis.C+")
//

#include "MyAnalysis.h"
#include <iostream>
#include <TH1F.h>
#include <TLatex.h>

using namespace std;

void MyAnalysis::BuildEvent() {
   
   Muons.clear();
   for (int i = 0; i < NMuon; ++i) {
      MyMuon muon(Muon_Px[i], Muon_Py[i], Muon_Pz[i], Muon_E[i]);
      muon.SetIsolation(Muon_Iso[i]);
      muon.SetCharge(Muon_Charge[i]);
      Muons.push_back(muon);
   }
   
   Electrons.clear();
   for (int i = 0; i < NElectron; ++i) {
      MyElectron electron(Electron_Px[i], Electron_Py[i], Electron_Pz[i], Electron_E[i]);
      electron.SetIsolation(Electron_Iso[i]);
      electron.SetCharge(Electron_Charge[i]);
      Electrons.push_back(electron);
   }
   
   Photons.clear();
   for (int i = 0; i < NPhoton; ++i) {
      MyPhoton photon(Photon_Px[i], Photon_Py[i], Photon_Pz[i], Photon_E[i]);
      photon.SetIsolation(Photon_Iso[i]);
      Photons.push_back(photon);
   }
   
   Jets.clear();
   for (int i = 0; i < NJet; ++i) {
      MyJet jet(Jet_Px[i], Jet_Py[i], Jet_Pz[i], Jet_E[i]);
      jet.SetBTagDiscriminator(Jet_btag[i]);
      jet.SetJetID(Jet_ID[i]);
      Jets.push_back(jet);
   }
   
   hadB.SetXYZM(MChadronicBottom_px, MChadronicBottom_py, MChadronicBottom_pz, 4.8);
   lepB.SetXYZM(MCleptonicBottom_px, MCleptonicBottom_py, MCleptonicBottom_pz, 4.8);
   hadWq.SetXYZM(MChadronicWDecayQuark_px, MChadronicWDecayQuark_py, MChadronicWDecayQuark_pz, 0.0);
   hadWqb.SetXYZM(MChadronicWDecayQuarkBar_px, MChadronicWDecayQuarkBar_py, MChadronicWDecayQuarkBar_pz, 0.0);
   lepWl.SetXYZM(MClepton_px, MClepton_py, MClepton_pz, 0.0);
   lepWn.SetXYZM(MCneutrino_px, MCneutrino_py, MCneutrino_pz, 0.0);
   met.SetXYZM(MET_px, MET_py, 0., 0.);
   
   EventWeight *= weight_factor;
   
}

void MyAnalysis::Begin(TTree * /*tree*/) {
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
}

void MyAnalysis::SlaveBegin(TTree * /*tree*/) {
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).
   
   TString option = GetOption();
   
   h_Mmumu = new TH1F("Mmumu", "Invariant di-muon mass", 60, 60, 120);
   h_Mmumu->SetXTitle("m_{#mu#mu}");
   h_Mmumu->SetName("No Cut");
   h_Mmumu->Sumw2();
   histograms.push_back(h_Mmumu);
   histograms_MC.push_back(h_Mmumu);
   
   h_NMuon = new TH1F("NMuon", "Number of muons", 7, 0, 7);
   h_NMuon->SetXTitle("Number of fMuons");
   h_NMuon->SetName("No Cut");
   h_NMuon->Sumw2();
   histograms.push_back(h_NMuon);
   histograms_MC.push_back(h_NMuon);

   h_Melel = new TH1F("Melel", "Invariant di-electron mass", 60, 60, 120);
   h_Melel->SetXTitle("m_{ee}");
   h_Melel->SetName("No Cut");
   h_Melel->Sumw2();
   histograms.push_back(h_Melel);
   histograms_MC.push_back(h_Melel);

   h_NElectron = new TH1F("NElectron", "Number of electrons", 7, 0, 7);
   h_NElectron->SetXTitle("Number of Electron");
   h_NElectron->SetName("No Cut");
   h_NElectron->Sumw2();
   histograms.push_back(h_NElectron);
   histograms_MC.push_back(h_NElectron);

   h_Mjeje = new TH1F("Mjeje", "Invariant t-quark mass", 60, 60, 120);
   h_Mjeje->SetXTitle("m_{jets}");
   h_Mjeje->SetName("No Cut");
   h_Mjeje->Sumw2();
   histograms.push_back(h_Mjeje);
   histograms_MC.push_back(h_Mjeje);

   h_NJet = new TH1F("NJet", "Number of jets", 7, 0, 7);
   h_NJet->SetXTitle("Number of jets");
   h_NJet->SetName("No Cut");
   h_NJet->Sumw2();
   histograms.push_back(h_NJet);
   histograms_MC.push_back(h_NJet);

   h_MBjet = new TH1F("NBjet", "Invariant b-quark mass", 60, 60, 120);
   h_MBjet->SetXTitle("m_{jets} included b-quark");
   h_MBjet->SetName("No Cut");
   h_MBjet->Sumw2();
   histograms.push_back(h_MBjet);
   histograms_MC.push_back(h_MBjet);

   h_NBJet = new TH1F("NBJet", "Number of bjets", 7, 0, 7);
   h_NBJet->SetXTitle("Number of jets included b-quark");
   h_NBJet->SetName("No Cut");
   h_NBJet->Sumw2();
   histograms.push_back(h_NBJet);
   histograms_MC.push_back(h_NBJet);

   h_MjejeD = new TH1F("MjejeD", "Invariant t-quark mass", 60, 60, 120);
   h_MjejeD->SetXTitle("m_{jets}");
   h_MjejeD->SetName("Cut : No.Electron&Muon < 2");
   h_MjejeD->Sumw2();
   histograms.push_back(h_MjejeD);
   histograms_MC.push_back(h_MjejeD);

   h_NJetD = new TH1F("NJetD", "Number of jets", 7, 0, 7);
   h_NJetD->SetXTitle("Number of jets");
   h_NJetD->SetName("Cut : No.Electron&Muon < 2");
   h_NJetD->Sumw2();
   histograms.push_back(h_NJetD);
   histograms_MC.push_back(h_NJetD);
   
   h_MBjetD = new TH1F("MBjetD", "Invariant b-quark mass", 60, 60, 120);
   h_MBjetD->SetXTitle("m_{jets} included b-quark");
   h_MBjetD->SetName("Cut : No.Electron&Muon < 2");
   h_MBjetD->Sumw2();
   histograms.push_back(h_MBjetD);
   histograms_MC.push_back(h_MBjetD);

   h_NBJetD = new TH1F("NBJetD", "Number of bjets", 7, 0, 7);
   h_NBJetD->SetXTitle("Number of jets included b-quark");
   h_NBJetD->SetName("Cut : No.Electron&Muon < 2");
   h_NBJetD->Sumw2();
   histograms.push_back(h_NBJetD);
   histograms_MC.push_back(h_NBJetD);

   h_MjejeD2 = new TH1F("MjejeD2", "Invariant t-quark mass", 60, 60, 120);
   h_MjejeD2->SetXTitle("m_{jets}");
   h_MjejeD2->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 2");
   h_MjejeD2->Sumw2();
   histograms.push_back(h_MjejeD2);
   histograms_MC.push_back(h_MjejeD2);

   h_NJetD2 = new TH1F("NJetD2", "Number of jets", 7, 0, 7);
   h_NJetD2->SetXTitle("Number of jets");
   h_NJetD2->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 2");
   h_NJetD2->Sumw2();
   histograms.push_back(h_NJetD2);
   histograms_MC.push_back(h_NJetD2);
   
   h_MBjetD2 = new TH1F("MBjetD2", "Invariant b-quark mass", 60, 60, 120);
   h_MBjetD2->SetXTitle("m_{jets} included b-quark");
   h_MBjetD2->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 2");
   h_MBjetD2->Sumw2();
   histograms.push_back(h_MBjetD2);
   histograms_MC.push_back(h_MBjetD2);

   h_NBJetD2 = new TH1F("NBJetD2", "Number of bjets", 7, 0, 7);
   h_NBJetD2->SetXTitle("Number of jets included b-quark");
   h_NBJetD2->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 2");
   h_NBJetD2->Sumw2();
   histograms.push_back(h_NBJetD2);
   histograms_MC.push_back(h_NBJetD2);

   h_MjejeD3 = new TH1F("MjejeD3", "Invariant t-quark mass", 60, 60, 120);
   h_MjejeD3->SetXTitle("m_{jets}");
   h_MjejeD3->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 1");
   h_MjejeD3->Sumw2();
   histograms.push_back(h_MjejeD3);
   histograms_MC.push_back(h_MjejeD3);

   h_NJetD3 = new TH1F("NJetD3", "Number of jets", 7, 0, 7);
   h_NJetD3->SetXTitle("Number of jets");
   h_NJetD3->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 1");
   h_NJetD3->Sumw2();
   histograms.push_back(h_NJetD3);
   histograms_MC.push_back(h_NJetD3);
   
   h_MBjetD3 = new TH1F("MBjetD3", "Invariant b-quark mass", 60, 60, 120);
   h_MBjetD3->SetXTitle("m_{jets} included b-quark");
   h_MBjetD3->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 1");
   h_MBjetD3->Sumw2();
   histograms.push_back(h_MBjetD3);
   histograms_MC.push_back(h_MBjetD3);

   h_NBJetD3 = new TH1F("NBJetD3", "Number of bjets", 7, 0, 7);
   h_NBJetD3->SetXTitle("Number of jets included b-quark");
   h_NBJetD3->SetName("Cut : No.Electron&Muon < 2, BTaggedJet < 1");
   h_NBJetD3->Sumw2();
   histograms.push_back(h_NBJetD3);
   histograms_MC.push_back(h_NBJetD3);
   
}

Bool_t MyAnalysis::Process(Long64_t entry) {
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // It can be passed to either MyAnalysis::GetEntry() or TBranch::GetEntry()
   // to read either all or the required parts of the data. When processing
   // keyed objects with PROOF, the object is already loaded and is available
   // via the fObject pointer.
   //
   // This function should contain the "body" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.
   
   ++TotalEvents;
   
   GetEntry(entry);
   
   if (TotalEvents % 10000 == 0)
      cout << "Next event -----> " << TotalEvents << endl;
   
   BuildEvent();
   
   double MuonPtCut = 25.; //PtCut : (p = 0.3 * B * r) 로우 핏 영역에서 발생하는 노이즈영역을 삭제.
   double MuonRelIsoCut = 0.10; //RelIsoCut : 
   
   double ElectronPtCut = 15.;
   double ElectronRelIsoCut = 999;

   double JetPtCut = 30.;
   double JetEtaCut = 2.5;
   
   //   cout << "Jets: " << endl;
   //   for (vector<MyJet>::iterator it = Jets.begin(); it != Jets.end(); ++it) {
   //      cout << "pt, eta, phi, btag, id: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->IsBTagged() << ", " << it->GetJetID()
   //      << endl;
   //   }
   //   cout << "Muons: " << endl;
   //   for (vector<MyMuon>::iterator it = Muons.begin(); it != Muons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Electrons: " << endl;
   //   for (vector<MyElectron>::iterator it = Electrons.begin(); it != Electrons.end(); ++it) {
   //      cout << "pt, eta, phi, iso, charge: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", "
   //      << it->GetIsolation() << ", " << it->GetCharge() << endl;
   //   }
   //   cout << "Photons: " << endl;
   //   for (vector<MyPhoton>::iterator it = Photons.begin(); it != Photons.end(); ++it) {
   //      cout << "pt, eta, phi, iso: " << it->Pt() << ", " << it->Eta() << ", " << it->Phi() << ", " << it->GetIsolation()
   //      << endl;
   //   }
   
   
   //////////////////////////////
   // Exercise 1: Invariant Di-Muon mass

   
   int N_IsoMuon = 0;
   MyMuon *muon1, *muon2;
   
   for (vector<MyMuon>::iterator jt = Muons.begin(); jt != Muons.end(); ++jt) {
      if (jt->IsIsolated(MuonRelIsoCut)) {
         ++N_IsoMuon;
         if (N_IsoMuon == 1) muon1 = &(*jt);
         if (N_IsoMuon == 2) muon2 = &(*jt);
      }
   }
   
   h_NMuon->Fill(N_IsoMuon, EventWeight); // It is nocut
   
   if (N_IsoMuon > 1 && triggerIsoMu24) {
      if (muon1->Pt()>MuonPtCut) {
         h_Mmumu->Fill((*muon1 + *muon2).M(), EventWeight);
      }
   }

   int N_IsoElectron = 0;
   MyElectron *electron1, *electron2;
   
	for (vector<MyElectron>::iterator jt = Electrons.begin(); jt != Electrons.end(); ++jt) {
		if (jt->IsIsolated(ElectronRelIsoCut)) {
         ++N_IsoElectron;
         if (N_IsoElectron == 1) electron1 = &(*jt);
         if (N_IsoElectron == 2) electron2 = &(*jt);
  		 }
 	  }
   
   h_NElectron->Fill(N_IsoElectron, EventWeight);
   
   if (N_IsoElectron > 1 && triggerIsoMu24) {
      if (electron1->Pt()>ElectronPtCut) {
         h_Melel->Fill((*electron1 + *electron2).M(), EventWeight);
     		 }
 	  }

   int N_IsBTaggedJet = 0;
   int N_Jet = 0;
   MyJet *bjet1, *bjet2;
   MyJet *jet1, *jet2;

   for (vector<MyJet>::iterator jt = Jets.begin(); jt != Jets.end(); ++jt) {
		if(jt->Pt() > JetPtCut && abs(jt->Eta()) < JetEtaCut ) {
			N_Jet++;			
			if (N_Jet == 1) jet1 = &(*jt);
			if (N_Jet == 2) jet2 = &(*jt);

			if (jt->IsBTagged(2.)) {
				  ++N_IsBTaggedJet;
				  if (N_IsBTaggedJet == 1) bjet1 = &(*jt);
				  if (N_IsBTaggedJet == 2) bjet2 = &(*jt);		
			    }
		}
   }

   h_NBJet->Fill(N_IsBTaggedJet, EventWeight);
   h_NJet->Fill(N_Jet, EventWeight);

   h_MBjet->Fill((*bjet1 + *bjet2).M(), EventWeight);
   h_Mjeje->Fill((*jet1 + *jet2).M(), EventWeight);

	/*(if (N_Jet > 1) {  //trigger~~ : Mu의 Pt가 24보다 큰 것만 가져오겠다.
	   if (jet1->Pt()>JetPtCut) {
	   		h_Mjeje->Fill((*jet1 *jet2).M(), EventWeight);
   		}
	} */ 
   //////////////////////////////
   if (N_IsoElectron + N_IsoMuon <2) return kTRUE; // cutting start!

   h_NBJetD->Fill(N_IsBTaggedJet, EventWeight);
   h_NJetD->Fill(N_Jet, EventWeight);

   h_MBjetD->Fill((*bjet1 + *bjet2).M(), EventWeight);
   h_MjejeD->Fill((*jet1 + *jet2).M(), EventWeight);

   if (N_IsBTaggedJet < 1) return kTRUE;
 
   h_NBJetD2->Fill(N_IsBTaggedJet, EventWeight);
   h_NJetD2->Fill(N_Jet, EventWeight);

   h_MBjetD2->Fill((*bjet1 + *bjet2).M(), EventWeight);
   h_MjejeD2->Fill((*jet1 + *jet2).M(), EventWeight);

   if (N_IsBTaggedJet < 2) return kTRUE;

   h_NBJetD3->Fill(N_IsBTaggedJet, EventWeight);
   h_NJetD3->Fill(N_Jet, EventWeight);

   h_MBjetD3->Fill((*bjet1 + *bjet2).M(), EventWeight);
   h_MjejeD3->Fill((*jet1 + *jet2).M(), EventWeight);

   return kTRUE;
}

void MyAnalysis::SlaveTerminate() {
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.
   
}

void MyAnalysis::Terminate() {
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.
   
}
