#ifndef EFT_ANIM_KEY_FRAME_H_
#define EFT_ANIM_KEY_FRAME_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

enum AnimKeyFrameInterpolationType
{
    EFT_ANIM_KEY_FRAME_LINEAR = 0,
    EFT_ANIM_KEY_FRAME_SMOOTH,

    EFT_ANIM_KEY_FRAME_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(AnimKeyFrameInterpolationType) == 4, "nw::eft::AnimKeyFrameInterpolationType size mismatch");

enum AnimKeyFrameApplyType
{
    EFT_ANIM_EM_RATE = 0,
    EFT_ANIM_LIFE,
    EFT_ANIM_EM_SX,
    EFT_ANIM_EM_SY,
    EFT_ANIM_EM_SZ,
    EFT_ANIM_EM_RX,
    EFT_ANIM_EM_RY,
    EFT_ANIM_EM_RZ,
    EFT_ANIM_EM_TX,
    EFT_ANIM_EM_TY,
    EFT_ANIM_EM_TZ,
    EFT_ANIM_COLOR0_R,
    EFT_ANIM_COLOR0_G,
    EFT_ANIM_COLOR0_B,
    EFT_ANIM_ALPHA,
    EFT_ANIM_ALL_DIR_VEL,
    EFT_ANIM_DIR_VEL,
    EFT_ANIM_PTCL_SX,
    EFT_ANIM_PTCL_SY,
    EFT_ANIM_COLOR1_R,
    EFT_ANIM_COLOR1_G,
    EFT_ANIM_COLOR1_B,
    EFT_ANIM_EM_FORM_SX,
    EFT_ANIM_EM_FORM_SY,
    EFT_ANIM_EM_FORM_SZ,
    EFT_ANIM_MAX,

    EFT_ANIM_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(AnimKeyFrameApplyType) == 4, "nw::eft::AnimKeyFrameApplyType size mismatch");

struct AnimKeyFrameKey
{
    f32     x;
    f32     y;
};
static_assert(sizeof(AnimKeyFrameKey) == 8, "nw::eft::AnimKeyFrameKey size mismatch");

struct KeyFrameAnim
{
    u32                                 keyNum;
    AnimKeyFrameInterpolationType       interpolation;
    AnimKeyFrameApplyType               target;
    u32                                 isLoop;
    u32                                 offset;
    u32                                 _14[1];
};
static_assert(sizeof(KeyFrameAnim) == 0x18, "nw::eft::KeyFrameAnim size mismatch");

struct KeyFrameAnimArray
{
    u8                                  magic[4];
    u32                                 numAnims;
};
static_assert(sizeof(KeyFrameAnimArray) == 8, "nw::eft::KeyFrameAnimArray size mismatch");

f32 CalcAnimKeyFrame(KeyFrameAnim* info, f32 x);

} } // namespace nw::eft

#endif // EFT_ANIM_KEY_FRAME_H_
