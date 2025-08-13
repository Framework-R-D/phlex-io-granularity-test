#include "HitWireGenerators.hpp"
#include "Wire.hpp"
#include <random>

HitVector generateRandomHitVector(long long eventID, int hitsPerEvent, std::mt19937& rng) {
    std::uniform_int_distribution<unsigned int> distChannel(0, 999);
    std::uniform_int_distribution<int> distTick(0, 5000);
    std::uniform_real_distribution<float> distFloat(0.0f, 100.0f);
    std::uniform_int_distribution<short> distShort(0, 10);
    std::uniform_int_distribution<int> distInt(0, 100);
    std::uniform_int_distribution<int> distEnum(0, 6);
    std::uniform_int_distribution<int> distSigEnum(0, 2);

    HitVector hit;
    hit.EventID = eventID;
    
    for (int hitIndex = 0; hitIndex < hitsPerEvent; ++hitIndex) {
        unsigned int channel = distChannel(rng);
        int start_tick = distTick(rng);
        int end_tick = start_tick + distTick(rng) % 100;
        float peak_time = distFloat(rng);
        float sigma_peak_time = distFloat(rng);
        float rms = distFloat(rng);
        float peak_amplitude = distFloat(rng);
        float sigma_peak_amplitude = distFloat(rng);
        float ROIsummedADC = distFloat(rng);
        float HitsummedADC = distFloat(rng);
        float hit_integral = distFloat(rng);
        float hit_sigma_integral = distFloat(rng);
        short multiplicity = distShort(rng);
        short local_index = distShort(rng);
        float goodness_of_fit = distFloat(rng);
        int dof = distInt(rng);
        int view = distEnum(rng);
        int signal_type = distSigEnum(rng);
        int cryo = distInt(rng);
        int tpc = distInt(rng);
        int plane = distInt(rng);
        int wire = distInt(rng);

        hit.getChannel().push_back(channel);
        hit.getView().push_back(view);
        hit.getStartTick().push_back(start_tick);
        hit.getEndTick().push_back(end_tick);
        hit.getPeakTime().push_back(peak_time);
        hit.getSigmaPeakTime().push_back(sigma_peak_time);
        hit.getRMS().push_back(rms);
        hit.getPeakAmplitude().push_back(peak_amplitude);
        hit.getSigmaPeakAmplitude().push_back(sigma_peak_amplitude);
        hit.getROISummedADC().push_back(ROIsummedADC);
        hit.getHitSummedADC().push_back(HitsummedADC);
        hit.getIntegral().push_back(hit_integral);
        hit.getSigmaIntegral().push_back(hit_sigma_integral);
        hit.getMultiplicity().push_back(multiplicity);
        hit.getLocalIndex().push_back(local_index);
        hit.getGoodnessOfFit().push_back(goodness_of_fit);
        hit.getNDF().push_back(dof);
        hit.getSignalType().push_back(signal_type);
        hit.getWireID_Cryostat().push_back(cryo);
        hit.getWireID_TPC().push_back(tpc);
        hit.getWireID_Plane().push_back(plane);
        hit.getWireID_Wire().push_back(wire);
    }
    return hit;
}

WireVector generateRandomWireVector(long long eventID, int wiresPerEvent, int roisPerWire, std::mt19937& rng) {
    std::uniform_int_distribution<unsigned int> distWireChannel(0, 1023);
    std::uniform_int_distribution<int> distWireEnum(0, 6);
    std::uniform_int_distribution<int> distOffset(0, 500);
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);

    WireVector wire;
    wire.EventID = eventID;
    
    for (int wireIndex = 0; wireIndex < wiresPerEvent; ++wireIndex) {
        unsigned int wire_channel = distWireChannel(rng);
        int wire_view = distWireEnum(rng);
        wire.getWire_Channel().push_back(wire_channel);
        wire.getWire_View().push_back(wire_view);
        // ROI flattening
        wire.getSignalROI_nROIs().push_back(roisPerWire);
        for (int roiIndex = 0; roiIndex < roisPerWire; ++roiIndex) {
            std::size_t offset = distOffset(rng);
            constexpr int size = 1;  // Fixed size for ROI data vector
            wire.getSignalROI_offsets().push_back(offset);
            for (int dataIndex = 0; dataIndex < size; ++dataIndex) {
                float val = distADC(rng);
                wire.getSignalROI_data().push_back(val);
            }
        }
    }
    return wire;
}

// Overload for backward compatibility – forwards to the 3-parameter version with roisPerWire = wiresPerEvent
WireVector generateRandomWireVector(long long eventID, int wiresPerEvent, std::mt19937& rng) {
    return generateRandomWireVector(eventID, wiresPerEvent, wiresPerEvent, rng);
}

HitIndividual generateRandomHitIndividual(long long eventID, std::mt19937& rng) {
    std::uniform_int_distribution<unsigned int> distChannel(0, 999);
    std::uniform_int_distribution<int> distTick(0, 5000);
    std::uniform_real_distribution<float> distFloat(0.0f, 100.0f);
    std::uniform_int_distribution<short> distShort(0, 10);
    std::uniform_int_distribution<int> distInt(0, 100);
    std::uniform_int_distribution<int> distEnum(0, 6);
    std::uniform_int_distribution<int> distSigEnum(0, 2);

    HitIndividual hit;
    hit.EventID = eventID;
    hit.fChannel = distChannel(rng);
    hit.fView = distEnum(rng);
    hit.fStartTick = distTick(rng);
    hit.fEndTick = hit.fStartTick + distTick(rng) % 100;
    hit.fPeakTime = distFloat(rng);
    hit.fSigmaPeakTime = distFloat(rng);
    hit.fRMS = distFloat(rng);
    hit.fPeakAmplitude = distFloat(rng);
    hit.fSigmaPeakAmplitude = distFloat(rng);
    hit.fROISummedADC = distFloat(rng);
    hit.fHitSummedADC = distFloat(rng);
    hit.fIntegral = distFloat(rng);
    hit.fSigmaIntegral = distFloat(rng);
    hit.fMultiplicity = distShort(rng);
    hit.fLocalIndex = distShort(rng);
    hit.fGoodnessOfFit = distFloat(rng);
    hit.fNDF = distInt(rng);
    hit.fSignalType = distSigEnum(rng);
    hit.fWireID_Cryostat = distInt(rng);
    hit.fWireID_TPC = distInt(rng);
    hit.fWireID_Plane = distInt(rng);
    hit.fWireID_Wire = distInt(rng);
    return hit;
}

WireIndividual generateRandomWireIndividual(long long eventID, int numROIs, std::mt19937& rng) {
    std::uniform_int_distribution<unsigned int> distWireChannel(0, 1023);
    std::uniform_int_distribution<int> distWireEnum(0, 6);
    std::uniform_int_distribution<int> distOffset(0, 500);
    std::uniform_real_distribution<float> distADC(0.0f, 100.0f);

    WireIndividual wire;
    wire.EventID = eventID;
    wire.fWire_Channel = distWireChannel(rng);
    wire.fWire_View = distWireEnum(rng);

    for (int roiIndex = 0; roiIndex < numROIs; ++roiIndex) {
        RegionOfInterest roi;
        roi.offset = distOffset(rng);
        constexpr int size = 10;  // Fixed size for ROI data vector
        
        for (int dataIndex = 0; dataIndex < size; ++dataIndex) {
            float val = distADC(rng);
            roi.data.push_back(val);
        }
        
        wire.fSignalROI.push_back(std::move(roi));
    }
    return wire;
}

// Overload for backward compatibility – forwards to the 3-parameter version (ignores the second int parameter)
WireIndividual generateRandomWireIndividual(long long eventID, int /*dummyROIs*/, int numROIs, std::mt19937& rng) {
    return generateRandomWireIndividual(eventID, numROIs, rng);
}

