#pragma once
#include <vector>
#include "WriterResult.hpp"
#include "ReaderResult.hpp"
#include <map>
#include <utility>

// AOS visualization functions
void visualize_aos_writer_results(const std::vector<WriterResult>& results);
void visualize_aos_reader_results(const std::vector<ReaderResult>& results);
void visualize_aos_file_sizes(const std::vector<std::pair<std::string, double>>& sizes);
void visualize_aos_scaling(const std::map<std::string, std::vector<std::pair<int, double>>>& data);

// SOA visualization functions
void visualize_soa_writer_results(const std::vector<WriterResult>& results);
void visualize_soa_reader_results(const std::vector<ReaderResult>& results);
void visualize_soa_file_sizes(const std::vector<std::pair<std::string, double>>& sizes);
void visualize_soa_scaling(const std::map<std::string, std::vector<std::pair<int, double>>>& data);

// Comparison functions for AOS vs SOA
void visualize_comparison_writer_results(const std::vector<WriterResult>& aosResults, const std::vector<WriterResult>& soaResults);
void visualize_comparison_reader_results(const std::vector<ReaderResult>& aosResults, const std::vector<ReaderResult>& soaResults);
void visualize_comparison_file_sizes(const std::vector<std::pair<std::string, double>>& aosSizes, const std::vector<std::pair<std::string, double>>& soaSizes); 