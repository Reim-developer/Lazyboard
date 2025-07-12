#ifndef CORE_NOTIFICATION_H
#define CORE_NOTIFICATION_H
#if defined(__gnu_linux__) || defined(__linux)
#if defined(__cplusplus)
extern "C" {
#endif
#define CORE_APP_NAME "zClipboard"
#define TIMEOUT 5000  // 5s.
#include <stdint.h>
#include <glib-object.h>
#include <libnotify/notification.h>
#include <libnotify/notify.h>

void sendLinuxNotification(const char *title, const char *body);

#if defined(__cplusplus)
}
#endif
#endif
#endif  // CORE_NOTIFICATION_H