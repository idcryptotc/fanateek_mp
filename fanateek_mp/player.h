#pragma once

class Player
{
public:
    static void play();
    static void pause();
    static void stop();
    static void next();
    static void prev();
    static void volume_up();
    static void volume_down();
    static void set_position();
    static void set_position_step_left();
    static void set_position_step_right();
    static void set_repeat_state();
    static void set_shuffle_state();
private:
    bool is_repeat;
    bool is_shuffle;
    static void close_track();
    static void open_track();
};