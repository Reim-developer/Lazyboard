#if defined(__gnu_linux__) || defined(__linux)
#include "Include/Notification.h"
#include <stdbool.h>
#include "../Include/Embed_Icon.h"

static GdkPixbuf *createPixbuf(const uint8_t *data, size_t length) {
    GdkPixbufLoader *loader = gdk_pixbuf_loader_new();
    gdk_pixbuf_loader_write(loader, data, length, NULL);

    gdk_pixbuf_loader_close(loader, NULL);

    GdkPixbuf *pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
    g_object_ref(pixbuf);

    g_object_unref(loader);
    return pixbuf;
}

void sendLinuxNotification(const char *title, const char *body) {
    static bool initialized = false;

    if (!initialized) {
        notify_init(CORE_APP_NAME);
        initialized = true;
    }
    GdkPixbuf *pixbuf = createPixbuf(ICON_EMBED, ICON_EMBED_LEN);
    NotifyNotification *notification = notify_notification_new(title, body, NULL);

    notify_notification_set_icon_from_pixbuf(notification, pixbuf);
    notify_notification_set_timeout(notification, TIMEOUT);
    notify_notification_show(notification, NULL);

    g_object_unref(notification);
    g_object_unref(pixbuf);
}
#endif