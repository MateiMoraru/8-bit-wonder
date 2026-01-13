#include "soundsystem.h"

SoundSystem::SoundSystem()
{
    looped.reserve(8);

    std::vector<string> filenames = {
        "assets/sfx/footstep_1.mp3",
        "assets/sfx/hit-tree.mp3",
        "assets/sfx/tree-fall.mp3",
        "assets/sfx/item-pickup.mp3",
        "assets/sfx/click.mp3"
    };

    for (auto& file : filenames)
    {
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(file)) {
            std::cerr << "Failed to load sound: " << file << std::endl;
        }
        sounds.push_back(buffer);
    }
}

void SoundSystem::update()
{
    active_sounds.erase(
        std::remove_if(active_sounds.begin(), active_sounds.end(),
            [](sf::Sound& s) { return s.getStatus() == sf::Sound::Stopped; }),
        active_sounds.end());
}


void SoundSystem::play_sound(int id)
{
    active_sounds.emplace_back();
    sf::Sound& s = active_sounds.back();
    s.setBuffer(sounds[id]);
    s.play();

}

void SoundSystem::play_sound(int id, float min, float max)
{
    active_sounds.emplace_back();
    sf::Sound& s = active_sounds.back();
    s.setBuffer(sounds[id]);
    s.setPitch(random_float(min, max));
    s.play();

}

void SoundSystem::play_sound(int id, float min, float max, float volume)
{
    active_sounds.emplace_back();
    sf::Sound& s = active_sounds.back();
    s.setBuffer(sounds[id]);
    s.setPitch(random_float(min, max));
    s.setVolume(volume);
    s.play();

}

void SoundSystem::play_critical_sound(int id, float min, float max)
{
    critical_sounds.emplace_back();
    sf::Sound& s = critical_sounds.back();
    s.setBuffer(sounds[id]);
    s.setPitch(random_float(min, max));
    s.play();

}

void SoundSystem::play_loop_sound(int id)
{
    looped.emplace_back();
    sf::Sound& s = looped.back();
    s.setBuffer(sounds[id]);
    s.play();
    s.setLoop(true);
}

void SoundSystem::reset_sounds()
{
    for (sf::Sound& sound : looped)
    {
        sound.stop();
    }
    for (sf::Sound& sound : active_sounds)
    {
        sound.stop();
    }
    looped.emplace_back();
    //sf::Sound& s = looped.back();
    //s.setBuffer(sounds[BACKGROUND_SOUND]);
    //s.play();
    //s.setLoop(true);
}

SoundSystem::~SoundSystem()
{
    for (auto& s : active_sounds)
        s.stop();

    for (auto& s : looped)
        s.stop();

    active_sounds.clear();
    looped.clear();
}