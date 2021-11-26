#include <agl/renderer.h>
#include <gfx/seadViewport.h>

namespace agl { namespace lyr {

/* Clear TV and DRC frame buffers to black before each frame */

bool Renderer::drawTVHaxx(DisplayType display_type) const
{
    if (gpuCounter % gpuCounterPeriod)
        return false;

    if (flags.isOffBit(4) && flags.isOffBit(0))
    {
        agl::RenderBuffer* tvBuffer = renderBuffers[cDisplayType_Top_TV];
        if (tvBuffer != NULL)
        {
            u32 clearFlags = 1;
            if (tvBuffer->renderTargetDepth != NULL)
                clearFlags = 3;

            tvBuffer->bind();

            sead::Viewport viewport = sead::Viewport(*tvBuffer);
            viewport.apply(*tvBuffer);

            sead::Color4f clearColor = sead::Color4f(0.0f, 0.0f, 0.0f, 1.0f);
            tvBuffer->clear(clearFlags, clearColor, 1.0f, 0);
        }

        // Render buffer clear bit
        flags.resetBit(8);
    }

    // This must return true
    return draw(display_type);
}

bool Renderer::drawDRCHaxx(DisplayType display_type) const
{
    if (gpuCounter % gpuCounterPeriod)
        return false;

    if (flags.isOffBit(4) && flags.isOffBit(0))
    {
        agl::RenderBuffer* drcBuffer = renderBuffers[cDisplayType_Bottom_DRC];
        if (drcBuffer != NULL)
        {
            u32 clearFlags = 1;
            if (drcBuffer->renderTargetDepth != NULL)
                clearFlags = 3;

            drcBuffer->bind();

            sead::Viewport viewport = sead::Viewport(*drcBuffer);
            viewport.apply(*drcBuffer);

            sead::Color4f clearColor = sead::Color4f(0.0f, 0.0f, 0.0f, 1.0f);
            drcBuffer->clear(clearFlags, clearColor, 1.0f, 0);
        }

        // Render buffer clear bit
        flags.resetBit(8);
    }

    // This must return true
    return draw(display_type);
}

} }
