#pragma once

#include "sead.h"
#include "util/mtx34.h"
#include "resarchive.h"

class Model     // this has 2 base classes
{
    SEAD_RTTI_BASE(Model)

public:
    virtual void vf1C();
    virtual void CalcView(int viewIndex, const Mtx34& cameraMtx);
    virtual void vf2C();
    virtual void vf34();
    virtual void vf3C();
    virtual void vf44();
    virtual void vf4C();
    virtual void vf54();
    virtual void vf5C();
    virtual void vf64();
    virtual void vf6C();                        // used during update
    virtual void vf74();                        // used during update
    virtual void setMtx(const Mtx34& mtx);
    virtual void vf84();
    virtual void setScale(const Vec3& scale);
    virtual void vf94();
    virtual void vf9C();
    virtual void vfA4();
    virtual u32 getBoneIdx(const sead::SafeString& name);
    virtual u32 getBoneName(u32 idx);
    virtual u32 getBoneCount();
    virtual void vfC4();
    virtual void vfCC();
    virtual void vfD4();
    virtual void getBoneTransform(u32 idx, Mtx34& transform);
    virtual void vfE4();
    virtual void vfEC();                        // deleted
    virtual void vfF4();
    virtual void vfFC();
    virtual void vf104();
    virtual void vf10C();
    virtual void vf114();
    virtual void vf11C();                        // deleted
    virtual void vf124();                        // deleted
    virtual void vf12C();
    virtual void vf134();
    virtual void vf13C();
    virtual void vf144();
    virtual void vf14C();
    virtual void vf154();                        // deleted
    virtual void vf15C();
    virtual void vf164();
    virtual void vf16C();
    virtual void vf174();
    virtual void vf17C();
    virtual void** getSklAnims();
    virtual void** getTexAnims();
    virtual void** getShuAnims();
    virtual void** getVisAnims();
    virtual void** getShaAnims();
};


struct Animation
{
    enum Flags
    {
        FlagRepeat  = 1 << 0,
        FlagUnk2    = 1 << 1,
        FlagIsDone  = 1 << 5,
    };

    void setRepeat(bool repeat);

    inline bool isAnimationDone() { return flags & FlagIsDone; }

    f32 startFrame; // 0    Inited to 0.0
    f32 endFrame;   // 4    Inited to 1.0
    f32 _8;         // 8    Inited to 0.0
    f32 _C;         // C    Inited to 1.0
    f32 frame;      // 10   Inited to 0.0
    f32 speed;      // 14   Inited to 1.0
    u32 flags;      // 18   Inited to FlagRepeat | FlagUnk2
};

class ModelAnimation : public Animation
{
public:
    ModelAnimation();
    virtual void calculate() = 0;
};

class SkeletalAnimation : public ModelAnimation  // size: 0x98
{
public:
    SkeletalAnimation();
    void calculate() override;

    void init(Model* model, ResArchive* archive, void* unk, sead::Heap* heap);
    void play(ResArchive* archive, const sead::SafeString& identifier);

    // nw::g3d::SkeletalAnimObj at 0x20
};

class TextureAnimation : public ModelAnimation
{
public:
    TextureAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShaderAnimation : public ModelAnimation
{
public:
    ShaderAnimation();
    void calculate() override;

    void playColorAnim(ResArchive* archive, const sead::SafeString& identifier);
    void playTexSrtAnim(ResArchive* archive, const sead::SafeString& identifier);
};

class VisibilityAnimation : public ModelAnimation
{
public:
    VisibilityAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};

class ShapeAnimation : public ModelAnimation
{
public:
    ShapeAnimation();
    void calculate() override;

    void play(ResArchive* archive, const sead::SafeString& identifier);
};


class ModelWrapper
{
public:
    ModelWrapper(Model* model, u32 numSklAnims, u32 numTexAnims, u32 numShuAnims, u32 numVisAnims, u32 numShaAnims);
    void setup(ResArchive* archive, void* unk, sead::Heap* heap);
    void updateModel();
    void updateAnimations();

    inline void setMtx(const Mtx34& mtx)
    {
        model->setMtx(mtx);
    }

    inline void setScale(const Vec3& scale)
    {
        model->setScale(scale);
    }

    inline void playSklAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < sklAnims.mSize)
            sklAnims[idx]->play(archive, identifier);
    }

    inline void playTexPatternAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < texAnims.mSize)
            texAnims[idx]->play(archive, identifier);
    }

    inline void playColorAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playColorAnim(archive, identifier);
    }

    inline void playTexSrtAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shuAnims.mSize)
            shuAnims[idx]->playTexSrtAnim(archive, identifier);
    }

    inline void playBoneVisAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < visAnims.mSize)
            visAnims[idx]->play(archive, identifier);
    }

    inline void playShapeAnim(const sead::SafeString& identifier, u32 idx)
    {
        if (idx < shaAnims.mSize)
            shaAnims[idx]->play(archive, identifier);
    }

    static inline ModelWrapper* create(const sead::SafeString& archiveIdentifier, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false)
    {
        ResArchive* archive = ResArchiveMgr::instance->get(archiveIdentifier);
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

    static inline ModelWrapper* create(ResArchive* archive, const sead::SafeString& modelIdentifier, u32 numSklAnims = 0, u32 numTexAnims = 0, u32 numShuAnims = 0, u32 numVisAnims = 0, u32 numShaAnims = 0, bool unk2 = false)
    {
        Model* model = archive->getModel(modelIdentifier, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims, unk2, nullptr);
        ModelWrapper* wrapper = new ModelWrapper(model, numSklAnims, numTexAnims, numShuAnims, numVisAnims, numShaAnims);
        wrapper->setup(archive, nullptr, nullptr);
        return wrapper;
    }

	Model* model;                                   // 0
	ResArchive* archive;                            // 4
	sead::Buffer<SkeletalAnimation*> sklAnims;      // 8
	sead::Buffer<TextureAnimation*> texAnims;       // 10
	sead::Buffer<ShaderAnimation*> shuAnims;        // 18
	sead::Buffer<VisibilityAnimation*> visAnims;    // 20
	sead::Buffer<ShapeAnimation*> shaAnims;         // 28
};
