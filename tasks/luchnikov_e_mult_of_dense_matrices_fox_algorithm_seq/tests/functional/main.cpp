#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <stdexcept>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/all/include/ops_all.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/common/include/common.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/omp/include/ops_omp.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/seq/include/ops_seq.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/stl/include/ops_stl.hpp"
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/tbb/include/ops_tbb.hpp"
#include "util/include/func_test_util.hpp"
#include "util/include/util.hpp"

namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq {

// Эталонная функция для вычисления ожидаемой суммы элементов результирующей матрицы.
// При заполнении матриц A и B единицами каждый элемент C[i][j] = n.
// Сумма всех элементов C = n * n * n.
static int CalculateExpectedChecksum(int n) {
  return n * n * n;
}

class LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads
    : public ppc::util::BaseRunFuncTests<InType, OutType, TestType> {
 public:
  static std::string PrintTestParam(const TestType &test_param) {
    return std::to_string(std::get<0>(test_param)) + "_" + std::get<1>(test_param);
  }

 protected:
  void SetUp() override {
    TestType params = std::get<static_cast<std::size_t>(ppc::util::GTestParamIndex::kTestParams)>(GetParam());
    int n = std::get<0>(params);
    if (n <= 0) {
      throw std::invalid_argument("Matrix size must be positive");
    }
    input_data_ = n;
  }

  bool CheckTestOutputData(OutType &output_data) final {
    int expected = CalculateExpectedChecksum(input_data_);
    return (output_data == expected);
  }

  InType GetTestInputData() final {
    return input_data_;
  }

 private:
  InType input_data_ = 0;
};

namespace {

// Тест 1: Проверка на малых размерах матриц
TEST_P(LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, SmallMatrixTest) {
  ExecuteTest(GetParam());
}

// Тест 2: Проверка на средних размерах матриц
TEST_P(LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, MediumMatrixTest) {
  ExecuteTest(GetParam());
}

// Тест 3: Проверка на больших размерах и граничных значениях
TEST_P(LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, LargeMatrixTest) {
  ExecuteTest(GetParam());
}

const std::array<TestType, 3> kSmallParams = {std::make_tuple(1, "1"), std::make_tuple(2, "2"),
                                              std::make_tuple(3, "3")};

const std::array<TestType, 3> kMediumParams = {std::make_tuple(4, "4"), std::make_tuple(5, "5"),
                                               std::make_tuple(6, "6")};

const std::array<TestType, 3> kLargeParams = {std::make_tuple(8, "8"), std::make_tuple(10, "10"),
                                              std::make_tuple(12, "12")};

const auto kSmallTasks = std::tuple_cat(ppc::util::AddFuncTask<LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq, InType>(
    kSmallParams, PPC_SETTINGS_luchnikov_e_mult_of_dense_matrices_fox_algorithm));
const auto kMediumTasks = std::tuple_cat(ppc::util::AddFuncTask<LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq, InType>(
    kMediumParams, PPC_SETTINGS_luchnikov_e_mult_of_dense_matrices_fox_algorithm));
const auto kLargeTasks = std::tuple_cat(ppc::util::AddFuncTask<LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq, InType>(
    kLargeParams, PPC_SETTINGS_luchnikov_e_mult_of_dense_matrices_fox_algorithm));

const auto kGtestSmallValues = ppc::util::ExpandToValues(kSmallTasks);
const auto kGtestMediumValues = ppc::util::ExpandToValues(kMediumTasks);
const auto kGtestLargeValues = ppc::util::ExpandToValues(kLargeTasks);

const auto kPrintFuncTestName = LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads::PrintFuncTestName<
    LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads>;

INSTANTIATE_TEST_SUITE_P(SmallMatrixTests, LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, kGtestSmallValues,
                         kPrintFuncTestName);
INSTANTIATE_TEST_SUITE_P(MediumMatrixTests, LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, kGtestMediumValues,
                         kPrintFuncTestName);
INSTANTIATE_TEST_SUITE_P(LargeMatrixTests, LuchnikovEMultOfDenseMatrixFoxAlgoritmFuncTestsThreads, kGtestLargeValues,
                         kPrintFuncTestName);

}  // namespace
}  // namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq
