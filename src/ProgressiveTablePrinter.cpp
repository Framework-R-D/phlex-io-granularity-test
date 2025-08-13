#include "ProgressiveTablePrinter.hpp"
#include <iostream>
#include <iomanip>

// Specialization for WriterResult
template<>
void ProgressiveTablePrinter<WriterResult>::printRow(const WriterResult& result) {
    std::cout << std::left
              << std::setw(columnWidths[0]) << result.label;
    
    if (result.failed) {
        std::cout << std::setw(columnWidths[1]) << "FAILED"
                  << std::setw(columnWidths[2]) << "-";
        // Fill remaining columns with "-" if there are iteration columns
        for (size_t i = 3; i < columnWidths.size(); ++i) {
            std::cout << std::setw(columnWidths[i]) << "-";
        }
    } else {
        std::cout << std::setw(columnWidths[1]) << result.avg
                  << std::setw(columnWidths[2]) << result.stddev;
        
        // Print individual iteration times if available
        for (size_t i = 0; i < result.iterationTimes.size() && i + 3 < columnWidths.size(); ++i) {
            std::cout << std::setw(columnWidths[i + 3]) << result.iterationTimes[i];
        }
        
        // Fill remaining columns with "-" if we have fewer iterations than columns
        for (size_t i = result.iterationTimes.size() + 3; i < columnWidths.size(); ++i) {
            std::cout << std::setw(columnWidths[i]) << "-";
        }
    }
    std::cout << std::endl;
    
    // Print error message if failed
    if (result.failed && !result.errorMessage.empty()) {
        std::cout << std::setw(columnWidths[0]) << ""
                  << "Error: " << result.errorMessage << std::endl;
    }
}

// Specialization for ReaderResult
template<>
void ProgressiveTablePrinter<ReaderResult>::printRow(const ReaderResult& result) {
    std::cout << std::left
              << std::setw(columnWidths[0]) << result.label;
    
    if (result.failed) {
        std::cout << std::setw(columnWidths[1]) << "FAILED"
                  << std::setw(columnWidths[2]) << "-"
                  << std::setw(columnWidths[3]) << "-";
        // Fill remaining columns with "-" if there are iteration columns
        for (size_t i = 4; i < columnWidths.size(); ++i) {
            std::cout << std::setw(columnWidths[i]) << "-";
        }
    } else {
        // Column 1: cold (first iteration)
        std::cout << std::setw(columnWidths[1]) << result.cold;
        // Column 2-3: warm avg/std
        if (!result.warmTimes.empty()) {
            std::cout << std::setw(columnWidths[2]) << result.warmAvg
                      << std::setw(columnWidths[3]) << result.warmStddev;
        } else {
            std::cout << std::setw(columnWidths[2]) << "-"
                      << std::setw(columnWidths[3]) << "-";
        }
        
        // Iteration columns: Itr1 = cold, Itr2.. = warm1, warm2, ...
        size_t colIndex = 4;
        if (colIndex < columnWidths.size()) {
            std::cout << std::setw(columnWidths[colIndex++]) << (result.coldTimes.empty() ? 0.0 : result.coldTimes.front());
        }
        for (size_t wi = 0; wi < result.warmTimes.size() && colIndex < columnWidths.size(); ++wi, ++colIndex) {
            std::cout << std::setw(columnWidths[colIndex]) << result.warmTimes[wi];
        }
        
        // Fill remaining columns with "-" if we have fewer iterations than columns
        for (size_t i = colIndex; i < columnWidths.size(); ++i) {
            std::cout << std::setw(columnWidths[i]) << "-";
        }
    }
    std::cout << std::endl;
    
    // Print error message if failed
    if (result.failed && !result.errorMessage.empty()) {
        std::cout << std::setw(columnWidths[0]) << ""
                  << "Error: " << result.errorMessage << std::endl;
    }
}