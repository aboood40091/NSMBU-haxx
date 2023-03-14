#ifndef EFT_RANDOM_H_
#define EFT_RANDOM_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

class Random
{
public:
    Random()
    {
        Init();
    }

    explicit Random(u32 seed)
    {
        Init(seed);
    }

    Random(u32 seed_0, u32 seed_1, u32 seed_2, u32 seed_3)
    {
        Init(seed_0, seed_1, seed_2, seed_3);
    }

    void Init()
    {
        Init(0);
    }

    void Init(u32 seed)
    {
        static const u32 a = 1812433253;
        mX = (seed ^ (seed >> 30)) * a + 1;
        mY = (mX ^ (mX >> 30)) * a + 2;
        mZ = (mY ^ (mY >> 30)) * a + 3;
        mW = (mZ ^ (mZ >> 30)) * a + 4;
    }

    void Init(u32 seed_0, u32 seed_1, u32 seed_2, u32 seed_3)
    {
        if (seed_0 == 0 && seed_1 == 0 && seed_2 == 0 && seed_3 == 0) // seeds must not be all zero.
            Init(0);

        else
        {
            mX = seed_0;
            mY = seed_1;
            mZ = seed_2;
            mW = seed_3;
        }
    }

    u32 GetU32()
    {
        u32 t = (mX^(mX<<11));
        mX = mY;
        mY = mZ;
        mZ = mW;
        mW = (mW^(mW>>19))^(t^(t>>8));
        return mW;
    }

    u32 GetU32(u32 ceil)
    {
        return static_cast<u32>(((u64)GetU32() * ceil) >> 32);
    }

    s32 GetS32Range(s32 a, s32 b)
    {
        return GetU32(b - a) + a;
    }

    f32 GetF32()
    {
        return GetU32() * (1.0f / 4294967296.0f);
    }

    f32 GetF32(f32 ceil)
    {
        return GetF32() * ceil;
    }

    f32 GetF32Range(f32 a, f32 b)
    {
        return GetF32(b - a) + a;
    }

    f64 GetF64()
    {
        return GetU32() * (1.0 / 4294967296.0);
    }

    f64 GetF64(f64 ceil)
    {
        return GetF64() * ceil;
    }

    f64 GetF64Range(f64 a, f64 b)
    {
        return GetF64(b - a) + a;
    }

    int GetSign()
    {
        return (GetU32() & 2) - 1;
    }

    bool GetBool()
    {
        return static_cast<bool>(GetU32() & 1);
    }

    void GetContext(u32* num_0, u32* num_1, u32* num_2, u32* num_3) const
    {
        *num_0 = mX;
        *num_1 = mY;
        *num_2 = mZ;
        *num_3 = mW;
    }

private:
    u32 mX;
    u32 mY;
    u32 mZ;
    u32 mW;
};
static_assert(sizeof(Random) == 0x10, "Random size mismatch");

class Heap;

class PtclRandom
{
public:
    PtclRandom();

    static void CreateRandomTbl(Heap* heap);
    static void DestroyRandomTbl(Heap* heap);

    void SetSeed(u32 val)
    {
        mVec3RndIx           = val >> 0;
        mNormalizedVec3RndIx = val >> 16;
        mRnd                 = val;
    }

    const nw::math::VEC3& GetVec3          () { return mVec3Tbl          [ ( mVec3RndIx++ )           & cNumVec3TblMask ]; }
    const nw::math::VEC3& GetNormalizedVec3() { return mNormalizedVec3Tbl[ ( mNormalizedVec3RndIx++ ) & cNumVec3TblMask ]; }

    u32 GetU32Direct()
    {
        u32 ret = mRnd;
        mRnd = mRnd * 1103515245 + 12345;
        return ret;
    }

    f32 GetF32()
    {
        return GetU32Direct() * (1.0f / 4294967296.0f);
    }

    /* f32 GetF32(f32 ceil)
    {
        return GetF32() * ceil;
    }

    f32 GetF32Range(f32 a, f32 b)
    {
        return GetF32(b - a) + a;
    } */

    s32 GetS32()
    {
        return GetU32Direct() >> 24;
    }

    s32 GetS32(int val)
    {
        return static_cast<s32>(((u64)GetU32Direct() * val) >> 32);
    }

    static Random* GetGlobalRandom();

private:
    enum
    {
        cNumVec3Tbl     = 512 ,
        cNumVec3TblMask = cNumVec3Tbl - 1
    };

    static nw::math::VEC3*  mVec3Tbl;
    static nw::math::VEC3*  mNormalizedVec3Tbl;

    u16                 mVec3RndIx;
    u16                 mNormalizedVec3RndIx;
    u32                 mRnd;

    static Random       gRandom;
};
static_assert(sizeof(PtclRandom) == 8, "nw::eft::PtclRandom size mismatch");

} } // namespace nw::eft

#endif // EFT_RANDOM_H_
