#pragma once
#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/common/include/common.hpp"
#include "task/include/task.hpp"

namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq {

class LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq : public BaseTask {
 public:
  static constexpr ppc::task::TypeOfTask GetStaticTypeOfTask() {
    return ppc::task::TypeOfTask::kSEQ;
  }

  explicit LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq(const InType &in);

 private:
  bool ValidationImpl() override;
  bool PreProcessingImpl() override;
  bool RunImpl() override;
  bool PostProcessingImpl() override;
};

}  // namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq
