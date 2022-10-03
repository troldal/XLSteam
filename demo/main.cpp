//
// Created by Troldal on 01/10/2022.
//

#include "../XLSteamBackend.h"
#include <iostream>

int main() {


    auto P = XLSteam::XLSteamPT(6.14027e+06, 276.282, "P");
    auto V = XLSteam::XLSteamPT(6.14027e+06, 276.282, "V");

    std::cout << XLSteam::XLSteamPV(P, V, "T") << std::endl;
    return 0;
}