#pragma once

#include "nw/snd.h"


class AudioFx
{
public:
    nw::snd::FxReverbHiParam& getReverbHiParam();
    nw::snd::FxDelayParam&    getDelayParam();
};

class SoundSystemBase
{
public:
    AudioFx* getAudioFx();
};

class SoundSystem : public SoundSystemBase
{
public:
    static SoundSystem* instance;
};
