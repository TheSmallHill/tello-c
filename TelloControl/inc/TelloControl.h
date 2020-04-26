#include <string>

class TelloControl
{
public:
   /// Constructor for the TelloControl object that connects to the correct network and puts into SDK mode.
   /// @param[in] ssid Name of network created by the Tello drone.
   /// @param[in] password Password for the Tello's network.
   TelloControl(const std::string& ssid, const std::string& password = "");
   
   ~TelloControl();
   
   
}
