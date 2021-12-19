#include <cafe/gfd.h>

#ifdef __cplusplus
extern "C" {
#endif

GX2VertexShader* GFDGetVertexShaderPointer(u32 index, const void* file)
{
    GX2VertexShader* shader = NULL;
    u32 currShaderIdx = 0;
    u32 currProgramIdx = 0;

    //if (!_GFDCheckHeaderVersions(file)) <-- Assume file header has already been checked
    //    return NULL;

    u8* ptr = (u8*)file + ((GFDHeader*)file)->size;
    GFDBlockHeader* block = (GFDBlockHeader*)ptr;

    while (true) // _GFDCheckBlockHeaderMagicVersions(block)
    {
        block = (GFDBlockHeader*)ptr;
        ptr += block->size;

        switch(block->type)
        {
        case GFD_BLOCK_TYPE_GX2_VSH_HEADER:
            if (index == currShaderIdx)
            {
                shader = (GX2VertexShader*)ptr;
                if (!_GFDRelocateBlock(block->dataSize, shader))
                    return NULL;
            }
            currShaderIdx++;
            break;

        case GFD_BLOCK_TYPE_GX2_VSH_PROGRAM:
            if (index == currProgramIdx)
            {
                if ((u32)ptr % GX2_SHADER_ALIGNMENT)
                    return NULL;

                if (shader == NULL)
                    return NULL;

                shader->shader_data = ptr;
            }
            currProgramIdx++;
        }

        ptr += block->dataSize;

        if (currShaderIdx > index && currProgramIdx > index)
            break;

        if (block->type == GFD_BLOCK_TYPE_END)
            break;
    }

    if (shader != NULL && shader->shader_data == NULL)
        return NULL;

    return shader;
}

GX2PixelShader *GFDGetPixelShaderPointer(u32 index, const void *file)
{
    GX2PixelShader *shader = NULL;
    u32 currShaderIdx = 0;
    u32 currProgramIdx = 0;

    //if (!_GFDCheckHeaderVersions(file)) <-- Assume file header has already been checked
    //    return NULL;

    u8* ptr = (u8*)file + ((GFDHeader*)file)->size;
    GFDBlockHeader* block = (GFDBlockHeader *)ptr;

    while (true) // _GFDCheckBlockHeaderMagicVersions(block)
    {
        block = (GFDBlockHeader*)ptr;
        ptr += block->size;

        switch(block->type)
        {
        case GFD_BLOCK_TYPE_GX2_PSH_HEADER:
            if (index == currShaderIdx)
            {
                shader = (GX2PixelShader*)ptr;
                if (!_GFDRelocateBlock(block->dataSize, shader))
                    return NULL;
            }
            currShaderIdx++;
            break;

        case GFD_BLOCK_TYPE_GX2_PSH_PROGRAM:
            if (index == currProgramIdx)
            {
                if ((u32)ptr % GX2_SHADER_ALIGNMENT)
                    return NULL;

                if (shader == NULL)
                    return NULL;

                shader->shader_data = ptr;
            }
            currProgramIdx++;
        }

        ptr += block->dataSize;

        if (currShaderIdx > index && currProgramIdx > index)
            break;

        if (block->type == GFD_BLOCK_TYPE_END)
            break;
    }

    if (shader != NULL && shader->shader_data == NULL)
        return NULL;

    return shader;
}

#ifdef __cplusplus
}
#endif
