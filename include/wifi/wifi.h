#ifndef XVROS_WIFI_H
#define XVROS_WIFI_H

#include <3ds.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct
{
    uint8_t signal_strength; /* 0-3 bars, as reported by the system */
    bool signal_available;
} XvrosWifiStatus;

/* Reads the current system Wi-Fi signal indicator.
 * This does not connect to an access point or create a network session.
 */
XvrosWifiStatus xvros_wifi_get_status(void);

#endif
