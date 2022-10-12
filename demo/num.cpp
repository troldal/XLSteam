//
// Created by Troldal on 06/10/2022.
//

#include "../numeric/roots/roots.hpp"
#include "TablePrinter.hpp"
#include <iostream>
#include <iomanip>
#include <format>

int main() {

    using namespace trl;



//    tp.Begin();
//    tp << "Dat Chu" << 1 << "Research Assistant" << -0.00000000001337;
//    tp << "John Doe" << 12 << "Too much float" << 125456789.123456789;
//    tp << "John Doe" << 123 << "Typical Int" << 1254567894;
//    tp << "John Doe" << 1234 << "Typical float" << 1254.36;
//    tp << "John Doe" << 12345 << "Too much negative" << -125456789.123456789;
//    tp << "John Doe" << 26 << "Exact size int" << 125456789;
//    tp << "John Doe" << 26 << "Exact size int" << -12545678;
//    tp << "John Doe" << 26 << "Exact size float" << -1254567.8;
//    tp << "John Doe" << 26 << "Negative Int" << -1254;
//    tp << "Jane Doe" << trl::endl();
//    tp << "Tom Doe" << 123456 << "Student" << 3.141;
//    tp.End();



    using namespace numerix::roots;

    auto solver = ridders([](double x) {return x * x - 5;});
    auto bounds = std::make_pair(0.0, 2.5);
    solver.init(bounds);

    trl::TablePrinter tp;

    trl::ColumnFormat colLower;
    colLower.alignment        = trl::TextAlignment::Decimal;
    colLower.decimalFormat    = trl::DecimalFormat::Fixed;
    colLower.decimalPlaces    = 20;
    colLower.headerText       = "Lower";
    colLower.width            = 24;

    trl::ColumnFormat colUpper;
    colUpper.alignment        = trl::TextAlignment::Decimal;
    colUpper.decimalFormat    = trl::DecimalFormat::Fixed;
    colUpper.decimalPlaces    = 20;
    colUpper.headerText       = "Upper";
    colUpper.width            = 24;

    trl::ColumnFormat colRoot;
    colRoot.alignment        = trl::TextAlignment::Decimal;
    colRoot.decimalFormat    = trl::DecimalFormat::Fixed;
    colRoot.decimalPlaces    = 20;
    colRoot.headerText       = "Root";
    colRoot.width            = 24;

    trl::ColumnFormat colEps;
    colEps.alignment        = trl::TextAlignment::Decimal;
    colEps.decimalFormat    = trl::DecimalFormat::Fixed;
    colEps.decimalPlaces    = 20;
    colEps.headerText       = "Eps";
    colEps.width            = 24;

    tp.AddColumn("Iter", 10);
    tp.AddColumn(colLower);
    tp.AddColumn(colUpper);
    tp.AddColumn(colRoot);
    tp.AddColumn(colEps);

    tp.Begin();

    for (int i = 0; i <= 100; ++i) {
        //std::cout << std::fixed << std::setprecision(10);

        tp << i;
        tp << bounds.first;
        tp << bounds.second;
        tp << (bounds.first + bounds.second) / 2.0;
        tp << abs(bounds.first - bounds.second);

        if (abs(bounds.first - bounds.second) < 1.0E-15) break;

        //std::cout << bounds.first << "\t" << bounds.second << "\t" << (bounds.first + bounds.second) / 2.0 << std::endl;
        solver.iterate();
        bounds = solver.get_bounds();
    }

    tp.End();

    auto result1 = fsolve(ridders([](double x) {return x * x - 5;}), std::make_pair(0.0, 2.5), 1.0E-15,10);
    std::cout << std::setprecision(20) << result1 << std::endl;

    auto result2 = fsolve(bisection([](double x) {return x * x - 5;}), std::make_pair(0.0, 2.5), 1.0E-15,52);
    std::cout << std::setprecision(20) << result2 << std::endl;

    return 0;
}