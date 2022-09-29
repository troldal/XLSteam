//
// Created by Troldal on 21/09/2022.
//

#ifndef XLSTEAM_XLSTEAMBACKEND_H
#define XLSTEAM_XLSTEAMBACKEND_H

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

        if (Temperature < 273.16 || Temperature > 2273.15) return std::nan("0");
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
            if (Pressure <= IF97::get_pcrit() &&
                IF97::Q_phmass(Pressure, Enthalpy) < 1.0 &&
                IF97::Q_phmass(Pressure, Enthalpy) > 0.0)
                return XLSteamPX(Pressure, IF97::Q_phmass(Pressure, Enthalpy), PropID);

            auto t_guess = IF97::T_phmass(Pressure, Enthalpy);

            auto t_upper = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit())
                    return (t_guess >= IF97::Tsat97(Pressure) ? t_guess * 1.02 : std::min(t_guess * 1.02, IF97::Tsat97(Pressure)));
                return t_guess * 1.02;
            });

            auto t_lower = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit())
                    return (t_guess >= IF97::Tsat97(Pressure) ? std::max(t_guess * 0.98, IF97::Tsat97(Pressure)) : t_guess * 0.98);
                return t_guess * 0.98;
            });

            auto temperature = numeric::ridders([&](double t) {return XLSteamPT(Pressure, t, "H") - Enthalpy;}, t_lower, t_upper, 1.0E-9);
            return XLSteamPT(Pressure, temperature, PropID);
        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPS(double Pressure, double Entropy, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100000000.0) return std::nan("0");

        try {
            if (Pressure <= IF97::get_pcrit() &&
                IF97::Q_psmass(Pressure, Entropy) < 1.0 &&
                IF97::Q_psmass(Pressure, Entropy) > 0.0)
                return XLSteamPX(Pressure, IF97::Q_psmass(Pressure, Entropy), PropID);

            auto t_guess = IF97::T_psmass(Pressure, Entropy);

            auto t_upper = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit())
                    return (t_guess >= IF97::Tsat97(Pressure) ? t_guess * 1.02 : std::min(t_guess * 1.02, IF97::Tsat97(Pressure)));
                return t_guess * 1.02;
            });

            auto t_lower = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit())
                    return (t_guess >= IF97::Tsat97(Pressure) ? std::max(t_guess * 0.98, IF97::Tsat97(Pressure)) : t_guess * 0.98);
                return t_guess * 0.98;
            });

            auto temperature = numeric::ridders([&](double t) {return XLSteamPT(Pressure, t, "S") - Entropy;}, t_lower, t_upper, 1.0E-9);
            return XLSteamPT(Pressure, temperature, PropID);
        }
        catch (...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPU(double Pressure, double InternalEnergy, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100000000.0) return std::nan("0");

        try {
            if (Pressure <= IF97::get_pcrit() &&
                IF97::Q_pumass(Pressure, InternalEnergy) < 1.0 &&
                IF97::Q_pumass(Pressure, InternalEnergy) > 0.0)
                return XLSteamPX(Pressure, IF97::Q_pumass(Pressure, InternalEnergy), PropID);

            auto t_min = 273.15;
            auto t_max = Pressure <= 50e6 ? 2273.15 : 1073.15;

            auto t_upper = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit()) {
                    if (InternalEnergy <= XLSteamPX(Pressure, 0.0, "U")) return IF97::Tsat97(Pressure);
                    if (InternalEnergy >= XLSteamPX(Pressure, 1.0, "U")) return t_max;
                    return std::nan("0");
                }
                return t_max;
            });

            auto t_lower = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit()) {
                    if (InternalEnergy <= XLSteamPX(Pressure, 0.0, "U")) return t_min;
                    if (InternalEnergy >= XLSteamPX(Pressure, 1.0, "U")) return IF97::Tsat97(Pressure);
                    return std::nan("0");
                }
                return t_min;
            });

            auto temperature = numeric::ridders([&](double t) {return XLSteamPT(Pressure, t, "U") - InternalEnergy;}, t_lower, t_upper, 1.0E-9);
            return XLSteamPT(Pressure, temperature, PropID);

        }
        catch(...) {
            return std::nan("0");
        }
    }

    inline double XLSteamPV(double Pressure, double Volume, const char* PropID) {

        if (Pressure < 0.0 || Pressure > 100000000.0) return std::nan("0");

        try {
            if (Pressure <= IF97::get_pcrit() &&
                IF97::Q_pv(Pressure, Volume) < 1.0 &&
                IF97::Q_pv(Pressure, Volume) > 0.0)
                return XLSteamPX(Pressure, IF97::Q_pv(Pressure, Volume), PropID);

            auto t_min = 273.15;
            auto t_max = Pressure <= 50e6 ? 2273.15 : 1073.15;

            auto t_upper = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit()) {
                    if (Volume <= XLSteamPX(Pressure, 0.0, "VOL")) return IF97::Tsat97(Pressure);
                    if (Volume >= XLSteamPX(Pressure, 1.0, "VOL")) return t_max;
                    return std::nan("0");
                }
                return t_max;
            });

            auto t_lower = std::invoke([&](){
                if (Pressure <= IF97::get_pcrit()) {
                    if (Volume <= XLSteamPX(Pressure, 0.0, "U")) return t_min;
                    if (Volume >= XLSteamPX(Pressure, 1.0, "U")) return IF97::Tsat97(Pressure);
                    return std::nan("0");
                }
                return t_min;
            });

            auto temperature = numeric::ridders([&](double t) {return XLSteamPT(Pressure, t, "VOL") - Volume;}, t_lower, t_upper, 1.0E-9);
            return XLSteamPT(Pressure, temperature, PropID);

        }
        catch(...) {
            return std::nan("0");
        }
    }

}


#endif //XLSTEAM_XLSTEAMBACKEND_H
