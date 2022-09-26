//
// Created by Troldal on 25/09/2022.
//

#include "catch_amalgamated.hpp"
#include "../XLSteamBackend.h"

using namespace Catch;

TEST_CASE("PT REGION 1")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "VOL") == Approx(0.100215168e-2));
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "H") == Approx(0.115331273e6));
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "U") == Approx(0.112324818e6));
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "S") == Approx(0.392294792e3));
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "CP") == Approx(0.417301218e4));
        REQUIRE(XLSteam::XLSteamPT(3000000, 300, "W") == Approx(0.150773921e4));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "VOL") == Approx(0.971180894e-3));
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "H") == Approx(0.184142828e6));
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "U") == Approx(0.106448356e6));
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "S") == Approx(0.368563852e3));
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "CP") == Approx(0.401008987e4));
        REQUIRE(XLSteam::XLSteamPT(80000000, 300, "W") == Approx(0.163469054e4));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "VOL") == Approx(0.120241800e-2));
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "H") == Approx(0.975542239e6));
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "U") == Approx(0.971934985e6));
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "S") == Approx(0.258041912e4));
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "CP") == Approx(0.465580682e4));
        REQUIRE(XLSteam::XLSteamPT(3000000, 500, "W") == Approx(0.124071337e4));
    }
}

TEST_CASE("PT REGION 2")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "VOL") == Approx(0.394913866e2));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "H") == Approx(0.254991145e7));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "U") == Approx(0.241169160e7));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "S") == Approx(0.852238967e4));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "CP") == Approx(0.191300162e4));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 300, "W") == Approx(0.427920172e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "VOL") == Approx(0.923015898e2));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "H") == Approx(0.333568375e7));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "U") == Approx(0.301262819e7));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "S") == Approx(0.101749996e5));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "CP") == Approx(0.208141274e4));
        REQUIRE(XLSteam::XLSteamPT(0.0035e6, 700, "W") == Approx(0.644289068e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "VOL") == Approx(0.542946619e-2));
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "H") == Approx(0.263149474e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "U") == Approx(0.246861076e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "S") == Approx(0.517540298e4));
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "CP") == Approx(0.103505092e5));
        REQUIRE(XLSteam::XLSteamPT(30e6, 700, "W") == Approx(0.480386523e3));
    }
}

TEST_CASE("PT REGION 2 METASTABLE REGION")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "VOL") == Approx(0.192516540));
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "H") == Approx(0.276881115e7));
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "U") == Approx(0.257629461e7));
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "S") == Approx(0.656660377e4));
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "CP") == Approx(0.276349265e4));
        REQUIRE(XLSteam::XLSteamPT(1e6, 450, "W") == Approx(0.498408101e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "VOL") == Approx(0.186212297));
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "H") == Approx(0.274015123e7));
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "U") == Approx(0.255393894e7));
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "S") == Approx(0.650218759e4));
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "CP") == Approx(0.298166443e4));
        REQUIRE(XLSteam::XLSteamPT(1e6, 440, "W") == Approx(0.489363295e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "VOL") == Approx(0.121685206));
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "H") == Approx(0.272134539e7));
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "U") == Approx(0.253881758e7));
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "S") == Approx(0.629170440e4));
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "CP") == Approx(0.362795578e4));
        REQUIRE(XLSteam::XLSteamPT(1.5e6, 450, "W") == Approx(0.481941819e3));
    }
}

TEST_CASE("PT REGION 3")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "P") == Approx(0.255837018e8));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "VOL") == Approx(1.0/500.0));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "H") == Approx(0.186343019e7));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "U") == Approx(0.181226279e7));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "S") == Approx(0.405427273e4));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "CP") == Approx(0.138935717e5));
        REQUIRE(XLSteam::XLSteamPT(25583821.9349626, 650, "W") == Approx(0.502005554e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "P") == Approx(0.222930643e8));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "VOL") == Approx(1.0/200.0));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "H") == Approx(0.237512401e7));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "U") == Approx(0.226365868e7));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "S") == Approx(0.485438792e4));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "CP") == Approx(0.446579342e5));
        REQUIRE(XLSteam::XLSteamPT(22293064, 650, "W") == Approx(0.383444594e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "P") == Approx(0.783095639e8));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "VOL") == Approx(1.0/500.0));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "H") == Approx(0.225868845e7));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "U") == Approx(0.210206932e7));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "S") == Approx(0.446971906e4));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "CP") == Approx(0.634165359e4));
        REQUIRE(XLSteam::XLSteamPT(78309739.59, 750, "W") == Approx(0.760696041e3));
    }
}

TEST_CASE("PT REGION 4")
{
    SECTION("Test Case #01") {
        REQUIRE(XLSteam::XLSteamTX(300, 0.5, "P") == Approx(0.353658941e4));
        REQUIRE(XLSteam::XLSteamTX(500, 0.5, "P") == Approx(0.263889776e7));
        REQUIRE(XLSteam::XLSteamTX(600, 0.5, "P") == Approx(0.123443146e8));
    }

    SECTION("Test Case #02") {
        REQUIRE(XLSteam::XLSteamPX(0.1e6, 0.5, "T") == Approx(0.372755919e3));
        REQUIRE(XLSteam::XLSteamPX(1e6, 0.5, "T") == Approx(0.453035632e3));
        REQUIRE(XLSteam::XLSteamPX(10e6, 0.5, "T") == Approx(0.584149488e3));
    }
}

TEST_CASE("PT REGION 5")
{
    SECTION("Test Case #01")
    {
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "VOL") == Approx(0.138455090e1));
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "H") == Approx(0.521976855e7));
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "U") == Approx(0.452749310e7));
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "S") == Approx(0.965408875e4));
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "CP") == Approx(0.261609445e4));
        REQUIRE(XLSteam::XLSteamPT(0.5e6, 1500, "W") == Approx(0.917068690e3));
    }

    SECTION("Test Case #02")
    {
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "VOL") == Approx(0.230761299e-1));
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "H") == Approx(0.516723514e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "U") == Approx(0.447495124e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "S") == Approx(0.772970133e4));
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "CP") == Approx(0.272724317e4));
        REQUIRE(XLSteam::XLSteamPT(30e6, 1500, "W") == Approx(0.928548002e3));
    }

    SECTION("Test Case #03")
    {
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "VOL") == Approx(0.311385219e-1));
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "H") == Approx(0.657122604e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "U") == Approx(0.563707038e7));
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "S") == Approx(0.853640523e4));
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "CP") == Approx(0.288569882e4));
        REQUIRE(XLSteam::XLSteamPT(30e6, 2000, "W") == Approx(0.106736948e4));
    }
}
