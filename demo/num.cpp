//
// Created by Troldal on 06/10/2022.
//

#include "../numeric/roots/roots.hpp"
#include <iostream>
#include <iomanip>
#include <format>

int main() {

    using namespace numerix::roots;

    auto solver = bisection([](double x) {return x * x - 5;});
    auto bounds = std::make_pair(0.0, 2.5);

//    for (int i = 1; i < 20; ++i) {
//        std::cout << std::fixed << std::setprecision(10);
//        std::cout << bounds.first << "\t" << bounds.second << "\t" << (bounds.first + bounds.second) / 2.0 << std::endl;
//        bounds = solver.iterate(bounds);
//    }

    auto result1 = fsolve(ridders([](double x) {return x * x - 5;}), std::make_pair(0.0, 2.5), 1.0E-15,10);
    std::cout << std::setprecision(20) << result1 << std::endl;

    auto result2 = fsolve(bisection([](double x) {return x * x - 5;}), std::make_pair(0.0, 2.5), 1.0E-15,52);
    std::cout << std::setprecision(20) << result2 << std::endl;

    return 0;
}