#include "visualization.hpp"
#include "HitWireReaders.hpp"
#include <TSystem.h>
#include <TROOT.h>
#include <thread>

#include "ReaderResult.hpp"

#include "WriterResult.hpp"

#include <iostream>
#include <filesystem>
#include <iomanip>

#include "HitWireWriters.hpp"
#include <TFile.h>



static std::string build_label_from_path(const std::string& filepath) {
    namespace fs = std::filesystem;
    fs::path p(filepath);
    std::string stem = p.stem().string(); // e.g. "aos_event_all"

    // Uppercase prefix (aos/soa)
    std::string label = stem;
    auto underscorePos = label.find('_');
    if (underscorePos != std::string::npos) {
        for (size_t i = 0; i < underscorePos; ++i) {
            label[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(label[i])));
        }
    }

    // Replace suffixes to match prior naming (…allDataProduct / …perDataProduct)
    auto replace_suffix = [&](const std::string& suffix, const std::string& replacement) {
        if (label.size() >= suffix.size() && label.compare(label.size() - suffix.size(), suffix.size(), suffix) == 0) {
            label.replace(label.size() - suffix.size(), suffix.size(), replacement);
        }
    };
    replace_suffix("_all", "_allDataProduct");
    replace_suffix("_perData", "_perDataProduct");

    return label;
}

static void print_file_sizes_table(const std::string& title,
                                   const std::vector<std::pair<std::string, double>>& fileSizesMB) {
    const int col1 = 40; // label
    const int col2 = 16; // size

    std::cout << "\n" << title << std::endl;
    std::cout << std::left
              << std::setw(col1) << "File"
              << std::setw(col2) << "Size (MB)" << std::endl;
    std::cout << std::string(col1 + col2, '-') << std::endl;

    for (const auto& [path, sizeMB] : fileSizesMB) {
        std::cout << std::left
                  << std::setw(col1) << build_label_from_path(path)
                  << std::setw(col2) << sizeMB
                  << std::endl;
    }
    std::cout << std::string(col1 + col2, '-') << std::endl;
}

int main() {
    ROOT::EnableThreadSafety();
    int nThreads = std::thread::hardware_concurrency();
    //int nThreads = 1;
    ROOT::EnableImplicitMT(nThreads);
    gSystem->Load("libWireDict");
    
    // Configuration parameters
    int numEvents = 1000;
    int hitsPerEvent = 100;
    int wiresPerEvent = 100;
    int roisPerWire = 10;
    int numSpills = 10;
    const std::string kOutputDir = "./output";
    
    // Create output directory if it doesn't exist
    std::filesystem::create_directories(kOutputDir);

    // Commented: AOS writer/reader benchmarks
    auto aos_writer_results = outAOS(nThreads, 3, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, numSpills, kOutputDir);
    visualize_aos_writer_results(aos_writer_results);
    auto aos_reader_results = inAOS(nThreads, 3, kOutputDir);
    visualize_aos_reader_results(aos_reader_results);

    // Collect AOS file sizes
    std::vector<std::pair<std::string, double>> aos_file_sizes;
    std::vector<std::string> aos_files = {
        kOutputDir + "/aos_event_all.root",
        kOutputDir + "/aos_event_perData.root",
        kOutputDir + "/aos_event_perGroup.root",
        kOutputDir + "/aos_spill_all.root",
        kOutputDir + "/aos_spill_perData.root",
        kOutputDir + "/aos_spill_perGroup.root",
        kOutputDir + "/aos_topObject_perData.root",
        kOutputDir + "/aos_topObject_perGroup.root",
        kOutputDir + "/aos_element_perData.root",
        kOutputDir + "/aos_element_perGroup.root"
    };
    for (const auto& f : aos_files) {
        auto tfile = TFile::Open(f.c_str(), "READ");
        if (tfile) {
            double sizeMB = tfile->GetSize() / (1024.0 * 1024.0);
            aos_file_sizes.emplace_back(f, sizeMB);
            tfile->Close();
        }
    }
    // Print AOS file sizes to terminal in a table format
    print_file_sizes_table("AOS File Sizes (MB)", aos_file_sizes);

    // Add SOA visualization - use separate SOA-only functions
    // Commented: SOA writer/reader benchmarks
    auto soa_writer_results = outSOA(nThreads, 3, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, numSpills, kOutputDir);
    visualize_soa_writer_results(soa_writer_results);
    auto soa_reader_results = inSOA(nThreads, 3, kOutputDir);
    visualize_soa_reader_results(soa_reader_results);

    // Collect SOA file sizes
    std::vector<std::pair<std::string, double>> soa_file_sizes;
    std::vector<std::string> soa_files = {
        kOutputDir + "/soa_event_all.root",
        kOutputDir + "/soa_event_perData.root",
        kOutputDir + "/soa_event_perGroup.root",
        kOutputDir + "/soa_spill_all.root",
        kOutputDir + "/soa_spill_perData.root",
        kOutputDir + "/soa_spill_perGroup.root",
        kOutputDir + "/soa_topObject_perData.root",
        kOutputDir + "/soa_topObject_perGroup.root",
        kOutputDir + "/soa_element_perData.root",
        kOutputDir + "/soa_element_perGroup.root"
    };
    for (const auto& f : soa_files) {
        auto tfile = TFile::Open(f.c_str(), "READ");
        if (tfile) {
            double sizeMB = tfile->GetSize() / (1024.0 * 1024.0);
            soa_file_sizes.emplace_back(f, sizeMB);
            tfile->Close();
        }
    }
    // Print SOA file sizes to terminal in a table format
    print_file_sizes_table("SOA File Sizes (MB)", soa_file_sizes);

    // Add comparison visualizations
    // Commented: comparison visualizations
    visualize_comparison_writer_results(aos_writer_results, soa_writer_results);
    visualize_comparison_reader_results(aos_reader_results, soa_reader_results);
    visualize_comparison_file_sizes(aos_file_sizes, soa_file_sizes);

    // auto aos_scaling = benchmarkAOSScaling(32, 3);
    // visualize_aos_scaling(aos_scaling);

    return 0;
}

/*
cd RNTuple-I-O-Config && \
rm -rf build && \
mkdir build && \
cd build && \
cmake .. && \
make && \
./tests/gen_test_rootfile && \
ctest -R test_split_range_by_clusters --output-on-failure && \
echo "Started at: $(date)" | tee ../experiments/log.txt && \
./hitwire 2>&1 | tee -a ../experiments/log.txt && \
rm -rf build && \
cd .. && cd ..
*/