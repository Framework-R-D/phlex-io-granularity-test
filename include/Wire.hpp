#pragma once

#include <vector>
#include <random>
#include <TObject.h>
#include "Hit.hpp"


/**
 * @class WireVector
 * @brief Container for multiple wires in an event, with flattened ROI data.
 *
 * Stores wire channels, views, and ROI (offsets + data) vectors.
 * Supports ROOT I/O via ClassDef and getters.
 */
class WireVector  {
public:
    long long EventID;
    std::vector<unsigned int> fWire_Channel;
    std::vector<int> fWire_View;
    std::vector<unsigned int> fSignalROI_nROIs;
    std::vector<std::size_t> fSignalROI_offsets;
    std::vector<float> fSignalROI_data;

    WireVector() = default;
    
    std::vector<unsigned int>& getWire_Channel() { return fWire_Channel; }
    const std::vector<unsigned int>& getWire_Channel() const { return fWire_Channel; }
    std::vector<int>& getWire_View() { return fWire_View; }
    const std::vector<int>& getWire_View() const { return fWire_View; }
    std::vector<unsigned int>& getSignalROI_nROIs() { return fSignalROI_nROIs; }
    const std::vector<unsigned int>& getSignalROI_nROIs() const { return fSignalROI_nROIs; }
    std::vector<std::size_t>& getSignalROI_offsets() { return fSignalROI_offsets; }
    const std::vector<std::size_t>& getSignalROI_offsets() const { return fSignalROI_offsets; }
    std::vector<float>& getSignalROI_data() { return fSignalROI_data; }
    const std::vector<float>& getSignalROI_data() const { return fSignalROI_data; }
    ClassDef(WireVector, 3)
};

// Forward-declare the struct and its generator function
struct WireIndividual;
WireIndividual generateRandomWireIndividual(long long eventID, int nROIs, std::mt19937& rng);

/**
 * @struct RegionOfInterest
 * @brief Single ROI with offset and data vector.
 *
 * Used in WireIndividual for per-wire ROIs.
 * Supports ROOT I/O via ClassDef.
 */
struct RegionOfInterest {
    std::size_t offset;
    std::vector<float> data;

    RegionOfInterest() = default;
    
    ClassDef(RegionOfInterest, 3)
};
using RegionsOfInterest_t = std::vector<RegionOfInterest>;

/**
 * @struct WireIndividual
 * @brief Represents a single wire with individual attributes and ROI vector.
 *
 * Non-vectorized wire storage; supports ROOT I/O via ClassDef.
 */
struct WireIndividual {
    long long EventID;
    unsigned int fWire_Channel;
    int fWire_View;
    RegionsOfInterest_t fSignalROI;

    WireIndividual() = default;
    
    WireIndividual(const RegionsOfInterest_t& roi, unsigned int channel, int view)
        : fWire_Channel(channel), fWire_View(view), fSignalROI(roi) {}

    RegionsOfInterest_t& getSignalROI() { return fSignalROI; }
    const RegionsOfInterest_t& getSignalROI() const { return fSignalROI; }
    ClassDef(WireIndividual, 3)
}; 

// Ensure SOAROI, SOAWire are present
struct SOAROI {
    std::vector<float> data;
    ClassDef(SOAROI, 1);
};

struct SOAWire {
    long long EventID;
    unsigned int Channel;
    int View;
    std::vector<SOAROI> ROIs;
    ClassDef(SOAWire, 1);
};

// For element perGroup wires without ROIs
struct SOAWireBase {
    long long EventID;
    unsigned int Channel;
    int View;
    ClassDef(SOAWireBase, 1);
};

// For flattened ROI with WireID in element
struct FlatSOAROI {
    unsigned int EventID;   // Parent event identifier
    unsigned int WireID;    // Row index (or channel) of the parent wire within the event
    std::vector<float> data;
    ClassDef(FlatSOAROI, 2);
};

struct SOAWireVector {
    std::vector<long long> EventIDs;
    std::vector<unsigned int> Channels;
    std::vector<int> Views;
    std::vector<std::vector<SOAROI>> ROIs;
    ClassDef(SOAWireVector, 1);
};

struct EventSOA {
    SOAHitVector hits;
    SOAWireVector wires;
    ClassDef(EventSOA, 1);
}; 