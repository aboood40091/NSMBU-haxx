#include <actor.h>
#include <enums.h>
#include <collider.h>
#include <globals.h>
#include <magicplatform.h>
#include <math.h>
#include <stdbool.h>
#include <tile.h>
//#include <logger.h>

/*
    Replaces Actor "Cookie".
    Known bugs:
    * Placing a magic platform close to level entrance
      causes very weird behavior.
    * Placing *any* solid actor behind the magic platform
      triggers the same glitch as above.
    * Baby Yoshi (and possibly everything that can be
      thrown is very glitchy with the Solid-On-Right collision.
*/

Profile profile(MagicPlatform::build, Cookie, "MagicPlatform", &MagicPlatform_ActorInfo, 0); // Overwrite the Cookie profile

Actor *MagicPlatform::build(ActorBuildInfo *buildInfo) {
    //log_printf("MagicPlatform::build reached\n");
    return new MagicPlatform(buildInfo);
}

int MagicPlatform::onCreate() {
    //log_printf("MagicPlatform::onCreate reached\n");

    setLevelInstances();
    setPhysCollMgrInstance();

    char areaId = LevelInfo->currentAreaId;
    LevelArea *area = getAreaById(Level, areaId);

    locationId = settings & 0xFF;
    location = getLocationById(area, 0, locationId);
    if (location == 0)
        return 2;

    //log_printf("Area id: %d\n", areaId + 1);
    //log_printf("Location id: %d\n", locationId);

    width = (location->width >> 4);
    height = (location->height >> 4);

    if (width == 0) // Avoid it being 0
        width = 1;

    if (height == 0) // Avoid it being 0
        height = 1;

    //collisionType = (CollisionType)((settings >> 8) & 0xF);
    collisionType = MagicPlatform::SolidOnLeft;
    //log_printf("CollisionType: %d\n", (char)collisionType);

    //TODO: use ColliderRect
    if (collisionType == Solid) {
        RectColliderParam collisionParam = {
            0.0, 0.0, 0.0, 0.0, -8.0, 8.0, -8.0 + width * 16.0, 8.0 + -height * 16.0, 0
        };

        float rect[] = {-8.0, 8.0, -8.0 + height * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam2 = {
            (width - 1) * 16.0, 0.0, 0.0, 0.0, rect, 0
        };

        float rect2[] = {-8.0, 8.0, -8.0 + width * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam3 = {
            0.0, 0.0, 0.0, 0.0, rect2, 0
        };

        solidCollider.init(this, &collisionParam, 2, 0);
        solidColliderFix.init(this, &collisionParam2, 2, 0);
        solidColliderFix2.init(this, &collisionParam3, 2, 0);

        doRegister(PhysicsCollisionMgr, &solidCollider);
        doRegister(PhysicsCollisionMgr, &solidColliderFix);
        doRegister(PhysicsCollisionMgr, &solidColliderFix2);
    }

    else if (collisionType == SolidOnTop) {
        float rect[] = {-8.0, 8.0, -8.0 + width * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam = {
            0.0, 0.0, 0.0, 0.0, rect, 0
        };

        solidOnTopCollider.init(this, &collisionParam, 2, 0);
        doRegister(PhysicsCollisionMgr, &solidOnTopCollider);
    }

    else if (collisionType == SolidOnBottom) {
        float rect[] = {-8.0, 8.0, -8.0 + width * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam = {
            (width - 1) * 16.0, (1 - height) * 16.0, 0.0, 0.0, rect, 0
        };

        solidOnBottomCollider.init(this, &collisionParam, 2, 0);
        doRegister(PhysicsCollisionMgr, &solidOnBottomCollider);
    }

    else if (collisionType == SolidOnLeft) {
        float rect[] = {-8.0, 8.0, -8.0 + height * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam = {
            0.0, (1 - height) * 16.0, 0.0, 0.0, rect, 0
        };

        solidOnLeftCollider.init(this, &collisionParam, 2, 0);
        doRegister(PhysicsCollisionMgr, &solidOnLeftCollider);
    }

    else if (collisionType == SolidOnRight) {
        float rect[] = {-8.0, 8.0, -8.0 + height * 16.0, 8.0};
        SemiSolidShapedColliderParam collisionParam = {
            (width - 1) * 16.0, 0.0, 0.0, 0.0, rect, 0
        };

        solidOnRightCollider.init(this, &collisionParam, 2, 0);
        doRegister(PhysicsCollisionMgr, &solidOnRightCollider);
    }

    movementType = (MovementType)((settings >> 12) & 0xF);

    //log_printf("MovementType: %d\n", (char)movementType);
    //log_printf("Movement ID: %d\n", movementId);

    unsigned int movementTypeMask = movementHandler.GetMaskForMovementType(movementType);
    movementHandler.FindMovementControllerAndDoState(&position, movementTypeMask, movementId);
    tileRotation = movementHandler.zRotation;

    return 1;
}

int MagicPlatform::onExecute() {
    movementHandler.executeState();
    position.X = movementHandler.position.X;
    position.Y = movementHandler.position.Y;
    rotation.Z = movementHandler.zRotation;
    tileRotation = rotation.Z;

    if (collisionType == Solid) {
        solidCollider.rotation = rotation.Z;
        solidCollider.vf3C();

        solidColliderFix.rotation = rotation.Z + 0xC0000000;
        solidColliderFix.vf3C();

        solidColliderFix2.rotation = rotation.Z;
        solidColliderFix2.vf3C();
    }

    else if (collisionType == SolidOnTop) {
        solidOnTopCollider.rotation = rotation.Z;
        solidOnTopCollider.vf3C();
    }

    else if (collisionType == SolidOnBottom) {
        solidOnBottomCollider.rotation = rotation.Z + 0x80000000;
        solidOnBottomCollider.vf3C();
    }

    else if (collisionType == SolidOnLeft) {
        solidOnLeftCollider.rotation = rotation.Z + 0x40000000;
        solidOnLeftCollider.vf3C();
    }

    else if (collisionType == SolidOnRight) {
        solidOnRightCollider.rotation = rotation.Z + 0xC0000000;
        solidOnRightCollider.vf3C();
    }

    return 1;
}

int MagicPlatform::onDraw() {
    setDrawerInstance();

    float angle = ((float)tileRotation / 0x80000000) * M_PI;
    float angleCos = cosf(angle);
    float angleSin = sinf(angle);

    for (int y = 0; y < height * 16; y += 16) {
        for (int x = 0; x < width * 16; x += 16) {
            unsigned short *tile = getTilePtr(location->x + x, location->y + y, 0, 0);
            if (tile) {
                // https://en.wikipedia.org/wiki/Rotation_matrix#In_two_dimensions
                float rotatedX =  x * angleCos + y * angleSin;
                float rotatedY = -x * angleSin + y * angleCos;
                Vec3 rotatedPos = {position.X + rotatedX, position.Y - rotatedY, position.Z};

                drawTile(Drawer, *tile, &rotatedPos, &tileRotation, &scale);
            }

            else {
                isDeleted = true;
                return 1;
            }
        }
    }

    return 1;
}
