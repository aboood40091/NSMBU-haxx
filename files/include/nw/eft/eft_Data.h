#ifndef EFT_DATA_H_
#define EFT_DATA_H_

#include <nw/eft/eft_typeDef.h>

namespace nw { namespace eft {

struct CommonEmitterData;

enum SystemConstants
{
    EFT_BINARY_VERSION                  = 0x00000028,
    EFT_EMITTER_INSET_NUM               = 16,
    EFT_TEXTURE_PATTERN_NUM             = 32 ,
    EFT_INFINIT_LIFE                    = 0x7fffffff,
    EFT_GROUP_MAX                       = 64,
    EFT_CALLBACK_MAX                    = 8,
    EFT_PTCL_BINARY_ALIGNMENT           = (16 * 1024),
    EFT_DEFAULT_DRAW_PRIORITY           = 128,
    EFT_SYSTEM_CONSTANTS_FORCE_4BYTE    = 0x80000000
};

enum CpuCore
{
    EFT_CPU_CORE_0 = 0,
    EFT_CPU_CORE_1 = 1,
    EFT_CPU_CORE_2 = 2,
    EFT_CPU_CORE_MAX = 3,
    EFT_CPU_CORE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(CpuCore) == 4, "nw::eft::CpuCore size mismatch");

enum EmitterType
{
    EFT_EMITTER_TYPE_SIMPLE     = 0,
    EFT_EMITTER_TYPE_COMPLEX,
    EFT_EMITTER_TYPE_MAX,
    EFT_EMITTER_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(EmitterType) == 4, "nw::eft::EmitterType size mismatch");

enum PtclType
{
    EFT_PTCL_TYPE_SIMPLE     = 0,
    EFT_PTCL_TYPE_COMPLEX,
    EFT_PTCL_TYPE_CHILD,
    EFT_PTCL_TYPE_MAX,
    EFT_PTCL_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(PtclType) == 4, "nw::eft::PtclType size mismatch");

enum PtclFollowType
{
    EFT_FOLLOW_TYPE_ALL = 0,
    EFT_FOLLOW_TYPE_NONE,
    EFT_FOLLOW_TYPE_POS_ONLY,
    EFT_FOLLOW_TYPE_MAX,
    EFT_FOLLOW_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(PtclFollowType) == 4, "nw::eft::PtclFollowType size mismatch");

enum UserDataCallBackID
{
    EFT_USER_DATA_CALLBACK_ID_NONE = -1,
    EFT_USER_DATA_CALLBACK_ID_0 = 0,
    EFT_USER_DATA_CALLBACK_ID_1 = 1,
    EFT_USER_DATA_CALLBACK_ID_2 = 2,
    EFT_USER_DATA_CALLBACK_ID_3 = 3,
    EFT_USER_DATA_CALLBACK_ID_4 = 4,
    EFT_USER_DATA_CALLBACK_ID_5 = 5,
    EFT_USER_DATA_CALLBACK_ID_6 = 6,
    EFT_USER_DATA_CALLBACK_ID_7 = 7,
    EFT_USER_DATA_CALLBACK_ID_MAX = 8,

    EFT_USER_CALLBACK_ID_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(UserDataCallBackID) == 8, "nw::eft::UserDataCallBackID size mismatch");

typedef u64 GroupFlag;
#define EFT_GROUP_FLAG(groupID) u64(u64(1) << u64(groupID))

enum DrawPathFlag
{
    EFT_DRAW_PATH_FLAG_0  = 0x01 << 0,
    EFT_DRAW_PATH_FLAG_1  = 0x01 << 1,
    EFT_DRAW_PATH_FLAG_2  = 0x01 << 2,
    EFT_DRAW_PATH_FLAG_3  = 0x01 << 3,
    EFT_DRAW_PATH_FLAG_4  = 0x01 << 4,
    EFT_DRAW_PATH_FLAG_5  = 0x01 << 5,
    EFT_DRAW_PATH_FLAG_6  = 0x01 << 6,
    EFT_DRAW_PATH_FLAG_7  = 0x01 << 7,
    EFT_DRAW_PATH_FLAG_8  = 0x01 << 8,
    EFT_DRAW_PATH_FLAG_9  = 0x01 << 9,
    EFT_DRAW_PATH_FLAG_10  = 0x01 << 10,
    EFT_DRAW_PATH_FLAG_11  = 0x01 << 11,
    EFT_DRAW_PATH_FLAG_12  = 0x01 << 12,
    EFT_DRAW_PATH_FLAG_13  = 0x01 << 13,
    EFT_DRAW_PATH_FLAG_14  = 0x01 << 14,
    EFT_DRAW_PATH_FLAG_15  = 0x01 << 15,
    EFT_DRAW_PATH_FLAG_16  = 0x01 << 16,
    EFT_DRAW_PATH_FLAG_17  = 0x01 << 17,
    EFT_DRAW_PATH_FLAG_18  = 0x01 << 18,
    EFT_DRAW_PATH_FLAG_19  = 0x01 << 19,
    EFT_DRAW_PATH_FLAG_20  = 0x01 << 20,
    EFT_DRAW_PATH_FLAG_21  = 0x01 << 21,
    EFT_DRAW_PATH_FLAG_22  = 0x01 << 22,
    EFT_DRAW_PATH_FLAG_23  = 0x01 << 23,
    EFT_DRAW_PATH_FLAG_24  = 0x01 << 24,
    EFT_DRAW_PATH_FLAG_25  = 0x01 << 25,
    EFT_DRAW_PATH_FLAG_26  = 0x01 << 26,
    EFT_DRAW_PATH_FLAG_27  = 0x01 << 27,
    EFT_DRAW_PATH_FLAG_28  = 0x01 << 28,
    EFT_DRAW_PATH_FLAG_29  = 0x01 << 29,
    EFT_DRAW_PATH_FLAG_30  = 0x01 << 30,
    EFT_DRAW_PATH_FLAG_31  = 0x01 << 31,

    EFT_DRAW_PATH_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(DrawPathFlag) == 8, "nw::eft::DrawPathFlag size mismatch");

#define EFT_INVALID_EMITTER_SET_ID (-1)
#define EFT_INVALID_EMITTER_ID (-1)
#define EFT_INVALID_ATTRIBUTE 0xFFFFFFFF
#define EFT_INVALID_LOCATION 0xFFFFFFFF
#define EFT_INVALID_SAMPLER 0xFFFFFFFF

enum UserShaderCallBackID
{
    EFT_USER_SHADER_CALLBACK_NONE  = 0,
    EFT_USER_SHADER_CALLBACK_1     = 1,
    EFT_USER_SHADER_CALLBACK_2     = 2,
    EFT_USER_SHADER_CALLBACK_3     = 3,
    EFT_USER_SHADER_CALLBACK_4     = 4,
    EFT_USER_SHADER_CALLBACK_5     = 5,
    EFT_USER_SHADER_CALLBACK_6     = 6,
    EFT_USER_SHADER_CALLBACK_7     = 7,
    EFT_USER_SHADER_CALLBACK_8     = 8,
    EFT_USER_SHADER_CALLBACK_MAX   = 9,

    EFT_USER_SHADER_CALLBACK_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(UserShaderCallBackID) == 4, "nw::eft::UserShaderCallBackID size mismatch");

enum TextureSlot
{
    EFT_TEXTURE_SLOT_0                  = 0,
    EFT_TEXTURE_SLOT_1                  = 1,
    EFT_TEXTURE_SLOT_BIN_MAX            = 2,
    EFT_TEXTURE_SLOT_DEPTH_BUFFER       = EFT_TEXTURE_SLOT_BIN_MAX,
    EFT_TEXTURE_SLOT_FRAME_BUFFER       = 3,
    EFT_TEXTURE_SLOT_MAX                = 4,

    EFT_USER_TEXTURE_SLOT_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(TextureSlot) == 4, "nw::eft::TextureSlot size mismatch");

enum TextureWrapMode
{
    EFT_TEXTURE_WRAP_TYPE_MIRROR,
    EFT_TEXTURE_WRAP_TYPE_REPEAT,
    EFT_TEXTURE_WRAP_TYPE_CLAMP,
    EFT_TEXTURE_WRAP_TYPE_MIROOR_ONCE,
    EFT_TEXTURE_WRAP_TYPE_MAX,

    EFT_TEXTURE_WRAP_MODE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(TextureWrapMode) == 4, "nw::eft::TextureWrapMode size mismatch");

enum TextureFilterMode
{
    EFT_TEXTURE_FILTER_TYPE_LINEAR,
    EFT_TEXTURE_FILTER_TYPE_NEAR,

    EFT_TEXTURE_FILTER_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(TextureFilterMode) == 4, "nw::eft::TextureFilterMode size mismatch");

enum DrawViewFlag
{
    EFT_DRAW_VIEW_FLAG_0          = ( 0x01 << 0 ),
    EFT_DRAW_VIEW_FLAG_1          = ( 0x01 << 1 ),
    EFT_DRAW_VIEW_FLAG_2          = ( 0x01 << 2 ),
    EFT_DRAW_VIEW_FLAG_3          = ( 0x01 << 3 ),
    EFT_DRAW_VIEW_FLAG_4          = ( 0x01 << 4 ),
    EFT_DRAW_VIEW_FLAG_5          = ( 0x01 << 5 ),
    EFT_DRAW_VIEW_FLAG_ALL        = EFT_DRAW_VIEW_FLAG_0 |
                                    EFT_DRAW_VIEW_FLAG_1 |
                                    EFT_DRAW_VIEW_FLAG_2 |
                                    EFT_DRAW_VIEW_FLAG_3 |
                                    EFT_DRAW_VIEW_FLAG_4 |
                                    EFT_DRAW_VIEW_FLAG_5,
    EFT_DRAW_VIEW_FLAG_NONE       = 0,

    EFT_DRAW_VIEW_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(DrawViewFlag) == 4, "nw::eft::DrawViewFlag size mismatch");

enum DisplaySideType
{
    EFT_DISPLAYSIDETYPE_BOTH = 0,
    EFT_DISPLAYSIDETYPE_FRONT,
    EFT_DISPLAYSIDETYPE_BACK,

    EFT_DISPLAYSIDETYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(DisplaySideType) == 4, "nw::eft::DisplaySideType size mismatch");

enum TextureAddressing
{
    EFT_TEX_ADDRESSING_NORMAL = 0 ,
    EFT_TEX_ADDRESSING_MIRROR_U2 ,
    EFT_TEX_ADDRESSING_MIRROR_V2 ,
    EFT_TEX_ADDRESSING_MIRROR_U2_V2 ,
    EFT_TEX_ADDRESSING_MAX,

    EFT_TEX_ADDRESSING_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(TextureAddressing) == 4, "nw::eft::TextureAddressing size mismatch");

enum EmitterFlg
{
    EFT_EMITTER_FLAG_COLOR_RANDOM               = ( 1 << 0 ) ,
    EFT_EMITTER_FLAG_DISP_EMITTER_MATRIX        = ( 1 << 1 ) ,
    EFT_EMITTER_FLAG_DISP_VOLUME                = ( 1 << 2 ) ,
    EFT_EMITTER_FLAG_DISP_FIELD_MAGNET          = ( 1 << 3 ) ,
    EFT_EMITTER_FLAG_DISP_FIELD_SPIN            = ( 1 << 4 ) ,
    EFT_EMITTER_FLAG_DISP_FIELD_COLLISION       = ( 1 << 5 ) ,
    EFT_EMITTER_FLAG_DISP_FIELD_CONVERGENCE     = ( 1 << 6 ) ,
    EFT_EMITTER_FLAG_ENABLE_FOG                 = ( 1 << 7 ) ,
    EFT_EMITTER_FLAG_ENABLE_SOFTEDGE            = ( 1 << 8 ) ,
    EFT_EMITTER_FLAG_ENABLE_SORTPARTICLE        = ( 1 << 9 ) ,
    EFT_EMITTER_FLAG_REVERSE_ORDER_PARTICLE     = ( 1 << 10 ) ,

    EFT_EMITTER_FLAG_TEXTURE0_COLOR_ONE         = ( 1 << 11 ) ,
    EFT_EMITTER_FLAG_TEXTURE1_COLOR_ONE         = ( 1 << 12 ) ,
    EFT_EMITTER_FLAG_PRIMITIVE_COLOR_ONE        = ( 1 << 13 ) ,
    EFT_EMITTER_FLAG_TEXTURE0_ALPHA_ONE         = ( 1 << 14 ) ,
    EFT_EMITTER_FLAG_TEXTURE1_ALPHA_ONE         = ( 1 << 15 ) ,
    EFT_EMITTER_FLAG_PRIMITIVE_ALPHA_ONE        = ( 1 << 16 ) ,

    EFT_EMITTER_FLAG_DISP_FIELD_MASK = EFT_EMITTER_FLAG_DISP_FIELD_MAGNET |
                        EFT_EMITTER_FLAG_DISP_FIELD_SPIN |
                        EFT_EMITTER_FLAG_DISP_FIELD_COLLISION |
                        EFT_EMITTER_FLAG_DISP_FIELD_CONVERGENCE,

    EFT_EMITTER_FLAG_ALL                        = 0xffffffff
};
static_assert(sizeof(EmitterFlg) == 4, "nw::eft::EmitterFlg size mismatch");

enum BehaviorFlg
{
    EFT_EMITTER_BEHAVIOR_FLAG_AIR_REGIST            = ( 1 << 0 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_GRAVITY               = ( 1 << 1 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_ROTATE                = ( 1 << 2 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_ROT_REGIST            = ( 1 << 3 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_WLD_POSDIF            = ( 1 << 4 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_LCL_POSDIF            = ( 1 << 5 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_SCALE_ANIM            = ( 1 << 6 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_ALPHA_ANIM            = ( 1 << 7 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_COLOR0_ANIM           = ( 1 << 8 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_COLOR1_ANIM           = ( 1 << 9 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_TEXTURE0_UV_ANIM      = ( 1 << 10 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_TEXTURE1_UV_ANIM      = ( 1 << 11 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_TEXTURE0_PTN_ANIM     = ( 1 << 12 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_TEXTURE1_PTN_ANIM     = ( 1 << 13 ) ,
    EFT_EMITTER_BEHAVIOR_FLAG_TEXTURE1_CALC         = ( 1 << 14 ) ,

    EFT_EMITTER_BEHAVIOR_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(BehaviorFlg) == 4, "nw::eft::BehaviorFlg size mismatch");

enum ShaderEnableAttrFlg
{
    EFT_SHADER_ATTRIBUTE_HAS_SCALE          = ( 1 << 0 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_TEX_ANIM       = ( 1 << 1 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_SUB_TEX_ANIM   = ( 1 << 2 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_WORLD_POS      = ( 1 << 3 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_WORLD_POS_DIFF = ( 1 << 4 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_COLOR0         = ( 1 << 5 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_COLOR1         = ( 1 << 6 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_ROTATE         = ( 1 << 7 ) ,
    EFT_SHADER_ATTRIBUTE_HAS_EMITTER_MATRIX = ( 1 << 8 ) ,
};
static_assert(sizeof(ShaderEnableAttrFlg) == 4, "nw::eft::ShaderEnableAttrFlg size mismatch");

enum VolumeType
{
    EFT_VOLUME_TYPE_POINT = 0,
    EFT_VOLUME_TYPE_CIRCLE,
    EFT_VOLUME_TYPE_CIRCLE_SAME_DIVIDE,
    EFT_VOLUME_TYPE_CIRCLE_FILL,
    EFT_VOLUME_TYPE_SPHERE,
    EFT_VOLUME_TYPE_SPHERE_SAME_DIVIDE,
    EFT_VOLUME_TYPE_SPHERE_SAME_DIVIDE64,
    EFT_VOLUME_TYPE_SPHERE_FILL,
    EFT_VOLUME_TYPE_CYLINDER,
    EFT_VOLUME_TYPE_CYLINDER_FILL,
    EFT_VOLUME_TYPE_BOX,
    EFT_VOLUME_TYPE_BOX_FILL,
    EFT_VOLUME_TYPE_LINE,
    EFT_VOLUME_TYPE_LINE_SAME_DIVIDE,
    EFT_VOLUME_TYPE_RECTANGLE,

    EFT_VOLUME_TYPE_MAX,
    EFT_VOLUME_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(VolumeType) == 4, "nw::eft::VolumeType size mismatch");

enum ShaderType
{
    EFT_SHADER_TYPE_NORMAL      = 0,
    EFT_SHADER_TYPE_USER_DEF1   = 1,
    EFT_SHADER_TYPE_USER_DEF2   = 2,
    EFT_SHADER_TYPE_MAX         = 3,

    EFT_SHADER_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(ShaderType) == 4, "nw::eft::ShaderType size mismatch");

enum BlendType
{
    EFT_BLEND_TYPE_NORMAL = 0,
    EFT_BLEND_TYPE_ADD,
    EFT_BLEND_TYPE_SUB,
    EFT_BLEND_TYPE_SCREEN,
    EFT_BLEND_TYPE_MULT,
    EFT_BLEND_TYPE_NONE,
    EFT_BLEND_TYPE_MAX,
    EFT_BLEND_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(BlendType) == 4, "nw::eft::BlendType size mismatch");

enum ZBufATestType
{
    EFT_ZBUFF_ATEST_TYPE_NORMAL = 0,
    EFT_ZBUFF_ATEST_TYPE_ZIGNORE,
    EFT_ZBUFF_ATEST_TYPE_ENTITY,
    EFT_ZBUFF_ATEST_TYPE_MAX,
    EFT_ZBUFF_ATEST_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(ZBufATestType) == 4, "nw::eft::ZBufATestType size mismatch");

enum PtclRotType
{
    EFT_ROT_TYPE_NO_WORK   = 0 ,
    EFT_ROT_TYPE_ROTX,
    EFT_ROT_TYPE_ROTY,
    EFT_ROT_TYPE_ROTZ,
    EFT_ROT_TYPE_ROTXYZ,
    EFT_ROT_TYPE_MAX,
    EFT_ROT_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(PtclRotType) == 4, "nw::eft::PtclRotType size mismatch");

enum MeshType
{
    EFT_MESH_TYPE_PARTICLE = 0,
    EFT_MESH_TYPE_PRIMITIVE,
    EFT_MESH_TYPE_STRIPE,
    EFT_MESH_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(MeshType) == 4, "nw::eft::MeshType size mismatch");

enum BillboardType
{
    EFT_BILLBOARD_TYPE_BILLBOARD = 0,
    EFT_BILLBOARD_TYPE_POLYGON_XY,
    EFT_BILLBOARD_TYPE_POLYGON_XZ,
    EFT_BILLBOARD_TYPE_VEL_LOOK,
    EFT_BILLBOARD_TYPE_VEL_LOOK_POLYGON,
    EFT_BILLBOARD_TYPE_STRIPE,
    EFT_BILLBOARD_TYPE_COMPLEX_STRIPE,
    EFT_BILLBOARD_TYPE_PRIMITIVE,
    EFT_BILLBOARD_TYPE_Y_BILLBOARD,

    EFT_BILLBOARD_TYPE_MAX,
    EFT_BILLBOARD_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(BillboardType) == 4, "nw::eft::BillboardType size mismatch");

enum CombinerType
{
    EFT_COMBINER_TYPE_COLOR                 = 0,
    EFT_COMBINER_TYPE_TEXTURE               = 1,
    EFT_COMBINER_TYPE_TEXTURE_INTERPOLATE   = 2,
    EFT_COMBINER_TYPE_TEXTURE_ADD           = 3,
    EFT_COMBINER_TYPE,
    EFT_COMBINER_TYPE_FORCE4BYTE            = 0x80000000
};
static_assert(sizeof(CombinerType) == 4, "nw::eft::CombinerType size mismatch");

enum AlphaCombinerType
{
    EFT_ALPHA_COMBINER_TYPE_MOD             = 0,
    EFT_ALPHA_COMBINER_TYPE_SUB             = 1,
    EFT_ALPHA_COMBINER_TYPE_MOD_R           = 2,
    EFT_ALPHA_COMBINER_TYPE_SUB_R           = 3,
    EFT_ALPHA_COMBINER_TYPE,
    EFT_ALPHA_COMBINER_TYPE_FORCE4BYTE = 0x80000000
};
static_assert(sizeof(AlphaCombinerType) == 4, "nw::eft::AlphaCombinerType size mismatch");

enum ColorBlendType
{
    EFT_COLOR_BLEND_TYPE_MOD = 0,
    EFT_COLOR_BLEND_TYPE_ADD,
    EFT_COLOR_BLEND_TYPE_SUB,
    EFT_COLOR_BLEND_TYPE_FORCE4BYTE = 0x80000000
};
static_assert(sizeof(ColorBlendType) == 4, "nw::eft::ColorBlendType size mismatch");

enum ColorCalcType
{
    EFT_COLOR_CALC_TYPE_NONE = 0,
    EFT_COLOR_CALC_TYPE_RANDOM,
    EFT_COLOR_CALC_TYPE_RANDOM_LINEAR3COLOR,

    EFT_COLOR_CALC_TYPE_FORCE4BYTE = 0x80000000
};
static_assert(sizeof(ColorCalcType) == 4, "nw::eft::ColorCalcType size mismatch");

enum ColorKind
{
    EFT_COLOR_KIND_0    = 0,
    EFT_COLOR_KIND_1    = 1,
    EFT_COLOR_KIND_MAX  = 2,
    EFT_COLOR_KIND_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(ColorKind) == 4, "nw::eft::ColorKind size mismatch");

enum TextureFormat
{
    EFT_TEXTURE_FORMAT_NONE = 0,
    EFT_TEXTURE_FORMAT_24BIT_COLOR,
    EFT_TEXTURE_FORMAT_32BIT_COLOR,
    EFT_TEXTURE_FORMAT_UNORM_BC1,
    EFT_TEXTURE_FORMAT_SRGB_BC1,
    EFT_TEXTURE_FORMAT_UNORM_BC2,
    EFT_TEXTURE_FORMAT_SRGB_BC2,
    EFT_TEXTURE_FORMAT_UNORM_BC3,
    EFT_TEXTURE_FORMAT_SRGB_BC3,
    EFT_TEXTURE_FORMAT_UNORM_BC4,
    EFT_TEXTURE_FORMAT_SNORM_BC4,
    EFT_TEXTURE_FORMAT_UNORM_BC5,
    EFT_TEXTURE_FORMAT_SNORM_BC5,
    EFT_TEXTURE_FORMAT_UNORM_8,
    EFT_TEXTURE_FORMAT_UNORM_8_8,
    EFT_TEXTURE_FORMAT_SRGB_8_8_8_8,

    EFT_TEXTURE_FORMAT_FORCE4BYTE = 0x80000000
};
static_assert(sizeof(TextureFormat) == 4, "nw::eft::TextureFormat size mismatch");

enum UvShiftAnimMode
{
    EFT_UV_SHIFT_ANIM_NONE = 0,
    EFT_UV_SHIFT_ANIM_SCROLL,
    EFT_UV_SHIFT_ANIM_SCALE,
    EFT_UV_SHIFT_ANIM_ROT,
    EFT_UV_SHIFT_ANIM_ALL,

    EFT_TEXTURE_ADD_ANIM__FORCE4BYTE = 0x80000000
};
static_assert(sizeof(UvShiftAnimMode) == 4, "nw::eft::UvShiftAnimMode size mismatch");

enum ChildFlg
{
    EFT_CHILD_FLAG_ENABLE                       = ( 1 << 0 ) ,
    EFT_CHILD_FLAG_COLOR0_INHERIT               = ( 1 << 1 ) ,
    EFT_CHILD_FLAG_ALPHA_INHERIT                = ( 1 << 2 ) ,
    EFT_CHILD_FLAG_SCALE_INHERIT                = ( 1 << 3 ) ,
    EFT_CHILD_FLAG_ROTATE_INHERIT               = ( 1 << 4 ) ,
    EFT_CHILD_FLAG_VEL_INHERIT                  = ( 1 << 5 ) ,
    EFT_CHILD_FLAG_EMITTER_FOLLOW               = ( 1 << 6 ) ,
    EFT_CHILD_FLAG_DISP_PARENT                  = ( 1 << 7 ) ,
    EFT_CHILD_FLAG_WORLD_FIELD                  = ( 1 << 8 ) ,
    EFT_CHILD_FLAG_IS_POLYGON                   = ( 1 << 9 ) ,
    EFT_CHILD_FLAG_IS_EMITTER_BILLBOARD_MTX     = ( 1 << 10 ),
    EFT_CHILD_FLAG_PARENT_FIELD                 = ( 1 << 11 ),
    EFT_CHILD_FLAG_PRE_CHILD_DRAW               = ( 1 << 12 ),
    EFT_CHILD_FLAG_IS_TEXTURE_PAT_ANIM          = ( 1 << 13 ),
    EFT_CHILD_FLAG_IS_TEXTURE_PAT_ANIM_RAND     = ( 1 << 14 ),
    EFT_CHILD_FLAG_COLOR1_INHERIT               = ( 1 << 15 ),
    EFT_CHILD_FLAG_COLOR_SCALE_INHERIT          = ( 1 << 16 ),

    EFT_CHILD_FLAG_TEXTURE_COLOR_ONE            = ( 1 << 17 ) ,
    EFT_CHILD_FLAG_PRIMITIVE_COLOR_ONE          = ( 1 << 18 ) ,
    EFT_CHILD_FLAG_TEXTURE_ALPHA_ONE            = ( 1 << 19 ) ,
    EFT_CHILD_FLAG_PRIMITIVE_ALPHA_ONE          = ( 1 << 20 ) ,

    EFT_CHILD_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(ChildFlg) == 4, "nw::eft::ChildFlg size mismatch");

enum FieldType
{
    EFT_FIELD_TYPE_RANDOM,
    EFT_FIELD_TYPE_MAGNET,
    EFT_FIELD_TYPE_SPIN,
    EFT_FIELD_TYPE_COLLISION,
    EFT_FIELD_TYPE_CONVERGENCE,
    EFT_FIELD_TYPE_POSADD,
    EFT_FIELD_TYPE_MAX,
    EFT_FIELD_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(FieldType) == 4, "nw::eft::FieldType size mismatch");

enum FieldMask
{
    EFT_FIELD_MASK_RANDOM       = ( 1 << EFT_FIELD_TYPE_RANDOM      ),
    EFT_FIELD_MASK_MAGNET       = ( 1 << EFT_FIELD_TYPE_MAGNET      ),
    EFT_FIELD_MASK_SPIN         = ( 1 << EFT_FIELD_TYPE_SPIN        ),
    EFT_FIELD_MASK_COLLISION    = ( 1 << EFT_FIELD_TYPE_COLLISION   ),
    EFT_FIELD_MASK_CONVERGENCE  = ( 1 << EFT_FIELD_TYPE_CONVERGENCE ),
    EFT_FIELD_MASK_POSADD       = ( 1 << EFT_FIELD_TYPE_POSADD      ),
    EFT_FIELD_MASK_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(FieldMask) == 4, "nw::eft::FieldMask size mismatch");

enum FluctuationFlg
{
    EFT_FLUCTUATION_FALG_ENABLE         = ( 1 << 0 ) ,
    EFT_FLUCTUATION_FALG_APPLY_ALPHA    = ( 1 << 1 ) ,
    EFT_FLUCTUATION_FALG_APPLY_SCLAE    = ( 1 << 2 ) ,
    EFT_FLUCTUATION_FALG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(FluctuationFlg) == 4, "nw::eft::FluctuationFlg size mismatch");

enum
{
    EFT_FLUCTUATION_TABLE_NUM           = 128 ,
    EFT_FLUCTUATION_TABLE_MASK          = EFT_FLUCTUATION_TABLE_NUM - 1 ,
    EFT_FLUCTUATION_TABLE_FORCE_4BYTE = 0x80000000
};

enum FieldMagnetFlg
{
    EFT_MAGNET_FLAG_X = ( 1 << 0 ) ,
    EFT_MAGNET_FLAG_Y = ( 1 << 1 ) ,
    EFT_MAGNET_FLAG_Z = ( 1 << 2 ) ,
    EFT_MAGNET_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(FieldMagnetFlg) == 4, "nw::eft::FieldMagnetFlg size mismatch");

enum FieldCollisionReaction
{
    EFT_FIELD_COLLISION_REACTION_CESSER = 0 ,
    EFT_FIELD_COLLISION_REACTION_REFLECTION ,
    EFT_FIELD_COLLISION_REACTION_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(FieldCollisionReaction) == 4, "nw::eft::FieldCollisionReaction size mismatch");

enum StripeFlg
{
    EFT_STRIPE_FLAG_EMITTER_COORD       = ( 1 << 0 ) ,
    EFT_STRIPE_FLAG_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(StripeFlg) == 4, "nw::eft::StripeFlg size mismatch");

enum StripeType
{
    EFT_STRIPE_TYPE_BILLBOARD,
    EFT_STRIPE_TYPE_EMITTER_MATRIX ,
    EFT_STRIPE_TYPE_EMITTER_UP_DOWN,
    EFT_STRIPE_TYPE_MAX,
    EFT_STRIPE_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(StripeType) == 4, "nw::eft::StripeType size mismatch");

enum StripeOption
{
    EFT_STRIPE_OPTION_TYPE_NORMAL,
    EFT_STRIPE_OPTION_TYPE_CROSS,
    EFT_STRIPE_OPTION_TYPE_MAX,
    EFT_STRIPE_OPTION_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(StripeOption) == 4, "nw::eft::StripeOption size mismatch");

enum StripeConnectOption
{
    EFT_STRIPE_CONNECT_OPTION_NORMAL,
    EFT_STRIPE_CONNECT_OPTION_HEAD,
    EFT_STRIPE_CONNECT_OPTION_EMITTER,
    EFT_STRIPE_CONNECT_OPTION_EMITTER_UNBIND,


    EFT_CONNECTION_STRIPE_OPTION_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(StripeConnectOption) == 4, "nw::eft::StripeConnectOption size mismatch");

enum StripeTexCoordOption
{
    EFT_STRIPE_TEXCOORD_OPTION_TYPE_FULL,
    EFT_STRIPE_TEXCOORD_OPTION_TYPE_DIVISION,
    EFT_STRIPE_TEXCOORD_OPTION_TYPE_MAX,
    EFT_STRIPE_TEXCOORD_OPTION_TYPE_FORCE_4BYTE = 0x80000000
};
static_assert(sizeof(StripeTexCoordOption) == 4, "nw::eft::StripeTexCoordOption size mismatch");

enum UserDataFlag
{
    EFT_USER_DATA_FLAG_0  = 0x01 << 16,
    EFT_USER_DATA_FLAG_1  = 0x01 << 17,
    EFT_USER_DATA_FLAG_2  = 0x01 << 18,
    EFT_USER_DATA_FLAG_3  = 0x01 << 19,
    EFT_USER_DATA_FLAG_4  = 0x01 << 20,
    EFT_USER_DATA_FLAG_5  = 0x01 << 21,
    EFT_USER_DATA_FLAG_6  = 0x01 << 22,
    EFT_USER_DATA_FLAG_7  = 0x01 << 23,
    EFT_USER_DATA_FLAG_8  = 0x01 << 24,
    EFT_USER_DATA_FLAG_9  = 0x01 << 25,
    EFT_USER_DATA_FLAG_10 = 0x01 << 26,
    EFT_USER_DATA_FLAG_11 = 0x01 << 27,
    EFT_USER_DATA_FLAG_12 = 0x01 << 28,
    EFT_USER_DATA_FLAG_13 = 0x01 << 29,
    EFT_USER_DATA_FLAG_14 = 0x01 << 30,
    EFT_USER_DATA_FLAG_15 = 0x01U << 31
};

enum UserDataParamIdx
{
    EFT_USER_DATA_PARAM_0   = 0,
    EFT_USER_DATA_PARAM_1   = 1,
    EFT_USER_DATA_PARAM_2   = 2,
    EFT_USER_DATA_PARAM_3   = 3,
    EFT_USER_DATA_PARAM_4   = 4,
    EFT_USER_DATA_PARAM_5   = 5,
    EFT_USER_DATA_PARAM_6   = 6,
    EFT_USER_DATA_PARAM_7   = 7,
    EFT_USER_DATA_PARAM_MAX = 8
};

struct VertexTextureLocation
{
    u32 loc;

    bool IsValid() const
    {
        return loc != u32(EFT_INVALID_LOCATION);
    }
};
static_assert(sizeof(VertexTextureLocation) == 4, "nw::eft::VertexTextureLocation size mismatch");

struct FragmentTextureLocation
{
    u32 loc;

    bool IsValid() const
    {
        return loc != u32(EFT_INVALID_LOCATION);
    }
};
static_assert(sizeof(FragmentTextureLocation) == 4, "nw::eft::FragmentTextureLocation size mismatch");

struct PtclAttributeBuffer
{
    nw::math::VEC4    pWldPos;
    nw::math::VEC4    pScl;
    nw::math::VEC4    pColor0;
    nw::math::VEC4    pColor1;
    nw::math::VEC4    pTexAnim;
    nw::math::VEC4    pWldPosDf;
    nw::math::VEC4    pRot;
    nw::math::VEC4    pSubTexAnim;
    nw::math::VEC4    pEmtMat[3];
};
static_assert(sizeof(PtclAttributeBuffer) == 0xB0, "nw::eft::PtclAttributeBuffer size mismatch");

struct PrimitiveImageInformation
{
    u32     primitiveNum;
    u32     totalSize;
    u32     offsetPrimitiveTableInfo;
};
static_assert(sizeof(PrimitiveImageInformation) == 0xC, "nw::eft::PrimitiveImageInformation size mismatch");

struct PrimitiveTableInfo
{
    struct PrimDataTable
    {
        u32     count;
        u32     column;
        u32     offset;
        u32     size;
    };
    static_assert(sizeof(PrimDataTable) == 0x10, "nw::eft::PrimitiveTableInfo::PrimDataTable size mismatch");

    PrimDataTable pos;
    PrimDataTable normal;
    PrimDataTable color;
    PrimDataTable texCoord;
    PrimDataTable index;
};
static_assert(sizeof(PrimitiveTableInfo) == 0x50, "nw::eft::PrimitiveTableInfo size mismatch");

struct HeaderData
{
    char    magic[4];
    u32     version;
    s32     numEmitterSet;
    s32     namePos;
    s32     nameTblPos;
    s32     textureTblPos;
    s32     textureTblSize;
    s32     shaderTblPos;
    s32     shaderTblSize;
    s32     animkeyTblPos;
    s32     animkeyTblSize;
    s32     primitiveTblPos;
    s32     primitiveTblSize;
    s32     totalTextureSize;
    s32     totalShaderSize;
    s32     totalEmitterSize;
};
static_assert(sizeof(HeaderData) == 0x40, "nw::eft::HeaderData size mismatch");

struct EmitterSetData
{
    u32     userData;
    u32     lastUpdateDate;
    s32     namePos;
    char*   name;
    s32     numEmitter;
    s32     emitterTblPos;
    u32*    emitterTbl;
};
static_assert(sizeof(EmitterSetData) == 0x1C, "nw::eft::EmitterSetData size mismatch");

struct EmitterTblData
{
    s32                 emitterPos;
    CommonEmitterData*  emitter;
};
static_assert(sizeof(EmitterTblData) == 8, "nw::eft::EmitterTblData size mismatch");

struct UserShaderParam
{
    f32 param[32];
};
static_assert(sizeof(UserShaderParam) == 0x80, "nw::eft::UserShaderParam size mismatch");

struct TextureRes
{
    u16                 width;
    u16                 height;
    GX2TileMode         tileMode;
    u32                 swizzle;
    u32                 alignment;
    u32                 pitch;
    u8                  wrapMode;
    u8                  filterMode;
    u8                  dummy[2];
    u32                 mipLevel;
    u32                 compSel;
    u32                 mipOffset[13];
    f32                 enableMipLevel;
    f32                 mipMapBias;
    TextureFormat       originalDataFormat;
    s32                 originalDataPos;
    s32                 originalDataSize;
    TextureFormat       nativeDataFormat;
    s32                 nativeDataSize;
    s32                 nativeDataPos;
    u32                 handle;
    GX2Texture          gx2Texture;
};
static_assert(sizeof(TextureRes) == 0x114, "nw::eft::TextureRes size mismatch");

struct AnimKeyTable
{
    void*               animKeyTable;
    u32                 animPos;
    u32                 dataSize;
};
static_assert(sizeof(AnimKeyTable) == 0xC, "nw::eft::AnimKeyTable size mismatch");

struct PrimitiveFigure
{
    void*               primitiveTableInfo;
    u32                 dataSize;
    u32                 index;
};
static_assert(sizeof(PrimitiveFigure) == 0xC, "nw::eft::PrimitiveFigure size mismatch");

struct CommonEmitterData
{
    EmitterType     type;
    u32             flg;
    u32             randomSeed;
    u32             userData;
    u32             userData2;
    f32             userDataF[EFT_USER_DATA_PARAM_MAX];
    s32             userCallbackID;
    s32             namePos;
    char*           name;
    TextureRes      texRes[EFT_TEXTURE_SLOT_BIN_MAX];
    AnimKeyTable    animKeyTable;
    PrimitiveFigure primitiveFigure;
};
static_assert(sizeof(CommonEmitterData) == 0x280, "nw::eft::CommonEmitterData size mismatch");

struct TextureEmitterData
{
    u8                  isTexPatAnim;
    u8                  isTexPatAnimRand;
    u8                  isTexPatAnimClump;
    u8                  numTexDivX;

    u8                  numTexDivY;
    u8                  numTexPat;
    u8                  dummy[2];

    s16                 texPatFreq;
    s16                 texPatTblUse;
    u8                  texPatTbl[EFT_TEXTURE_PATTERN_NUM];
    TextureAddressing   texAddressingMode;
    f32                 texUScale;
    f32                 texVScale;

    UvShiftAnimMode     uvShiftAnimMode;
    nw::math::VEC2      uvScroll;
    nw::math::VEC2      uvScrollInit;
    nw::math::VEC2      uvScrollInitRand;
    nw::math::VEC2      uvScale;
    nw::math::VEC2      uvScaleInit;
    nw::math::VEC2      uvScaleInitRand;
    f32                 uvRot;
    f32                 uvRotInit;
    f32                 uvRotInitRand;
};
static_assert(sizeof(TextureEmitterData) == 0x78, "nw::eft::TextureEmitterData size mismatch");

struct SimpleEmitterData : public CommonEmitterData
{
    //------------------------------------------------------------------------------
    //  Flags
    //------------------------------------------------------------------------------
    u8                  isPolygon;
    u8                  isFollowAll;
    u8                  isEmitterBillboardMtx;
    u8                  isWorldGravity;

    u8                  isDirectional;
    u8                  isStopEmitInFade;
    u8                  volumeTblIndex;
    u8                  volumeSweepStartRandom;

    u8                  isDisplayParent;
    u8                  emitDistEnabled;
    u8                  isVolumeLatitudeEnabled;
    u8                  dummy;

    //------------------------------------------------------------------------------
    //  Various Settings
    //------------------------------------------------------------------------------
    PtclRotType         ptclRotType;
    PtclFollowType      ptclFollowType;
    CombinerType        colorCombinerType;
    AlphaCombinerType   alphaCombinerType;
    s32                 drawPath;
    DisplaySideType     displaySide;
    f32                 dynamicsRandom;

    nw::math::MTX34     transformSRT;
    nw::math::MTX34     transformRT;

    nw::math::VEC3      scale;
    nw::math::VEC3      rot;
    nw::math::VEC3      trans;

    nw::math::VEC3      rotRnd;
    nw::math::VEC3      transRnd;

    //------------------------------------------------------------------------------
    //  Emitter
    //------------------------------------------------------------------------------
    BlendType           blendType;
    ZBufATestType       zBufATestType;
    VolumeType          volumeType;
    nw::math::VEC3      volumeRadius;
    s32                 volumeSweepStart;
    u32                 volumeSweepParam;
    f32                 volumeCaliber;
    f32                 volumeLatitude;
    nw::math::VEC3      volumeLatitudeDir;
    f32                 lineCenter;
    nw::math::VEC3      formScale;

    nw::ut::FloatColor  color0;
    nw::ut::FloatColor  color1;
    f32                 alpha;

    f32                 emitDistUnit;
    f32                 emitDistMax;
    f32                 emitDistMin;
    f32                 emitDistMargin;

    //------------------------------------------------------------------------------
    //  Emission
    //------------------------------------------------------------------------------
    f32                 emitRate;
    s32                 startFrame;
    s32                 endFrame;
    s32                 lifeStep;
    s32                 lifeStepRnd;
    f32                 figureVel;
    f32                 emitterVel;
    f32                 initVelRnd;
    nw::math::VEC3      emitterVelDir;
    f32                 emitterVelDirAngle;
    nw::math::VEC3      spreadVec;
    f32                 airRegist;
    nw::math::VEC3      gravity;
    f32                 xzDiffusionVel;
    f32                 initPosRand;

    //------------------------------------------------------------------------------
    //  Particle
    //------------------------------------------------------------------------------
    s32                 ptclLife;
    s32                 ptclLifeRnd;
    MeshType            meshType;
    BillboardType       billboardType;
    nw::math::VEC2      rotBasis;
    f32                 toCameraOffset;

    //------------------------------------------------------------------------------
    //  Texture
    //------------------------------------------------------------------------------
    TextureEmitterData  textureData[EFT_TEXTURE_SLOT_BIN_MAX];

    //------------------------------------------------------------------------------
    //  Particle Color
    //------------------------------------------------------------------------------
    ColorCalcType       colorCalcType[EFT_COLOR_KIND_MAX];
    nw::ut::FloatColor  color[EFT_COLOR_KIND_MAX][3];
    s32                 colorSection1[EFT_COLOR_KIND_MAX];
    s32                 colorSection2[EFT_COLOR_KIND_MAX];
    s32                 colorSection3[EFT_COLOR_KIND_MAX];
    s32                 colorNumRepeat[EFT_COLOR_KIND_MAX];
    s32                 colorRepeatStartRand[EFT_COLOR_KIND_MAX];
    f32                 colorScale;

    //------------------------------------------------------------------------------
    //  Particle Alpha
    //------------------------------------------------------------------------------
    f32                 initAlpha;
    f32                 diffAlpha21;
    f32                 diffAlpha32;
    s32                 alphaSection1;
    s32                 alphaSection2;

    //------------------------------------------------------------------------------
    //  Combiner
    //------------------------------------------------------------------------------
    ColorBlendType      texture1ColorBlend;
    ColorBlendType      primitiveColorBlend;
    ColorBlendType      texture1AlphaBlend;
    ColorBlendType      primitiveAlphaBlend;

    //------------------------------------------------------------------------------
    //  Particle Scale
    //------------------------------------------------------------------------------
    s32                 scaleSection1;
    s32                 scaleSection2;
    f32                 scaleRand;
    nw::math::VEC2      baseScale;
    nw::math::VEC2      initScale;
    nw::math::VEC2      diffScale21;
    nw::math::VEC2      diffScale32;

    //------------------------------------------------------------------------------
    //  Particle Rotation
    //------------------------------------------------------------------------------
    nw::math::VEC3      initRot;
    nw::math::VEC3      initRotRand;
    nw::math::VEC3      rotVel;
    nw::math::VEC3      rotVelRand;
    f32                 rotRegist;

    //------------------------------------------------------------------------------
    //  Fade Out
    //------------------------------------------------------------------------------
    f32                 alphaAddInFade;

    //------------------------------------------------------------------------------
    //  Shader
    //------------------------------------------------------------------------------
    u8                  shaderType;
    u8                  userShaderSetting;
    u8                  shaderUseSoftEdge;
    u8                  shaderApplyAlphaToRefract;
    f32                 shaderParam0;
    f32                 shaderParam1;
    f32                 softFadeDistance;
    f32                 softVolumeParam;
    u8                  userShaderDefine1[16];
    u8                  userShaderDefine2[16];
    u32                 userShaderFlag;
    u32                 userShaderSwitchFlag;
    UserShaderParam     userShaderParam;
};
static_assert(sizeof(SimpleEmitterData) == 0x6F4, "nw::eft::SimpleEmitterData size mismatch");

struct ComplexEmitterData : public SimpleEmitterData
{
    u32                 childFlg;

    u16                 fieldFlg;
    u16                 fluctuationFlg;
    u16                 stripeFlg;
    u16                 dummy;

    u16                 childDataOffset;
    u16                 fieldDataOffset;
    u16                 fluctuationDataOffset;
    u16                 stripeDataOffset;

    s32                 emitterDataSize;
};
static_assert(sizeof(ComplexEmitterData) == 0x70C, "nw::eft::ComplexEmitterData size mismatch");

struct ChildData
{
    s32                 childEmitRate;
    s32                 childEmitTiming;
    s32                 childLife;
    s32                 childEmitStep;

    f32                 childVelInheritRate;
    f32                 childFigureVel;
    nw::math::VEC3      childRandVel;
    f32                 childInitPosRand;
    PrimitiveFigure     childPrimitiveFigure;
    f32                 childDynamicsRandom;

    BlendType           childBlendType;
    MeshType            childMeshType;
    BillboardType       childBillboardType;
    ZBufATestType       childZBufATestType;
    TextureRes          childTex;
    DisplaySideType     childDisplaySide;

    nw::math::VEC3      childColor0;
    nw::math::VEC3      childColor1;
    f32                 childColorScale;

    ColorBlendType      primitiveColorBlend;
    ColorBlendType      primitiveAlphaBlend;

    f32                 childAlpha;
    f32                 childAlphaTarget;
    f32                 childAlphaInit;

    f32                 childScaleInheritRate;
    nw::math::VEC2      childScale;
    f32                 childScaleRand;

    PtclRotType         childRotType;
    nw::math::VEC3      childInitRot;
    nw::math::VEC3      childInitRotRand;
    nw::math::VEC3      childRotVel;
    nw::math::VEC3      childRotVelRand;
    f32                 childRotRegist;

    nw::math::VEC2      childRotBasis;

    nw::math::VEC3      childGravity;
    s32                 childAlphaStartFrame;
    s32                 childAlphaBaseFrame;
    s32                 childScaleStartFrame;
    nw::math::VEC2      childScaleTarget;

    u16                 childNumTexPat;
    u8                  childNumTexDivX;
    u8                  childNumTexDivY;
    f32                 childTexUScale;
    f32                 childTexVScale;
    u8                  childTexPatTbl[EFT_TEXTURE_PATTERN_NUM];
    s16                 childTexPatFreq;
    s16                 childTexPatTblUse;
    u8                  isChildTexPatAnimClump;
    u8                  dummy2[3];

    CombinerType        childCombinerType;
    AlphaCombinerType   childAlphaCombinerType;
    f32                 childAirRegist;

    //------------------------------------------------------------------------------
    //  Shader
    //------------------------------------------------------------------------------
    u8                  childShaderType;
    u8                  childUserShaderSetting;
    u8                  childShaderUseSoftEdge;
    u8                  childShaderApplyAlphaToRefract;
    f32                 childShaderParam0;
    f32                 childShaderParam1;
    f32                 childSoftFadeDistance;
    f32                 childSoftVolumeParam;
    u8                  childUserShaderDefine1[16];
    u8                  childUserShaderDefine2[16];
    u32                 childUserShaderFlag;
    u32                 childUserShaderSwitchFlag;
    UserShaderParam     childUserShaderParam;
};
static_assert(sizeof(ChildData) == 0x2FC, "nw::eft::ChildData size mismatch");

struct FieldRandomData
{
    s32                 fieldRandomBlank;
    nw::math::VEC3      fieldRandomVelAdd;
};
static_assert(sizeof(FieldRandomData) == 0x10, "nw::eft::FieldRandomData size mismatch");

struct FieldMagnetData
{
    f32                 fieldMagnetPower;
    nw::math::VEC3      fieldMagnetPos;
    u32                 fieldMagnetFlg;
};
static_assert(sizeof(FieldMagnetData) == 0x14, "nw::eft::FieldMagnetData size mismatch");

struct FieldSpinData
{
    s32                 fieldSpinRotate;
    s32                 fieldSpinAxis;
    f32                 fieldSpinOuter;
};
static_assert(sizeof(FieldSpinData) == 0xC, "nw::eft::FieldSpinData size mismatch");

struct FieldCollisionData
{
    u16                 fieldCollisionType;
    u16                 fieldCollisionIsWorld;
    f32                 fieldCollisionCoord;
    f32                 fieldCollisionCoef;
};
static_assert(sizeof(FieldCollisionData) == 0xC, "nw::eft::FieldCollisionData size mismatch");

struct FieldConvergenceData
{
    nw::math::VEC3          fieldConvergencePos;
    f32                     fieldConvergenceRatio;
};
static_assert(sizeof(FieldConvergenceData) == 0x10, "nw::eft::FieldConvergenceData size mismatch");

struct FieldPosAddData
{
    nw::math::VEC3      fieldPosAdd;
};
static_assert(sizeof(FieldPosAddData) == 0xC, "nw::eft::FieldPosAddData size mismatch");

struct FluctuationData
{
    f32                 fluctuationScale;
    f32                 fluctuationFreq;
    u32                 fluctuationPhaseRnd;
};
static_assert(sizeof(FluctuationData) == 0xC, "nw::eft::FluctuationData size mismatch");

struct StripeData
{
    StripeType              stripeType;
    StripeOption            stripeOption;
    StripeConnectOption     stripeConnectOpt;
    StripeTexCoordOption    stripeTexCoordOpt;
    s32                     stripeNumHistory;
    s32                     stripeDivideNum;
    f32                     stripeStartAlpha;
    f32                     stripeEndAlpha;
    nw::math::VEC2          stripeUVScroll;
    s32                     stripeHistoryStep;
    f32                     stripeHistoryInterpolate;
    f32                     stripeDirInterpolate;
};
static_assert(sizeof(StripeData) == 0x34, "nw::eft::StripeData size mismatch");

} } // namespace nw::eft

#endif // EFT_DATA_H_
