#include <iostream>

#include "block_matrix.hpp"

int main()
{
  DenseMatrix dm (3, 4);
  std::cout << "Dense Matrix dm = [" << std::endl;
  dm.print();
  std::cout << "]" << std::endl;

  for (unsigned i = 0; i < dm.get_n_rows(); ++i)
    for (unsigned j = 0; j < dm.get_n_cols(); ++j)
      dm(i, j) = i + j;
  std::cout << "Updated dm = [" << std::endl;
  dm.print();
  std::cout << "]" << std::endl;

  BlockMatrix bm;
  Block block1 (
      0,
      0,
      1,
      1,
      {1, 1, 1, 1}
  );
  bm.add_block (block1);
  Block block2 (
      2,
      2,
      4,
      5,
      {2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}
  );
  bm.add_block (block2);
  std::cout << "Block Matrix bm = [" << std::endl;
  bm.print();
  std::cout << "]" << std::endl;

  bm(3, 4) = 3;
  std::cout << "Updated bm = [" << std::endl;
  bm.print();
  std::cout << "]" << std::endl;

  // Be careful! If we define a const matrix...
  const BlockMatrix const_bm(bm);
  std::cout << "\nconst_bm(10,10) = " << const_bm(10,10) << std::endl;
  std::cout << "Const Block Matrix const_bm = [" << std::endl;
  const_bm.print();
  std::cout << "]" << std::endl;

  // ...but bm is not constant!!
  std::cout << "\nbm(10,10) = " << bm(10,10) << std::endl;
  std::cout << "Updated bm = [" << std::endl;
  bm.print();
  std::cout << "]" << std::endl;

  return 0;
}
