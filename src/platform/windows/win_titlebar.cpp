#include "platform/titlebar.hpp"

#ifdef PLATFORM_WINDOWS

void set_title_bar(HWND hwnd, Color color) {
    BOOL useDark = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDark, sizeof(useDark));

    COLORREF captionColor = RGB(color.r, color.g, color.b);
    DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &captionColor, sizeof(captionColor));
}

#endif