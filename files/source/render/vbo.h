#pragma once

#include <cafe.h>

#include <heap/seadHeap.h>

class VBO
{
public:
    enum VarType
    {
        // BOOL types can be used interchangeably between bool and u8 input data
        // INT refers to s32 input data
        // UINT refers to u32 input data
        // FLOAT refers to f32 input data
        // All matrices are FLOAT
        // TODO: s8, u16 and s16 input data

        VAR_TYPE_BOOL = 1,
        VAR_TYPE_INT,
        VAR_TYPE_UINT,
        VAR_TYPE_FLOAT,
        VAR_TYPE_VEC2 = 9,
        VAR_TYPE_VEC3,
        VAR_TYPE_VEC4,
        VAR_TYPE_BVEC2,
        VAR_TYPE_BVEC3,
        VAR_TYPE_BVEC4,
        VAR_TYPE_IVEC2,
        VAR_TYPE_IVEC3,
        VAR_TYPE_IVEC4,
        VAR_TYPE_UVEC2,
        VAR_TYPE_UVEC3,
        VAR_TYPE_UVEC4,
        VAR_TYPE_MAT2,
        VAR_TYPE_MAT2X3,
        VAR_TYPE_MAT2X4,
        VAR_TYPE_MAT3X2,
        VAR_TYPE_MAT3,
        VAR_TYPE_MAT3X4,
        VAR_TYPE_MAT4X2,
        VAR_TYPE_MAT4X3,
        VAR_TYPE_MAT4
    };

    enum AttribFormat
    {
        ATTRIB_FORMAT_8_UNORM           = 0x000,
        ATTRIB_FORMAT_8_UINT            = 0x100,
        ATTRIB_FORMAT_8_8_UNORM         = 0x004,
        ATTRIB_FORMAT_8_8_UINT          = 0x104,
        ATTRIB_FORMAT_32_UINT           = 0x105,
        ATTRIB_FORMAT_32_SINT           = 0x305,
        ATTRIB_FORMAT_32_FLOAT          = 0x806,
        ATTRIB_FORMAT_32_32_UINT        = 0x10C,
        ATTRIB_FORMAT_32_32_SINT        = 0x30C,
        ATTRIB_FORMAT_32_32_FLOAT       = 0x80D,
        ATTRIB_FORMAT_8_8_8_8_UNORM     = 0x00A,
        ATTRIB_FORMAT_8_8_8_8_UINT      = 0x10A,
        ATTRIB_FORMAT_32_32_32_UINT     = 0x110,
        ATTRIB_FORMAT_32_32_32_SINT     = 0x310,
        ATTRIB_FORMAT_32_32_32_FLOAT    = 0x811,
        ATTRIB_FORMAT_32_32_32_32_UINT  = 0x112,
        ATTRIB_FORMAT_32_32_32_32_SINT  = 0x312,
        ATTRIB_FORMAT_32_32_32_32_FLOAT = 0x813,

        ATTRIB_FORMAT_INVALID  = 0xFFFFFFFF
    };

private:
    enum
    {
        MAX_STREAM_COUNT = 32
    };

public:
    // bufferIdx: index of attribute buffer to use (0-15)
    //            Unlike GX2, only 1 buffer per drawcall (limitation of this abstraction)
    VBO(u32 bufferIdx);
    ~VBO();

    // Set definition of a vertex attribute
    // index: index of vertex attribute in the shader (aka location)
    // offset: offset of the attribute data of first vertex within the specified buffer
    // type: glsl element type of the vertex attribute
    // arrayCount: element array count, e.g. 5 if type was int[5]
    // normalized: if type is fixed-point, normalize data to float in ranges [0.0, 1.0] or [-1.0, 1.0] (depending on signedness of type)
    // divisor: number of instances that will pass between advancing of the attribute data
    //          = 0 -> attribute data will advance once per vertex
    //          > 0 -> attribute data will advance once per "divisor" instances
    //          Other than 0 and 1, you can have up to two unique divisors per VBO (HW limit)
    bool setVertexAttrib(u32 index, u32 offset, VarType type, u32 arrayCount = 1, bool normalized = false, u32 divisor = 0);

    // Build the structure of this VBO
    // *Must* be called after all vertex attributes have been set
    void build(sead::Heap* heap = nullptr);

    // Bind buffer data
    // As long as this VBO exists, user must *not* free the buffer data passed
    // stride: number of bytes between each vertex
    void bindBufferData(const void* bufferData, u32 size, u32 stride);

    // Get the data bound to the specified buffer through this VBO
    const void* getBufferData() const;

    // Bind the VBO
    // Must be done *after* shader is bound
    void bind() const;

private:
    u32 mBufferIdx;
    const void* mBufferData;
    u32 mBufferDataSize;
    u32 mStride;

    GX2AttribStream mStreams[MAX_STREAM_COUNT];
    u32 mStreamUsedCount;

    bool mBuilt;
    GX2FetchShader mFetchShader;
    u32 mFetchShaderBufSize;
    u8* mFetchShaderBuf;
};
