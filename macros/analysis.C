#include "TBranchProxyDirector.h"
#include "TFile.h"
#include "TH1.h"
#include "TString.h"
#include "TTreeReader.h"

#include "TTreeReaderValue.h"
#include "iostream"
#include <ostream>
void analysis() {

  // wczytanie danych
  TFile fin("data/events.root", "READ");

  TTreeReader reader("events", &fin);

  // Wskaźniki na aktualny rekord w gałęzi drzewa
  TTreeReaderValue<std::vector<int>> id(reader, "id");
  TTreeReaderValue<std::vector<float>> pt(reader, "pt");
  TTreeReaderValue<std::vector<float>> eta(reader, "eta");
  TTreeReaderValue<std::vector<float>> phi(reader, "phi");

  // plik wynikowy
  TFile fout("data/analysis.root", "RECREATE");
  fout.cd();

  const char *tag[7] = {"all", "pip", "pim", "Kp", "Km", "p", "pbar"};
  // wektory histogramów dla każdej zmiennej
  TH1F *hN[7], *hPt[7], *hPhi[7], *hEta[7];

  for (int i = 0; i < 7; ++i) {
    const char *name = tag[i];
    hN[i] = new TH1F(Form("N_%s", name), Form("N_%s", name), 400, 0, 400);
    hPt[i] = new TH1F(Form("Pt_%s", name), Form("Pt_%s", name), 100, 0, 10);
    hEta[i] = new TH1F(Form("Eta_%s", name), Form("Eta_%s", name), 100, -5, 5);
    hPhi[i] =
        new TH1F(Form("Phi_%s", name), Form("Phi_%s", name), 64, 0, 3.1415926);
  }

  int processed_events = 0;
  while (reader.Next()) {
    int n[7] = {0, 0, 0, 0, 0, 0, 0}; // zlicza wystąpienia każdej cząstki
    for (int k = 0; k < (*id).size(); ++k) {

      int id_k = (*id)[k];
      bool in[7] = {true,         id_k == 211,  id_k == -211, id_k == 321,
                    id_k == -321, id_k == 2212, id_k == -2212};
      for (int i = 0; i < 7; ++i) {
        if (!in[i])
          continue;
        hEta[i]->Fill((*eta)[k]);
        hPhi[i]->Fill((*phi)[k]);
        hPt[i]->Fill((*pt)[k]);
        n[i]++;
      }
    }
    for (int i = 0; i < 7; ++i)
      hN[i]->Fill(n[i]);
    processed_events++;
  }

  fout.Write();
  std::cout << "Zapisano do " << "data/analysis.root" << std::endl;
  fout.Close();
  fin.Close();
  std::cout << "Przerobiono " << processed_events << " zderzeń" << std::endl;
}
