#include "soundObject.h"

namespace {
constexpr int MusicCount = static_cast<int>(MusicTrack::Count);
constexpr int SoundCount = static_cast<int>(SoundCue::Count);

// Add these music files later:
// assets/sounds/music_overworld.ogg
// assets/sounds/music_underground.ogg
// assets/sounds/music_castle.ogg
const char* MusicFiles[MusicCount] = {
    "assets/sounds/music_overworld.ogg",
    "assets/sounds/music_underground.ogg",
    "assets/sounds/music_castle.ogg"
};

const char* SoundFiles[SoundCount] = {
    "assets/sounds/game_start.wav",
    "assets/sounds/jump.wav",
    "assets/sounds/coin.wav",
    "assets/sounds/block_bump.wav",
    "assets/sounds/brick_break.wav",
    "assets/sounds/powerup_appears.wav",
    "assets/sounds/powerup_collect.wav",
    "assets/sounds/one_up.wav",
    "assets/sounds/fireball.wav",
    "assets/sounds/enemy_defeat.wav",
    "assets/sounds/pipe.wav",
    "assets/sounds/player_damage.wav",
    "assets/sounds/death.wav",
    "assets/sounds/flagpole.wav",
    "assets/sounds/bowser_defeat.wav"
};
}

void SoundObject::load() {
    if (!audioReady) {
        InitAudioDevice();
        audioReady = IsAudioDeviceReady();
    }
    if (!audioReady) return;

    SetMasterVolume(0.8f);

    for (int i = 0; i < MusicCount; i++) {
        if (FileExists(MusicFiles[i])) {
            musicTracks[i] = LoadMusicStream(MusicFiles[i]);
            musicTracks[i].looping = true;
            musicLoaded[i] = true;
        }
    }

    for (int i = 0; i < SoundCount; i++) {
        if (FileExists(SoundFiles[i])) {
            sounds[i] = LoadSound(SoundFiles[i]);
            soundLoaded[i] = true;
        }
    }
}

void SoundObject::update() {
    if (!audioReady || currentMusic < 0 || !musicLoaded[currentMusic]) return;
    UpdateMusicStream(musicTracks[currentMusic]);
}

void SoundObject::playMusic(MusicTrack track) {
    if (!audioReady) return;

    int index = static_cast<int>(track);
    if (index < 0 || index >= MusicCount || !musicLoaded[index]) return;
    if (currentMusic == index && IsMusicStreamPlaying(musicTracks[index])) return;

    if (currentMusic >= 0 && musicLoaded[currentMusic]) {
        StopMusicStream(musicTracks[currentMusic]);
    }

    currentMusic = index;
    PlayMusicStream(musicTracks[currentMusic]);
}

void SoundObject::stopMusic() {
    if (!audioReady || currentMusic < 0 || !musicLoaded[currentMusic]) return;
    StopMusicStream(musicTracks[currentMusic]);
    currentMusic = -1;
}

void SoundObject::play(SoundCue cue) {
    if (!audioReady) return;

    int index = static_cast<int>(cue);
    if (index < 0 || index >= SoundCount || !soundLoaded[index]) return;
    PlaySound(sounds[index]);
}

void SoundObject::unload() {
    if (!audioReady) return;

    if (currentMusic >= 0 && musicLoaded[currentMusic]) {
        StopMusicStream(musicTracks[currentMusic]);
    }

    for (int i = 0; i < MusicCount; i++) {
        if (musicLoaded[i]) {
            UnloadMusicStream(musicTracks[i]);
            musicLoaded[i] = false;
        }
    }

    for (int i = 0; i < SoundCount; i++) {
        if (soundLoaded[i]) {
            UnloadSound(sounds[i]);
            soundLoaded[i] = false;
        }
    }

    CloseAudioDevice();
    audioReady = false;
    currentMusic = -1;
}
