#ifndef EFT_EMITTER_COMPLEX_H_
#define EFT_EMITTER_COMPLEX_H_

#include <nw/eft/eft_typeDef.h>
#include <nw/eft/eft_EmitterSimple.h>

namespace nw { namespace eft {

class EmitterComplexCalc : public EmitterSimpleCalc
{
public:
    explicit EmitterComplexCalc(System* sys)
        : EmitterSimpleCalc(sys)
    {
    }

    virtual void CalcEmitter(EmitterInstance* e);
    virtual u32 CalcParticle(EmitterInstance* e, CpuCore core, bool skipBehavior, bool skipMakeAttribute);
    virtual u32 CalcChildParticle(EmitterInstance* e, CpuCore core, bool skipBehavior, bool skipMakeAttribute);

    static void EmitChildParticle(EmitterInstance* e, PtclInstance* p);

    virtual PtclType GetPtclType() const
    {
        return EFT_PTCL_TYPE_COMPLEX;
    }

private:
    static inline void AddChildPtclToList(EmitterInstance* e, PtclInstance* ptcl)
    {
        if (e->childHead == NULL)
        {
            e->childHead       = ptcl;
            ptcl->prev         = ptcl->next = NULL;
        }
        else
        {
            e->childHead->prev = ptcl;
            ptcl->next         = e->childHead;
            e->childHead       = ptcl;
            ptcl->prev         = NULL;
        }

        if (e->childTail == NULL)
            e->childTail = ptcl;

        e->childPtclNum++;
    }

    static void CalcComplex(EmitterInstance* __restrict e, PtclInstance* __restrict ptcl, CpuCore core);
};
static_assert(sizeof(EmitterComplexCalc) == 4, "nw::eft::EmitterComplexCalc size mismatch");

} } // namespace nw::eft

#endif // EFT_EMITTER_COMPLEX_H_
