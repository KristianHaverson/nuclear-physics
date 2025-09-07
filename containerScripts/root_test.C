#include "TH2D.h"
#include "TCanvas.h"
#include "TRandom.h"
#include "TSystem.h"

void root_test() {
    // Create canvas and histogram
    TCanvas *c = new TCanvas("c", "Live 2D Histogram", 800, 600);
    TH2D *h2 = new TH2D("h2", "Live Gaussian 2D Histogram;X;Y", 
                        100, -5, 5, 100, -5, 5);

    h2->Draw("COLZ"); // draw once

    // Real-time filling
    for (int i = 0; i < 10000; ++i) {
        double x = gRandom->Gaus(0, 1);
        double y = gRandom->Gaus(0, 1);
        h2->Fill(x, y);

        // Update canvas every 50 points for efficiency
        if (i % 50 == 0) {
            c->Modified();
            c->Update();
            gSystem->ProcessEvents(); // keep GUI responsive
        }

        gSystem->Sleep(1); // slow down a bit so you can see it filling
    }

    // Final update
    c->Modified();
    c->Update();
}
