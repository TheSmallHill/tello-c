#include "TelloControl.h"

#include <iostream>

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TelloControlTests)

BOOST_AUTO_TEST_SUITE(Commands)

BOOST_AUTO_TEST_CASE(Constructor)
{
   // Create instance of TelloControl
   TelloControl UUT;
   
   UUT.ToggleCommandMode();
   UUT.Takeoff();
   UUT.FlyForward(50);
   UUT.Land();
}

BOOST_AUTO_TEST_SUITE_END() // Commands

BOOST_AUTO_TEST_SUITE_END() // TelloControlTests
