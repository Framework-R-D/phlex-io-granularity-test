#include "Hit.hpp"
#include "Wire.hpp"
#include "Utils.hpp" // Assuming this exists for utilities like generateSeeds
#include "HitWireWriterHelpers.hpp"
#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RNTupleWriter.hxx>
#include <ROOT/RNTupleParallelWriter.hxx>
#include <ROOT/RNTupleWriteOptions.hxx>
#include <TFile.h>
#include <TStopwatch.h>
#include <filesystem>
#include <thread>
#include <future>
#include <vector>
#include <mutex>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <map>
#include <utility>
#include "ProgressiveTablePrinter.hpp"
#include "WriterResult.hpp"
#include <functional>
#include <exception>
#include <TROOT.h>

// Add forward declarations
double SOA_spill_allDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_spill_perDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_spill_perGroup(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_topObject_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_topObject_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_element_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);
double SOA_element_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads);

double RunAOS_element_perDataProductCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wireROIContext, ROOT::REntry& wireROIEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);

double RunAOS_element_perGroupCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);

double RunSOA_element_perDataProductCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);

double RunSOA_element_perGroupCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);

// Move executeInParallel to the top of the file, before any function implementations
static double executeInParallel(int totalEvents, int nThreads, const std::function<double(int, int, unsigned, int)>& workFunc) {
    if (nThreads <= 0 || totalEvents < 0) return 0.0;
    if (totalEvents == 0) return 0.0;
    auto seeds = Utils::generateSeeds(nThreads);
    int chunk = totalEvents / nThreads;
    std::vector<std::future<double>> futures;
    for (int th = 0; th < nThreads; ++th) {
        int start = th * chunk;
        int end = (th == nThreads - 1) ? totalEvents : start + chunk;
        if (start >= end) continue;
        futures.push_back(std::async(std::launch::async, workFunc, start, end, seeds[th], th));
    }
    double totalTime = 0.0;
    for (auto& f : futures) {
        totalTime += f.get();
    }
    return totalTime;
}

// One-pass implementation with single EventAOS ntuple (matches reader expectations)
double AOS_event_allDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;

    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    

    auto [model, token] = CreateAOSAllDataProductModelAndToken();
    auto writer = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(model), "aos_events", *file, options);

    // Thread-local contexts and entries
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> contexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> entries(nThreads);

    for (int th = 0; th < nThreads; ++th) {
        contexts[th] = writer->CreateFillContext();
        entries[th] = contexts[th]->GetModel().CreateRawPtrWriteEntry();
    }

    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_event_allDataProductWorkFunc(first, last, seed, *contexts[th], *entries[th], token, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };

    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// Implementation for perDataProduct
double AOS_event_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateAOSHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateAOSWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_event_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// Implementation for perGroup (similar, with added rois writer)
double AOS_event_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateAOSHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateAOSBaseWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_wires", *file, options);
    auto [roisModel, roisToken] = CreateAOSROIsModelAndToken();
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "aos_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_event_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, *roisContexts[th], *roisEntries[th], roisToken, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// SOA_event_allDataProduct
double SOA_event_allDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [model, token] = CreateSOAAllDataProductModelAndToken();
    auto writer = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(model), "soa_events", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> contexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> entries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        contexts[th] = writer->CreateFillContext();
        entries[th] = contexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_event_allDataProductWorkFunc(first, last, seed, *contexts[th], *entries[th], token, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// SOA_event_perDataProduct
double SOA_event_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateSOAHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateSOAWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_event_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// SOA_event_perGroup
double SOA_event_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateSOAHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateSOABaseWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_wires", *file, options);
    auto [roisModel, roisToken] = CreateSOAROIsModelAndToken();
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "soa_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_event_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, *roisContexts[th], *roisEntries[th], roisToken, mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

// Add any shared helpers here, e.g., executeInParallel from existing code (duplicated to avoid changes)

double AOS_spill_allDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [model, token] = CreateAOSAllDataProductModelAndToken();
    auto writer = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(model), "aos_spills", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> contexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> entries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        contexts[th] = writer->CreateFillContext();
        entries[th] = contexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_spill_allDataProductWorkFunc(first, last, seed, *contexts[th], *entries[th], token, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

// Similarly implement AOS_spill_perDataProduct and AOS_spill_perGroup 

double AOS_spill_perDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateAOSHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_spill_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateAOSWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_spill_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_spill_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

double AOS_spill_perGroup(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateAOSHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_spill_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateAOSBaseWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_spill_wires", *file, options);
    auto [roisModel, roisToken] = CreateAOSROIsModelAndToken();
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "aos_spill_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunAOS_spill_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, *roisContexts[th], *roisEntries[th], roisToken, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
} 


double AOS_topObject_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int totalEntries = numEvents * hitsPerEvent;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<HitIndividual>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_top_hits", *file, options);
    auto wiresModel = ROOT::RNTupleModel::Create();
    wiresModel->MakeField<WireIndividual>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_top_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads), wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads), wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) -> double {
        return RunAOS_topObject_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], *wiresContexts[th], *wiresEntries[th], mutex, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}


double AOS_topObject_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int totalEntries = numEvents * hitsPerEvent;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<HitIndividual>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "aos_top_hits", *file, options);
    auto wiresModel = ROOT::RNTupleModel::Create();
    wiresModel->MakeField<WireBase>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "aos_top_wires", *file, options);
    auto roisModel = ROOT::RNTupleModel::Create();
    roisModel->MakeField<std::vector<FlatROI>>("rois");
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "aos_top_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads), wiresContexts(nThreads), roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads), wiresEntries(nThreads), roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) -> double {
        return RunAOS_topObject_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], *wiresContexts[th], *wiresEntries[th], *roisContexts[th], *roisEntries[th], mutex, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
} 

double AOS_element_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    

    // Hits model and writer
    auto hitsModel = ROOT::RNTupleModel::Create();
    auto hitField = hitsModel->MakeField<HitIndividual>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "element_hits", *file, options);

    // WireROI model and writer
    auto wireROIModel = ROOT::RNTupleModel::Create();
    auto wireROIField = wireROIModel->MakeField<WireROI>("wire_roi");
    auto wireROIWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wireROIModel), "element_wire_rois", *file, options);

    // Contexts and entries for hits
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads);

    // Contexts and entries for wireROIs
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wireROIContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> wireROIEntries(nThreads);

    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wireROIContexts[th] = wireROIWriter->CreateFillContext();
        wireROIEntries[th] = wireROIContexts[th]->CreateEntry();
    }

    // Single-pass combined work function (parallel over events)
    auto workFunc = [&](int firstEvt, int lastEvt, unsigned seed, int th) -> double {
        return RunAOS_element_perDataProductCombinedWorkFunc(firstEvt, lastEvt, seed,
                                                             *hitsContexts[th], *hitsEntries[th],
                                                             *wireROIContexts[th], *wireROIEntries[th],
                                                             mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

double AOS_element_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    

    // Hits model and writer (single HitIndividual per row)
    auto hitsModel = ROOT::RNTupleModel::Create();
    auto hitField = hitsModel->MakeField<HitIndividual>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "element_hits", *file, options);

    // Wires model and writer (single WireBase per row)
    auto wiresModel = ROOT::RNTupleModel::Create();
    auto wireField = wiresModel->MakeField<WireBase>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "element_wires", *file, options);

    // ROIs model and writer (single FlatROI per row)
    auto roisModel = ROOT::RNTupleModel::Create();
    auto roiField = roisModel->MakeField<FlatROI>("roi");
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "element_rois", *file, options);

    // Contexts and entries
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads), wiresContexts(nThreads), roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads), wiresEntries(nThreads), roisEntries(nThreads);

    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->CreateEntry();
    }

    // Single-pass combined work function (parallel over events)
    auto workFunc = [&](int firstEvt, int lastEvt, unsigned seed, int th) -> double {
        return RunAOS_element_perGroupCombinedWorkFunc(firstEvt, lastEvt, seed,
                                                       *hitsContexts[th], *hitsEntries[th],
                                                       *wiresContexts[th], *wiresEntries[th],
                                                       *roisContexts[th], *roisEntries[th],
                                                       mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
} 

std::vector<WriterResult> outAOS(int nThreads, int iter, int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, int numSpills, const std::string& outputDir) {
    std::vector<WriterResult> results;
    
    // Create progressive table printer
    ProgressiveTablePrinter<WriterResult> tablePrinter(
        "AOS Writer Benchmarks (Progressive Results)",
        {"Writer", "Average (s)", "StdDev (s)", "Itr 1 (s)", "Itr 2 (s)", "Itr 3 (s)"},
        {32, 16, 16, 12, 12, 12}
    );
    
    auto benchmark = [&](const std::string& label, auto func, auto&&... args) {
        WriterResult result = {label, 0.0, 0.0, {}, false, ""};
        
        try {
            std::vector<double> times;
            for (int i = 0; i < iter; ++i) {
                double t = func(args...);
                times.push_back(t);
            }
            double avg = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
            double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
            double stddev = std::sqrt((sq_sum - times.size() * avg * avg) / (times.size() - 1));
            result.avg = avg;
            result.stddev = stddev;
            result.iterationTimes = times; // Store individual iteration times
        } catch (const std::exception& e) {
            std::cout << "Running " << label << "... FAILED" << std::endl;
            result.failed = true;
            result.errorMessage = e.what();
        } catch (...) {
            std::cout << "Running " << label << "... FAILED" << std::endl;
            result.failed = true;
            result.errorMessage = "Unknown error occurred";
        }
        
        results.push_back(result);
        tablePrinter.addRow(result);
    };
    benchmark("AOS_event_allDataProduct", AOS_event_allDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_event_all.root", nThreads);
    benchmark("AOS_event_perDataProduct", AOS_event_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_event_perData.root", nThreads);
    benchmark("AOS_event_perGroup", AOS_event_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_event_perGroup.root", nThreads);
    benchmark("AOS_spill_allDataProduct", AOS_spill_allDataProduct, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_spill_all.root", nThreads);
    benchmark("AOS_spill_perDataProduct", AOS_spill_perDataProduct, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_spill_perData.root", nThreads);
    benchmark("AOS_spill_perGroup", AOS_spill_perGroup, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_spill_perGroup.root", nThreads);
    benchmark("AOS_topObject_perDataProduct", AOS_topObject_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_topObject_perData.root", nThreads);
    benchmark("AOS_topObject_perGroup", AOS_topObject_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_topObject_perGroup.root", nThreads);
    benchmark("AOS_element_perDataProduct", AOS_element_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_element_perData.root", nThreads);
    benchmark("AOS_element_perGroup", AOS_element_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/aos_element_perGroup.root", nThreads);

    tablePrinter.printFooter();
    return results;
} 

std::map<std::string, std::vector<std::pair<int, double>>> benchmarkAOSScaling(int maxThreads, int iter) {
    std::vector<int> threadCounts = {1, 2, 4, 8, 16, 32};
    std::map<std::string, std::vector<std::pair<int, double>>> data;
    for (int threads : threadCounts) {
        ROOT::EnableImplicitMT(threads);
        auto results = outAOS(threads, iter, 1000000, 100, 100, 10, 10, "./output");
        for (const auto& res : results) {
            data[res.label].emplace_back(threads, res.avg);
        }
    }
    ROOT::DisableImplicitMT();
    return data;
} 

// Group 2: SOA spill functions - complete perData and perGroup
double SOA_spill_perDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateSOAHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_spill_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateSOAWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_spill_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_spill_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

double SOA_spill_perGroup(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [hitsModel, hitsToken] = CreateSOAHitsModelAndToken();
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_spill_hits", *file, options);
    auto [wiresModel, wiresToken] = CreateSOABaseWiresModelAndToken();
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_spill_wires", *file, options);
    auto [roisModel, roisToken] = CreateSOAROIsModelAndToken();
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "soa_spill_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads), wiresContexts(nThreads), roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> hitsEntries(nThreads), wiresEntries(nThreads), roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->GetModel().CreateRawPtrWriteEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->GetModel().CreateRawPtrWriteEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_spill_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], hitsToken, *wiresContexts[th], *wiresEntries[th], wiresToken, *roisContexts[th], *roisEntries[th], roisToken, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

// Group 3: Complete topObject perGroup
double SOA_topObject_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int totalEntries = numEvents * hitsPerEvent;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<SOAHit>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_top_hits", *file, options);
    auto wiresModel = ROOT::RNTupleModel::Create();
    wiresModel->MakeField<SOAWireBase>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_top_wires", *file, options);
    auto roisModel = ROOT::RNTupleModel::Create();
    roisModel->MakeField<std::vector<SOAROI>>("rois");
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "soa_top_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads), wiresContexts(nThreads), roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads), wiresEntries(nThreads), roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) -> double {
        return RunSOA_topObject_perGroupWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], *wiresContexts[th], *wiresEntries[th], *roisContexts[th], *roisEntries[th], mutex, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

// Group 4: Complete element perData and perGroup
double SOA_element_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<SOAHit>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_element_hits", *file, options);
    auto roisModel = ROOT::RNTupleModel::Create();
    roisModel->MakeField<FlatSOAROI>("roi");
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "soa_element_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int firstEvt, int lastEvt, unsigned seed, int th) -> double {
        return RunSOA_element_perDataProductCombinedWorkFunc(firstEvt, lastEvt, seed,
                                                             *hitsContexts[th], *hitsEntries[th],
                                                             *roisContexts[th], *roisEntries[th],
                                                             mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
}

double SOA_element_perGroup(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<SOAHit>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_element_hits", *file, options);
    auto wiresModel = ROOT::RNTupleModel::Create();
    wiresModel->MakeField<SOAWireBase>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_element_wires", *file, options);
    auto roisModel = ROOT::RNTupleModel::Create();
    roisModel->MakeField<FlatSOAROI>("roi");
    auto roisWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(roisModel), "soa_element_rois", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> wiresEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> roisContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> roisEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
        roisContexts[th] = roisWriter->CreateFillContext();
        roisEntries[th] = roisContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int firstEvt, int lastEvt, unsigned seed, int th) -> double {
        return RunSOA_element_perGroupCombinedWorkFunc(firstEvt, lastEvt, seed,
            *hitsContexts[th], *hitsEntries[th],
            *wiresContexts[th], *wiresEntries[th],
            *roisContexts[th], *roisEntries[th],
            mutex, hitsPerEvent, wiresPerEvent, roisPerWire);
    };
    double totalTime = executeInParallel(numEvents, nThreads, workFunc);
    return totalTime;
} 

double SOA_spill_allDataProduct(int numEvents, int numSpills, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int adjustedHits = hitsPerEvent / numSpills;
    int adjustedWires = wiresPerEvent / numSpills;
    int totalEntries = numEvents * numSpills;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto [model, token] = CreateSOAAllDataProductModelAndToken();
    auto writer = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(model), "soa_spill_all", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> contexts(nThreads);
    std::vector<std::unique_ptr<ROOT::Experimental::Detail::RRawPtrWriteEntry>> entries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        contexts[th] = writer->CreateFillContext();
        entries[th] = contexts[th]->GetModel().CreateRawPtrWriteEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_spill_allDataProductWorkFunc(first, last, seed, *contexts[th], *entries[th], token, mutex, numSpills, adjustedHits, adjustedWires, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
}

double SOA_topObject_perDataProduct(int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, const std::string& fileName, int nThreads) {
    int totalEntries = numEvents * hitsPerEvent;
    auto file = std::make_unique<TFile>(fileName.c_str(), "RECREATE");
    std::mutex mutex;
    ROOT::RNTupleWriteOptions options;
    options.SetUseBufferedWrite(true);
    
    auto hitsModel = ROOT::RNTupleModel::Create();
    hitsModel->MakeField<SOAHit>("hit");
    auto hitsWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(hitsModel), "soa_top_hits", *file, options);
    auto wiresModel = ROOT::RNTupleModel::Create();
    wiresModel->MakeField<SOAWire>("wire");
    auto wiresWriter = ROOT::Experimental::RNTupleParallelWriter::Append(std::move(wiresModel), "soa_top_wires", *file, options);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> hitsContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> hitsEntries(nThreads);
    std::vector<std::shared_ptr<ROOT::Experimental::RNTupleFillContext>> wiresContexts(nThreads);
    std::vector<std::unique_ptr<ROOT::REntry>> wiresEntries(nThreads);
    for (int th = 0; th < nThreads; ++th) {
        hitsContexts[th] = hitsWriter->CreateFillContext();
        hitsEntries[th] = hitsContexts[th]->CreateEntry();
        wiresContexts[th] = wiresWriter->CreateFillContext();
        wiresEntries[th] = wiresContexts[th]->CreateEntry();
    }
    auto workFunc = [&](int first, int last, unsigned seed, int th) {
        return RunSOA_topObject_perDataProductWorkFunc(first, last, seed, *hitsContexts[th], *hitsEntries[th], *wiresContexts[th], *wiresEntries[th], mutex, roisPerWire);
    };
    double totalTime = executeInParallel(totalEntries, nThreads, workFunc);
    return totalTime;
} 

std::vector<WriterResult> outSOA(int nThreads, int iter, int numEvents, int hitsPerEvent, int wiresPerEvent, int roisPerWire, int numSpills, const std::string& outputDir) {
    std::vector<WriterResult> results;
    
    // Create progressive table printer
    ProgressiveTablePrinter<WriterResult> tablePrinter(
        "SOA Writer Benchmarks (Progressive Results)",
        {"SOA Writer", "Average (s)", "StdDev (s)", "Itr 1 (s)", "Itr 2 (s)", "Itr 3 (s)"},
        {32, 16, 16, 12, 12, 12}
    );
    
    auto benchmark = [&](const std::string& label, auto func, auto&&... args) {
        WriterResult result = {label, 0.0, 0.0, {}, false, ""};
        
        try {
            std::vector<double> times;
            for (int i = 0; i < iter; ++i) {
                double t = func(args...);
                times.push_back(t);
            }
            double avg = std::accumulate(times.begin(), times.end(), 0.0) / times.size();
            double sq_sum = std::inner_product(times.begin(), times.end(), times.begin(), 0.0);
            double stddev = std::sqrt((sq_sum - times.size() * avg * avg) / (times.size() - 1));
            result.avg = avg;
            result.stddev = stddev;
            result.iterationTimes = times; // Store individual iteration times
        } catch (const std::exception& e) {
            std::cout << "Running " << label << "... FAILED" << std::endl;
            result.failed = true;
            result.errorMessage = e.what();
        } catch (...) {
            std::cout << "Running " << label << "... FAILED" << std::endl;
            result.failed = true;
            result.errorMessage = "Unknown error occurred";
        }
        
        results.push_back(result);
        tablePrinter.addRow(result);
    };
    benchmark("SOA_event_allDataProduct", SOA_event_allDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_event_all.root", nThreads);
    benchmark("SOA_event_perDataProduct", SOA_event_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_event_perData.root", nThreads);
    benchmark("SOA_event_perGroup", SOA_event_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_event_perGroup.root", nThreads);
    benchmark("SOA_spill_allDataProduct", SOA_spill_allDataProduct, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_spill_all.root", nThreads);
    benchmark("SOA_spill_perDataProduct", SOA_spill_perDataProduct, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_spill_perData.root", nThreads);
    benchmark("SOA_spill_perGroup", SOA_spill_perGroup, numEvents, numSpills, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_spill_perGroup.root", nThreads);
    benchmark("SOA_topObject_perDataProduct", SOA_topObject_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_topObject_perData.root", nThreads);
    benchmark("SOA_topObject_perGroup", SOA_topObject_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_topObject_perGroup.root", nThreads);
    benchmark("SOA_element_perDataProduct", SOA_element_perDataProduct, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_element_perData.root", nThreads);
    benchmark("SOA_element_perGroup", SOA_element_perGroup, numEvents, hitsPerEvent, wiresPerEvent, roisPerWire, outputDir + "/soa_element_perGroup.root", nThreads);

    tablePrinter.printFooter();
    return results;
} 