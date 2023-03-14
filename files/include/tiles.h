#pragma once

enum TileId
{
    cTileId_Invalid = -1,
    cTileId_Null = 0,

    cTileId_InvBlockSolid,
    cTileId_InvVineStopper,
    cTileId_InvBlockCoin,
    cTileId_InvBlockFireFlower,
    cTileId_InvBlockStar,
    cTileId_InvBlock1UP,
    cTileId_InvBlockVine,
    cTileId_InvBlockMiniMushroom,
    cTileId_InvBlockPropeller,
    cTileId_InvBlockPenguin,
    cTileId_InvBlockSolidOnTop,
    cTileId_InvBlockSolidHalf,
    cTileId_InvBlockIceFlower,
    cTileId_InvClimbablePole,
    cTileId_InvRope, // Not functional?
    cTileId_InvBlockAcorn = 29,
    cTileId_InvMuncher = 45,

    cTileId_BrickBlockFireFlower = 16,
    cTileId_BrickBlockStar,
    cTileId_BrickBlock1UP,
    cTileId_BrickBlockVine,
    cTileId_BrickBlockMiniMushroom,
    cTileId_BrickBlockPropeller,
    cTileId_BrickBlockPenguin,
    cTileId_BrickBlockIceFlower,
    cTileId_BrickBlockAcorn,
    cTileId_BrickBlockYoshiEgg,
    cTileId_BrickBlockCoin,
    cTileId_BrickBlockCoin10,
    cTileId_BrickBlock = 48,

    cTileId_CoinDashMultiplayer = 28,
    cTileId_Coin = 30,
    cTileId_CoinDash,

    cTileId_QBlockFireFlower,
    cTileId_QBlockStar,
    cTileId_QBlockCoinStar,
    cTileId_QBlockVine,
    cTileId_QBlockMiniMushroom,
    cTileId_QBlockPropeller,
    cTileId_QBlockPenguin,
    cTileId_QBlockIceFlower,
    cTileId_QBlockAcorn,
    cTileId_QBlockYoshiEgg,
    cTileId_QBlockSpring,
    cTileId_QBlock = 49,

    cTileId_Bridge = 43,
    cTileId_MiniPassage,

    cTileId_BlueCoin = 46,
    cTileId_BlueCoin_CoreCoin,

    cTileId_BlockUsed = 50,
    cTileId_BlockWood,
    cTileId_BlockStone,
    cTileId_BlockBlue,
    cTileId_BlockDonutLift,
    cTileId_BlockRed = 208,

    cTileId_Fragment_BrickBlock_0 = 55,
    cTileId_Fragment_BrickBlock_1,
    cTileId_Fragment_BrickBlock_2,

    cTileId_Fragment_QBlock_0,
    cTileId_Fragment_QBlock_1,
    cTileId_Fragment_QBlock_2,

    cTileId_Fragment_BlockRed_0,
    cTileId_Fragment_BlockRed_1,
    cTileId_Fragment_BlockRed_2,

    cTileId_Fragment_BlockUsed_0 = 71,
    cTileId_Fragment_BlockUsed_1,
    cTileId_Fragment_BlockUsed_2,

    cTileId_Fragment_BlockWood_0,
    cTileId_Fragment_BlockWood_1,
    cTileId_Fragment_BlockWood_2,

    cTileId_Fragment_BlockStone_0,
    cTileId_Fragment_BlockStone_1,
    cTileId_Fragment_BlockStone_2,

    // ...

    cTileId_ConveyorRight_0 = 144,
    cTileId_ConveyorRight_1,
    cTileId_ConveyorRight_2,

    cTileId_ConveyorLeft_0,
    cTileId_ConveyorLeft_1,
    cTileId_ConveyorLeft_2,

    cTileId_ConveyorRightFast_0 = 160,
    cTileId_ConveyorRightFast_1,
    cTileId_ConveyorRightFast_2,

    cTileId_ConveyorLeftFast_0,
    cTileId_ConveyorLeftFast_1,
    cTileId_ConveyorLeftFast_2,

    // ...

    cTileId_Pa0Tiles_Num = 256,
    cTileId_Pa1Tiles_Num = cTileId_Pa0Tiles_Num + 256,
    cTileId_Pa2Tiles_Num = cTileId_Pa1Tiles_Num + 256,
    cTileId_Pa3Tiles_Num = cTileId_Pa2Tiles_Num + 256
};
