#include <logger.h>
#include <music.h>
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

        log_printf("Stream id: %d\n", strmID);
        log_printf("Stream name: %s\n", strName);
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

        log_printf("Sequence id: %d\n", strmID);
        log_printf("Sequence name: %s\n", seqName);
        return seqName;
    }
}
