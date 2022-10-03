//
// Created by Troldal on 01/10/2022.
//

#include "../XLSteamBackend.h"
#include <random>
#include <iostream>
#include <string>

std::pair<double, double> generate_pt() {

    std::random_device rd;  // Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()
    std::uniform_real_distribution<double> rand_pressure(0.0, 100E6);

    double pressure = rand_pressure(gen);
    double temperature {};

    if (pressure > 50E6) {
        std::uniform_real_distribution<double> rand_temperature(273.15, 1073.15);
        temperature = rand_temperature(gen);
    }
    else {
        std::uniform_real_distribution<double> rand_temperature(273.15, 2273.15);
        temperature = rand_temperature(gen);
    }

    return std::make_pair(pressure, temperature);
}

std::string test(double pressure, double temperature) {
    auto P = XLSteam::XLSteamPT(pressure, temperature, "P");
    auto T = XLSteam::XLSteamPT(pressure, temperature, "T");
    auto H = XLSteam::XLSteamPT(pressure, temperature, "H");
    auto S = XLSteam::XLSteamPT(pressure, temperature, "S");
    auto U = XLSteam::XLSteamPT(pressure, temperature, "U");
    auto V = XLSteam::XLSteamPT(pressure, temperature, "V");

    if (std::isnan(P)) return "PT-P";
    if (std::isnan(T)) return "PT-T";
    if (std::isnan(H)) return "PT-H";
    if (std::isnan(S)) return "PT-S";
    if (std::isnan(U)) return "PT-U";
    if (std::isnan(V)) return "PT-V";

    if (std::isnan(XLSteam::XLSteamPH(P, H, "P"))) return "PH-P";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "T"))) return "PH-T";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "H"))) return "PH-H";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "S"))) return "PH-S";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "U"))) return "PH-U";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "V"))) return "PH-V";

    if (std::isnan(XLSteam::XLSteamPS(P, S, "P"))) return "PS-P";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "T"))) return "PS-T";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "H"))) return "PS-H";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "S"))) return "PS-S";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "U"))) return "PS-U";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "V"))) return "PS-V";

    if (std::isnan(XLSteam::XLSteamPU(P, U, "P"))) return "PU-P";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "T"))) return "PU-T";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "H"))) return "PU-H";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "S"))) return "PU-S";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "U"))) return "PU-U";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "V"))) return "PU-V";

    if (std::isnan(XLSteam::XLSteamPV(P, V, "P"))) return "PV-P";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "T"))) return "PV-T";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "H"))) return "PV-H";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "S"))) return "PV-S";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "U"))) return "PV-U";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "V"))) return "PV-V";

    if (std::isnan(XLSteam::XLSteamTV(T, V, "P"))) return "TV-P";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "T"))) return "TV-T";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "H"))) return "TV-H";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "S"))) return "TV-S";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "U"))) return "TV-U";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "V"))) return "TV-V";

    return "";
}

int main() {

    for (int i = 0; i < 10000; ++i) {
        auto pt = generate_pt();
        auto result = test(pt.first, pt.second);
        if (!result.empty()) {
            std::cout << result << "\t" << "P = " << pt.first << "\tT = " << pt.second << std::endl;
        }
    }

    std::cout << "TEST COMPLETED!";
    return 0;
}