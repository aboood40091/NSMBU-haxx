#include <actor.h>
#include <collider.h>
#include <level.h>
#include <movement.h>

class MagicPlatform : public StageActor {
public:
    static Actor *build(ActorBuildInfo *);

    int onCreate();
    int onExecute();
    int onDraw();

    enum CollisionType {
        None = 0,
        Solid = 1,
        SolidOnTop = 2,
        SolidOnBottom = 3,
        SolidOnLeft = 4,
        SolidOnRight = 5
    };

    // Settings
    MovementType movementType; // Nybble 9
    CollisionType collisionType;  // Nybble 10
    char locationId; // Nybbles 11 and 12
    // Nybbles 21 and 22 are movement id

    unsigned short width;
    unsigned short height;
    unsigned int tileRotation;

    Location *location;
    MovementHandler movementHandler;

    RectCollider solidCollider;
    SemiSolidShapedCollider solidColliderFix;
    SemiSolidShapedCollider solidColliderFix2;

    SemiSolidShapedCollider solidOnTopCollider;
    SemiSolidShapedCollider solidOnBottomCollider;
    SemiSolidShapedCollider solidOnLeftCollider;
    SemiSolidShapedCollider solidOnRightCollider;

    inline MagicPlatform(ActorBuildInfo *buildInfo) : StageActor(buildInfo) {} // Constructor
};

const ActorInfo MagicPlatform_ActorInfo = {8.0, -8.0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

// Set it to not have any files
const SetActorFiles setMagicPlatformFiles(Cookie, 0, 0);
