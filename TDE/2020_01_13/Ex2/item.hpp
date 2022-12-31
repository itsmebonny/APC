#ifndef RANDOMKNAPSACK_ITEM_H
#define RANDOMKNAPSACK_ITEM_H
#include <iostream>
namespace random_greedy
{
    class item {
        double weight;
        double size;
        double value;
        public:
        item(double w, double s, double v)
        : weight(w), size(s), value(v) {}
        double get_size() const;
        double get_weight() const;
        double get_value() const;
        void print(void) const;
    };
}
#endif //RANDOMKNAPSACK_ITEM_H
