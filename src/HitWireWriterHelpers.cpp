#include "HitWireWriterHelpers.hpp"
#include "HitWireGenerators.hpp"
#include "Hit.hpp"
#include "Wire.hpp"
#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RFieldToken.hxx>
#include <ROOT/RRawPtrWriteEntry.hxx>
#include <ROOT/RNTupleFillContext.hxx>
#include <ROOT/RNTupleFillStatus.hxx>
#include <unordered_map>
#include <random>
#include <vector>
#include <mutex>
#include <TStopwatch.h>

// Data generation (adapt from existing generators)
std::vector<HitIndividual> generateEventHits(long long eventID, int numHits, std::mt19937& rng) {
    std::vector<HitIndividual> hits;
    for (int i = 0; i < numHits; ++i) {
        hits.push_back(generateRandomHitIndividual(eventID, rng)); // Assume this exists or implement
    }
    return hits;
}

std::vector<WireIndividual> generateEventWires(long long eventID, int numWires, int roisPerWire, std::mt19937& rng) {
    std::vector<WireIndividual> wires;
    for (int i = 0; i < numWires; ++i) {
        wires.push_back(generateRandomWireIndividual(eventID, roisPerWire, rng));
    }
    return wires;
}

// Flatten ROIs with WireID (assume WireID from fWire_Channel for simplicity)
std::vector<FlatROI> flattenROIs(const std::vector<WireIndividual>& wires) {
    std::vector<FlatROI> flatROIs;
    for (const auto& wire : wires) {
        unsigned int wireID = wire.fWire_Channel;
        for (const auto& roi : wire.getSignalROI()) {
            FlatROI flat;
            flat.EventID = wire.EventID;
            flat.WireID  = wireID;
            flat.offset = roi.offset;
            flat.data = roi.data;
            flatROIs.push_back(flat);
        }
    }
    return flatROIs;
}

std::vector<WireROI> flattenWiresToROIs(const std::vector<WireIndividual>& allWires) {
    std::vector<WireROI> wireROIs;
    for (const auto& wire : allWires) {
        for (const auto& roi : wire.getSignalROI()) {
            WireROI wroi;
            wroi.EventID = wire.EventID;
            wroi.fWire_Channel = wire.fWire_Channel;
            wroi.fWire_View = wire.fWire_View;
            wroi.roi = roi;
            wireROIs.push_back(wroi);
        }
    }
    return wireROIs;
}

// Model for allDataProduct: struct EventAOS { std::vector<HitIndividual> hits; std::vector<WireIndividual> wires; }
auto CreateAOSAllDataProductModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<EventAOS>("EventAOS");
    return {std::move(model), model->GetToken("EventAOS")};
}

// Model for perDataProduct: separate hits and wires models
auto CreateAOSHitsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<HitIndividual>>("hits");
    return {std::move(model), model->GetToken("hits")};
}
auto CreateAOSWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<WireIndividual>>("wires");
    return {std::move(model), model->GetToken("wires")};
}

// Model for perGroup: hits, wires, rois separately
auto CreateAOSROIsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<FlatROI>>("rois");
    return {std::move(model), model->GetToken("rois")};
}

auto CreateAOSBaseWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<WireBase>>("wires");
    return {std::move(model), model->GetToken("wires")};
}

// Work function for allDataProduct
double RunAOS_event_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        EventAOS eventData;
        eventData.hits = generateEventHits(evt, hitsPerEvent, rng);
        eventData.wires = generateEventWires(evt, wiresPerEvent, roisPerWire, rng);
        sw.Start();
        entry.BindRawPtr(token, &eventData);
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

// Work function for perDataProduct
double RunAOS_event_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        auto hits = generateEventHits(evt, hitsPerEvent, rng);
        auto wires = generateEventWires(evt, wiresPerEvent, roisPerWire, rng);
        sw.Start();
        // Fill hits
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        // Fill wires
        wiresEntry.BindRawPtr(wiresToken, &wires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

// Work function for perGroup
double RunAOS_event_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        auto hits = generateEventHits(evt, hitsPerEvent, rng);
        auto wires = generateEventWires(evt, wiresPerEvent, roisPerWire, rng);
        auto rois = flattenROIs(wires);
        std::vector<WireBase> baseWires;
        for(const auto& w : wires) baseWires.push_back(extractWireBase(w));
        sw.Start();
        // Fill hits
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        // Fill wires (without ROIs? or with empty? Assuming wires still include non-ROI fields)
        wiresEntry.BindRawPtr(wiresToken, &baseWires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        // Fill rois
        roisEntry.BindRawPtr(roisToken, &rois);
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
} 

// Adjusted generation (can reuse existing with adjusted counts)
// No change needed if passing adjusted params

// Work function for spill allDataProduct
double RunAOS_spill_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        int spill = idx % numSpills;
        EventAOS spillData;
        spillData.hits = generateEventHits(evt * numSpills + spill, adjustedHits, rng); // Use unique ID
        spillData.wires = generateEventWires(evt * numSpills + spill, adjustedWires, roisPerWire, rng);
        sw.Start();
        entry.BindRawPtr(token, &spillData);
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

// Similar for perDataProduct and perGroup with adjustments
double RunAOS_spill_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        int spill = idx % numSpills;
        auto hits = generateEventHits(evt * numSpills + spill, adjustedHits, rng);
        auto wires = generateEventWires(evt * numSpills + spill, adjustedWires, roisPerWire, rng);
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &wires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

double RunAOS_spill_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        int spill = idx % numSpills;
        auto hits = generateEventHits(evt * numSpills + spill, adjustedHits, rng);
        auto wires = generateEventWires(evt * numSpills + spill, adjustedWires, roisPerWire, rng);
        auto rois = flattenROIs(wires);
        std::vector<WireBase> baseWires;
        for(const auto& w : wires) baseWires.push_back(extractWireBase(w));
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &baseWires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        roisEntry.BindRawPtr(roisToken, &rois);
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
} 

// Single generation functions
HitIndividual generateSingleHit(long long id, std::mt19937& rng) {
    return generateRandomHitIndividual(id, rng); // Assume exists
}

WireIndividual generateSingleWire(long long id, int roisPerWire, std::mt19937& rng) {
    return generateRandomWireIndividual(id, roisPerWire, rng);
}

// Struct for topObject allDataProduct (but skipped), for perDataProduct: perhaps pair or separate
// For 3.2: perDataProduct stores single hit and single wire in separate RNTuples per row

// Work for 3.2
// Adjust RunAOS_topObject_perDataProductWorkFunc and RunAOS_topObject_perGroupWorkFunc to use REntry: GetPtr, set values, context.Fill(entry)

double RunAOS_topObject_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = hitsEntry.GetPtr<HitIndividual>("hit");
    auto wirePtr = wiresEntry.GetPtr<WireIndividual>("wire");
    for (int idx = first; idx < last; ++idx) {
        HitIndividual hit = generateSingleHit(idx, rng);
        WireIndividual wire = generateSingleWire(idx, roisPerWire, rng);
        sw.Start();
        *hitPtr = hit;
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        *wirePtr = wire;
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    { std::lock_guard<std::mutex> lock(mutex);
      hitsContext.FlushCluster();
      wiresContext.FlushCluster(); }
    return totalTime;
}

double RunAOS_topObject_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = hitsEntry.GetPtr<HitIndividual>("hit");
    auto wirePtr = wiresEntry.GetPtr<WireBase>("wire");
    auto roisPtr = roisEntry.GetPtr<std::vector<FlatROI>>("rois");
    for (int idx = first; idx < last; ++idx) {
        HitIndividual hit = generateSingleHit(idx, rng);
        WireIndividual fullWire = generateSingleWire(idx, roisPerWire, rng);
        WireBase wire = extractWireBase(fullWire);
        auto rois = flattenROIs({fullWire});
        sw.Start();
        *hitPtr = hit;
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        *wirePtr = wire;
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        *roisPtr = rois;
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    { std::lock_guard<std::mutex> lock(mutex);
      hitsContext.FlushCluster();
      wiresContext.FlushCluster();
      roisContext.FlushCluster(); }
    return totalTime;
}

// For 3.3: perGroup with flattened ROIs (multiple per wire)
WireBase extractWireBase(const WireIndividual& wire) {
    WireBase base;
    base.EventID = wire.EventID;
    base.fWire_Channel = wire.fWire_Channel;
    base.fWire_View = wire.fWire_View;
    return base;
}



double RunAOS_element_hitsWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = entry.GetPtr<HitIndividual>("hit");
    for (int idx = first; idx < last; ++idx) {
        *hitPtr = generateSingleHit(idx, rng);
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

double RunAOS_element_wireROIWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);
    double totalTime = 0.0;
    auto wroiPtr = entry.GetPtr<WireROI>("wire_roi");
    for (int idx = first; idx < last; ++idx) {
        wroiPtr->EventID = idx / roisPerWire;
        wroiPtr->fWire_Channel = rng() % 1024;
        wroiPtr->fWire_View = rng() % 7;
        wroiPtr->roi.offset = rng() % 500;
        wroiPtr->roi.data.resize(10);
        for (auto& val : wroiPtr->roi.data) val = distADC(rng);
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

double RunAOS_element_wiresWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto wirePtr = entry.GetPtr<WireBase>("wire");
    for (int idx = first; idx < last; ++idx) {
        wirePtr->EventID = idx;
        wirePtr->fWire_Channel = rng() % 1024;
        wirePtr->fWire_View = rng() % 7;
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

double RunAOS_element_roisWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);
    double totalTime = 0.0;
    auto roiPtr = entry.GetPtr<FlatROI>("roi");
    for (int idx = first; idx < last; ++idx) {
        unsigned int eventID = idx / (roisPerWire * 1000000); // rough grouping; adjust as needed
        unsigned int wireIdx = (idx / roisPerWire) % 1000000;
        roiPtr->EventID = eventID;
        roiPtr->WireID  = wireIdx;
        roiPtr->offset  = rng() % 500;
        roiPtr->data.resize(10);
        for (auto& val : roiPtr->data) val = distADC(rng);
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

// Combined hits + wireROI per-event work function for element_perDataProduct (single pass)
double RunAOS_element_perDataProductCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wireROIContext, ROOT::REntry& wireROIEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);
    double totalTime = 0.0;

    auto hitPtr   = hitsEntry.GetPtr<HitIndividual>("hit");
    auto wroiPtr  = wireROIEntry.GetPtr<WireROI>("wire_roi");

    for (int evt = firstEvt; evt < lastEvt; ++evt) {
        // hits
        for (int h = 0; h < hitsPerEvent; ++h) {
            *hitPtr = generateSingleHit(static_cast<long long>(evt) * hitsPerEvent + h, rng);
            sw.Start();
            ROOT::RNTupleFillStatus hitStatus;
            hitsContext.FillNoFlush(hitsEntry, hitStatus);
            if (hitStatus.ShouldFlushCluster()) {
                hitsContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
            }
            totalTime += sw.RealTime();
        }
        // wire ROIs: generate wiresPerEvent wires, each with roisPerWire ROIs
        for (int w = 0; w < wiresPerEvent; ++w) {
            long long wireGlobalID = static_cast<long long>(evt) * wiresPerEvent + w;
            for (int r = 0; r < roisPerWire; ++r) {
                wroiPtr->EventID       = evt;
                wroiPtr->fWire_Channel = rng() % 1024;
                wroiPtr->fWire_View    = rng() % 7;
                wroiPtr->roi.offset    = rng() % 500;
                wroiPtr->roi.data.resize(10);
                for (auto& val : wroiPtr->roi.data) val = distADC(rng);
                sw.Start();
                ROOT::RNTupleFillStatus wroiStatus;
                wireROIContext.FillNoFlush(wireROIEntry, wroiStatus);
                if (wroiStatus.ShouldFlushCluster()) {
                    wireROIContext.FlushColumns();
                    { std::lock_guard<std::mutex> lock(mutex); wireROIContext.FlushCluster(); }
                }
                totalTime += sw.RealTime();
            }
        }
    }
    // Flush once per thread to minimise contention
    {
        std::lock_guard<std::mutex> lock(mutex);
        hitsContext.FlushCluster();
        wireROIContext.FlushCluster();
    }
    return totalTime;
}

// Combined hits + wires + ROIs per-event work function for element_perGroup (single pass)

// Combined hits + wireROI per-event work function for SOA_element_perDataProduct (single pass)
double RunSOA_element_perDataProductCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;

    auto hitPtr  = hitsEntry.GetPtr<SOAHit>("hit");
    auto roiPtr  = roisEntry.GetPtr<FlatSOAROI>("roi");

    for (int evt = firstEvt; evt < lastEvt; ++evt) {
        for (int h = 0; h < hitsPerEvent; ++h) {
            *hitPtr = generateSOASingleHit(static_cast<long long>(evt) * hitsPerEvent + h, rng);
            sw.Start();
            ROOT::RNTupleFillStatus hitStatus;
            hitsContext.FillNoFlush(hitsEntry, hitStatus);
            totalTime += sw.RealTime();
            if (hitStatus.ShouldFlushCluster()) {
                hitsContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
            }
        }
        for (int w = 0; w < wiresPerEvent; ++w) {
            for (int r = 0; r < roisPerWire; ++r) {
                *roiPtr = generateSOASingleROI(evt, static_cast<unsigned int>(w), rng);
                sw.Start();
                ROOT::RNTupleFillStatus roiStatus;
                roisContext.FillNoFlush(roisEntry, roiStatus);
                totalTime += sw.RealTime();
                if (roiStatus.ShouldFlushCluster()) {
                    roisContext.FlushColumns();
                    { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
                }
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        hitsContext.FlushCluster();
        roisContext.FlushCluster();
    }
    return totalTime;
}

// Combined hits + wires + ROIs per-event work function for element_perGroup (single pass)
double RunAOS_element_perGroupCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);
    double totalTime = 0.0;

    auto hitPtr  = hitsEntry.GetPtr<HitIndividual>("hit");
    auto wirePtr = wiresEntry.GetPtr<WireBase>("wire");
    auto roiPtr  = roisEntry.GetPtr<FlatROI>("roi");

    for (int evt = firstEvt; evt < lastEvt; ++evt) {
        // hits
        for (int h = 0; h < hitsPerEvent; ++h) {
            *hitPtr = generateSingleHit(static_cast<long long>(evt) * hitsPerEvent + h, rng);
            sw.Start();
            ROOT::RNTupleFillStatus hitStatus;
            hitsContext.FillNoFlush(hitsEntry, hitStatus);
            if (hitStatus.ShouldFlushCluster()) {
                hitsContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
            }
            totalTime += sw.RealTime();
        }
        // wires & ROIs
        for (int w = 0; w < wiresPerEvent; ++w) {
            // base wire
            wirePtr->EventID = evt;
            wirePtr->fWire_Channel = rng() % 1024;
            wirePtr->fWire_View    = rng() % 7;
            sw.Start();
            ROOT::RNTupleFillStatus wireStatus;
            wiresContext.FillNoFlush(wiresEntry, wireStatus);
            totalTime += sw.RealTime();
            if (wireStatus.ShouldFlushCluster()) {
                wiresContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
            }

            // its ROIs
            for (int r = 0; r < roisPerWire; ++r) {
                roiPtr->EventID = evt;
                roiPtr->WireID  = w;
                roiPtr->offset = rng() % 500;
                roiPtr->data.resize(10);
                for (auto& val : roiPtr->data) val = distADC(rng);
                sw.Start();
                ROOT::RNTupleFillStatus roiStatus;
                roisContext.FillNoFlush(roisEntry, roiStatus);
                totalTime += sw.RealTime();
                if (roiStatus.ShouldFlushCluster()) {
                    roisContext.FlushColumns();
                    { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
                }
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        hitsContext.FlushCluster();
        wiresContext.FlushCluster();
        roisContext.FlushCluster();
    }
    return totalTime;
}



// Combined hits + wires + ROIs per-event work function for SOA_element_perGroup (single pass)
double RunSOA_element_perGroupCombinedWorkFunc(int firstEvt, int lastEvt, unsigned seed,
    ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry,
    ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry,
    ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry,
    std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;

    auto hitPtr  = hitsEntry.GetPtr<SOAHit>("hit");
    auto wirePtr = wiresEntry.GetPtr<SOAWireBase>("wire");
    auto roiPtr  = roisEntry.GetPtr<FlatSOAROI>("roi");

    for (int evt = firstEvt; evt < lastEvt; ++evt) {
        for (int h = 0; h < hitsPerEvent; ++h) {
            *hitPtr = generateSOASingleHit(static_cast<long long>(evt) * hitsPerEvent + h, rng);
            sw.Start();
            ROOT::RNTupleFillStatus hitStatus;
            hitsContext.FillNoFlush(hitsEntry, hitStatus);
            totalTime += sw.RealTime();
            if (hitStatus.ShouldFlushCluster()) {
                hitsContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
            }
        }
        for (int w = 0; w < wiresPerEvent; ++w) {
            wirePtr->EventID = evt;
            wirePtr->Channel = rng() % 1024;
            wirePtr->View    = rng() % 7;
            sw.Start();
            ROOT::RNTupleFillStatus wireStatus;
            wiresContext.FillNoFlush(wiresEntry, wireStatus);
            totalTime += sw.RealTime();
            if (wireStatus.ShouldFlushCluster()) {
                wiresContext.FlushColumns();
                { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
            }
            for (int r = 0; r < roisPerWire; ++r) {
                *roiPtr = generateSOASingleROI(evt, w, rng);
                sw.Start();
                ROOT::RNTupleFillStatus roiStatus;
                roisContext.FillNoFlush(roisEntry, roiStatus);
                totalTime += sw.RealTime();
                if (roiStatus.ShouldFlushCluster()) {
                    roisContext.FlushColumns();
                    { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
                }
            }
        }
    }
    {
        std::lock_guard<std::mutex> lock(mutex);
        hitsContext.FlushCluster();
        wiresContext.FlushCluster();
        roisContext.FlushCluster();
    }
    return totalTime;
}

// SOA Data Generation
SOAHitVector generateSOAEventHits(long long eventID, int numHits, std::mt19937& rng) {
    SOAHitVector hits;
    hits.EventIDs.resize(numHits, eventID);
    hits.Channels.resize(numHits);
    hits.Views.resize(numHits);
    hits.StartTicks.resize(numHits);
    hits.EndTicks.resize(numHits);
    hits.PeakTimes.resize(numHits);
    hits.SigmaPeakTimes.resize(numHits);
    hits.RMSs.resize(numHits);
    hits.PeakAmplitudes.resize(numHits);
    hits.SigmaPeakAmplitudes.resize(numHits);
    hits.ROISummedADCs.resize(numHits);
    hits.HitSummedADCs.resize(numHits);
    hits.Integrals.resize(numHits);
    hits.SigmaIntegrals.resize(numHits);
    hits.Multiplicities.resize(numHits);
    hits.LocalIndices.resize(numHits);
    hits.GoodnessOfFits.resize(numHits);
    hits.NDFs.resize(numHits);
    hits.SignalTypes.resize(numHits);
    hits.WireID_Cryostats.resize(numHits);
    hits.WireID_TPCs.resize(numHits);
    hits.WireID_Planes.resize(numHits);
    hits.WireID_Wires.resize(numHits);
    for (int i = 0; i < numHits; ++i) {
        HitIndividual temp = generateRandomHitIndividual(eventID, rng);
        hits.Channels[i] = temp.fChannel;
        hits.Views[i] = temp.fView;
        hits.StartTicks[i] = temp.fStartTick;
        hits.EndTicks[i] = temp.fEndTick;
        hits.PeakTimes[i] = temp.fPeakTime;
        hits.SigmaPeakTimes[i] = temp.fSigmaPeakTime;
        hits.RMSs[i] = temp.fRMS;
        hits.PeakAmplitudes[i] = temp.fPeakAmplitude;
        hits.SigmaPeakAmplitudes[i] = temp.fSigmaPeakAmplitude;
        hits.ROISummedADCs[i] = temp.fROISummedADC;
        hits.HitSummedADCs[i] = temp.fHitSummedADC;
        hits.Integrals[i] = temp.fIntegral;
        hits.SigmaIntegrals[i] = temp.fSigmaIntegral;
        hits.Multiplicities[i] = temp.fMultiplicity;
        hits.LocalIndices[i] = temp.fLocalIndex;
        hits.GoodnessOfFits[i] = temp.fGoodnessOfFit;
        hits.NDFs[i] = temp.fNDF;
        hits.SignalTypes[i] = temp.fSignalType;
        hits.WireID_Cryostats[i] = temp.fWireID_Cryostat;
        hits.WireID_TPCs[i] = temp.fWireID_TPC;
        hits.WireID_Planes[i] = temp.fWireID_Plane;
        hits.WireID_Wires[i] = temp.fWireID_Wire;
    }
    return hits;
}

SOAWireVector generateSOAEventWires(long long eventID, int numWires, int roisPerWire, std::mt19937& rng) {
    SOAWireVector wires;
    wires.EventIDs.resize(numWires, eventID);
    wires.Channels.resize(numWires);
    wires.Views.resize(numWires);
    wires.ROIs.resize(numWires);
    for (int i = 0; i < numWires; ++i) {
        WireIndividual temp = generateRandomWireIndividual(eventID, roisPerWire, rng);
        wires.Channels[i] = temp.fWire_Channel;
        wires.Views[i] = temp.fWire_View;
        wires.ROIs[i].resize(roisPerWire);
        for (int j = 0; j < roisPerWire; ++j) {
            wires.ROIs[i][j].data = temp.getSignalROI()[j].data;
        }
    }
    return wires;
}

std::vector<SOAROI> flattenSOAROIs(const SOAWireVector& wires) {
    std::vector<SOAROI> flat;
    for (const auto& wireROIs : wires.ROIs) {
        for (const auto& roi : wireROIs) {
            flat.push_back(roi);
        }
    }
    return flat;
}

std::vector<SOAWireBase> extractSOABaseWires(const SOAWireVector& wires) {
    std::vector<SOAWireBase> base(wires.EventIDs.size());
    for (size_t i = 0; i < wires.EventIDs.size(); ++i) {
        base[i].EventID = wires.EventIDs[i];
        base[i].Channel = wires.Channels[i];
        base[i].View = wires.Views[i];
    }
    return base;
}

// SOA Model Creators
auto CreateSOAAllDataProductModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<EventSOA>("EventSOA");
    return {std::move(model), model->GetToken("EventSOA")};
}

auto CreateSOAHitsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<SOAHitVector>("hits");
    return {std::move(model), model->GetToken("hits")};
}

auto CreateSOAWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<SOAWireVector>("wires");
    return {std::move(model), model->GetToken("wires")};
}

auto CreateSOAROIsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<SOAROI>>("rois");
    return {std::move(model), model->GetToken("rois")};
}

auto CreateSOABaseWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken> {
    auto model = ROOT::RNTupleModel::Create();
    model->MakeField<std::vector<SOAWireBase>>("wires");
    return {std::move(model), model->GetToken("wires")};
}

// SOA Work Functions
double RunSOA_event_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        EventSOA eventData;
        eventData.hits = generateSOAEventHits(evt, hitsPerEvent, rng);
        eventData.wires = generateSOAEventWires(evt, wiresPerEvent, roisPerWire, rng);
        sw.Start();
        entry.BindRawPtr(token, &eventData);
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

double RunSOA_event_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        auto hits = generateSOAEventHits(evt, hitsPerEvent, rng);
        auto wires = generateSOAEventWires(evt, wiresPerEvent, roisPerWire, rng);
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &wires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

double RunSOA_event_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int evt = first; evt < last; ++evt) {
        auto hits = generateSOAEventHits(evt, hitsPerEvent, rng);
        auto wires = generateSOAEventWires(evt, wiresPerEvent, roisPerWire, rng);
        auto rois = flattenSOAROIs(wires);
        auto baseWires = extractSOABaseWires(wires);
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &baseWires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        roisEntry.BindRawPtr(roisToken, &rois);
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
} 

// Adjusted for spills (reuse with adjusted counts)
SOAHitVector generateSOASpillHits(long long spillID, int adjustedHits, std::mt19937& rng) {
    return generateSOAEventHits(spillID, adjustedHits, rng);  // Reuse, but with spillID
}

SOAWireVector generateSOASpillWires(long long spillID, int adjustedWires, int roisPerWire, std::mt19937& rng) {
    return generateSOAEventWires(spillID, adjustedWires, roisPerWire, rng);
}

// Single generation for topObject/element
SOAHit generateSOASingleHit(long long id, std::mt19937& rng) {
    HitIndividual temp = generateRandomHitIndividual(id, rng);
    SOAHit hit;
    hit.EventID = temp.EventID;
    hit.Channel = temp.fChannel;
    hit.View = temp.fView;
    hit.StartTick = temp.fStartTick;
    hit.EndTick = temp.fEndTick;
    hit.PeakTime = temp.fPeakTime;
    hit.SigmaPeakTime = temp.fSigmaPeakTime;
    hit.RMS = temp.fRMS;
    hit.PeakAmplitude = temp.fPeakAmplitude;
    hit.SigmaPeakAmplitude = temp.fSigmaPeakAmplitude;
    hit.ROISummedADC = temp.fROISummedADC;
    hit.HitSummedADC = temp.fHitSummedADC;
    hit.Integral = temp.fIntegral;
    hit.SigmaIntegral = temp.fSigmaIntegral;
    hit.Multiplicity = temp.fMultiplicity;
    hit.LocalIndex = temp.fLocalIndex;
    hit.GoodnessOfFit = temp.fGoodnessOfFit;
    hit.NDF = temp.fNDF;
    hit.SignalType = temp.fSignalType;
    hit.WireID_Cryostat = temp.fWireID_Cryostat;
    hit.WireID_TPC = temp.fWireID_TPC;
    hit.WireID_Plane = temp.fWireID_Plane;
    hit.WireID_Wire = temp.fWireID_Wire;
    return hit;
}

SOAWire generateSOASingleWire(long long id, int roisPerWire, std::mt19937& rng) {
    WireIndividual temp = generateRandomWireIndividual(id, roisPerWire, rng);
    SOAWire wire;
    wire.EventID = temp.EventID;
    wire.Channel = temp.fWire_Channel;
    wire.View = temp.fWire_View;
    wire.ROIs.resize(roisPerWire);
    for (int j = 0; j < roisPerWire; ++j) {
        wire.ROIs[j].data = temp.getSignalROI()[j].data;
    }
    return wire;
}

FlatSOAROI generateSOASingleROI(unsigned int eventID, unsigned int wireID, std::mt19937& rng) {
    FlatSOAROI roi;
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);
    roi.EventID = eventID;
    roi.WireID  = wireID;
    roi.data.resize(10);
    for (auto& val : roi.data) val = distADC(rng);
    return roi;
}

std::vector<FlatSOAROI> flattenSOAROIsWithID(const SOAWireVector& wires) {
    std::vector<FlatSOAROI> flat;
    for (size_t w = 0; w < wires.Channels.size(); ++w) {
        for (const auto& roi : wires.ROIs[w]) {
            FlatSOAROI froi;
            froi.EventID = wires.EventIDs[w];
            froi.WireID  = wires.Channels[w];
            froi.data    = roi.data;
            flat.push_back(froi);
        }
    }
    return flat;
}

// SOA spill work functions (mirror AOS but use SOA gen)
double RunSOA_spill_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        long long spillID = evt * numSpills + (idx % numSpills);
        EventSOA spillData;
        spillData.hits = generateSOASpillHits(spillID, adjustedHits, rng);
        spillData.wires = generateSOASpillWires(spillID, adjustedWires, roisPerWire, rng);
        sw.Start();
        entry.BindRawPtr(token, &spillData);
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

double RunSOA_spill_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        long long spillID = evt * numSpills + (idx % numSpills);
        auto hits = generateSOASpillHits(spillID, adjustedHits, rng);
        auto wires = generateSOASpillWires(spillID, adjustedWires, roisPerWire, rng);
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &wires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

double RunSOA_spill_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    for (int idx = first; idx < last; ++idx) {
        int evt = idx / numSpills;
        long long spillID = evt * numSpills + (idx % numSpills);
        auto hits = generateSOASpillHits(spillID, adjustedHits, rng);
        auto wires = generateSOASpillWires(spillID, adjustedWires, roisPerWire, rng);
        auto rois = flattenSOAROIs(wires);
        auto baseWires = extractSOABaseWires(wires);
        sw.Start();
        hitsEntry.BindRawPtr(hitsToken, &hits);
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        wiresEntry.BindRawPtr(wiresToken, &baseWires);
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        roisEntry.BindRawPtr(roisToken, &rois);
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    return totalTime;
}

// For topObject
SOAHit generateSOATopHit(long long id, std::mt19937& rng) {
    return generateSOASingleHit(id, rng);
}

SOAWire generateSOATopWire(long long id, int roisPerWire, std::mt19937& rng) {
    return generateSOASingleWire(id, roisPerWire, rng);
}

double RunSOA_topObject_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = hitsEntry.GetPtr<SOAHit>("hit");
    auto wirePtr = wiresEntry.GetPtr<SOAWire>("wire");
    for (int idx = first; idx < last; ++idx) {
        SOAHit hit = generateSOASingleHit(idx, rng);
        SOAWire wire = generateSOASingleWire(idx, roisPerWire, rng);
        sw.Start();
        *hitPtr = hit;
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        *wirePtr = wire;
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    { std::lock_guard<std::mutex> lock(mutex);
      hitsContext.FlushCluster();
      wiresContext.FlushCluster(); }
    return totalTime;
}

// Add RunSOA_topObject_perGroupWorkFunc similarly, with flattening ROIs to vector<SOAROI> per row (but since per wire, it's the vector in SOAWire; for perGroup, separate base wire and flattened ROIs with WireID).

// For element
double RunSOA_element_hitsWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = entry.GetPtr<SOAHit>("hit");
    for (int idx = first; idx < last; ++idx) {
        *hitPtr = generateSOASingleHit(idx, rng);
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

// Similarly for wires (SOAWireBase), rois (FlatSOAROI or SOAROI with WireID), and wire_roi (SOAWire for perDataProduct).

// TopObject perGroup
double RunSOA_topObject_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto hitPtr = hitsEntry.GetPtr<SOAHit>("hit");
    auto wirePtr = wiresEntry.GetPtr<SOAWireBase>("wire");
    auto roisPtr = roisEntry.GetPtr<std::vector<SOAROI>>("rois");
    for (int idx = first; idx < last; ++idx) {
        SOAHit hit = generateSOASingleHit(idx, rng);
        SOAWire fullWire = generateSOASingleWire(idx, roisPerWire, rng);
        SOAWireBase wireBase;
        wireBase.EventID = fullWire.EventID;
        wireBase.Channel = fullWire.Channel;
        wireBase.View = fullWire.View;
        auto rois = fullWire.ROIs;
        sw.Start();
        *hitPtr = hit;
        ROOT::RNTupleFillStatus hitsStatus;
        hitsContext.FillNoFlush(hitsEntry, hitsStatus);
        if (hitsStatus.ShouldFlushCluster()) {
            hitsContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); hitsContext.FlushCluster(); }
        }
        *wirePtr = wireBase;
        ROOT::RNTupleFillStatus wiresStatus;
        wiresContext.FillNoFlush(wiresEntry, wiresStatus);
        if (wiresStatus.ShouldFlushCluster()) {
            wiresContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); wiresContext.FlushCluster(); }
        }
        *roisPtr = rois;
        ROOT::RNTupleFillStatus roisStatus;
        roisContext.FillNoFlush(roisEntry, roisStatus);
        if (roisStatus.ShouldFlushCluster()) {
            roisContext.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); roisContext.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    { std::lock_guard<std::mutex> lock(mutex);
      hitsContext.FlushCluster();
      wiresContext.FlushCluster();
      roisContext.FlushCluster(); }
    return totalTime;
}

// Element work funcs
double RunSOA_element_wireROIFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto wirePtr = entry.GetPtr<SOAWire>("wire_roi");
    for (int idx = first; idx < last; ++idx) {
        *wirePtr = generateSOASingleWire(idx, roisPerWire, rng);
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

double RunSOA_element_wiresWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto wirePtr = entry.GetPtr<SOAWireBase>("wire");
    for (int idx = first; idx < last; ++idx) {
        wirePtr->EventID = idx;
        wirePtr->Channel = rng() % 1024;
        wirePtr->View = rng() % 7;
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}

double RunSOA_element_roisWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire) {
    std::mt19937 rng(seed);
    TStopwatch sw;
    double totalTime = 0.0;
    auto roiPtr = entry.GetPtr<FlatSOAROI>("roi");
    for (int idx = first; idx < last; ++idx) {
        {
            unsigned int eventID = idx / (roisPerWire); // approximate mapping when standalone
            unsigned int wireIdx = idx % roisPerWire;   // assuming sequential order within event
            *roiPtr = generateSOASingleROI(eventID, wireIdx, rng);
        }
        sw.Start();
        ROOT::RNTupleFillStatus status;
        context.FillNoFlush(entry, status);
        if (status.ShouldFlushCluster()) {
            context.FlushColumns();
            { std::lock_guard<std::mutex> lock(mutex); context.FlushCluster(); }
        }
        totalTime += sw.RealTime();
    }
    std::lock_guard<std::mutex> lock(mutex);
    context.FlushCluster();
    return totalTime;
}