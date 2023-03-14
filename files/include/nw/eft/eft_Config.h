#ifndef EFT_CONFIG_H_
#define EFT_CONFIG_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

class Heap;

class Config
{
public:
    enum ConfigDefault
    {
        EFT_DEFAULT_EMITTER_NUM                     = 64,
        EFT_DEFAULT_PARTICLE_NUM                    = 1024,
        EFT_DEFAULT_EMITTER_SET_NUM                 = 32,
        EFT_DEFAULT_RESOURCE_NUM                    = 8,
        EFT_DEFAULT_RESOURCE_VIEWER_RESERVE_NUM     = 16,
        EFT_DEFAULT_STRIPE_NUM                      = 32,
        EFT_DEFAULT_DOUBLE_BUFFER_SIZE              = 128 * 1024,
        EFT_DEFAULT_FORCE_4BYTE                     = 0x80000000
    };

public:
    Config() : mHeap                    ( NULL )
             , mEmitterNum              ( EFT_DEFAULT_EMITTER_NUM )
             , mParticleNum             ( EFT_DEFAULT_PARTICLE_NUM )
             , mEmitterSetNum           ( EFT_DEFAULT_EMITTER_SET_NUM )
             , mResourceNum             ( EFT_DEFAULT_RESOURCE_NUM )
             , mStripeNum               ( EFT_DEFAULT_STRIPE_NUM )
             , mSizeDoubleBufferSize    ( EFT_DEFAULT_DOUBLE_BUFFER_SIZE )
    {
    }

    virtual ~Config()
    {
    }

    virtual void SetEffectHeap(Heap* heap)
    {
        mHeap = heap;
    }

    virtual Heap* GetEffectHeap() const
    {
        return mHeap;
    }


    void SetEmitterNum(u32 num)
    {
        u32 bit = getCarryCount(num);
        if ((1 << bit) == num)
            mEmitterNum = num;
        else
            mEmitterNum = 1 << (bit + 1);
    }

    u32 GetEmitterNum() const
    {
        return mEmitterNum;
    }

    void SetParticleNum(u32 num)
    {
        u32 bit = getCarryCount(num);
        if ((1 << bit) == num)
            mParticleNum = num;
        else
            mParticleNum = 1 << (bit + 1);
    }

    u32 GetParticleNum() const
    {
        return mParticleNum;
    }

    void SetEmitterSetNum(u32 num)
    {
        u32 bit = getCarryCount(num);
        if ((1 << bit) == num)
            mEmitterSetNum = num;
        else
            mEmitterSetNum = 1 << (bit + 1);
    }

    u32 GetEmitterSetNum() const
    {
        return mEmitterSetNum;
    }

    void SetResourceNum(u32 num)
    {
        mResourceNum = num;
    }

    u32 GetResourceNum() const
    {
        return mResourceNum;
    }

    void SetStripeNum(u32 num)
    {
        u32 bit = getCarryCount(num);
        if ((1 << bit) == num)
            mStripeNum = num;
        else
            mStripeNum = 1 << (bit + 1);
    }

    u32 GetStripeNum() const
    {
        return mStripeNum;
    }

    void SetDoubleBufferSize(u32 size)
    {
        mSizeDoubleBufferSize = size;
    }

    u32 GetDoubleBufferSize() const
    {
        return mSizeDoubleBufferSize;
    }

private:
    u32 getCarryCount(u32 bits)
    {
        u32 num  = 31;
        u32 mask = 0x80000000;

        for (; mask != 0; mask = mask >> 1)
        {
            if (bits & mask)
                break;
            num--;
        }

        return num;
    }

protected:
    Heap*           mHeap;
    u32             mEmitterNum;
    u32             mParticleNum;
    u32             mEmitterSetNum;
    u32             mResourceNum;
    u32             mStripeNum;
    u32             mSizeDoubleBufferSize;
};
static_assert(sizeof(Config) == 0x20, "nw::eft::Config size mismatch");

} } // namespace nw::eft

#endif // EFT_CONFIG_H_
