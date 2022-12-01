#include"SalesData.hpp"


using std::cout;
using std::cerr;
using std::endl;


SalesData&
SalesData::combine (const SalesData &rhs)
{
units_sold += rhs.units_sold;
revenue += rhs.revenue;
return *this;
}
double
SalesData::avg_price () const
{
if (units_sold==0)
{
cerr << "No books have been sold" << endl;
return 0.0;
}
return revenue/units_sold;
}
void
SalesData::print (void) const
{
cout << "ISBN: " << BookNo <<
" units_sold: " << units_sold << " revenue: " << revenue << endl;
}
