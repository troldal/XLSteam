// xll_template.cpp - Sample xll project.
#include <cmath> // for double tgamma(double)
#include "xll_template.h"
#include "XLSteamBackend.h"

using namespace xll;

AddIn xai_XLSteam_PT(
        Function(XLL_DOUBLE, "XLSteam_PT", "XLSTEAM.PT")
        .Arguments({
            Arg(XLL_DOUBLE, "P", "is the pressure in Pascal."),
            Arg(XLL_DOUBLE, "T", "is the temperature in Kelvin."),
            Arg(XLL_CSTRING4, "PropID", "is the ID of the property to be calculated.")
        })
        .FunctionHelp("Compute properties of steam/water at the given pressure and temperature.")
        .Category("Engineering")
        .HelpTopic("https://github.com/CoolProp/IF97")
        .Documentation("The computation is done using CoolProp's implementation of the IAPWS Industrial Formulation 1997 (IF97).")
        );

double WINAPI XLSteam_PT(double P, double T, const char* PropID) {
#pragma XLLEXPORT
    return XLSteam::XLSteamPT(P, T, PropID);
}

AddIn xai_XLSteam_PX(
        Function(XLL_DOUBLE, "XLSteam_PX", "XLSTEAM.PX")
                .Arguments({
                                   Arg(XLL_DOUBLE, "P", "is the pressure in Pascal."),
                                   Arg(XLL_DOUBLE, "X", "is the vapor fraction"),
                                   Arg(XLL_CSTRING4, "PropID", "is the ID of the property to be calculated.")
                           })
                .FunctionHelp("Compute saturation properties of steam/water at the given pressure and vapor fraction.")
                .Category("Engineering")
                .HelpTopic("https://github.com/CoolProp/IF97")
                .Documentation("The computation is done using CoolProp's implementation of the IAPWS Industrial Formulation 1997 (IF97).")
);

double WINAPI XLSteam_PX(double P, double X, const char* PropID) {
#pragma XLLEXPORT
    return XLSteam::XLSteamPX(P, X, PropID);
}

AddIn xai_XLSteam_TX(
        Function(XLL_DOUBLE, "XLSteam_TX", "XLSTEAM.TX")
                .Arguments({
                                   Arg(XLL_DOUBLE, "T", "is the temperature in Kelvin."),
                                   Arg(XLL_DOUBLE, "X", "is the vapor fraction"),
                                   Arg(XLL_CSTRING4, "PropID", "is the ID of the property to be calculated.")
                           })
                .FunctionHelp("Compute saturation properties of steam/water at the given temperature and vapor fraction.")
                .Category("Engineering")
                .HelpTopic("https://github.com/CoolProp/IF97")
                .Documentation("The computation is done using CoolProp's implementation of the IAPWS Industrial Formulation 1997 (IF97).")
);

double WINAPI XLSteam_TX(double T, double X, const char* PropID) {
#pragma XLLEXPORT
    return XLSteam::XLSteamTX(T, X, PropID);
}

AddIn xai_XLSteam_PH(
        Function(XLL_DOUBLE, "XLSteam_PH", "XLSTEAM.PH")
                .Arguments({
                                   Arg(XLL_DOUBLE, "P", "is the pressure in Pascal."),
                                   Arg(XLL_DOUBLE, "H", "is the enthalpy in J/kg"),
                                   Arg(XLL_CSTRING4, "PropID", "is the ID of the property to be calculated.")
                           })
                .FunctionHelp("Compute the properties of steam/water at the given pressure and enthalpy.")
                .Category("Engineering")
                .HelpTopic("https://github.com/CoolProp/IF97")
                .Documentation("The computation is done using CoolProp's implementation of the IAPWS Industrial Formulation 1997 (IF97).")
);

double WINAPI XLSteam_PH(double P, double H, const char* PropID) {
#pragma XLLEXPORT
    return XLSteam::XLSteamPH(P, H, PropID);
}

AddIn xai_XLSteam_PS(
        Function(XLL_DOUBLE, "XLSteam_PS", "XLSTEAM.PS")
                .Arguments({
                                   Arg(XLL_DOUBLE, "P", "is the pressure in Pascal."),
                                   Arg(XLL_DOUBLE, "S", "is the entropy in J/kg-K"),
                                   Arg(XLL_CSTRING4, "PropID", "is the ID of the property to be calculated.")
                           })
                .FunctionHelp("Compute the properties of steam/water at the given pressure and entropy.")
                .Category("Engineering")
                .HelpTopic("https://github.com/CoolProp/IF97")
                .Documentation("The computation is done using CoolProp's implementation of the IAPWS Industrial Formulation 1997 (IF97).")
);

double WINAPI XLSteam_PS(double P, double S, const char* PropID) {
#pragma XLLEXPORT
    return XLSteam::XLSteamPS(P, S, PropID);
}

AddIn xai_tgamma(
	// Return double, C++ name of function, Excel name.
	Function(XLL_DOUBLE, "xll_tgamma", "TROLDAL.TGAMMA")
	// Array of function arguments.
	.Arguments({
		Arg(XLL_DOUBLE, "x", "is the value for which you want to calculate Gamma.")
	})
	// Function Wizard help.
	.FunctionHelp("Return the Gamma function value.")
	// Function Wizard category.
	.Category("MATH")
	// URL linked to `Help on this function`.
	.HelpTopic("https://docs.microsoft.com/en-us/cpp/c-runtime-library/reference/tgamma-tgammaf-tgammal")
	.Documentation(R"xyzyx(
The <i>Gamma</i> function is \(\Gamma(x) = \int_0^\infty t^{x - 1} e^{-t}\,dt\), \(x \ge 0\).
If \(n\) is a natural number then \(\Gamma(n + 1) = n! = n(n - 1)\cdots 1\).
<p>
Any valid HTML using <a href="https://katex.org/" target="_blank">KaTeX</a> can
be used for documentation.
)xyzyx")
);
// WINAPI calling convention must be specified
double WINAPI xll_tgamma(double x)
{
#pragma XLLEXPORT // must be specified to export function

	return tgamma(x);
}

// Press Alt-F8 then type 'XLL.MACRO' to call 'xll_macro'
// See https://xlladdins.github.io/Excel4Macros/
AddIn xai_macro(
	// C++ function, Excel name of macro
	Macro("xll_macro", "XLL.MACRO")
);
// Macros must have `int WINAPI (*)(void)` signature.
int WINAPI xll_macro(void)
{
#pragma XLLEXPORT
	// https://xlladdins.github.io/Excel4Macros/reftext.html
	// A1 style instead of default R1C1.
	OPER reftext = Excel(xlfReftext, Excel(xlfActiveCell), OPER(true));
	// UTF-8 strings can be used.
	Excel(xlcAlert, OPER("XLL.MACRO called with активный 细胞: ") & reftext);

	return TRUE;
}

#ifdef _DEBUG

// Create XML documentation and index.html in `$(TargetPath)` folder.
// Use `xsltproc file.xml -o file.html` to create HTML documentation.
Auto<Open> xao_template_docs([]() {

	return Documentation("MATH", "Documentation for the xll_template add-in.");

});

#endif // _DEBUG
