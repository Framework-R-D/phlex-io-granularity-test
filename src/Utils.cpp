#include "Utils.hpp"
#include <random>
#include <vector>
#include <utility>
#include <cstddef>
#include <ROOT/RNTupleReader.hxx>

namespace Utils {

std::vector<unsigned int> generateSeeds(int numThreads) {
    // Use a constant seed for reproducibility
    std::mt19937 gen(42); // 42 is the chosen constant seed
    std::vector<unsigned int> seeds;
    for (int i = 0; i < numThreads; ++i) {
        seeds.push_back(gen());
    }
    return seeds;
}


std::vector<std::pair<std::size_t, std::size_t>> split_range_by_clusters(ROOT::RNTupleReader& reader, int nChunks) {
    const auto& desc = reader.GetDescriptor();
    auto nClusters = desc.GetNClusters();
    if (nClusters == 0) {
        return {};
    }
    int clusters_per_chunk = nClusters / nChunks;
    int remainder = nClusters % nChunks;
    std::vector<std::pair<std::size_t, std::size_t>> chunks;
    std::uint64_t current_cid = 0;
    for (int i = 0; i < nChunks; ++i) {
        int num_clusters = clusters_per_chunk + (i < remainder ? 1 : 0);
        if (num_clusters == 0) continue;
        auto start_cid = current_cid;
        current_cid += num_clusters;
        const auto& start_desc = desc.GetClusterDescriptor(start_cid);
        const auto& end_desc = desc.GetClusterDescriptor(current_cid - 1);
        std::size_t start = start_desc.GetFirstEntryIndex();
        std::size_t end = end_desc.GetFirstEntryIndex() + end_desc.GetNEntries();
        chunks.emplace_back(start, end);
    }
    return chunks;
}


} // namespace Utils 