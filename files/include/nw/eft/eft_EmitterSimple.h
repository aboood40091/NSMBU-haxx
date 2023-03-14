#ifndef EFT_EMITTER_SIMPLE_H_
#define EFT_EMITTER_SIMPLE_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_Emitter.h>

namespace nw { namespace eft {

class EmitterSimpleCalc : public EmitterCalc
{
public:
    explicit EmitterSimpleCalc(System* sys)
        : EmitterCalc(sys)
    {
    }

    virtual void CalcEmitter(EmitterInstance* e);
    virtual u32 CalcParticle(EmitterInstance* e, CpuCore core, bool skipBehavior, bool skipMakeAttribute);

    virtual PtclType GetPtclType() const
    {
        return EFT_PTCL_TYPE_SIMPLE;
    }

protected:
    void ApplyAnim(EmitterInstance* e);
    void ApplyTransformAnim(EmitterInstance* e);
    void EmitSameDistance(const SimpleEmitterData* __restrict res, EmitterInstance* e);
};
static_assert(sizeof(EmitterSimpleCalc) == 4, "nw::eft::EmitterSimpleCalc size mismatch");

} } // namespace nw::eft

#endif // EFT_EMITTER_SIMPLE_H_
