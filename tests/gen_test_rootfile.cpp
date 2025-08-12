#include <ROOT/RNTupleModel.hxx>
#include <ROOT/RNTupleWriter.hxx>
#include <memory>
#include <string>
#include <random>  // For random data generation

void GenerateTestNTuple(const std::string& filePath, int numEntries, std::size_t approxClusterSize, int payloadSize = 4) {
    auto model = ROOT::RNTupleModel::Create();
    // Use a vector<char> for flexible payload size (simulates larger entries)
    auto val = model->MakeField<std::vector<char>>("value");

    ROOT::RNTupleWriteOptions options;
    options.SetApproxZippedClusterSize(approxClusterSize);

    auto writer = ROOT::RNTupleWriter::Recreate(std::move(model), "hits", filePath, options);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned char> dist(0, 255);  // Random bytes for poor compression

    for (int i = 0; i < numEntries; ++i) {
        val->resize(payloadSize);
        for (auto& byte : *val) {
            byte = dist(gen);
        }
        writer->Fill();
    }
    // Writer auto-closes on destruction
}

int main() {
    GenerateTestNTuple("test_file.root", 1000000, 1024, 4);
    return 0;
}