# NSMBU-haxx
**This project has been archived. You can find the new version [here](https://github.com/aboood40091/NSMBU-Haxx-Rewrite).**  
---------------------------------------------------------------------------------  
A compilation of code hacks for NSMBU. Also an example for the [CafeLoader Project Compiler](https://github.com/aboood40091/CafeLoader-Project-Compiler) ([cemu branch](https://github.com/aboood40091/CafeLoader-Project-Compiler/tree/cemu) is needed for building for cemu).  
Pre-built versions can be found in the `build` folder. Stable builds are in the [releases](https://github.com/aboood40091/NSMBU-haxx/releases) page.

## Current haxx:
* Custom music list (Currently does nothing, but will help with new music slots in the future.)  
* Space physics as area option (Area data `wrapByte & 2`.)  
* NSMBW-style SFX reverb and delay  
* Disabled Fast approximate anti-aliasing (FXAA)  
* Fixed zone BG offsets  
* Collision Drawer (Set `COLLISION_DRAW` in `areatask.cpp` to non-zero integer to enable.)  
* Custom Profile setup to allow for new sprites  
* Actor Spawner sprite (Added as sprite 724.)  
* Flip Block sprite (Added as sprite 725. Currently uses the Snake Block model.)  
* Magic Platform sprite (Added as sprite 726.)  
* Effect Viewer (Added as sprite 727. Check `effectplayer.cpp` for controls.)

## Credits:
### Libraries:
* [NW4F Eft](https://github.com/open-ead/NW4F-Eft/tree/nsmbu) - NintendoWare for Cafe Effect Library.
* [SEAD](https://github.com/aboood40091/sead) - Nintendo EAD Standard Library.
* Modified dynamic_libs to work with this project, based on original implementation by dimok and [Maschell fork](https://github.com/Maschell/dynamic_libs).  

### Special thanks:
* [RicBent](https://github.com/RicBent/codedx): Contribution to headers, original Actor Spawner and basic Magic Platform implementations.  