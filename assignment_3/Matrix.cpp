#include "Matrix.h"
#include <sstream>
#include <iostream>

size_t Matrix::sub2ind(size_t i, size_t j) const {
	if (rowMajor)
		return i * n_columns + j;
	else
		return j * n_rows + i;
}

Matrix::Matrix (size_t nRows, size_t nCols):Matrix("row-major",nRows,nCols){}

Matrix::Matrix(const std::string & major, size_t nRows, size_t nCols) {
	if (major == "col-major")
		rowMajor = false;
	else
		rowMajor = true;
	n_rows = nRows;
	n_columns = nCols;
	m_data.resize(nRows*nCols,0);
}

Matrix::Matrix(const std::string &  major, size_t nRows, size_t nCols, const std::vector<double> & d)
       :Matrix(major, nRows, nCols) { m_data = d; }

void Matrix::setDim(std::size_t m, std::size_t n){
	n_rows = m; 
	n_columns = n;
	m_data.resize(m*n);
}

void Matrix::read (std::istream & in){
	std::string line;
	std::getline (in, line);
	std::istringstream first_line (line);
	std::string major;
	first_line >> n_rows >> n_columns >> major;
	if(major == "row-major")
		rowMajor = true;
	else{ 
		if(major == "col-major") 
			rowMajor = false;
			else{
				std::cerr<<"Wrong major"<<std::endl;
				return;
			}
	}
	m_data.resize (n_rows * n_columns);
	for (size_t i = 0; i < n_rows; ++i){
		std::getline (in, line);
		std::istringstream current_line (line);
		for (size_t j = 0; j < n_columns; ++j)
			current_line >> (*this)(i, j);
	}
}

std::ostream & Matrix::print(std::ostream & os) const {
	std::cout<<n_rows<<" x "<<n_columns<<" ";
	if(n_rows > 1 && n_columns > 1) 
		std::cout<<getMajor();
	std::cout<<std::endl;
	for (size_t i =0; i < n_rows; ++i)
		for (size_t j=0; j< n_columns; ++j)
			std::cout << getElem(i,j) << ((j==n_columns-1) ? "\n" : " ");
	return os;
}

