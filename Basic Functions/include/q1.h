#ifndef Q1_H
#define Q1_H

#include <cmath>

namespace q1
{
    template <typename T, typename Fun>
    static double gradient_descent(T initial_value, double step_size, Fun func = Fun{})
    {
        double Dispute{step_size * ((func(initial_value) - func(initial_value - 0.001)) / 0.001)};
        while (std::abs(Dispute) >= 0.000001)
        {
            Dispute = step_size * ((func(initial_value) - func(initial_value - 0.001)) / 0.001);
            initial_value = initial_value - Dispute;
        }
        return initial_value;
    }
}

#endif // Q1_H