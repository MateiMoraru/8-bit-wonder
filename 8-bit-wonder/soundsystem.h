#ifndef SOUNDSYSTEM_H
#define SOUNDSYSTEM_H

#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <deque>

#include "utils.h"

using namespace std;

const int FOOTSTEP = 0,
TREE_HIT = 1,
TREE_FALL = 2,
PICKUP = 3,
CLICK = 4;

class SoundSystem
{
public:
    SoundSystem();
    ~SoundSystem();

    void play_sound(int id);
    void play_loop_sound(int id);
    void play_sound(int id, float min, float max);
    void play_sound(int id, float min, float max, float volume);
    void play_critical_sound(int id, float min, float max);
    void update();
    void reset_sounds();

    vector<sf::Sound>& get_looped() { return looped; }

private:
    vector<sf::SoundBuffer> sounds;
    vector<sf::Sound> looped;
    deque<sf::Sound> active_sounds;
    deque<sf::Sound> critical_sounds;


};


#endif