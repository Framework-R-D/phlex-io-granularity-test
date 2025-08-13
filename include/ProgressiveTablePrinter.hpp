#ifndef PROGRESSIVE_TABLE_PRINTER_HPP
#define PROGRESSIVE_TABLE_PRINTER_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include "WriterResult.hpp"
#include "ReaderResult.hpp"

template<typename ResultType>
class ProgressiveTablePrinter {
private:
    bool headerPrinted = false;
    std::vector<std::string> columnHeaders;
    std::vector<int> columnWidths;
    std::string tableTitle;
    
public:
    ProgressiveTablePrinter(const std::string& title, 
                          const std::vector<std::string>& headers, 
                          const std::vector<int>& widths)
        : tableTitle(title), columnHeaders(headers), columnWidths(widths) {}
    
    void printHeader() {
        if (headerPrinted) return;
        
        std::cout << "\n" << tableTitle << std::endl;
        std::cout << std::left;
        for (size_t i = 0; i < columnHeaders.size(); ++i) {
            std::cout << std::setw(columnWidths[i]) << columnHeaders[i];
        }
        std::cout << std::endl;
        
        int totalWidth = 0;
        for (int width : columnWidths) {
            totalWidth += width;
        }
        std::cout << std::string(totalWidth, '-') << std::endl;
        headerPrinted = true;
    }
    
    void addRow(const ResultType& result) {
        printHeader();
        printRow(result);
        std::cout.flush(); // Ensure immediate output
    }
    
    void printFooter() {
        if (!headerPrinted) return;
        
        int totalWidth = 0;
        for (int width : columnWidths) {
            totalWidth += width;
        }
        std::cout << std::string(totalWidth, '-') << std::endl;
        std::cout << std::endl;
    }
    
private:
    void printRow(const ResultType& result);
};

// Template specialization declarations (implementations in .cpp file)
template<>
void ProgressiveTablePrinter<WriterResult>::printRow(const WriterResult& result);

template<>
void ProgressiveTablePrinter<ReaderResult>::printRow(const ReaderResult& result);

#endif