#ifndef SEAD_GRAPHICS_H_
#define SEAD_GRAPHICS_H_

#include <cafe.h>

namespace sead {

class Graphics
{
public:
    enum DevicePosture
    {
        cDevicePosture_Same             = 0,
        cDevicePosture_RotateRight      = 1,
        cDevicePosture_RotateLeft       = 2,
        cDevicePosture_RotateHalfAround = 3,
        cDevicePosture_FlipX            = 4,
        cDevicePosture_FlipY            = 5,
        cDevicePosture_FlipXY           = 3,
        cDevicePosture_Invalid          = 4
    };

    enum DepthFunc
    {
        cDepthFunc_Never        = GX2_COMPARE_NEVER,
        cDepthFunc_Less         = GX2_COMPARE_LESS,
        cDepthFunc_Equal        = GX2_COMPARE_EQUAL,
        cDepthFunc_LessEqual    = GX2_COMPARE_LEQUAL,
        cDepthFunc_Greater      = GX2_COMPARE_GREATER,
        cDepthFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
        cDepthFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
        cDepthFunc_Always       = GX2_COMPARE_ALWAYS
    };

    enum CullingMode
    {
        cCullingMode_Front = 0,
        cCullingMode_Back  = 1,
        cCullingMode_None  = 2,
        cCullingMode_All   = 3
    };

    enum BlendFactor
    {
        cBlendFactor_Zero             = GX2_BLEND_ZERO,
        cBlendFactor_One              = GX2_BLEND_ONE,
        cBlendFactor_SrcColor         = GX2_BLEND_SRC_COLOR,
        cBlendFactor_InvSrcColor      = GX2_BLEND_ONE_MINUS_SRC_COLOR,
        cBlendFactor_SrcAlpha         = GX2_BLEND_SRC_ALPHA,
        cBlendFactor_InvSrcAlpha      = GX2_BLEND_ONE_MINUS_SRC_ALPHA,
        cBlendFactor_DstAlpha         = GX2_BLEND_DST_ALPHA,
        cBlendFactor_InvDstAlpha      = GX2_BLEND_ONE_MINUS_DST_ALPHA,
        cBlendFactor_DstColor         = GX2_BLEND_DST_COLOR,
        cBlendFactor_InvDstColor      = GX2_BLEND_ONE_MINUS_DST_COLOR,
        cBlendFactor_SrcAlphaSaturate = GX2_BLEND_SRC_ALPHA_SATURATE,
        cBlendFactor_ConstantColor    = GX2_BLEND_CONSTANT_COLOR,
        cBlendFactor_InvConstantColor = GX2_BLEND_ONE_MINUS_CONSTANT_COLOR,
        cBlendFactor_ConstantAlpha    = GX2_BLEND_CONSTANT_ALPHA,
        cBlendFactor_InvConstantAlpha = GX2_BLEND_ONE_MINUS_CONSTANT_ALPHA
    };

    enum BlendEquation
    {
        cBlendEquation_Add        = GX2_BLEND_COMBINE_ADD,
        cBlendEquation_Sub        = GX2_BLEND_COMBINE_SRC_MINUS_DST,
        cBlendEquation_Min        = GX2_BLEND_COMBINE_MIN,
        cBlendEquation_Max        = GX2_BLEND_COMBINE_MAX,
        cBlendEquation_ReverseSub = GX2_BLEND_COMBINE_DST_MINUS_SRC
    };

    enum AlphaFunc
    {
        cAlphaFunc_Never        = GX2_COMPARE_NEVER,
        cAlphaFunc_Less         = GX2_COMPARE_LESS,
        cAlphaFunc_Equal        = GX2_COMPARE_EQUAL,
        cAlphaFunc_LessEqual    = GX2_COMPARE_LEQUAL,
        cAlphaFunc_Greater      = GX2_COMPARE_GREATER,
        cAlphaFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
        cAlphaFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
        cAlphaFunc_Always       = GX2_COMPARE_ALWAYS
    };

    enum StencilFunc
    {
        cStencilFunc_Never        = GX2_COMPARE_NEVER,
        cStencilFunc_Less         = GX2_COMPARE_LESS,
        cStencilFunc_Equal        = GX2_COMPARE_EQUAL,
        cStencilFunc_LessEqual    = GX2_COMPARE_LEQUAL,
        cStencilFunc_Greater      = GX2_COMPARE_GREATER,
        cStencilFunc_NotEqual     = GX2_COMPARE_NOTEQUAL,
        cStencilFunc_GreaterEqual = GX2_COMPARE_GEQUAL,
        cStencilFunc_Always       = GX2_COMPARE_ALWAYS
    };

    enum StencilOp
    {
        cStencilOp_Keep          = GX2_STENCIL_KEEP,
        cStencilOp_Zero          = GX2_STENCIL_ZERO,
        cStencilOp_Replace       = GX2_STENCIL_REPLACE,
        cStencilOp_Increment     = GX2_STENCIL_INCR,
        cStencilOp_Decrement     = GX2_STENCIL_DECR,
        cStencilOp_Invert        = GX2_STENCIL_INVERT,
        cStencilOp_IncrementWrap = GX2_STENCIL_INCR_WRAP,
        cStencilOp_DecrementWrap = GX2_STENCIL_DECR_WRAP
    };

    enum PolygonMode
    {
        cPolygonMode_Point = GX2_POLYGON_MODE_POINT,
        cPolygonMode_Line  = GX2_POLYGON_MODE_LINE,
        cPolygonMode_Fill  = GX2_POLYGON_MODE_TRIANGLE
    };
};

} // namespace sead

#endif // SEAD_GRAPHICS_H_
