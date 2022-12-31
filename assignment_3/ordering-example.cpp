#include "Matrix.h"
#include <iostream>

int main(){
	std::cout<<"M:\n";
	Matrix m("row-major",2,2,{1,2,3,4});
	m.print()<<std::endl;
	std::cout<<"N:\n";
	Matrix n("col-major",2,2,{1,2,3,4});
	n.print()<<std::endl;
	std::cout<<"M after order switch:\n";
	m.switch_ordering();
	m.print();
return 0;
}
