#pragma once

#include "nw/snd.h"


class AudFxSocket
{
public:
    nw::snd::internal::FxReverbHiParam& getReverbHiParam();
    nw::snd::internal::FxDelayParam&    getDelayParam();
};

class AudAudioMgr
{
public:
    AudFxSocket* getFxSocket();
};

class SndAudioMgr : public AudAudioMgr
{
public:
    static SndAudioMgr* instance;
};
