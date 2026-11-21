#include "TCanvas.h"
#include "TFile.h"
#include "TH1F.h"
#include "TROOT.h"
#include "TString.h"
#include "TStyle.h"

void draw_plots() {

  TFile fin("data/analysis.root", "READ");

  const char *tag[7] = {"all", "pip", "pim", "Kp", "Km", "p", "pbar"};
  const char *tagLatex[7] = {"all charged particles",
                             "#pi^{+}",
                             "#pi^{-}",
                             "K^{+}",
                             "K^{-}",
                             "p",
                             "#bar{p}"};
  TH1F *hN[7], *hPt[7], *hPhi[7], *hEta[7];

  for (int i = 0; i < 7; ++i) {
    const char *name = tag[i];
    hN[i] = fin.Get<TH1F>(Form("N_%s", name));
    hPt[i] = fin.Get<TH1F>(Form("Pt_%s", name));
    hEta[i] = fin.Get<TH1F>(Form("Eta_%s", name));
    hPhi[i] = fin.Get<TH1F>(Form("Phi_%s", name));
  }

  TCanvas *canvas = new TCanvas("canvas", "GridCanvas");
  for (int i = 0; i < 7; ++i) {
    // Wspólne ustawienia
    for (TH1F *h : {hN[i], hPt[i], hPhi[i], hEta[i]}) {
      h->GetXaxis()->CenterTitle();
      h->GetYaxis()->CenterTitle();
      h->GetXaxis()->SetTitleSize(0.04);
      h->GetYaxis()->SetTitleSize(0.04);
      h->GetYaxis()->SetTitle("count");

      h->SetLineColor(kBlue + 3);
      // h->SetLineWidth(2);
      h->SetFillColor(kBlue - 9);
      h->SetFillColorAlpha(kBlue, 0.3); // półprzezroczyste
    }
    canvas->Clear();
    canvas->Divide(2, 2);
    for (int p = 1; p <= 4; ++p)
      canvas->GetPad(p)->SetLeftMargin(0.12);

    canvas->cd(1);
    hN[i]->SetTitle(Form("Multiplicity of %s", tagLatex[i]));
    hN[i]->GetXaxis()->SetTitle("Multiplicity N");
    hN[i]->Draw();

    canvas->cd(2);
    hPt[i]->SetTitle(
        Form("Transverse momentum distribution of %s", tagLatex[i]));
    hPt[i]->GetXaxis()->SetTitle("p_{T} [GeV]");
    hPt[i]->GetYaxis()->SetTitle("count");
    hPt[i]->Draw();

    canvas->cd(3);
    hPhi[i]->SetTitle(Form("Azimuthal angle distribution of %s", tagLatex[i]));
    hPhi[i]->GetXaxis()->SetTitle("#varphi [rad]");
    hPhi[i]->Draw();

    canvas->cd(4);
    hEta[i]->SetTitle(Form("Pseudorapidity distribution of %s", tagLatex[i]));
    hEta[i]->GetXaxis()->SetTitle("#eta");
    hEta[i]->GetYaxis()->CenterTitle();
    hEta[i]->Draw();

    const char *name = i == 0   ? "plots.pdf("
                       : i == 6 ? "plots.pdf)"
                                : "plots.pdf";
    canvas->Print(name, Form("Title:%s", tag[i]));
  }
}
