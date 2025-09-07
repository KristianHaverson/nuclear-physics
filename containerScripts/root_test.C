void root_test() {
    // Create a histogram
    TH1F *h = new TH1F("h", "Gaussian histogram", 100, -5, 5);
    for (int i = 0; i < 10000; ++i) {
        h->Fill(gRandom->Gaus(0, 1));
    }
    h->Draw();

    // Fit a Gaussian
    h->Fit("gaus");

    gSystem->ProcessEvents(); // Keep GUI responsive
}
