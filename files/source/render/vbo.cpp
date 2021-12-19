#include "vbo.h"

static inline u32 VarTypeToStreamCount(VBO::VarType type)
{
    switch (type)
    {
    case VBO::VAR_TYPE_BOOL:
    case VBO::VAR_TYPE_INT:
    case VBO::VAR_TYPE_UINT:
    case VBO::VAR_TYPE_FLOAT:
    case VBO::VAR_TYPE_VEC2:
    case VBO::VAR_TYPE_VEC3:
    case VBO::VAR_TYPE_VEC4:
    case VBO::VAR_TYPE_BVEC2:
    case VBO::VAR_TYPE_BVEC3:
    case VBO::VAR_TYPE_BVEC4:
    case VBO::VAR_TYPE_IVEC2:
    case VBO::VAR_TYPE_UVEC2:
    case VBO::VAR_TYPE_IVEC3:
    case VBO::VAR_TYPE_UVEC3:
    case VBO::VAR_TYPE_IVEC4:
    case VBO::VAR_TYPE_UVEC4:
        return 1;
    case VBO::VAR_TYPE_MAT2:
    case VBO::VAR_TYPE_MAT2X3:
    case VBO::VAR_TYPE_MAT2X4:
        return 2;
    case VBO::VAR_TYPE_MAT3X2:
    case VBO::VAR_TYPE_MAT3:
    case VBO::VAR_TYPE_MAT3X4:
        return 3;
    case VBO::VAR_TYPE_MAT4X2:
    case VBO::VAR_TYPE_MAT4X3:
    case VBO::VAR_TYPE_MAT4:
        return 4;
    default:
        return 0;
    }
}

static inline VBO::AttribFormat VarTypeToAttribFormat(VBO::VarType type, bool normalized)
{
    switch (type)
    {
    case VBO::VAR_TYPE_FLOAT:
        return VBO::ATTRIB_FORMAT_32_FLOAT;
    case VBO::VAR_TYPE_VEC2:
    case VBO::VAR_TYPE_MAT2:
    case VBO::VAR_TYPE_MAT3X2:
    case VBO::VAR_TYPE_MAT4X2:
        return VBO::ATTRIB_FORMAT_32_32_FLOAT;
    case VBO::VAR_TYPE_VEC3:
    case VBO::VAR_TYPE_MAT2X3:
    case VBO::VAR_TYPE_MAT3:
    case VBO::VAR_TYPE_MAT4X3:
        return VBO::ATTRIB_FORMAT_32_32_32_FLOAT;
    case VBO::VAR_TYPE_VEC4:
    case VBO::VAR_TYPE_MAT2X4:
    case VBO::VAR_TYPE_MAT3X4:
    case VBO::VAR_TYPE_MAT4:
        return VBO::ATTRIB_FORMAT_32_32_32_32_FLOAT;
    }

    if (normalized)
    {
        switch (type)
        {
        case VBO::VAR_TYPE_BOOL:
            return VBO::ATTRIB_FORMAT_8_UNORM;
        case VBO::VAR_TYPE_INT:
        case VBO::VAR_TYPE_UINT:
            return VBO::ATTRIB_FORMAT_INVALID; // Not supported
        case VBO::VAR_TYPE_BVEC2:
            return VBO::ATTRIB_FORMAT_8_8_UNORM;
        case VBO::VAR_TYPE_BVEC3:
            return VBO::ATTRIB_FORMAT_INVALID; // Not supported
        case VBO::VAR_TYPE_BVEC4:
            return VBO::ATTRIB_FORMAT_8_8_8_8_UNORM;
        case VBO::VAR_TYPE_IVEC2:
        case VBO::VAR_TYPE_UVEC2:
        case VBO::VAR_TYPE_IVEC3:
        case VBO::VAR_TYPE_UVEC3:
        case VBO::VAR_TYPE_IVEC4:
        case VBO::VAR_TYPE_UVEC4:
            return VBO::ATTRIB_FORMAT_INVALID; // Not supported
        }
    }
    else
    {
        switch (type)
        {
        case VBO::VAR_TYPE_BOOL:
            return VBO::ATTRIB_FORMAT_8_UINT;
        case VBO::VAR_TYPE_INT:
            return VBO::ATTRIB_FORMAT_32_SINT;
        case VBO::VAR_TYPE_UINT:
            return VBO::ATTRIB_FORMAT_32_UINT;
        case VBO::VAR_TYPE_BVEC2:
            return VBO::ATTRIB_FORMAT_8_8_UINT;
        case VBO::VAR_TYPE_BVEC3:
            return VBO::ATTRIB_FORMAT_INVALID; // Not supported
        case VBO::VAR_TYPE_BVEC4:
            return VBO::ATTRIB_FORMAT_8_8_8_8_UINT;
        case VBO::VAR_TYPE_IVEC2:
            return VBO::ATTRIB_FORMAT_32_32_SINT;
        case VBO::VAR_TYPE_UVEC2:
            return VBO::ATTRIB_FORMAT_32_32_UINT;
        case VBO::VAR_TYPE_IVEC3:
            return VBO::ATTRIB_FORMAT_32_32_32_SINT;
        case VBO::VAR_TYPE_UVEC3:
            return VBO::ATTRIB_FORMAT_32_32_32_UINT;
        case VBO::VAR_TYPE_IVEC4:
            return VBO::ATTRIB_FORMAT_32_32_32_32_SINT;
        case VBO::VAR_TYPE_UVEC4:
            return VBO::ATTRIB_FORMAT_32_32_32_32_UINT;
        }
    }

    return VBO::ATTRIB_FORMAT_INVALID;
}

static inline u32 AttribFormatByteSize(VBO::AttribFormat format)
{
    switch (format)
    {
    case VBO::ATTRIB_FORMAT_8_UNORM:
    case VBO::ATTRIB_FORMAT_8_UINT:
        return 1;
    case VBO::ATTRIB_FORMAT_8_8_UNORM:
    case VBO::ATTRIB_FORMAT_8_8_UINT:
        return 2;
    case VBO::ATTRIB_FORMAT_32_UINT:
    case VBO::ATTRIB_FORMAT_32_SINT:
    case VBO::ATTRIB_FORMAT_32_FLOAT:
    case VBO::ATTRIB_FORMAT_8_8_8_8_UNORM:
    case VBO::ATTRIB_FORMAT_8_8_8_8_UINT:
        return 4;
    case VBO::ATTRIB_FORMAT_32_32_UINT:
    case VBO::ATTRIB_FORMAT_32_32_SINT:
    case VBO::ATTRIB_FORMAT_32_32_FLOAT:
        return 8;
    case VBO::ATTRIB_FORMAT_32_32_32_UINT:
    case VBO::ATTRIB_FORMAT_32_32_32_SINT:
    case VBO::ATTRIB_FORMAT_32_32_32_FLOAT:
        return 12;
    case VBO::ATTRIB_FORMAT_32_32_32_32_UINT:
    case VBO::ATTRIB_FORMAT_32_32_32_32_SINT:
    case VBO::ATTRIB_FORMAT_32_32_32_32_FLOAT:
        return 16;
    default:
        return 0;
    }
}

static inline u32 AttribFormatMask(VBO::AttribFormat format)
{
    return attribute_dest_comp_selector[format & 0x1F];
}

VBO::VBO(u32 bufferIdx)
    : mBufferIdx(bufferIdx)
    , mBufferDataSize(0)
    , mStreamUsedCount(0)
    , mBuilt(false)
    , mFetchShaderBufSize(0)
    , mFetchShaderBuf(nullptr)
{
}

VBO::~VBO()
{
    if (mBuilt && mFetchShaderBuf)
    {
        delete[] mFetchShaderBuf;
        mFetchShaderBuf = nullptr;
    }
}

bool VBO::setVertexAttrib(u32 index, u32 offset, VarType type, u32 arrayCount, bool normalized, u32 divisor)
{
    if (mBuilt)
        return false;

    if (arrayCount == 0)
        arrayCount = 1;

    const u32 elemStreamCount = VarTypeToStreamCount(type);
    if (elemStreamCount == 0)
        return false;

    if (mStreamUsedCount + arrayCount * elemStreamCount > MAX_STREAM_COUNT)
        return false;

    const AttribFormat attribFormat = VarTypeToAttribFormat(type, normalized);
    if (attribFormat == VBO::ATTRIB_FORMAT_INVALID)
        return false;

    const u32 streamByteSize = AttribFormatByteSize(attribFormat);
    const u32 attribFormatMask = AttribFormatMask(attribFormat);

    const u32 indexType = (divisor == 0) ? GX2_ATTRIB_INDEX_PER_VERTEX
                                         : GX2_ATTRIB_INDEX_PER_INSTANCE;

    GX2AttribStream* streams = &mStreams[mStreamUsedCount];

    for (u32 i = 0; i < arrayCount; i++)
    {
        for (u32 j = 0; j < elemStreamCount; j++)
        {
            GX2AttribStream& stream = *streams++; // streams[i * arrayCount + j]
            stream.location = index++;            // index + i * arrayCount + j
            stream.buffer = mBufferIdx;
            stream.offset = offset; offset += streamByteSize; // offset + (i * arrayCount + j) * streamByteSize
            stream.format = attribFormat;
            stream.destination_selector = attribFormatMask;
            stream.endian_swap = GX2_ENDIANSWAP_DEFAULT;
            stream.index_type = indexType;
            stream.divisor = divisor;
        }
    }

    mStreamUsedCount += arrayCount * elemStreamCount;

    return true;
}

void VBO::build(sead::Heap* heap)
{
    if (mBuilt)
        return;

    mFetchShaderBufSize = GX2CalcFetchShaderSizeEx(
        mStreamUsedCount,
        GX2_FETCH_SHADER_TESSELATION_NONE, // No Tessellation
        GX2_TESSELLATION_MODE_DISCRETE     // ^^^^^^^^^^^^^^^
    );
    mFetchShaderBuf = new (heap, GX2_SHADER_ALIGNMENT) u8[mFetchShaderBufSize];

    GX2InitFetchShaderEx(
        &mFetchShader,
        mFetchShaderBuf,
        mStreamUsedCount,
        mStreams,
        GX2_FETCH_SHADER_TESSELATION_NONE, // No Tessellation
        GX2_TESSELLATION_MODE_DISCRETE     // ^^^^^^^^^^^^^^^
    );

    GX2Invalidate(GX2_INVALIDATE_CPU_SHADER, mFetchShader.shader_program, mFetchShader.shader_size);

    mBuilt = true;
}

void VBO::bindBufferData(const void* bufferData, u32 size, u32 stride)
{
    mBufferData = bufferData;
    mBufferDataSize = size;
    mStride = stride;

    if (bufferData && size)
        GX2Invalidate(GX2_INVALIDATE_CPU_ATTRIB_BUFFER, (void*)bufferData, size);
}

void VBO::bind() const
{
    if (!mBuilt || !mBufferData)
        return;

    GX2SetAttribBuffer(mBufferIdx, mBufferDataSize, mStride, mBufferData);
    GX2SetFetchShader(&mFetchShader);
}
