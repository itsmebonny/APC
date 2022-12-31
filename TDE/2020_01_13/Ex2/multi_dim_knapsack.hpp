#ifndef RANDOMKNAPSACK_MULTI_DIM_KNAPSACK_H
#define RANDOMKNAPSACK_MULTI_DIM_KNAPSACK_H
#include <random>
#include <utility>
#include <algorithm>
#include <vector>
#include <fstream>
#include "item.hpp"
namespace random_greedy
{
std::vector<double> normalize(std::vector<double> vec){
    std::vector<double> result;
    double min = *std::min_element(vec.begin(), vec.end());
    double max = *std::max_element(vec.begin(), vec.end());
    for (size_t i = 0; i < vec.size(); i++)
    {
        result.push_back((vec.at(i)-min)/(max-min));
    }
    return result;
}
class multi_dim_knapsack
{
    public:
    using solution_type = std::vector<bool>;
    private:
    std::vector<item> m_items;
    std::vector<double> m_weights;
    std::vector<double> m_sizes;
    std::vector<double> m_values;
    double m_w;
    double m_s;
    std::mt19937_64 m_random_engine;
    bool check_feasibility (const solution_type &solution) const{
        int sol_w, sol_s;
        for (size_t i = 0; i < solution.size(); i++)
        {
            sol_w = solution.at(i)*m_weights.at(i);
            sol_s = solution.at(i)*m_sizes.at(i);
        }
        return sol_w <= m_w && sol_s <= m_s;
        
    };
    void make_feasible (solution_type &solution){
        int size = solution.size()-1;
        while(!check_feasibility(solution)){
            std::uniform_int_distribution<int> dist(0, size);
            int chosen = dist(m_random_engine);
            solution.at(chosen) = false;
        }
        
    };
    public:
    multi_dim_knapsack (double w, double s, std::size_t seed = 0):m_w(w), m_s(s), m_random_engine(seed){};

    void add_item (const item & i); // Add i to m_items and updates
    // m_weights, m_sizes, and m_values accordingly
    solution_type greedy_random_solution (void) {
        solution_type solution;
        std::vector<std::vector<double>> top_hat;
        std::uniform_int_distribution top_hat_choice(0,2);
        std::uniform_real_distribution poisson(0,1);
        top_hat.push_back(normalize(m_values));
        top_hat.push_back(normalize(m_sizes));
        top_hat.push_back(normalize(m_weights));
        for (size_t i = 0; i < m_items.size(); i++)
        {
            int chosen = top_hat_choice(m_random_engine);
            double p = top_hat.at(chosen).at(i);
            if (p > poisson(m_random_engine))
                solution.push_back(true);
            else
                solution.push_back(false);
        }
        if (!check_feasibility(solution))
        {
            make_feasible(solution);
        }
        
        return solution;
    }; // returns a random feasible solution
    double solution_value (const solution_type & s) const{
        int total = 0;
        for (size_t i = 0; i < s.size(); i++)
        {
            total += s.at(i)*m_values.at(i);
        }
        return total;
        
    }; // returns the value of the solution s
    void print_solution (std::ofstream & os, const solution_type & s) const; // prints the solution s
    // on the stream os
};
multi_dim_knapsack::solution_type random_greedy_search(multi_dim_knapsack m, unsigned local_iterations){
    multi_dim_knapsack::solution_type solution;
    multi_dim_knapsack::solution_type best_solution;
    double top = 0;
    for (size_t i = 0; i < local_iterations; i++)
    {
        solution = m.greedy_random_solution();
        if (m.solution_value(solution) > top){
            best_solution = solution;
            top = m.solution_value(solution);
        }
    }
    return best_solution;
}
}
#endif //RANDOMKNAPSACK_MULTI_DIM_KNAPSACK_H