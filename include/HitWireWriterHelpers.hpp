#pragma once
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

struct FlatROI {
    unsigned int EventID;   // parent event
    unsigned int WireID;    // row index / channel within event
    std::size_t  offset;
    std::vector<float> data;
    ClassDef(FlatROI, 2);
};

std::vector<HitIndividual> generateEventHits(long long eventID, int numHits, std::mt19937& rng);
std::vector<WireIndividual> generateEventWires(long long eventID, int numWires, int roisPerWire, std::mt19937& rng);
std::vector<FlatROI> flattenROIs(const std::vector<WireIndividual>& wires);

struct EventAOS {
    std::vector<HitIndividual> hits;
    std::vector<WireIndividual> wires;
    ClassDef(EventAOS, 1);
};

auto CreateAOSAllDataProductModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateAOSHitsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateAOSWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateAOSROIsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateAOSBaseWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;

double RunAOS_event_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);
double RunAOS_event_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);
double RunAOS_event_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire); 
double RunAOS_spill_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire);
double RunAOS_spill_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire);
double RunAOS_spill_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire); 

HitIndividual generateSingleHit(long long id, std::mt19937& rng);
WireIndividual generateSingleWire(long long id, int roisPerWire, std::mt19937& rng);

double RunAOS_topObject_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, std::mutex& mutex, int roisPerWire);
double RunAOS_topObject_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry, std::mutex& mutex, int roisPerWire); 

struct WireBase {
    long long EventID;
    unsigned int fWire_Channel;
    int fWire_View;
    ClassDef(WireBase, 1);
};

WireBase extractWireBase(const WireIndividual& wire); 

struct WireROI {
    long long EventID;
    unsigned int fWire_Channel;
    int fWire_View;
    RegionOfInterest roi;
    ClassDef(WireROI, 1);
};

std::vector<WireROI> flattenWiresToROIs(const std::vector<WireIndividual>& wires); 

double RunAOS_element_hitsWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex);
double RunAOS_element_wireROIWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire);
double RunAOS_element_wiresWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex);
double RunAOS_element_roisWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire); 

// SOA Declarations
SOAHitVector generateSOAEventHits(long long eventID, int numHits, std::mt19937& rng);
SOAWireVector generateSOAEventWires(long long eventID, int numWires, int roisPerWire, std::mt19937& rng);
std::vector<SOAROI> flattenSOAROIs(const SOAWireVector& wires);
std::vector<SOAWireBase> extractSOABaseWires(const SOAWireVector& wires);

auto CreateSOAAllDataProductModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateSOAHitsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateSOAWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateSOAROIsModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;
auto CreateSOABaseWiresModelAndToken() -> std::pair<std::unique_ptr<ROOT::RNTupleModel>, ROOT::RFieldToken>;

double RunSOA_event_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);
double RunSOA_event_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire);
double RunSOA_event_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int hitsPerEvent, int wiresPerEvent, int roisPerWire); 

// Spill generation
SOAHitVector generateSOASpillHits(long long spillID, int adjustedHits, std::mt19937& rng);
SOAWireVector generateSOASpillWires(long long spillID, int adjustedWires, int roisPerWire, std::mt19937& rng);

// Single for topObject/element
SOAHit generateSOASingleHit(long long id, std::mt19937& rng);
SOAWire generateSOASingleWire(long long id, int roisPerWire, std::mt19937& rng);
FlatSOAROI generateSOASingleROI(unsigned int eventID, unsigned int wireID, std::mt19937& rng);
std::vector<FlatSOAROI> flattenSOAROIsWithID(const SOAWireVector& wires);

// SOA spill work funcs
double RunSOA_spill_allDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::Experimental::Detail::RRawPtrWriteEntry& entry, ROOT::RFieldToken token, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire);
double RunSOA_spill_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire);
double RunSOA_spill_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& hitsEntry, ROOT::RFieldToken hitsToken, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& wiresEntry, ROOT::RFieldToken wiresToken, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::Experimental::Detail::RRawPtrWriteEntry& roisEntry, ROOT::RFieldToken roisToken, std::mutex& mutex, int numSpills, int adjustedHits, int adjustedWires, int roisPerWire);

// Update declarations for AOS_topObject_perDataProductWorkFunc and AOS_topObject_perGroupWorkFunc to use REntry without tokens

double RunAOS_topObject_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, std::mutex& mutex, int roisPerWire);
double RunAOS_topObject_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry, std::mutex& mutex, int roisPerWire);
// Element work funcs
double RunSOA_element_hitsWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex);
double RunSOA_element_wiresWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex);
double RunSOA_element_roisWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire);
double RunSOA_element_wireROIFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& context, ROOT::REntry& entry, std::mutex& mutex, int roisPerWire); 

double RunSOA_topObject_perDataProductWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, std::mutex& mutex, int roisPerWire);
double RunSOA_topObject_perGroupWorkFunc(int first, int last, unsigned seed, ROOT::Experimental::RNTupleFillContext& hitsContext, ROOT::REntry& hitsEntry, ROOT::Experimental::RNTupleFillContext& wiresContext, ROOT::REntry& wiresEntry, ROOT::Experimental::RNTupleFillContext& roisContext, ROOT::REntry& roisEntry, std::mutex& mutex, int roisPerWire); 