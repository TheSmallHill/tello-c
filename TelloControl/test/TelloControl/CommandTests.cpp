#include "TelloControl.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(TelloControlTests)

BOOST_AUTO_TEST_SUITE(Commands)

BOOST_AUTO_TEST_CASE(Constructor)
{
   // Create instance of TelloControl
   TelloControl UUT;
   UUT.ToggleCommandMode();
   
   /*
   UUT.DoTakeoff();
   
   unsigned int i = 0;
   while (i < 1000)
   {
      i++;
   }
   
   UUT.DoLand();
   */
}

BOOST_AUTO_TEST_SUITE_END() // Commands

BOOST_AUTO_TEST_SUITE_END() // TelloControlTests
