#include <actor.h>
#include <block.h>
#include <enums.h>
#include <flipblock.h>
#include <globals.h>
#include <misc.h>
#include <model.h>
#include <mtx.h>
#include <player.h>
#include <rect.h>
#include <res.h>
#include <state.h>
#include <stdbool.h>
#include <vec.h>
//#include <logger.h>

/*
    Replaces Actor "Giant4WayCannon".
    Currently uses the Snake Block model.
    Known bugs:
    * The flip block does not check if there
      is an actor (other than the player)
      overlapping with it and can change from
      the "flipping" state to the "waiting"
      state while the actor is inside.
*/

Profile FlipBlock_Profile(FlipBlock::build, Giant4WayCannon, "FlipBlock", &FlipBlock_ActorInfo, 0);
CREATE_STATE(FlipBlock, Flipping)

Actor *FlipBlock::build(ActorBuildInfo *buildInfo) {
    return new FlipBlock(buildInfo);
}

int FlipBlock::onCreate() {
    //log_printf("FlipBlock::onCreate reached!\n");
    setResLoaderInstance();

    resArchive = getResArchive(ResLoader, "block_snake");
    ModelObj * mdl = resArchive->getModel("block_snake", 0, 0, 0, 0, 0, 0, 0);
    model = new Model2(mdl, 0, 0, 0, 0, 0);
    model->init(resArchive, 0, 0);

    //log_printf("FlipBlock::onCreate: block_snake loaded.\n");

    if (!init(true, true))
        return 2;

    topLeft = (Vec2){-8.0, 16.0};
    bottomRight = (Vec2){8.0, 0.0};
    solidColl.setRect(&topLeft, &bottomRight);

    doStateChange(&StateID_Wait);
    return 1;
}

int FlipBlock::onDraw() {
    Vec3 pos = {this->position.X, this->position.Y + 8, this->position.Z};
    Mtx mtx;

    calcMatrix(&mtx, &rotation, &pos);
    model->obj->setMatrix(&mtx);
    model->obj->setScale(&scale);
    model->obj->vf6C();
    model->obj->vf74();
    model->update();

    setDrawerInstance();
    drawModel(Drawer, model);
    return 1;
}

void FlipBlock::spawnItemUp() {
    //log_printf("FlipBlock::spawnItemUp reached!\n");
    doStateChange(&FlipBlock::StateID_Flipping);
}

void FlipBlock::spawnItemDown() {
    //log_printf("FlipBlock::spawnItemDown reached!\n");
    doStateChange(&FlipBlock::StateID_Flipping);
}

void FlipBlock::beginState_Flipping() {
    //log_printf("FlipBlock::beginState_Flipping reached!\n");
    flipsRemaining = 7;

    topLeft = (Vec2){0.0, 0.0};
    bottomRight = (Vec2){0.0, 0.0};
    solidColl.setRect(&topLeft, &bottomRight);
}

void FlipBlock::executeState_Flipping() {
    //log_printf("FlipBlock::executeState_Flipping reached!\n");
    if (spawnDirection == Down)
        rotation.X += 0x8000000;

    else
        rotation.X -= 0x8000000;

    if (rotation.X == 0)
        if (--flipsRemaining <= 0)
            if (!playerOverlaps())
                doStateChange(&StateID_Wait);
}

void FlipBlock::endState_Flipping() {
    //log_printf("FlipBlock::endState_Flipping reached!\n");
    topLeft = (Vec2){-8.0, 16.0};
    bottomRight = (Vec2){8.0, 0.0};
    solidColl.setRect(&topLeft, &bottomRight);
}

bool FlipBlock::playerOverlaps() {
    setPlayerMgrInstance();

    unsigned int playerActiveMask = 1;
    bool overlaps = false;

    Player *player;
    Rect thisRect;
    Rect playerRect;

    for (int i = 0; i < 4; i++) {
        if (PlayerMgrInst->playerFlags & playerActiveMask) {
            player = PlayerMgrInst->players[i];
            if (player != 0) {
                GetStageActorRect(this, &thisRect);
                GetStageActorRect(player, &playerRect);
                overlaps = RectsOverlap(&thisRect, &playerRect);
            }
        }

        if (overlaps)
            return true;

        playerActiveMask <<= 1;
    }

    return false;
}
