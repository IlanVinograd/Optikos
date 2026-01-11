#include "platform/titlebar.hpp"

#ifdef PLATFORM_WINDOWS

void set_title_bar(HWND hwnd) {
    BOOL useDark = TRUE;
    DwmSetWindowAttribute(hwnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDark, sizeof(useDark));

    COLORREF captionColor = RGB(25, 25, 25);
    DwmSetWindowAttribute(hwnd, DWMWA_CAPTION_COLOR, &captionColor, sizeof(captionColor));
}

#endif