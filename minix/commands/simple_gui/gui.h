#ifndef GUI_H
#define GUI_H

typedef struct {
    int x, y, width, height;
    char title[100];
} Window;

typedef struct {
    int x, y, width, height;
    char label[100];
    void (*on_click)();
} Button;

Window create_window(int x, int y, int w, int h, const char *title);
Button create_button(int x, int y, int w, int h, const char *label, void (*on_click)());
void draw_window(Window w);
void draw_button(Button b);
void simulate_click(Button b);

#endif
