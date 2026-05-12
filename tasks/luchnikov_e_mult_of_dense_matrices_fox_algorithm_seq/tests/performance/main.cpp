#include <gtest/gtest.h>

#include <array>
#include <tuple>

#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/all/include/ops_all.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/common/include/common.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/seq/include/ops_seq.hpp"
#include "util/include/perf_test_util.hpp"

namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq {

class LuchnikovEMultOfDenseMatrixFoxAlgoritmPerfTestThreads : public ppc::util::BaseRunPerfTests<InType, OutType> {
 protected:
  const int kCount_ = 200;
  InType input_data_{};

  void SetUp() override {
    input_data_ = kCount_;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    return input_data_ == output_data;
  }

  InType GetTestInputData() final {
    return input_data_;
  }
};

TEST_P(LuchnikovEMultOfDenseMatrixFoxAlgoritmPerfTestThreads, RunPerfModes) {
  ExecuteTest(GetParam());
}

namespace {
const auto kAllPerfTasks = ppc::util::MakeAllPerfTasks<InType, LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq>(
    PPC_SETTINGS_luchnikov_e_mult_of_dense_matrices_fox_algorithm);

const auto kGtestValues = ppc::util::TupleToGTestValues(kAllPerfTasks);
const auto kPerfTestName = LuchnikovEMultOfDenseMatrixFoxAlgoritmPerfTestThreads::CustomPerfTestName;

INSTANTIATE_TEST_SUITE_P(RunModeTests, LuchnikovEMultOfDenseMatrixFoxAlgoritmPerfTestThreads, kGtestValues,
                         kPerfTestName);
}  // namespace
}  // namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq
