#include "matrix.hpp"

Matrix::Matrix (std::size_t rows, std::size_t cols): n_rows (rows), n_cols (cols)
{}

std::size_t
Matrix::get_n_cols() const
{
  return n_cols;
}

std::size_t
Matrix::get_n_rows() const
{
  return n_rows;
}

void
Matrix::print() const
{
  for (unsigned i = 0; i < n_rows; ++i)
  {
    for (unsigned j = 0; j < n_cols; ++j) {
      std::cout << operator()(i, j) << " ";
    }
    std::cout << std::endl;
  }
}
