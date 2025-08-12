#ifndef READERRESULT_HPP
#define READERRESULT_HPP

#include <string>
#include <vector>

struct ReaderResult {
    std::string label;
    double cold;
    double warmAvg;
    double warmStddev;
    std::vector<double> coldTimes; // Store individual cold iteration times
    std::vector<double> warmTimes; // Store individual warm iteration times
    bool failed = false;
    std::string errorMessage = "";
};

std::vector<ReaderResult> in(int nThreads, int iter);

#endif 