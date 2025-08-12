#pragma once
#include "Hit.hpp"
#include "Wire.hpp"
#include <random>

/**
 * @brief Generates a random HitVector for a given event with specified hits.
 *
 * Populates all fields with random values using the provided RNG.
 * Useful for simulating hit data in tests or benchmarks.
 *
 * @param eventID Event identifier to assign.
 * @param hitsPerEvent Number of hits to generate.
 * @param rng Random number generator (mt19937).
 * @return HitVector with random data.
 */
HitVector generateRandomHitVector(long long eventID, int hitsPerEvent, std::mt19937& rng);

/**
 * @brief Generates a random WireVector for a given event with specified wires and ROIs.
 *
 * Populates wire channels, views, and flattened ROI data randomly.
 *
 * @param eventID Event identifier.
 * @param wiresPerEvent Number of wires.
 * @param roisPerWire ROIs per wire.
 * @param rng Random number generator.
 * @return WireVector with random data.
 */
WireVector generateRandomWireVector(long long eventID, int wiresPerEvent, int roisPerWire, std::mt19937& rng);

/**
 * @brief Overload for generateRandomWireVector with roisPerWire = wiresPerEvent.
 *
 * Forwards to the full version for compatibility.
 */
WireVector generateRandomWireVector(long long eventID, int wiresPerEvent, std::mt19937& rng);

/**
 * @brief Generates a random individual Hit for a given event.
 *
 * Fills all fields with random values.
 *
 * @param eventID Event identifier.
 * @param rng Random number generator.
 * @return HitIndividual with random data.
 */
HitIndividual generateRandomHitIndividual(long long eventID, std::mt19937& rng);

/**
 * @brief Generates a random individual Wire with specified ROIs.
 *
 * Populates channel, view, and ROI vector randomly.
 *
 * @param eventID Event identifier.
 * @param roisPerWire Number of ROIs (ignored in some overloads).
 * @param rng Random number generator.
 * @return WireIndividual with random data.
 */
WireIndividual generateRandomWireIndividual(long long eventID, int roisPerWire, std::mt19937& rng);

/**
 * @brief Overload ignoring dummyROIs, using numROIs for actual count.
 */
WireIndividual generateRandomWireIndividual(long long eventID, int /*dummyROIs*/, int numROIs, std::mt19937& rng); 