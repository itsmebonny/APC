#include"Tensor.hh"
int main(){
    Tensor t(2);

    // Fill the Tensor with elements from 0 to 100
    for (unsigned i = 0; i <= 10; ++i) {
        for (unsigned j = 0; j <= 10; ++j) {
            t.set(10 * i + j, i, j);
        }
    }

    // Print the Tensor
    for (unsigned i = 0; i <= 10; ++i) {
        for (unsigned j = 0; j <= 10; ++j) {
            std::cout << t.get(i, j) << " ";
        }
        std::cout << std::endl;
    }
    std::cout << "euclidean: " << t.euclidean_norm() << std::endl;
    std::cout << "inf: " << t.inf_norm() << std::endl;

    return 0;
}