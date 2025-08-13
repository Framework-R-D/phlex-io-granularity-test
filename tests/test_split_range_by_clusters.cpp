#include <gtest/gtest.h>
#include <ROOT/RNTupleReader.hxx>
#include <memory>
#include <vector>
#include <utility>
#include "Utils.hpp"
#include <filesystem>  // For temp file cleanup
#include <ROOT/RNTupleDescriptor.hxx>  // For cluster summaries

// Assuming GenerateTestNTuple is declared in a header or externally linked
extern void GenerateTestNTuple(const std::string& filePath, int numEntries, std::size_t approxClusterSize, int payloadSize = 4);

class NTupleClusterTest : public ::testing::Test {
protected:
    std::string tempFilePath = "temp_test_file.root";

    std::vector<std::pair<uint64_t, uint64_t>> GetClusterBoundaries(const std::string& filePath, const std::string& ntupleName) {
        auto reader = ROOT::RNTupleReader::Open(ntupleName, filePath);
        auto& desc = reader->GetDescriptor();
        std::vector<std::pair<uint64_t, uint64_t>> boundaries;
        auto nClusters = desc.GetNClusters();
        for (decltype(nClusters) i = 0; i < nClusters; ++i) {
            auto& clusterDesc = desc.GetClusterDescriptor(i);
            uint64_t start = clusterDesc.GetFirstEntryIndex();
            uint64_t num = clusterDesc.GetNEntries();
            boundaries.emplace_back(start, start + num);
        }
        return boundaries;
    }

    void SetUp() override {
        // Generate a temp file with defaults; override in specific tests if needed
        GenerateTestNTuple(tempFilePath, 1000000, 1024, 4);
    }

    void TearDown() override {
        std::filesystem::remove(tempFilePath);
    }
};

TEST_F(NTupleClusterTest, RealROOTFile) {
    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    ASSERT_TRUE(reader);

    auto chunks = Utils::split_range_by_clusters(*reader, 2);

    ASSERT_EQ(chunks.size(), 2);
    EXPECT_EQ(chunks[0], std::make_pair(0ul, 512ul));
    EXPECT_EQ(chunks[1], std::make_pair(512ul, 1000000ul));
}

TEST_F(NTupleClusterTest, SingleClusterSmallData) {
    GenerateTestNTuple(tempFilePath, 100, 1024, 4);
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_EQ(clusters.size(), 1);
    EXPECT_EQ(clusters[0], std::make_pair(0ul, 100ul));

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    ASSERT_EQ(chunks.size(), 1);  // Should not split if only one cluster
    EXPECT_EQ(chunks[0], std::make_pair(0ul, 100ul));
}

TEST_F(NTupleClusterTest, NoEntriesEmptyFile) {
    GenerateTestNTuple(tempFilePath, 0, 1024, 4);
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_TRUE(clusters.empty());

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    EXPECT_TRUE(chunks.empty());
}

TEST_F(NTupleClusterTest, InvalidClusterSizeZero) {
    GenerateTestNTuple(tempFilePath, 1000000, 0, 4);
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_GE(clusters.size(), 1);  // Expect at least one cluster (ROOT default)

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    EXPECT_FALSE(chunks.empty());
}

TEST_F(NTupleClusterTest, LargeClusterSize) {
    GenerateTestNTuple(tempFilePath, 100, 10000, 4);
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_EQ(clusters.size(), 1);

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    ASSERT_EQ(chunks.size(), 1);
    EXPECT_EQ(chunks[0], std::make_pair(0ul, 100ul));
}

TEST_F(NTupleClusterTest, OverflowLargeEntries) {
    GenerateTestNTuple(tempFilePath, 10, 1024, 2000);  // Large payload to force overflow
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_GT(clusters.size(), 1);  // Expect multiple due to size

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    EXPECT_GE(chunks.size(), 1);
}

TEST_F(NTupleClusterTest, MinimalNonEmpty) {
    GenerateTestNTuple(tempFilePath, 1, 1024, 4);
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_EQ(clusters.size(), 1);
    EXPECT_EQ(clusters[0], std::make_pair(0ul, 1ul));

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    ASSERT_EQ(chunks.size(), 1);
    EXPECT_EQ(chunks[0], std::make_pair(0ul, 1ul));
}

TEST_F(NTupleClusterTest, NegativeClusterSize) {
    // Negative size should be handled as unsigned (large value) or default; test for at least one cluster
    GenerateTestNTuple(tempFilePath, 1000000, static_cast<std::size_t>(-1), 4);  // Cast to simulate invalid
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_GE(clusters.size(), 1);

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    EXPECT_FALSE(chunks.empty());
}

TEST_F(NTupleClusterTest, MultiFieldModel) {
    // Assuming GenerateTestNTuple updated to support multi-field (e.g., add string field)
    // Generate with multi-field for variable-size testing
    GenerateTestNTuple(tempFilePath, 1000000, 1024, 4);  // Update call if param added
    auto clusters = GetClusterBoundaries(tempFilePath, "hits");
    EXPECT_GT(clusters.size(), 1);  // Expect multiple with varied sizes

    auto reader = ROOT::RNTupleReader::Open("hits", tempFilePath);
    auto chunks = Utils::split_range_by_clusters(*reader, 2);
    EXPECT_GE(chunks.size(), 1);
}

TEST_F(NTupleClusterTest, InvalidFilePath) {
    // Test reader open failure
    auto reader = ROOT::RNTupleReader::Open("hits", "non_existent_file.root");
    EXPECT_FALSE(reader);  // Expect failure
    // No split possible
} 