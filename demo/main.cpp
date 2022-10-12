//
// Created by Troldal on 01/10/2022.
//

#include "../XLSteamBackend.h"
#include <iostream>

int main() {


    auto U = XLSteam::XLSteamPT(1.82824e+06, 440.277, "U");
    auto V = XLSteam::XLSteamPT(1.82824e+06, 440.277, "V");

    std::cout << XLSteam::XLSteamUV(U, V, "P") << std::endl;
    return 0;
}