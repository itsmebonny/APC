// Price deviation evaluation v1

#include <iostream>
#include <iomanip>

using std::cout;
using std::cin;
using std::endl;
using std::setw;
void evaluate_deviation(unsigned num, double sum, const double prices[], const std::string zone);

const unsigned MAXDIM = 5;
const char center = 'c';
const char suburb = 's';
int main (void)
{
    // Your code goes here
    double pricesC[MAXDIM];
    double pricesS[MAXDIM];

    bool exit = false;
    unsigned numC = 0;
    unsigned numS = 0;
    double sumS = 0;
    double sumC = 0;
    while (!exit)
    {
        double price;
        char place;
        cout  << "Input price: ";
        cin >> price;
        cout << "Location: ";
        cin >> place;     
        if (numS >= MAXDIM || numC >= MAXDIM || !cin || (place != center && place != suburb))
        {
            exit = true;
        }
        else if (place == center)
        {
            pricesC[numC] = price;
            numC++;
            sumS = sumS + price;
        
        }
        else if (place == suburb)
        {
            pricesS[numS] = price;
            numS++;
            sumC = sumC + price;
        }
    }
void evaluate_deviation(numS, sumS, pricesS[], center);
void evaluate_deviation(numC, sumC, pricesC[], suburb);   
    
    

    // Your code goes here

return 0;
}
void evaluate_deviation(unsigned num, double sum, const double prices[], const std::string zone){     
    if (num != 0)
    {
        cout << endl << setw(20) << "Prices" << setw(40) << "Deviation from the mean" << endl;
        double mean = sum / num;
        
        for (unsigned i = 0; i < num; ++i)
        {
            double deviation = prices[i] - mean;
            cout << endl << setw(20) << prices[i] << setw(40) << deviation << endl;
        }
    }
}