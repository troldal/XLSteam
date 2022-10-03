//
// Created by Troldal on 21/09/2022.
//

#ifndef XLSTEAM_XLSTEAMBACKEND_H
#define XLSTEAM_XLSTEAMBACKEND_H

#include <limits>
#include "IF97.h"
#include "numeric/roots.hpp"

namespace XLSteam {

    enum class PropertyType {
        Pressure,
        Temperature,
        SaturationPressure,
        SaturationTemperature,
        Density,
        Volume,
        Enthalpy,
        Entropy,
        InternalEnergy,
        Cp,
        Cv,
        SpeedOfSound,
        IsentropicExponent,
        HelmholtzEnergy,
        GibbsEnergy,
        CompressibilityFactor,
        VaporQuality,
        DynamicViscosity,
        KinematicViscosity,
        ThermalConductivity,
        PrandtlNumber,
        Undefined
    };

    inline PropertyType Property(const char* PropID) {

        auto PropertyID = std::string(PropID);
        std::transform(PropertyID.begin(), PropertyID.end(), PropertyID.begin(), [](unsigned char c){ return std::toupper(c); });

        if (PropertyID == "P" || PropertyID == "PRESSURE")
            return PropertyType::Pressure;

        if (PropertyID == "T" || PropertyID == "TEMPERATURE")
            return PropertyType::Temperature;

        if (PropertyID == "PSAT")
            return PropertyType::SaturationPressure;

        if (PropertyID == "TSAT")
            return PropertyType::SaturationTemperature;

        if (PropertyID == "RHO" || PropertyID == "DENSITY")
            return PropertyType::Density;

        if (PropertyID == "V" || PropertyID == "VOL" || PropertyID == "VOLUME")
            return PropertyType::Volume;

        if (PropertyID == "H" || PropertyID == "ENTHALPY")
            return PropertyType::Enthalpy;

        if (PropertyID == "S" || PropertyID == "ENTROPY")
            return PropertyType::Entropy;

        if (PropertyID == "U" || PropertyID == "INTERNAL ENERGY")
            return PropertyType::InternalEnergy;

        if (PropertyID == "CP")
            return PropertyType::Cp;

        if (PropertyID == "CV")
            return PropertyType::Cv;

        if (PropertyID == "W" || PropertyID == "SPEED OF SOUND")
            return PropertyType::SpeedOfSound;

        if (PropertyID == "KAPPA" || PropertyID == "ISENTROPIC EXPONENT")
            return PropertyType::IsentropicExponent;

        if (PropertyID == "A" || PropertyID == "F" || PropertyID == "HELMHOLTZ FREE ENERGY")
            return PropertyType::HelmholtzEnergy;

        if (PropertyID == "G" || PropertyID == "GIBBS FREE ENERGY")
            return PropertyType::GibbsEnergy;

        if (PropertyID == "Z" || PropertyID == "COMPRESSIBILITY FACTOR")
            return PropertyType::CompressibilityFactor;

        if (PropertyID == "X" || PropertyID == "QUALITY")
            return PropertyType::VaporQuality;

        if (PropertyID == "ETA" || PropertyID == "DYNAMIC VISCOSITY")
            return PropertyType::DynamicViscosity;

        if (PropertyID == "NU" || PropertyID == "KINEMATIC VISCOSITY")
            return PropertyType::KinematicViscosity;

        if (PropertyID == "TC" || PropertyID == "THERMAL CONDUCTIVITY")
            return PropertyType::ThermalConductivity;

        if (PropertyID == "PR" || PropertyID == "PRANDTL NUMBER")
            return PropertyType::PrandtlNumber;

        return PropertyType::Undefined;
    }

    inline double XLSteamPT(double Pressure, double Temperature, const char* PropID) {

        if (Temperature < 273.15 || Temperature > 2273.15) return std::nan("0");
        if (Pressure < 0.0 || Pressure > 100000000.0) return std::nan("0");
        if (Temperature > 1073.15 && Pressure > 50000000.0) return std::nan("0");

        try {
            switch (Property(PropID)) {

                case PropertyType::Pressure:
                    return Pressure;
                case PropertyType::Temperature:
                    return Temperature;
                case PropertyType::SaturationPressure:
                    return IF97::psat97(Temperature);
                case PropertyType::SaturationTemperature:
                    return IF97::Tsat97(Pressure);
                case PropertyType::Density:
                    return IF97::rhomass_Tp(Temperature, Pressure);
                case PropertyType::Volume:
                    return 1.0 / IF97::rhomass_Tp(Temperature, Pressure);
                case PropertyType::Enthalpy:
                    return IF97::hmass_Tp(Temperature, Pressure);
                case PropertyType::Entropy:
                    return IF97::smass_Tp(Temperature, Pressure);
                case PropertyType::InternalEnergy:
                    return IF97::umass_Tp(Temperature, Pressure);
                case PropertyType::Cp:
                    return IF97::cpmass_Tp(Temperature, Pressure);
                case PropertyType::Cv:
                    return IF97::cvmass_Tp(Temperature, Pressure);
                case PropertyType::SpeedOfSound:
                    return IF97::speed_sound_Tp(Temperature, Pressure);
                case PropertyType::IsentropicExponent:
                    return IF97::cpmass_Tp(Temperature, Pressure) / IF97::cvmass_Tp(Temperature, Pressure);
                case PropertyType::HelmholtzEnergy:
                    return IF97::umass_Tp(Temperature, Pressure) - Temperature * IF97::smass_Tp(Temperature, Pressure);
                case PropertyType::GibbsEnergy:
                    return IF97::hmass_Tp(Temperature, Pressure) - Temperature * IF97::smass_Tp(Temperature, Pressure);
                case PropertyType::CompressibilityFactor:
                    return Pressure * (1.0 / IF97::rhomass_Tp(Temperature, Pressure)) * IF97::get_MW() /
                           (Temperature * 8.31446261815324);
                case PropertyType::VaporQuality:
                    if (Temperature > IF97::get_Tcrit() && Pressure > IF97::get_pcrit()) return std::nan("0");
                    if (Temperature <= IF97::get_Tcrit() && Pressure > IF97::psat97(Temperature)) return 0.0;
                    if (Pressure <= IF97::get_pcrit() && Temperature > IF97::Tsat97(Pressure)) return 1.0;
                    return std::nan("0");
                case PropertyType::DynamicViscosity:
                    return IF97::visc_Tp(Temperature, Pressure);
                case PropertyType::KinematicViscosity:
                    return IF97::visc_Tp(Temperature, Pressure) / IF97::rhomass_Tp(Temperature, Pressure);
                case PropertyType::ThermalConductivity:
                    return IF97::tcond_Tp(Temperature, Pressure);
                case PropertyType::PrandtlNumber:
                    return IF97::prandtl_Tp(Temperature, Pressure);
                default:
                    return std::nan("0");
            }
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPX(double Pressure, double Quality, const char* PropID) {

        if (Pressure < 0.0 || Pressure > IF97::get_pcrit()) return std::nan("0");
        if (Quality < 0.0 || Quality > 1.0) return std::nan("0");

        try {
            switch (Property(PropID)) {

                case PropertyType::Pressure:
                    return Pressure;
                case PropertyType::Temperature:
                    return IF97::Tsat97(Pressure);
                case PropertyType::SaturationPressure:
                    return Pressure;
                case PropertyType::SaturationTemperature:
                    return IF97::Tsat97(Pressure);
                case PropertyType::Density:
                    return IF97::rhomass_pQ(Pressure, Quality);
                case PropertyType::Volume:
                    return 1.0 / IF97::rhomass_pQ(Pressure, Quality);
                case PropertyType::Enthalpy:
                    return IF97::hmass_pQ(Pressure, Quality);
                case PropertyType::Entropy:
                    return IF97::smass_pQ(Pressure, Quality);
                case PropertyType::InternalEnergy:
                    return IF97::umass_pQ(Pressure, Quality);
                case PropertyType::Cp:
                    return IF97::cpvap_p(Pressure) * Quality + IF97::cpliq_p(Pressure) * (1 - Quality);
                case PropertyType::Cv:
                    return IF97::cvvap_p(Pressure) * Quality + IF97::cvliq_p(Pressure) * (1 - Quality);
                case PropertyType::SpeedOfSound:
                    if (Quality == 1.0) return IF97::speed_soundvap_p(Pressure);
                    if (Quality == 0.0) return IF97::speed_soundliq_p(Pressure);
                    return std::nan("0");
                case PropertyType::IsentropicExponent:
                    return XLSteamPX(Pressure, Quality, "CP") / XLSteamPX(Pressure, Quality, "CV");
                case PropertyType::HelmholtzEnergy:
                    return IF97::umass_pQ(Pressure, Quality) -
                           IF97::Tsat97(Pressure) * IF97::smass_pQ(Pressure, Quality);
                case PropertyType::GibbsEnergy:
                    return IF97::hmass_pQ(Pressure, Quality) -
                           IF97::Tsat97(Pressure) * IF97::smass_pQ(Pressure, Quality);
                case PropertyType::CompressibilityFactor:
                    return Pressure * (1.0 / IF97::rhomass_pQ(Pressure, Quality)) * IF97::get_MW() /
                           (IF97::Tsat97(Pressure) * 8.31446261815324);
                case PropertyType::VaporQuality:
                    return Quality;
                case PropertyType::DynamicViscosity:
                    if (Quality == 1.0) return IF97::viscvap_p(Pressure);
                    if (Quality == 0.0) return IF97::viscliq_p(Pressure);
                    return std::nan("0");
                case PropertyType::KinematicViscosity:
                    return XLSteamPX(Pressure, Quality, "ETA") / XLSteamPX(Pressure, Quality, "RHO");
                case PropertyType::ThermalConductivity:
                    if (Quality == 1.0) return IF97::tcondvap_p(Pressure);
                    if (Quality == 0.0) return IF97::tcondliq_p(Pressure);
                    return std::nan("0");
                case PropertyType::PrandtlNumber:
                    if (Quality == 1.0) return IF97::prandtlvap_p(Pressure);
                    if (Quality == 0.0) return IF97::prandtlliq_p(Pressure);
                    return std::nan("0");
                default:
                    return std::nan("0");
            }
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamTX(double Temperature, double Quality, const char* PropID) {

        if (Temperature < 273.16 || Temperature > IF97::get_Tcrit()) return std::nan("0");
        if (Quality < 0.0 || Quality > 1.0) return std::nan("0");

        try {
            return XLSteamPX(IF97::psat97(Temperature), Quality, PropID);
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPH(double Pressure, double Enthalpy, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100000000.0) return std::nan("0");

        try {
            if (Pressure > IF97::get_pcrit()) {
                auto t_lower = 273.15;
                auto t_upper = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature =
                    numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "H") - Enthalpy; }, t_lower, t_upper, 1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            auto h_liq = XLSteamPX(Pressure, 0.0, "H");
            auto h_vap = XLSteamPX(Pressure, 1.0, "H");

            if (Enthalpy >= h_liq && Enthalpy <= h_vap) {
                auto quality =
                    numeric::ridders([&](double x) { return XLSteamPX(Pressure, x, "H") - Enthalpy; }, 0.0, 1.0, 1.0E-9);
                return XLSteamPX(Pressure, quality, PropID);
            }

            if (Enthalpy < h_liq) {
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "H") - Enthalpy; },
                                                    273.15,
                                                    IF97::Tsat97(Pressure),
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            if (Enthalpy > h_vap) {
                auto t_upper  = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "H") - Enthalpy; },
                                                    IF97::Tsat97(Pressure),
                                                    t_upper,
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }
            return std::nan("0");
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPS(double Pressure, double Entropy, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100E6) return std::nan("0");

        try {
            if (Pressure > IF97::get_pcrit()) {
                auto t_lower = 273.15;
                auto t_upper = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature =
                    numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "S") - Entropy; }, t_lower, t_upper, 1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            auto s_liq = XLSteamPX(Pressure, 0.0, "S");
            auto s_vap = XLSteamPX(Pressure, 1.0, "S");

            if (Entropy >= s_liq && Entropy <= s_vap) {
                auto quality =
                    numeric::ridders([&](double x) { return XLSteamPX(Pressure, x, "S") - Entropy; }, 0.0, 1.0, 1.0E-9);
                return XLSteamPX(Pressure, quality, PropID);
            }

            if (Entropy < s_liq) {
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "S") - Entropy; },
                                                    273.15,
                                                    IF97::Tsat97(Pressure),
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            if (Entropy > s_vap) {
                auto t_upper  = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "S") - Entropy; },
                                                    IF97::Tsat97(Pressure),
                                                    t_upper,
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }
            return std::nan("0");
        }
        catch (...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPU(double Pressure, double InternalEnergy, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100E6) return std::nan("0");

        try {
            if (Pressure > IF97::get_pcrit()) {
                auto t_lower = 273.15;
                auto t_upper = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature =
                    numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "U") - InternalEnergy; }, t_lower, t_upper, 1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            auto u_liq = XLSteamPX(Pressure, 0.0, "U");
            auto u_vap = XLSteamPX(Pressure, 1.0, "U");

            if (InternalEnergy >= u_liq && InternalEnergy <= u_vap) {
                auto quality =
                    numeric::ridders([&](double x) { return XLSteamPX(Pressure, x, "U") - InternalEnergy; }, 0.0, 1.0, 1.0E-9);
                return XLSteamPX(Pressure, quality, PropID);
            }

            if (InternalEnergy < u_liq) {
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "U") - InternalEnergy; },
                                                    273.15,
                                                    IF97::Tsat97(Pressure),
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            if (InternalEnergy > u_vap) {
                auto t_upper  = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "U") - InternalEnergy; },
                                                    IF97::Tsat97(Pressure),
                                                    t_upper,
                                                    1.0E-9);
                return XLSteamPT(Pressure, temperature, PropID);
            }
            return std::nan("0");
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPV(double Pressure, double Volume, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100e6) return std::nan("0");

        try {
            if (Pressure > IF97::get_pcrit()) {
                auto t_lower = 273.15;
                auto t_upper = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature =
                    numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "VOL") - Volume; }, t_lower, t_upper, 1.0E-12);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            auto v_liq = XLSteamPX(Pressure, 0.0, "VOL");
            auto v_vap = XLSteamPX(Pressure, 1.0, "VOL");

            if (Volume >= v_liq && Volume <= v_vap) {
                auto quality =
                    numeric::ridders([&](double x) { return XLSteamPX(Pressure, x, "VOL") - Volume; }, 0.0, 1.0, 1.0E-12);
                return XLSteamPX(Pressure, quality, PropID);
            }

            if (Volume < v_liq) {
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "VOL") - Volume; },
                                                      (std::max(273.15,-2.0494E-7*Pressure + 2.7715E2)), // This expression calculates the temperature at which the liquid volume is the lowest
                                                      IF97::Tsat97(Pressure),
                                                      1.0E-15);
                return XLSteamPT(Pressure, temperature, PropID);
            }

            if (Volume > v_vap) {
                auto t_upper  = Pressure > 50E6 ? 1073.15 : 2273.15;
                auto temperature = numeric::ridders([&](double t) { return XLSteamPT(Pressure, t, "VOL") - Volume; },
                                                 IF97::Tsat97(Pressure),
                                                 t_upper,
                                                 1.0E-12);
                return XLSteamPT(Pressure, temperature, PropID);
            }
            return std::nan("0");
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamTV(double Temperature, double Volume, const char* PropID) {
        if (Temperature < 273.15 || Temperature > 2273.15) return std::nan("0");

        try {
            if (Temperature > IF97::get_Tcrit()) {
                auto p_lower = 0.0;
                auto p_upper = Temperature > 1073.15 ? 50E6 : 100E6;
                auto pressure =
                    numeric::ridders([&](double p) { return XLSteamPT(p, Temperature, "VOL") - Volume; }, p_lower, p_upper, 1.0E-12);
                return XLSteamPT(pressure, Temperature, PropID);
            }

            auto v_liq = XLSteamTX(Temperature, 0.0, "VOL");
            auto v_vap = XLSteamTX(Temperature, 1.0, "VOL");

            if (Volume >= v_liq && Volume <= v_vap) {
                auto quality =
                    numeric::ridders([&](double x) { return XLSteamTX(Temperature, x, "VOL") - Volume; }, 0.0, 1.0, 1.0E-12);
                return XLSteamTX(Temperature, quality, PropID);
            }

            if (Volume > v_vap) {
                auto pressure = numeric::ridders([&](double p) { return XLSteamPT(p, Temperature, "VOL") - Volume; },
                                                 1000.0,
                                                 IF97::psat97(Temperature) - 1.0, // Required to ensure we are outside saturation line.
                                                 1.0E-12);
                return XLSteamPT(pressure, Temperature, PropID);
            }

            if (Volume < v_liq) {
                auto p_upper  = Temperature > 1073.15 ? 50E6 : 100E6;
                auto pressure = numeric::ridders([&](double p) { return XLSteamPT(p, Temperature, "VOL") - Volume; },
                                                 IF97::psat97(Temperature) + 1.0, // Required to ensure we are outside saturation line.
                                                 p_upper,
                                                 1.0E-15);
                return XLSteamPT(pressure, Temperature, PropID);
            }
            return std::nan("0");
        }
        catch (...) {
            return std::nan("0");
        }
    }

}


#endif //XLSTEAM_XLSTEAMBACKEND_H
