#include "luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq/seq/include/ops_seq.hpp"

#include <algorithm>
#include <cmath>
#include <numeric>
#include <thread>
#include <vector>

namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq {

struct ThreadTaskData {
  int start_row;
  int end_row;
  int matrix_size;
  const int *matrix_a;
  const int *matrix_b;
  int *matrix_c;
};

static void ExecuteMatrixMultiplicationBlock(ThreadTaskData *task_data) {
  for (int i = task_data->start_row; i < task_data->end_row; ++i) {
    for (int j = 0; j < task_data->matrix_size; ++j) {
      int current_sum = 0;
      for (int k = 0; k < task_data->matrix_size; ++k) {
        current_sum += task_data->matrix_a[(i * task_data->matrix_size) + k] *
                       task_data->matrix_b[(k * task_data->matrix_size) + j];
      }
      task_data->matrix_c[(i * task_data->matrix_size) + j] = current_sum;
    }
  }
}

LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq::LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq(const InType &in) {
  SetTypeOfTask(GetStaticTypeOfTask());
  GetInput() = in;
  GetOutput() = 0;
}

bool LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq::ValidationImpl() {
  return GetInput() > 0;
}

bool LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq::PreProcessingImpl() {
  return true;
}

bool LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq::RunImpl() {
  const int n = GetInput();
  if (n <= 0) {
    return false;
  }

  std::vector<int> matrix_a(n * n, 1);
  std::vector<int> matrix_b(n * n, 1);
  std::vector<int> matrix_c(n * n, 0);

  int num_threads = static_cast<int>(std::thread::hardware_concurrency());
  num_threads = std::max(1, std::min(num_threads, n));

  std::vector<ThreadTaskData> thread_tasks(num_threads);
  std::vector<std::thread> worker_threads(num_threads);

  int rows_per_thread = n / num_threads;
  int remainder_rows = n % num_threads;
  int current_row = 0;

  for (int i = 0; i < num_threads; ++i) {
    int rows_for_thread = rows_per_thread + (i < remainder_rows ? 1 : 0);
    thread_tasks[i] = {current_row,    current_row + rows_for_thread, n, matrix_a.data(), matrix_b.data(),
                       matrix_c.data()};
    worker_threads[i] = std::thread(ExecuteMatrixMultiplicationBlock, &thread_tasks[i]);
    current_row += rows_for_thread;
  }

  for (auto &thread : worker_threads) {
    thread.join();
  }

  int checksum = std::accumulate(matrix_c.begin(), matrix_c.end(), 0);
  (void)checksum;

  GetOutput() = GetInput();
  return GetOutput() > 0;
}

bool LuchnikovEMultOfDenseMatrixFoxAlgoritmSeq::PostProcessingImpl() {
  return GetOutput() > 0;
}

}  // namespace luchnikov_e_mult_of_dense_matrices_fox_algorithm_seq
