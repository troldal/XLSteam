//
// Created by Troldal on 25/09/2022.
//

#include "catch_amalgamated.hpp"
#include "../XLSteamBackend.h"

using namespace Catch;

TEST_CASE("PH REGION 1")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "T") == Approx(300.0));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "VOL") == Approx(0.100215168e-2));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "H") == Approx(0.115331273e6));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "U") == Approx(0.112324818e6));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "S") == Approx(0.392294792e3));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "CP") == Approx(0.417301218e4));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.115331273e6, "W") == Approx(0.150773921e4));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "T") == Approx(300.0));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "VOL") == Approx(0.971180894e-3));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "H") == Approx(0.184142828e6));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "U") == Approx(0.106448356e6));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "S") == Approx(0.368563852e3));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "CP") == Approx(0.401008987e4));
        REQUIRE(XLSteam::XLSteamPH(80000000, 0.184142828e6, "W") == Approx(0.163469054e4));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "T") == Approx(500.0));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "VOL") == Approx(0.120241800e-2));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "H") == Approx(0.975542239e6));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "U") == Approx(0.971934985e6));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "S") == Approx(0.258041912e4));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "CP") == Approx(0.465580682e4));
        REQUIRE(XLSteam::XLSteamPH(3000000, 0.975542239e6, "W") == Approx(0.124071337e4));
    }
}

TEST_CASE("PH REGION 2")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "T") == Approx(300.0));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "VOL") == Approx(0.394913866e2));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "H") == Approx(0.254991145e7));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "U") == Approx(0.241169160e7));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "S") == Approx(0.852238967e4));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "CP") == Approx(0.191300162e4));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.254991145e7, "W") == Approx(0.427920172e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "T") == Approx(700.0));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "VOL") == Approx(0.923015898e2));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "H") == Approx(0.333568375e7));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "U") == Approx(0.301262819e7));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "S") == Approx(0.101749996e5));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "CP") == Approx(0.208141274e4));
        REQUIRE(XLSteam::XLSteamPH(0.0035e6, 0.333568375e7, "W") == Approx(0.644289068e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "T") == Approx(700.0));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "VOL") == Approx(0.542946619e-2));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "H") == Approx(0.263149474e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "U") == Approx(0.246861076e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "S") == Approx(0.517540298e4));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "CP") == Approx(0.103505092e5));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.263149474e7, "W") == Approx(0.480386523e3));
    }
}


TEST_CASE("PH REGION 3")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "T") == Approx(650.0));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "P") == Approx(0.255837018e8));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "VOL") == Approx(1.0/500.0));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "H") == Approx(0.186343019e7));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "U") == Approx(0.181226279e7));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "S") == Approx(0.405427273e4));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "CP") == Approx(0.138935717e5));
        REQUIRE(XLSteam::XLSteamPH(25583821.9349626, 0.186343019e7, "W") == Approx(0.502005554e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "T") == Approx(650.0));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "P") == Approx(0.222930643e8));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "VOL") == Approx(1.0/200.0));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "H") == Approx(0.237512401e7));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "U") == Approx(0.226365868e7));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "S") == Approx(0.485438792e4));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "CP") == Approx(0.446579342e5));
        REQUIRE(XLSteam::XLSteamPH(22293064, 0.237512401e7, "W") == Approx(0.383444594e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "T") == Approx(750.0));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "P") == Approx(0.783095639e8));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "VOL") == Approx(1.0/500.0));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "H") == Approx(0.225868845e7));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "U") == Approx(0.210206932e7));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "S") == Approx(0.446971906e4));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "CP") == Approx(0.634165359e4));
        REQUIRE(XLSteam::XLSteamPH(78309739.59, 0.225868845e7, "W") == Approx(0.760696041e3));
    }
}


TEST_CASE("PH REGION 5")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "T") == Approx(1500.0));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "VOL") == Approx(0.138455090e1));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "H") == Approx(0.521976855e7));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "U") == Approx(0.452749310e7));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "S") == Approx(0.965408875e4));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "CP") == Approx(0.261609445e4));
        REQUIRE(XLSteam::XLSteamPH(0.5e6, 0.521976855e7, "W") == Approx(0.917068690e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "T") == Approx(1500.0));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "VOL") == Approx(0.230761299e-1));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "H") == Approx(0.516723514e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "U") == Approx(0.447495124e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "S") == Approx(0.772970133e4));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "CP") == Approx(0.272724317e4));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.516723514e7, "W") == Approx(0.928548002e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "T") == Approx(2000.0));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "VOL") == Approx(0.311385219e-1));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "H") == Approx(0.657122604e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "U") == Approx(0.563707038e7));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "S") == Approx(0.853640523e4));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "CP") == Approx(0.288569882e4));
        REQUIRE(XLSteam::XLSteamPH(30e6, 0.657122604e7, "W") == Approx(0.106736948e4));
    }
}
