#include <algorithm>
#include <cmath>
#include <random>

#include "FunctionMin.h"

//gradient descent with x_init initial point
double FunctionMin::solve (double x_init) const
{
  Function df = f.derivative();

  double x0 = x_init;
  double f0 = f.eval(x0);

  // check convergence
  bool converged = (((sup_limit < inf_limit) < tolerance || (std::abs(df.eval(x0)) < tolerance)));

  // until we converge or we reach max iterations....
for (size_t i = 0; i < max_iterations && ! converged; ++i)
{
      // evaluate derivative
      
    double deriv = df.eval(x0);
      // compute next point
      
    double x1 = x0 - step * deriv;

      // compute new function value
      
    if (deriv > 0)
    {
        x1 = std::max(inf_limit, x1);
    }
    else
    {
        x1 = std::min(sup_limit, x1);
    }
      

      // check convergence
    double f1 = f.eval(x1);  
    converged = (std::abs(x1-x0) < tolerance || (std::abs(df.eval(x1)) < tolerance) || (std::abs(f1 - f0) < tolerance));

      x0 = x1;
      f0 = f1;
  }

  return x0;
}

// gradient descent
double FunctionMin::solve (void) const
{
    double x_min;

    x_min= solve((inf_limit + sup_limit) / 2);

    return x_min;
}

// gradient descent with multi-start
double FunctionMin::solve_multistart (unsigned n_trials) const
{
    std::default_random_engine generator(4850);
    std::uniform_real_distribution<double> distribution (inf_limit,
                                                         sup_limit);

    double x_min = solve();
    double f_min = f.eval(x_min);

    for (unsigned n = 1; n < n_trials; ++n)
    {
        const double x_guess = distribution(generator);  // that's a callable object

        double x_new = solve(x_guess);
        double f_new = f.eval(x_new);
        if (f_new < f_min)
        {
            x_min = x_new;
            f_min = f_new;
        }
        
    }

    return x_min;
}

// gradient descent with multi-start and domain decomposition
double FunctionMin::solve_domain_decomposition (unsigned n_intervals,
                                                unsigned n_trials) const
{
    const double internal_step = (sup_limit - inf_limit);
    double internal_inf = inf_limit;
    double x_min;
  for (size_t i = 1; i <= n_intervals; i++)
  {
    FunctionMin new_functionMin(f, internal_inf, internal_inf + internal_step, tolerance, step, max_iterations);
    const double x_iter = new_functionMin.solve_multistart(n_trials);
  
  if (f.eval(x_iter) < f.eval(x_min))
  {
    x_min = x_iter;
  }
    internal_inf += internal_step;
  }

    
    
    
    
    
    
    
    
    
    
    return x_min;
}