#include <stdio.h>
#include "gui.h"

void on_hello_click() {
    printf("Hello from the button!\n");
}

int main() {
    Window win = create_window(10, 10, 300, 200, "My First GUI");
    Button helloBtn = create_button(20, 40, 100, 30, "Say Hello", on_hello_click);

    draw_window(win);
    draw_button(helloBtn);

    // Simulate button click
    simulate_click(helloBtn);

    return 0;
}
