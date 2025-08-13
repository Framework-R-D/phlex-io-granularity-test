#ifndef WRITERRESULT_HPP
#define WRITERRESULT_HPP

#include <string>
#include <vector>

struct WriterResult {
    std::string label;
    double avg;
    double stddev;
    std::vector<double> iterationTimes; // Store individual iteration times
    bool failed = false;
    std::string errorMessage = "";
};

#endif 