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
    std::uniform_real_distribution<double> rand_pressure(612.0, 100E6);

    double pressure = rand_pressure(gen);
    double temperature {};

    if (pressure > 50E6) {
        std::uniform_real_distribution<double> rand_temperature(std::max(273.15,-2.0494E-7*pressure + 2.7715E2), 1073.15);
        temperature = rand_temperature(gen);
    }
    else {
        std::uniform_real_distribution<double> rand_temperature(std::max(273.15,-2.0494E-7*pressure + 2.7715E2), 2273.15);
        temperature = rand_temperature(gen);
    }

    return std::make_pair(pressure, temperature);
}

bool Approx(double a, double b) {
    auto diff = std::abs(a - b);
    return (diff / a) <= 1E-5;
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

    if (std::isnan(XLSteam::XLSteamPH(P, H, "P")) || !Approx(XLSteam::XLSteamPH(P, H, "P"), P)) return "PH-P";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "T")) || !Approx(XLSteam::XLSteamPH(P, H, "T"), T)) return "PH-T";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "H")) || !Approx(XLSteam::XLSteamPH(P, H, "H"), H)) return "PH-H";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "S")) || !Approx(XLSteam::XLSteamPH(P, H, "S"), S)) return "PH-S";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "U")) || !Approx(XLSteam::XLSteamPH(P, H, "U"), U)) return "PH-U";
    if (std::isnan(XLSteam::XLSteamPH(P, H, "V")) || !Approx(XLSteam::XLSteamPH(P, H, "V"), V)) return "PH-V";

    if (std::isnan(XLSteam::XLSteamPS(P, S, "P")) || !Approx(XLSteam::XLSteamPS(P, S, "P"), P)) return "PS-P";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "T")) || !Approx(XLSteam::XLSteamPS(P, S, "T"), T)) return "PS-T";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "H")) || !Approx(XLSteam::XLSteamPS(P, S, "H"), H)) return "PS-H";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "S")) || !Approx(XLSteam::XLSteamPS(P, S, "S"), S)) return "PS-S";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "U")) || !Approx(XLSteam::XLSteamPS(P, S, "U"), U)) return "PS-U";
    if (std::isnan(XLSteam::XLSteamPS(P, S, "V")) || !Approx(XLSteam::XLSteamPS(P, S, "V"), V)) return "PS-V";

    if (std::isnan(XLSteam::XLSteamPU(P, U, "P")) || !Approx(XLSteam::XLSteamPU(P, U, "P"), P)) return "PU-P";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "T")) || !Approx(XLSteam::XLSteamPU(P, U, "T"), T)) return "PU-T";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "H")) || !Approx(XLSteam::XLSteamPU(P, U, "H"), H)) return "PU-H";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "S")) || !Approx(XLSteam::XLSteamPU(P, U, "S"), S)) return "PU-S";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "U")) || !Approx(XLSteam::XLSteamPU(P, U, "U"), U)) return "PU-U";
    if (std::isnan(XLSteam::XLSteamPU(P, U, "V")) || !Approx(XLSteam::XLSteamPU(P, U, "V"), V)) return "PU-V";

    if (std::isnan(XLSteam::XLSteamPV(P, V, "P")) || !Approx(XLSteam::XLSteamPV(P, V, "P"), P)) return "PV-P";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "T")) || !Approx(XLSteam::XLSteamPV(P, V, "T"), T)) return "PV-T";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "H")) || !Approx(XLSteam::XLSteamPV(P, V, "H"), H)) return "PV-H";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "S")) || !Approx(XLSteam::XLSteamPV(P, V, "S"), S)) return "PV-S";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "U")) || !Approx(XLSteam::XLSteamPV(P, V, "U"), U)) return "PV-U";
    if (std::isnan(XLSteam::XLSteamPV(P, V, "V")) || !Approx(XLSteam::XLSteamPV(P, V, "V"), V)) return "PV-V";

    if (std::isnan(XLSteam::XLSteamTV(T, V, "P")) || !Approx(XLSteam::XLSteamTV(T, V, "P"), P)) return "TV-P";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "T")) || !Approx(XLSteam::XLSteamTV(T, V, "T"), T)) return "TV-T";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "H")) || !Approx(XLSteam::XLSteamTV(T, V, "H"), H)) return "TV-H";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "S")) || !Approx(XLSteam::XLSteamTV(T, V, "S"), S)) return "TV-S";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "U")) || !Approx(XLSteam::XLSteamTV(T, V, "U"), U)) return "TV-U";
    if (std::isnan(XLSteam::XLSteamTV(T, V, "V")) || !Approx(XLSteam::XLSteamTV(T, V, "V"), V)) return "TV-V";

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