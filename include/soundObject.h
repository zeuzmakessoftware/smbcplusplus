#ifndef SOUND_OBJECT_H
#define SOUND_OBJECT_H

#include <array>
#include <raylib.h>

enum class MusicTrack {
    Overworld = 0,
    Underground,
    Castle,
    Count
};

enum class SoundCue {
    GameStart = 0,
    Jump,
    Coin,
    BlockBump,
    BrickBreak,
    PowerupAppears,
    PowerupCollect,
    OneUp,
    Fireball,
    EnemyDefeat,
    Pipe,
    PlayerDamage,
    Death,
    Flagpole,
    BowserDefeat,
    Count
};

class SoundObject {
public:
    void load();
    void update();
    void playMusic(MusicTrack track);
    void stopMusic();
    void play(SoundCue cue);
    void unload();

private:
    std::array<Music, static_cast<int>(MusicTrack::Count)> musicTracks{};
    std::array<bool, static_cast<int>(MusicTrack::Count)> musicLoaded{};
    std::array<Sound, static_cast<int>(SoundCue::Count)> sounds{};
    std::array<bool, static_cast<int>(SoundCue::Count)> soundLoaded{};
    bool audioReady = false;
    int currentMusic = -1;
};

#endif
