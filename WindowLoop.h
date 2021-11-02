//
// Created by Robbe on 2/11/2021.
//

#ifndef CSV_PARSER_WINDOWLOOP_H
#define CSV_PARSER_WINDOWLOOP_H


class WindowLoop {
public:
    bool running = true;

    WindowLoop(int screen_width, int screen_height, int target_fps);

    void handle_event();

    void update();

    void draw();
};


#endif //CSV_PARSER_WINDOWLOOP_H
