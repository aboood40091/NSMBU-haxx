#include "music.h"
#include <stdbool.h>

extern "C" {
    bool isValidStrmID(void *_this, int strmID) {
        return strmID < MUSIC_LIST_NUM - 1;
    }


    const char *getStrmNameForID(void *_this, int strmID) {
        bool valid = isValidStrmID(_this, strmID);
        if (valid == false)
            return 0;

        const char *strName;

        bool isHurryUp = shouldHurryUp();
        if (isHurryUp)
            strName = musicStrmListFast[strmID];

        else
            strName = musicStrmListNormal[strmID];

        int log_printf_ = *(int *)(DATA_ADDR + 0x20000);
        ((void (*)(const char *format, ...))(log_printf_))("Stream id: %d\n", strmID);
        ((void (*)(const char *format, ...))(log_printf_))("Stream name: %s\n", strName);
        return strName;
    }


    const char *getSeqNameForID(void *_this, int strmID) {
        bool valid = isValidStrmID(_this, strmID);
        if (valid == false)
            return 0;

        const char *seqName;

        bool isHurryUp = shouldHurryUp();
        if (isHurryUp)
            seqName = musicSeqListFast[strmID];

        else
            seqName = musicSeqListNormal[strmID];

        int log_printf_ = *(int *)(DATA_ADDR + 0x20000);
        ((void (*)(const char *format, ...))(log_printf_))("Sequence id: %d\n", strmID);
        ((void (*)(const char *format, ...))(log_printf_))("Sequence name: %s\n", seqName);
        return seqName;
    }
}
