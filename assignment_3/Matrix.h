#ifndef ROWCOLMAJORMATRIX_MATRIX_H
#define ROWCOLMAJORMATRIX_MATRIX_H

#include <vector>
#include <string>
#include <cstddef>
#include <iostream>

class Matrix {
private:
	bool rowMajor;
	std::vector<double> m_data;
	std::size_t n_rows, n_columns;

	std::size_t sub2ind (std::size_t i, std::size_t j) const;
public:
	Matrix (std::size_t nRows, std::size_t nCols);
	Matrix (const std::string & major, std::size_t nRows, std::size_t nCols);
	Matrix (const std::string & major, std::size_t nRows, std::size_t nCols, const std::vector<double> & d);

	double getElem(size_t i, size_t j) const {return m_data[sub2ind(i,j)];}
	std::size_t getNcols() const {return n_columns;}
	std::size_t getNrows() const {return n_rows;}
	std::string getMajor() const {return rowMajor ? "row-major" : "col-major";}

	void setDim(std::size_t, std::size_t);

	void switch_ordering(){rowMajor=!rowMajor;}

	double * data(){return m_data.data();}
	const double * data() const {return m_data.data();}

	double & operator()(std::size_t i, std::size_t j){return m_data[sub2ind(i,j)];}
	const double & operator()(std::size_t i, std::size_t j) const{return m_data[sub2ind(i,j)];}

	void read (std::istream &);
	std::ostream & print(std::ostream & os = std::cout) const;
};

#endif //ROWCOLMAJORMATRIX_MATRIX_H
