// Headers and Namespaces.
#include "Pythia8/Pythia.h" // Include Pythia headers.
#include <Pythia8/Event.h>
#include <iostream>
using namespace Pythia8;    // Let Pythia8:: be implicit.
int main(int argc, char* argv[]) {                // Begin main program.
  // Set up generation.
  Pythia pythia;                          // Declare a Pythia object
  pythia.readFile(argv[1]);
  // pythia.readString("Top:gg2ttbar = on"); // Switch on process.
  // pythia.readString("Top:qqbar2ttbar = on");
  // pythia.readString("Beams:eCM = 8000."); // 8 TeV CM energy.
  pythia.init(); // Initialize; incoming pp beams is default.

  Hist pT("top transverse momentum", 100, 0., 200.);
  Hist eta("top pseudorapidity", 100, -5., 5.);

  int nEvent = pythia.mode("Main:numberOfEvents");
  for (int iEvent = 0; iEvent < nEvent; ++iEvent) {
    pythia.next();
    int iTop = 0;
    for (Particle particle : pythia.event) {
      if (particle.id() == 6) {
        iTop = particle.id();
      }
    }
    Particle finalTop = pythia.event[iTop];
    cout << "Final Top pT:" << finalTop.pT() << endl;
    pT.fill(finalTop.pT());
    eta.fill(finalTop.eta());

  }
  cout << pT ;
  cout << eta;

  pythia.stat();
  return 0;
}
