#include <dbus/dbus.h>

#include <string>

class NetworkConnect
{
public:
   NetworkConnect(const std::string& ssid, const std::string& password);
   
   ~NetworkConnect();

protected:
   DBusError error_;
   DBusConnection* connection_;
   DBusMessage* message_;
   DBusMessage* reply_;
}
