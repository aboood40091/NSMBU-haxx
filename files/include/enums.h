#pragma once

enum ActorIDs {
    EventTrigger,
    EventAnd,
    EventOr,
    EventRandom,
    EventChainer,
    EventIf,
    EventMultiChainer,
    EventConstOnOff,
    DRCTouch,
    TwoWayController,
    PathController,
    ClapController,
    Cookie = 0x118
};

enum Direction {
    Right,
    Left,
    Up,
    Down
};

enum MovementType {
    None,
    SwayOrSpin, // Linked with sprites 68, 69, 116 and 118
    Bolt, // Linked with sprite 238
    Path, // Linked with sprite 100
    TwoWay, // Linked with sprite 70
    BoltMushroom = 6, // Linked with sprite 241
    NoBoltMushroom, // Linked with sprite 242
    ShiftingPlatform, // Linked with sprite 132
    Spinning, // Linked with sprites 214 and 484
    RollingHill, // Linked with sprite 265
    ColorMushroomLift // Linked with sprite 210
};
