#include "Pythia8/Pythia.h"
#include "TFile.h"
#include "TTree.h"
#include <Pythia8/Basics.h>
#include <Pythia8/Event.h>
#include <Pythia8/NucleonExcitations.h>
using namespace Pythia8;
int main(int argc, char *argv[]) {
  Pythia pythia;
  pythia.readFile(argv[1]);
  if (!pythia.init())
    return 1;


  TFile hfile("data/events.root", "RECREATE", "Finalne naladowane czastki");

  std::vector<int> id;
  std::vector<float> pt, eta, phi;
  TTree tree("events", "pp 13.6 TeV");
  tree.Branch("id", &id);
  tree.Branch("pt", &pt);
  tree.Branch("eta", &eta);
  tree.Branch("phi", &phi);

  int nEvent = pythia.mode("Main:numberOfEvents");
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    pythia.next();
    id.clear();
    pt.clear();
    eta.clear();
    phi.clear();
    for (Particle particle : pythia.event) {
      if (!particle.isFinal() || !particle.isCharged())
        continue;
      id.push_back(particle.id());
      pt.push_back(particle.pT());
      eta.push_back(particle.eta());
      phi.push_back(particle.phi());
    }
    tree.Fill();
  }
  tree.Print();
  hfile.Write();

  pythia.stat();
  return 0;
}
