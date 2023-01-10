#ifndef TENSOR_HH
#define TENSOR_HH
#include<vector>
#include<iostream>
#include<string>
#include<limits>
#include<unordered_map>
#include<cmath>
int to_int(char c){
        int res = c;
        return res;
    }
char to_char(int c){
        char res = c;
        return res;
    }
class Tensor
{
private:
    size_t dim;
    std::unordered_map<std::string, double> tensor;
public:
    Tensor(size_t dimensions){
        dim = dimensions;
    };
    int get_size(std::string &s){
        size_t count = 0;
        for (auto j:s){
            if (j ==  ' ')
                count++;
        }
        return count + 1;
    }

    std::string create_pos(unsigned i, int j=-1, int k= -1)const{
        std::string pos;
        pos = std::to_string(i);
        pos += " ";
        if(j != -1){
            pos += std::to_string(j);
            pos += " ";
            if(k != -1){
                pos += std::to_string(k);;
            }
        }
        return pos;
    }
    void set(double value, unsigned i, int j=-1, int k= -1){
        std::string pos = create_pos(i, j, k);
            tensor[pos] = value;
    }
    double get(unsigned i, int j=-1, int k= -1) const{
        std::string pos = create_pos(i, j, k);
        if((tensor.find(pos) == tensor.end()))
            return std::numeric_limits<double>::quiet_NaN();
        else
            return tensor.at(pos);
    }
    Tensor operator*(double alpha){
        Tensor res(this->dim);
        for (auto j : tensor){
            if (this->dim == 1){
                res.set(j.second*alpha, std::stoi(j.first));
            }
            else if (this->dim == 2){
                int it = j.first.find(' ');
                res.set(j.second*alpha, std::stoi(j.first.substr(0, it)), std::stoi(j.first.substr(it+1, j.first.size())));
            }
            else if (this->dim == 3){
                int it = j.first.find(' '), it2 = j.first.find(' ', it+1);
                res.set(j.second*alpha, std::stoi(j.first.substr(0, it)), std::stoi(j.first.substr(it+1, it2)), std::stoi(j.first.substr(it2, j.first.size())));
            }
        }
        return res;
    }
    std::vector<size_t> max_dims(){
        std::vector<size_t> res;
        size_t max_i = 0, max_j = 0, max_k = 0;
        for(auto j : tensor){
            int it = j.first.find(' '), it2 = j.first.find(' ', it+1);
            if (dim == 1){
                if (max_i < std::stoi(j.first.substr(0, it)))
                    max_i = std::stoi(j.first.substr(0, it));
                res.push_back(max_i);
            }
            else if (dim == 2){
                if (max_i < std::stoi(j.first.substr(0, it)))
                    max_i = std::stoi(j.first.substr(0, it));
                if(max_j < std::stoi(j.first.substr(it+1, j.first.size())))
                    max_j = std::stoi(j.first.substr(it+1, j.first.size()));
                res.push_back(max_i);
                res.push_back(max_j);
            }
            else if (dim == 3){
                if (max_i < std::stoi(j.first.substr(0, it)))
                    max_i = std::stoi(j.first.substr(0, it));
                if(max_j < std::stoi(j.first.substr(it+1, j.first.size())))
                    max_j = std::stoi(j.first.substr(it+1, j.first.size()));
                if (max_k < std::stoi(j.first.substr(it2+1, j.first.size())))
                    max_k = std::stoi(j.first.substr(it2+1, j.first.size()));
                res.push_back(max_i);
                res.push_back(max_j);
                res.push_back(max_k);
            }
        }
        return res;
    }
    double euclidean_norm(){
        double tot = 0;
        std::vector<size_t> dims = this->max_dims();
        if (dims.size() == 1){
            for (size_t i = 0; i < dims[0]; i++)
            {
                if(get(i) != std::numeric_limits<double>::quiet_NaN())
                    tot += get(i)*get(i);
            }
        }
        if (dims.size() == 2){
            for (size_t i = 0; i < dims[0]; i++)
            {
                for(size_t j = 0; j < dims[1]; j++){
                    if(get(i,j) != std::numeric_limits<double>::quiet_NaN())
                        tot += get(i,j)*get(i,j);
                }
            }
        }
        if (dims.size() == 3){
            for (size_t i = 0; i < dims[0]; i++)
            {
                for(size_t j = 0; j < dims[1]; j++){
                    for(size_t k = 0; k < dims[2]; k++){
                        if(get(i,j,k) != std::numeric_limits<double>::quiet_NaN())
                            tot += get(i,j,k)*get(i,j,k);
                        }
                }
            }
        }
        return std::sqrt(tot);
    }
    double inf_norm(){
        double tot = 0;
        int max_i = 0, max_j = 0, max_k = 0;
        std::vector<size_t> dims = this->max_dims();
        if (dims.size() == 1){
            for (size_t i = 0; i < dims[0]; i++)
            {   
                if (std::abs(get(i)) > max_i && get(i) != std::numeric_limits<double>::quiet_NaN())
                    max_i = std::abs(get(i));
            }
            return max_i;
        }
        if (dims.size() == 2){
            for (size_t i = 0; i < dims[0]; i++)
            {
                for(size_t j = 0; j < dims[1]; j++){
                if (get(i,j) != std::numeric_limits<double>::quiet_NaN())
                    max_i += std::abs(get(i,j));
                    if (max_i > max_j)
                        max_j = max_i;
                }
            }
            return max_j;
        }
        if (dims.size() == 3){
            Tensor T(2);
            for (size_t i = 0; i < dims[0]; i++)
            {
                for(size_t j = 0; j < dims[1]; j++){
                    for(size_t k = 0; k < dims[2]; k++){
                        if (get(i,j,k) != std::numeric_limits<double>::quiet_NaN())
                            max_k += std::abs(get(i,j,k));
                    }
                T.set(max_k, i, j);
                }
            }
        return T.inf_norm();
        }
    }

    double norm(const std::string& norm_type){
        //types = "fro", "inf", "euclidean", "2"
        if (dim == 2){
            if (norm_type == "euclidean" || norm_type == "2" || norm_type == "fro")
                return this->euclidean_norm();
        }
    }
};

#endif //TENSOR_HH