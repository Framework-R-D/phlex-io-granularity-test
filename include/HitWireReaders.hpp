#pragma once
#include <string>
#include <vector>
#include "ReaderResult.hpp"

double readAOS_event_allDataProduct(const std::string& fileName);
double readAOS_event_perDataProduct(const std::string& fileName);
double readAOS_event_perGroup(const std::string& fileName);
double readAOS_spill_allDataProduct(const std::string& fileName);
double readAOS_spill_perDataProduct(const std::string& fileName);
double readAOS_spill_perGroup(const std::string& fileName);
double readAOS_topObject_perDataProduct(const std::string& fileName);
double readAOS_topObject_perGroup(const std::string& fileName);
double readAOS_element_perDataProduct(const std::string& fileName);
double readAOS_element_perGroup(const std::string& fileName);

std::vector<ReaderResult> inAOS(int nThreads, int iter, const std::string& outputDir);
std::vector<ReaderResult> inSOA(int nThreads, int iter, const std::string& outputDir); 