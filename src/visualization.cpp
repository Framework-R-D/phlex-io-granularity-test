#include <TH1F.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <filesystem>
#include <vector>
#include <string>
#include <memory>
#include <iomanip>
#include <iostream>
#include <TText.h>
#include <map>
#include <vector>
#include <utility> // for std::pair
#include <algorithm> // for std::sort
#include <TCanvas.h>
#include <TGraph.h>
#include <TString.h>
#include <TMultiGraph.h>
#include <TAxis.h>

#include "WriterResult.hpp"
#include "ReaderResult.hpp"

using namespace std;

// Function to get the sort order for consistent x-axis ordering
int getSortOrder(const std::string& label) {
    // Remove AOS_ or SOA_ prefix for sorting
    std::string cleanLabel = label;
    if (cleanLabel.find("AOS_") == 0) {
        cleanLabel = cleanLabel.substr(4);
    } else if (cleanLabel.find("SOA_") == 0) {
        cleanLabel = cleanLabel.substr(4);
    }
    
    // Define the desired order
    if (cleanLabel == "event_allDataProduct") return 1;
    if (cleanLabel == "event_perDataProduct") return 2;
    if (cleanLabel == "event_perGroup") return 3;
    if (cleanLabel == "spill_allDataProduct") return 4;
    if (cleanLabel == "spill_perGroup") return 5;
    if (cleanLabel == "topObject_perDataProduct") return 6;
    if (cleanLabel == "topObject_perGroup") return 7;
    if (cleanLabel == "element_allDataProduct") return 8;
    if (cleanLabel == "element_perDataProduct") return 9;
    if (cleanLabel == "element_perGroup") return 10;
    
    // Default for any other labels
    return 999;
}

// Function to sort WriterResult vectors
std::vector<WriterResult> sortWriterResults(const std::vector<WriterResult>& results) {
    std::vector<WriterResult> sorted = results;
    std::sort(sorted.begin(), sorted.end(), 
        [](const WriterResult& a, const WriterResult& b) {
            return getSortOrder(a.label) < getSortOrder(b.label);
        });
    return sorted;
}

// Function to sort ReaderResult vectors
std::vector<ReaderResult> sortReaderResults(const std::vector<ReaderResult>& results) {
    std::vector<ReaderResult> sorted = results;
    std::sort(sorted.begin(), sorted.end(), 
        [](const ReaderResult& a, const ReaderResult& b) {
            return getSortOrder(a.label) < getSortOrder(b.label);
        });
    return sorted;
}

// Function to sort file size vectors
std::vector<std::pair<std::string, double>> sortFileSizes(const std::vector<std::pair<std::string, double>>& fileSizes) {
    std::vector<std::pair<std::string, double>> sorted = fileSizes;
    std::sort(sorted.begin(), sorted.end(), 
        [](const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
            return getSortOrder(a.first) < getSortOrder(b.first);
        });
    return sorted;
}

void visualize_aos_writer_results(const std::vector<WriterResult>& results) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedResults = sortWriterResults(results);

    // Write times bar plot with error bars
    auto hWrite = make_unique<TH1F>("hWriteAOS", "AOS Write Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hWrite->SetFillColor(kRed - 2); // Red color for AOS
    hWrite->SetStats(0);
    hWrite->SetBarWidth(0.6);
    hWrite->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hWrite->SetBinContent(i + 1, sortedResults[i].avg);
        hWrite->SetBinError(i + 1, sortedResults[i].stddev);
        // Remove AOS_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hWrite->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWrite->GetXaxis()->SetLabelSize(0.06);
    hWrite->GetXaxis()->LabelsOption("a");
    hWrite->GetYaxis()->SetLabelSize(0.06);
    auto cWrite = make_unique<TCanvas>("cWriteAOS", "AOS Write Times", 1600, 800);
    cWrite->SetBottomMargin(0.3);
    hWrite->SetMinimum(0);
    hWrite->Draw("BAR E");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxY = hWrite->GetMaximum();
    double offset = maxY * 0.05 + 1;
    for (int i = 1; i <= hWrite->GetNbinsX(); ++i) {
        double yPos = hWrite->GetBinContent(i) + hWrite->GetBinError(i) + offset;
        auto text = make_unique<TText>(hWrite->GetBinCenter(i), yPos, Form("%.1f±%.1f", hWrite->GetBinContent(i), hWrite->GetBinError(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cWrite->SaveAs("../experiments/aos_write_times.pdf");
    cout << "AOS Write times plot saved to ../experiments/aos_write_times.pdf" << endl;
}

void visualize_aos_reader_results(const std::vector<ReaderResult>& results) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedResults = sortReaderResults(results);

    // Cold times bar plot
    auto hCold = make_unique<TH1F>("hColdAOS", "AOS Cold Read Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hCold->SetFillColor(kRed - 2); // Red color for AOS
    hCold->SetStats(0);
    hCold->SetBarWidth(0.6);
    hCold->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hCold->SetBinContent(i + 1, sortedResults[i].cold);
        // Remove AOS_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hCold->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hCold->GetXaxis()->SetLabelSize(0.06);
    hCold->GetXaxis()->LabelsOption("a");
    hCold->GetYaxis()->SetLabelSize(0.06);
    auto cCold = make_unique<TCanvas>("cColdAOS", "AOS Cold Read Times", 1600, 800);
    cCold->SetBottomMargin(0.3);
    hCold->SetMinimum(0);
    hCold->Draw("BAR");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxYCold = hCold->GetMaximum();
    double offsetCold = maxYCold * 0.05 + 1;
    for (int i = 1; i <= hCold->GetNbinsX(); ++i) {
        double yPos = hCold->GetBinContent(i) + offsetCold;
        auto text = make_unique<TText>(hCold->GetBinCenter(i), yPos, Form("%.1f", hCold->GetBinContent(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cCold->SaveAs("../experiments/aos_cold_times.pdf");

    // Warm times bar plot with error bars
    auto hWarm = make_unique<TH1F>("hWarmAOS", "AOS Warm Read Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hWarm->SetFillColor(kRed - 2); // Red color for AOS
    hWarm->SetStats(0);
    hWarm->SetBarWidth(0.6);
    hWarm->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hWarm->SetBinContent(i + 1, sortedResults[i].warmAvg);
        hWarm->SetBinError(i + 1, sortedResults[i].warmStddev);
        // Remove AOS_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hWarm->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWarm->GetXaxis()->SetLabelSize(0.06);
    hWarm->GetXaxis()->LabelsOption("a");
    hWarm->GetYaxis()->SetLabelSize(0.06);
    auto cWarm = make_unique<TCanvas>("cWarmAOS", "AOS Warm Read Times", 1600, 800);
    cWarm->SetBottomMargin(0.3);
    hWarm->SetMinimum(0);
    hWarm->Draw("BAR E");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxYWarm = hWarm->GetMaximum();
    double offsetWarm = maxYWarm * 0.05 + 1;
    for (int i = 1; i <= hWarm->GetNbinsX(); ++i) {
        double yPos = hWarm->GetBinContent(i) + hWarm->GetBinError(i) + offsetWarm;
        auto text = make_unique<TText>(hWarm->GetBinCenter(i), yPos, Form("%.1f±%.1f", hWarm->GetBinContent(i), hWarm->GetBinError(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cWarm->SaveAs("../experiments/aos_warm_times.pdf");
    cout << "AOS Read times plots saved to ../experiments/aos_cold_times.pdf and ../experiments/aos_warm_times.pdf" << endl;
}

void visualize_aos_file_sizes(const std::vector<std::pair<std::string, double>>& fileSizes) {
    filesystem::create_directory("../experiments");

    // Sort the file sizes for consistent ordering
    auto sortedFileSizes = sortFileSizes(fileSizes);

    auto hSize = make_unique<TH1F>("hSizeAOS", "AOS File Sizes;;Size (MB)", sortedFileSizes.size(), 0, sortedFileSizes.size());
    hSize->SetFillColor(kRed - 2); // Red color for AOS
    hSize->SetStats(0);
    hSize->SetBarWidth(0.6);
    hSize->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedFileSizes.size(); ++i) {
        hSize->SetBinContent(i + 1, sortedFileSizes[i].second);
        // Extract just the filename without path and aos_ prefix
        std::string label = sortedFileSizes[i].first;
        size_t lastSlash = label.find_last_of('/');
        if (lastSlash != std::string::npos) {
            label = label.substr(lastSlash + 1); // Remove path
        }
        if (label.find("aos_") == 0) {
            label = label.substr(4); // Remove "aos_" prefix
        }
        hSize->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hSize->GetXaxis()->SetLabelSize(0.06);
    hSize->GetXaxis()->LabelsOption("a");
    hSize->GetYaxis()->SetLabelSize(0.06);
    auto cSize = make_unique<TCanvas>("cSizeAOS", "AOS File Sizes", 1600, 800);
    cSize->SetBottomMargin(0.3);
    hSize->SetMinimum(0);
    hSize->Draw("BAR");
    gPad->SetGrid(1, 1);
    double maxY = hSize->GetMaximum();
    double offset = maxY * 0.05 + 1;
    for (int i = 1; i <= hSize->GetNbinsX(); ++i) {
        double yPos = hSize->GetBinContent(i) + offset;
        auto text = make_unique<TText>(hSize->GetBinCenter(i), yPos, Form("%.1f", hSize->GetBinContent(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cSize->SaveAs("../experiments/aos_file_sizes.pdf");
    cout << "AOS File sizes plot saved to ../experiments/aos_file_sizes.pdf" << endl;
}

void visualize_aos_scaling(const std::map<std::string, std::vector<std::pair<int, double>>>& data) {
    if (data.empty()) return;

    filesystem::create_directory("../experiments");

    int n = data.size();
    int cols = 3;
    int rows = (n + cols - 1) / cols; // Ceiling division

    TCanvas* canvas = new TCanvas("aos_scaling_canvas", "AOS Write Performance Scaling by Thread Count", 1800, 1200);
    canvas->Divide(cols, rows);

    int padIndex = 1;
    for (const auto& entry : data) {
        const auto& label = entry.first;
        const auto& points = entry.second;

        canvas->cd(padIndex++);
        gPad->SetLogx(1);
        TGraph* graph = new TGraph(points.size());
        double maxY = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            graph->SetPoint(i, points[i].first, points[i].second);
            if (points[i].second > maxY) maxY = points[i].second;
        }
        graph->SetTitle(("AOS " + label).c_str());
        graph->GetXaxis()->SetTitle("Number of Threads");
        graph->GetYaxis()->SetTitle("Average Time (s)");
        graph->Draw("ALP");
        graph->GetYaxis()->SetRangeUser(0, maxY * 1.1);
        graph->SetMarkerStyle(20);
        graph->SetLineWidth(2);
        graph->SetLineColor(kRed);
        graph->SetMarkerColor(kRed);
    }

    canvas->SaveAs("../experiments/aos_scaling_plot.pdf");
    delete canvas;
    cout << "AOS Scaling plot saved to ../experiments/aos_scaling_plot.pdf" << endl;
}

// SOA visualization functions
void visualize_soa_writer_results(const std::vector<WriterResult>& results) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedResults = sortWriterResults(results);

    // Write times bar plot with error bars
    auto hWrite = make_unique<TH1F>("hWriteSOA", "SOA Write Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hWrite->SetFillColor(kBlue - 2); // Blue color for SOA
    hWrite->SetStats(0);
    hWrite->SetBarWidth(0.6);
    hWrite->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hWrite->SetBinContent(i + 1, sortedResults[i].avg);
        hWrite->SetBinError(i + 1, sortedResults[i].stddev);
        // Remove SOA_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("SOA_") == 0) {
            label = label.substr(4); // Remove "SOA_" prefix
        }
        hWrite->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWrite->GetXaxis()->SetLabelSize(0.06);
    hWrite->GetXaxis()->LabelsOption("a");
    hWrite->GetYaxis()->SetLabelSize(0.06);
    auto cWrite = make_unique<TCanvas>("cWriteSOA", "SOA Write Times", 1600, 800);
    cWrite->SetBottomMargin(0.3);
    hWrite->SetMinimum(0);
    hWrite->Draw("BAR E");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxY = hWrite->GetMaximum();
    double offset = maxY * 0.05 + 1;
    for (int i = 1; i <= hWrite->GetNbinsX(); ++i) {
        double yPos = hWrite->GetBinContent(i) + hWrite->GetBinError(i) + offset;
        auto text = make_unique<TText>(hWrite->GetBinCenter(i), yPos, Form("%.1f±%.1f", hWrite->GetBinContent(i), hWrite->GetBinError(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cWrite->SaveAs("../experiments/soa_write_times.pdf");
    cout << "SOA Write times plot saved to ../experiments/soa_write_times.pdf" << endl;
}

void visualize_soa_reader_results(const std::vector<ReaderResult>& results) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedResults = sortReaderResults(results);

    // Cold times bar plot
    auto hCold = make_unique<TH1F>("hColdSOA", "SOA Cold Read Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hCold->SetFillColor(kBlue - 2); // Blue color for SOA
    hCold->SetStats(0);
    hCold->SetBarWidth(0.6);
    hCold->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hCold->SetBinContent(i + 1, sortedResults[i].cold);
        // Remove SOA_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("SOA_") == 0) {
            label = label.substr(4); // Remove "SOA_" prefix
        }
        hCold->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hCold->GetXaxis()->SetLabelSize(0.06);
    hCold->GetXaxis()->LabelsOption("a");
    hCold->GetYaxis()->SetLabelSize(0.06);
    auto cCold = make_unique<TCanvas>("cColdSOA", "SOA Cold Read Times", 1600, 800);
    cCold->SetBottomMargin(0.3);
    hCold->SetMinimum(0);
    hCold->Draw("BAR");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxYCold = hCold->GetMaximum();
    double offsetCold = maxYCold * 0.05 + 1;
    for (int i = 1; i <= hCold->GetNbinsX(); ++i) {
        double yPos = hCold->GetBinContent(i) + offsetCold;
        auto text = make_unique<TText>(hCold->GetBinCenter(i), yPos, Form("%.1f", hCold->GetBinContent(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cCold->SaveAs("../experiments/soa_cold_times.pdf");

    // Warm times bar plot with error bars
    auto hWarm = make_unique<TH1F>("hWarmSOA", "SOA Warm Read Times;;Time (s)", sortedResults.size(), 0, sortedResults.size());
    hWarm->SetFillColor(kBlue - 2); // Blue color for SOA
    hWarm->SetStats(0);
    hWarm->SetBarWidth(0.6);
    hWarm->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedResults.size(); ++i) {
        hWarm->SetBinContent(i + 1, sortedResults[i].warmAvg);
        hWarm->SetBinError(i + 1, sortedResults[i].warmStddev);
        // Remove SOA_ prefix from label
        std::string label = sortedResults[i].label;
        if (label.find("SOA_") == 0) {
            label = label.substr(4); // Remove "SOA_" prefix
        }
        hWarm->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWarm->GetXaxis()->SetLabelSize(0.06);
    hWarm->GetXaxis()->LabelsOption("a");
    hWarm->GetYaxis()->SetLabelSize(0.06);
    auto cWarm = make_unique<TCanvas>("cWarmSOA", "SOA Warm Read Times", 1600, 800);
    cWarm->SetBottomMargin(0.3);
    hWarm->SetMinimum(0);
    hWarm->Draw("BAR E");
    gPad->SetGrid(1, 1);
    // Add labels on top of bars
    double maxYWarm = hWarm->GetMaximum();
    double offsetWarm = maxYWarm * 0.05 + 1;
    for (int i = 1; i <= hWarm->GetNbinsX(); ++i) {
        double yPos = hWarm->GetBinContent(i) + hWarm->GetBinError(i) + offsetWarm;
        auto text = make_unique<TText>(hWarm->GetBinCenter(i), yPos, Form("%.1f±%.1f", hWarm->GetBinContent(i), hWarm->GetBinError(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cWarm->SaveAs("../experiments/soa_warm_times.pdf");
    cout << "SOA Read times plots saved to ../experiments/soa_cold_times.pdf and ../experiments/soa_warm_times.pdf" << endl;
}

void visualize_soa_file_sizes(const std::vector<std::pair<std::string, double>>& fileSizes) {
    filesystem::create_directory("../experiments");

    // Sort the file sizes for consistent ordering
    auto sortedFileSizes = sortFileSizes(fileSizes);

    auto hSize = make_unique<TH1F>("hSizeSOA", "SOA File Sizes;;Size (MB)", sortedFileSizes.size(), 0, sortedFileSizes.size());
    hSize->SetFillColor(kBlue - 2); // Blue color for SOA
    hSize->SetStats(0);
    hSize->SetBarWidth(0.6);
    hSize->SetBarOffset(0.1);
    for (size_t i = 0; i < sortedFileSizes.size(); ++i) {
        hSize->SetBinContent(i + 1, sortedFileSizes[i].second);
        // Extract just the filename without path and soa_ prefix
        std::string label = sortedFileSizes[i].first;
        size_t lastSlash = label.find_last_of('/');
        if (lastSlash != std::string::npos) {
            label = label.substr(lastSlash + 1); // Remove path
        }
        if (label.find("soa_") == 0) {
            label = label.substr(4); // Remove "soa_" prefix
        }
        hSize->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hSize->GetXaxis()->SetLabelSize(0.06);
    hSize->GetXaxis()->LabelsOption("a");
    hSize->GetYaxis()->SetLabelSize(0.06);
    auto cSize = make_unique<TCanvas>("cSizeSOA", "SOA File Sizes", 1600, 800);
    cSize->SetBottomMargin(0.3);
    hSize->SetMinimum(0);
    hSize->Draw("BAR");
    gPad->SetGrid(1, 1);
    double maxY = hSize->GetMaximum();
    double offset = maxY * 0.05 + 1;
    for (int i = 1; i <= hSize->GetNbinsX(); ++i) {
        double yPos = hSize->GetBinContent(i) + offset;
        auto text = make_unique<TText>(hSize->GetBinCenter(i), yPos, Form("%.1f", hSize->GetBinContent(i)));
        text->SetTextAlign(22);
        text->SetTextSize(0.02);
        text->Draw();
    }
    cSize->SaveAs("../experiments/soa_file_sizes.pdf");
    cout << "SOA File sizes plot saved to ../experiments/soa_file_sizes.pdf" << endl;
}

void visualize_soa_scaling(const std::map<std::string, std::vector<std::pair<int, double>>>& data) {
    if (data.empty()) return;

    filesystem::create_directory("../experiments");

    int n = data.size();
    int cols = 3;
    int rows = (n + cols - 1) / cols; // Ceiling division

    TCanvas* canvas = new TCanvas("soa_scaling_canvas", "SOA Write Performance Scaling by Thread Count", 1800, 1200);
    canvas->Divide(cols, rows);

    int padIndex = 1;
    for (const auto& entry : data) {
        const auto& label = entry.first;
        const auto& points = entry.second;

        canvas->cd(padIndex++);
        gPad->SetLogx(1);
        TGraph* graph = new TGraph(points.size());
        double maxY = 0;
        for (size_t i = 0; i < points.size(); ++i) {
            graph->SetPoint(i, points[i].first, points[i].second);
            if (points[i].second > maxY) maxY = points[i].second;
        }
        graph->SetTitle(("SOA " + label).c_str());
        graph->GetXaxis()->SetTitle("Number of Threads");
        graph->GetYaxis()->SetTitle("Average Time (s)");
        graph->Draw("ALP");
        graph->GetYaxis()->SetRangeUser(0, maxY * 1.1);
        graph->SetMarkerStyle(20);
        graph->SetLineWidth(2);
        graph->SetLineColor(kBlue);
        graph->SetMarkerColor(kBlue);
    }

    canvas->SaveAs("../experiments/soa_scaling_plot.pdf");
    delete canvas;
    cout << "SOA Scaling plot saved to ../experiments/soa_scaling_plot.pdf" << endl;
}

// Comparison functions for AOS vs SOA
void visualize_comparison_writer_results(const std::vector<WriterResult>& aosResults, const std::vector<WriterResult>& soaResults) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedAosResults = sortWriterResults(aosResults);
    auto sortedSoaResults = sortWriterResults(soaResults);

    // Create comparison plot
    auto hWrite = make_unique<TH1F>("hWriteComp", "AOS vs SOA Write Times;;Time (s)", sortedAosResults.size(), 0, sortedAosResults.size());
    hWrite->SetStats(0);
    hWrite->SetBarWidth(0.35);
    hWrite->SetBarOffset(0.1);
    
    // AOS data
    for (size_t i = 0; i < sortedAosResults.size(); ++i) {
        hWrite->SetBinContent(i + 1, sortedAosResults[i].avg);
        hWrite->SetBinError(i + 1, sortedAosResults[i].stddev);
        // Extract generic label without AOS_ prefix
        std::string label = sortedAosResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hWrite->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWrite->SetFillColor(kRed - 2);
    hWrite->GetXaxis()->SetLabelSize(0.06);
    hWrite->GetXaxis()->LabelsOption("a");
    hWrite->GetYaxis()->SetLabelSize(0.06);
    
    auto cWrite = make_unique<TCanvas>("cWriteComp", "AOS vs SOA Write Times", 1600, 800);
    cWrite->SetBottomMargin(0.3);
    hWrite->SetMinimum(0);
    hWrite->Draw("BAR E");
    gPad->SetGrid(1, 1);
    
    // SOA data as overlay
    auto hWriteSOA = make_unique<TH1F>("hWriteSOAComp", "SOA Write Times", sortedAosResults.size(), 0, sortedAosResults.size());
    hWriteSOA->SetBarWidth(0.35);
    hWriteSOA->SetBarOffset(0.55);
    for (size_t i = 0; i < sortedSoaResults.size(); ++i) {
        hWriteSOA->SetBinContent(i + 1, sortedSoaResults[i].avg);
        hWriteSOA->SetBinError(i + 1, sortedSoaResults[i].stddev);
    }
    hWriteSOA->SetFillColor(kBlue - 2);
    hWriteSOA->Draw("BAR E SAME");
    
    // Add legend
    auto legend = make_unique<TLegend>(0.45, 0.7, 0.58, 0.9);
    legend->SetTextSize(0.06);
    legend->AddEntry(hWrite.get(), "AOS", "f");
    legend->AddEntry(hWriteSOA.get(), "SOA", "f");
    legend->Draw();
    
    cWrite->SaveAs("../experiments/comparison_write_times.pdf");
    cout << "Comparison write times plot saved to ../experiments/comparison_write_times.pdf" << endl;
}

void visualize_comparison_reader_results(const std::vector<ReaderResult>& aosResults, const std::vector<ReaderResult>& soaResults) {
    filesystem::create_directory("../experiments");

    // Sort the results for consistent ordering
    auto sortedAosResults = sortReaderResults(aosResults);
    auto sortedSoaResults = sortReaderResults(soaResults);

    // Cold times comparison
    auto hCold = make_unique<TH1F>("hColdComp", "AOS vs SOA Cold Read Times;;Time (s)", sortedAosResults.size(), 0, sortedAosResults.size());
    hCold->SetStats(0);
    hCold->SetBarWidth(0.35);
    hCold->SetBarOffset(0.1);
    
    for (size_t i = 0; i < sortedAosResults.size(); ++i) {
        hCold->SetBinContent(i + 1, sortedAosResults[i].cold);
        // Extract generic label without AOS_ prefix
        std::string label = sortedAosResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hCold->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hCold->SetFillColor(kRed - 2);
    hCold->GetXaxis()->SetLabelSize(0.06);
    hCold->GetXaxis()->LabelsOption("a");
    hCold->GetYaxis()->SetLabelSize(0.06);
    
    auto cCold = make_unique<TCanvas>("cColdComp", "AOS vs SOA Cold Read Times", 1600, 800);
    cCold->SetBottomMargin(0.3);
    hCold->SetMinimum(0);
    hCold->Draw("BAR");
    gPad->SetGrid(1, 1);
    
    auto hColdSOA = make_unique<TH1F>("hColdSOAComp", "SOA Cold Read Times", sortedAosResults.size(), 0, sortedAosResults.size());
    hColdSOA->SetBarWidth(0.35);
    hColdSOA->SetBarOffset(0.55);
    for (size_t i = 0; i < sortedSoaResults.size(); ++i) {
        hColdSOA->SetBinContent(i + 1, sortedSoaResults[i].cold);
    }
    hColdSOA->SetFillColor(kBlue - 2);
    hColdSOA->Draw("BAR SAME");
    
    auto legendCold = make_unique<TLegend>(0.85, 0.7, 0.98, 0.9);
    legendCold->SetTextSize(0.06);
    legendCold->AddEntry(hCold.get(), "AOS", "f");
    legendCold->AddEntry(hColdSOA.get(), "SOA", "f");
    legendCold->Draw();
    
    cCold->SaveAs("../experiments/comparison_cold_times.pdf");

    // Warm times comparison
    auto hWarm = make_unique<TH1F>("hWarmComp", "AOS vs SOA Warm Read Times;;Time (s)", sortedAosResults.size(), 0, sortedAosResults.size());
    hWarm->SetStats(0);
    hWarm->SetBarWidth(0.35);
    hWarm->SetBarOffset(0.1);
    
    for (size_t i = 0; i < sortedAosResults.size(); ++i) {
        hWarm->SetBinContent(i + 1, sortedAosResults[i].warmAvg);
        hWarm->SetBinError(i + 1, sortedAosResults[i].warmStddev);
        // Extract generic label without AOS_ prefix
        std::string label = sortedAosResults[i].label;
        if (label.find("AOS_") == 0) {
            label = label.substr(4); // Remove "AOS_" prefix
        }
        hWarm->GetXaxis()->SetBinLabel(i + 1, label.c_str());
    }
    hWarm->SetFillColor(kRed - 2);
    hWarm->GetXaxis()->SetLabelSize(0.06);
    hWarm->GetXaxis()->LabelsOption("a");
    hWarm->GetYaxis()->SetLabelSize(0.06);
    
    auto cWarm = make_unique<TCanvas>("cWarmComp", "AOS vs SOA Warm Read Times", 1600, 800);
    cWarm->SetBottomMargin(0.3);
    hWarm->SetMinimum(0);
    hWarm->Draw("BAR E");
    gPad->SetGrid(1, 1);
    
    auto hWarmSOA = make_unique<TH1F>("hWarmSOAComp", "SOA Warm Read Times", sortedAosResults.size(), 0, sortedAosResults.size());
    hWarmSOA->SetBarWidth(0.35);
    hWarmSOA->SetBarOffset(0.55);
    for (size_t i = 0; i < sortedSoaResults.size(); ++i) {
        hWarmSOA->SetBinContent(i + 1, sortedSoaResults[i].warmAvg);
        hWarmSOA->SetBinError(i + 1, sortedSoaResults[i].warmStddev);
    }
    hWarmSOA->SetFillColor(kBlue - 2);
    hWarmSOA->Draw("BAR E SAME");
    
    auto legendWarm = make_unique<TLegend>(0.85, 0.7, 0.98, 0.9);
    legendWarm->SetTextSize(0.06);
    legendWarm->AddEntry(hWarm.get(), "AOS", "f");
    legendWarm->AddEntry(hWarmSOA.get(), "SOA", "f");
    legendWarm->Draw();
    
    cWarm->SaveAs("../experiments/comparison_warm_times.pdf");
    cout << "Comparison read times plots saved to ../experiments/comparison_cold_times.pdf and ../experiments/comparison_warm_times.pdf" << endl;
}

void visualize_comparison_file_sizes(const std::vector<std::pair<std::string, double>>& aosSizes, const std::vector<std::pair<std::string, double>>& soaSizes) {
    filesystem::create_directory("../experiments");

    // Sort the file sizes for consistent ordering
    auto sortedAosSizes = sortFileSizes(aosSizes);
    auto sortedSoaSizes = sortFileSizes(soaSizes);

    auto hSize = make_unique<TH1F>("hSizeComp", "AOS vs SOA File Sizes;;Size (MB)", sortedAosSizes.size(), 0, sortedAosSizes.size());
    hSize->SetStats(0);
    hSize->SetBarWidth(0.35);
    hSize->SetBarOffset(0.1);
    
    for (size_t i = 0; i < sortedAosSizes.size(); ++i) {
        hSize->SetBinContent(i + 1, sortedAosSizes[i].second);
        // Extract base name without path and AOS_ prefix
        std::string fullPath = sortedAosSizes[i].first;
        size_t lastSlash = fullPath.find_last_of('/');
        std::string fileName = (lastSlash != std::string::npos) ? fullPath.substr(lastSlash + 1) : fullPath;
        // Remove AOS_ prefix
        std::string baseName = fileName;
        if (baseName.find("aos_") == 0) {
            baseName = baseName.substr(4); // Remove "aos_" prefix
        }
        hSize->GetXaxis()->SetBinLabel(i + 1, baseName.c_str());
    }
    hSize->SetFillColor(kRed - 2);
    hSize->GetXaxis()->SetLabelSize(0.06);
    hSize->GetXaxis()->LabelsOption("a");
    hSize->GetYaxis()->SetLabelSize(0.06);
    
    auto cSize = make_unique<TCanvas>("cSizeComp", "AOS vs SOA File Sizes", 1600, 800);
    cSize->SetBottomMargin(0.3);
    hSize->SetMinimum(0);
    hSize->Draw("BAR");
    gPad->SetGrid(1, 1);
    
    auto hSizeSOA = make_unique<TH1F>("hSizeSOAComp", "SOA File Sizes", sortedAosSizes.size(), 0, sortedAosSizes.size());
    hSizeSOA->SetBarWidth(0.35);
    hSizeSOA->SetBarOffset(0.55);
    for (size_t i = 0; i < sortedSoaSizes.size(); ++i) {
        hSizeSOA->SetBinContent(i + 1, sortedSoaSizes[i].second);
    }
    hSizeSOA->SetFillColor(kBlue - 2);
    hSizeSOA->Draw("BAR SAME");
    
    auto legend = make_unique<TLegend>(0.85, 0.7, 0.98, 0.9);
    legend->SetTextSize(0.06);
    legend->AddEntry(hSize.get(), "AOS", "f");
    legend->AddEntry(hSizeSOA.get(), "SOA", "f");
    legend->Draw();
    
    cSize->SaveAs("../experiments/comparison_file_sizes.pdf");
    cout << "Comparison file sizes plot saved to ../experiments/comparison_file_sizes.pdf" << endl;
}