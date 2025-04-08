#include <stdio.h>
#include <string.h>
#include "gui.h"

Window create_window(int x, int y, int w, int h, const char *title) {
    Window win = {x, y, w, h};
    strncpy(win.title, title, sizeof(win.title));
    return win;
}

Button create_button(int x, int y, int w, int h, const char *label, void (*on_click)()) {
    Button btn = {x, y, w, h, "", on_click};
    strncpy(btn.label, label, sizeof(btn.label));
    return btn;
}

void draw_window(Window w) {
    printf("[DRAW] Window '%s' at (%d,%d) size %dx%d\n", w.title, w.x, w.y, w.width, w.height);
}

void draw_button(Button b) {
    printf("[DRAW] Button '%s' at (%d,%d) size %dx%d\n", b.label, b.x, b.y, b.width, b.height);
}

void simulate_click(Button b) {
    printf("[EVENT] Simulating click on '%s'\n", b.label);
    if (b.on_click) b.on_click();
}
