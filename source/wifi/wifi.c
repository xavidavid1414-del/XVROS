#include "wifi/wifi.h"

XvrosWifiStatus xvros_wifi_get_status(void)
{
    XvrosWifiStatus status;
    status.signal_strength = osGetWifiStrength();
    status.signal_available = status.signal_strength > 0;
    return status;
}
