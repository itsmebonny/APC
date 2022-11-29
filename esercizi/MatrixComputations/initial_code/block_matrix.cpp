#include <limits>
#include <iostream>

#include "block_matrix.hpp"

BlockMatrix::BlockMatrix(): Matrix (0, 0)
{}

// BlockMatrix B;
// B.add_block(..);

void
BlockMatrix::add_block(const Block& block)
{
  blocks.push_back(block);

  n_rows = std::max(n_rows, block.get_bottom_right_row() + 1);
  n_cols = std::max(n_cols, block.get_bottom_right_col() + 1);
}

bool
BlockMatrix::indexes_in_block(std::size_t i, std::size_t j, const Block& block) const
{
  bool b1 = (i >= block.get_top_left_row());
  bool b2 = (i <= block.get_bottom_right_row());
  bool b3 = (j >= block.get_top_left_col());
  bool b4 = (j <= block.get_bottom_right_col());

  return b1 && b2 && b3 && b4;
}

double
BlockMatrix::operator () (std::size_t i, std::size_t j) const
{
  double value = 0.;

  if (i >= n_rows || j >= n_cols)
  {
    std::cerr << "ERROR: indexes out of bound" << std::endl;
    value = std::numeric_limits<double>::quiet_NaN();
  }
  else {
    for (const Block& block : blocks)
    {
      // check if (i,j) are in the block
      if (indexes_in_block(i, j, block))
      {
        std::size_t block_i = i - block.get_top_left_row();
        std::size_t block_j = j - block.get_top_left_col();
        value = block(block_i, block_j);
      }
    }
  }

  return value;
}


double&
BlockMatrix::operator () (std::size_t i, std::size_t j)
{
  for (Block& block : blocks)
  {
    if (indexes_in_block(i, j, block))
    {
      std::size_t block_i = i - block.get_top_left_row();
      std::size_t block_j = j - block.get_top_left_col();
      return block(block_i, block_j);
    }
  }

  Block new_block(i, j, i, j, {0});
  add_block(new_block);
  return blocks.back()(0,0);
}

