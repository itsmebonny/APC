#include<openmpi/mpi.h>
#include<string>

#ifndef DATAFRAME_HH
#define DATAFRAME_HH
#include<string>
#include<map>
#include<vector>
#include<stdexcept>
#include<random>
#include<set>
std::vector<std::string> split(const std::string & s, char d = ' ');
class DataFrame
{
private:
    std::map<std::string, std::vector<double>> df;
public:
    DataFrame(std::set<std::string> s){
        for (auto i : s){
            df[i] = {};
        }
    };
    DataFrame(std::string s){
        std::vector<std::string> names = split(s);
        for (auto i : names){
            df[i] = {};
        }
    };
    void set_column(std::vector<double> v, std::string s){
        if(df.find(s) != df.end())
        {df.erase(s);
        df[s] = v;}
    }
    std::set<double> unique(std::string s) const {
        if(df.find(s) != df.end()){
            std::set<double> res(df.find(s)->second.begin(), df.find(s)->second.end());
        return res;}
    }
    std::vector<double> get_values(std::string s) const {
        if(df.find(s) != df.end()){
            std::vector<double> res = df.at(s);
        return res;}
    } 
    std::vector<std::string> get_column_names() const {
        std::vector<std::string> res;
        for(auto i:df)
            res.push_back(i.first);
        return res;
    }
    void drop_column(std::string s){
        if(df.find(s) != df.end())
        df.erase(s);
    }
    size_t max_rows() const{
        size_t max = 0;
        for (auto i : df)
        {
            if (i.second.size() > max)
                max = i.second.size();
        }
        return max;
    }
    /*
    DataFrame concatenate(const DataFrame second) const {
        DataFrame res = *this;
        for (auto i : second.get_column_names())
        {
            std::vector<double> column = this->df.at(i);
            column.insert(column.end(), second.get_values(i).begin(), second.get_values(i).end());
            res.set_column(column, i);
        }
        return res;
    }
    */
    std::vector<double> sum_by_rows() const {
        std::vector<double> res(max_rows());
        for(auto j:df){
            for (size_t i = 0; i < res.size(); i++)
            {   try
                {res[i] += j.second.at(i);}
                catch(std::out_of_range)
                {
                    //do nothing
                }
            }
            
        }
        return res;
    }
};


#endif //DATAFRAME_HH

DataFrame concatenate(const DataFrame& df){
    std::set<std::string> names(df.get_column_names().begin(), df.get_column_names().end());
    DataFrame res(names);
    int rank, size;
    for (auto i : df.get_column_names())
    {
        std::vector<double> val_local = df.get_values(i);
        std::vector<double> val_total;
        if(rank == 0){
            val_total.insert(val_total.end(), val_local.begin(), val_local.end());
        }
        size_t size_loc = val_local.size();
        if(rank!= 0)
        {
            for (size_t j = 1; j < size; j++)
            {
            MPI_Send(&size_loc, 1, MPI_UNSIGNED, j, 0, MPI_COMM_WORLD);
            MPI_Send(&val_local[0], size_loc, MPI_DOUBLE, j, 0, MPI_COMM_WORLD);}
        }
        else{
            for (size_t j = 1; j < size; j++)
            {
            MPI_Recv(&size_loc, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            MPI_Recv(&val_local[0], size_loc, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            val_total.insert(val_total.end(), val_local.begin(), val_local.end());
            }

        }
        res.set_column(val_total, i);
    }
    return res;
}

int main(int argc, char** argv) {
  MPI_Init(&argc, &argv);
  int rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  // Create a randomized data frame on each process
  std::set<std::string> column_names = {"col1", "col2"};
  DataFrame df(column_names);
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<> dis(0.0, 1.0);
  std::vector<double> values1(3), values2(3);
  for (int i = 0; i < 3; i++) {
    values1[i] = dis(gen);
    values2[i] = dis(gen);
  }
  df.set_column(values1, "col1");
  df.set_column(values2, "col2");

  // Send the data frame to each process
  if (rank == 0) {
    for (int i = 1; i < size; i++) {
      size_t num_values = df.get_values("col1").size();
      MPI_Send(&num_values, 1, MPI_UNSIGNED, i, 0, MPI_COMM_WORLD);
      for (const std::string& col_name : df.get_column_names()) {
        std::vector<double> values = df.get_values(col_name);
        MPI_Send(values.data(), values.size(), MPI_DOUBLE, i, 0, MPI_COMM_WORLD);
      }
    }
  } else {
    size_t num_values;
    MPI_Recv(&num_values, 1, MPI_UNSIGNED, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    std::set<std::string> column_names_recv = {"col1", "col2"};
    DataFrame df_recv(column_names_recv);
    for (const std::string& col_name : df_recv.get_column_names()) {
      std::vector<double> values(num_values);
      MPI_Recv(values.data(), num_values, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      df_recv.set_column(values, col_name);
    }
    df = df_recv;
  }
  // Concatenate the data frames
  DataFrame df_concatenated = concatenate(df);

  // Print the resulting data frame
  if (rank == 0) {
    std::cout << "Concatenated data frame:" << std::endl;
    for (const std::string& col_name : df_concatenated.get_column_names()) {
      std::cout << col_name << ": [";
      for (double value : df_concatenated.get_values(col_name)) {
        std::cout << value << " ";
      }
      std::cout << "]" << std::endl;
    }
  }

  MPI_Finalize();
  return 0;
}