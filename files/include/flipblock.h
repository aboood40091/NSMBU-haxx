#include <sead/string.h>
#include <actor.h>
#include <block.h>
#include <enums.h>
#include <model.h>
#include <state.h>
#include <vec.h>

class FlipBlock : public BlockBase {
public:
    Vec2 topLeft;
    Vec2 bottomRight;

    int onCreate();
    int onDraw();

    void spawnItemUp();
    void spawnItemDown();

    ResArchive *resArchive;
    Model2 *model;

    int flipsRemaining;

    DECLARE_STATE(FlipBlock, Flipping)

    static Actor *build(ActorBuildInfo *);
    inline FlipBlock(ActorBuildInfo *buildInfo) : BlockBase(buildInfo) {} // Constructor
};

const ActorInfo FlipBlock_ActorInfo = {8.0, -16.0};

const sead::String FlipBlockFileList[] = {"block_snake"};
const SetActorFiles setFlipBlockFiles(Giant4WayCannon, 1, FlipBlockFileList);
