#pragma once

#include <nw/g3d.h>
#include <sead/array.h>
#include <sead/heap.h>
#include <sead/string.h>
#include <mtx.h>

class ModelObj {
public:
    /* Incomplete */
    virtual void vf0C();
    virtual void vf14();
    virtual void vf1C();
    virtual void vf24();
    virtual void vf2C();
    virtual void vf34();
    virtual void vf3C();
    virtual void vf44();
    virtual void vf4C();
    virtual void vf54();
    virtual void vf5C();
    virtual void vf64();
    virtual void vf6C();
    virtual void vf74();
    virtual void setMatrix(Mtx *);
    virtual void vf84();
    virtual void setScale(Vec3 *);
    /* ........ */
};

class ResArchive {
public:
    /* Incomplete */
    ModelObj *getModel(sead::String filename, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool, sead::Heap *heap);
};

class Animation {
public:
    float startFrame;
    float endFrame;
    float _8;
    float _C;
    float frame;
    float speed;
    unsigned int flags;

    void setRepeat(bool);
    void update();
};

class ModelAnimation : public Animation {
public:
    void update();

    virtual void Calc() = 0;
};

class SkeletalAnim : public ModelAnimation {
public:
    nw::g3d::SkeletalAnimObj animObj;
    char _58[0x40];

    void Calc();

    void play(ResArchive * archive, sead::String * filename);
};

template <class T>
struct AnimationList {
    unsigned int count;
    T **anims;
};

class Model {
public:
    ModelObj *obj;
    ResArchive *archive;
    AnimationList<SkeletalAnim> sklAnims;
    AnimationList<ModelAnimation> texAnims;
    AnimationList<ModelAnimation> shuAnims;
    AnimationList<ModelAnimation> visAnims;
    AnimationList<ModelAnimation> shaAnims;

    Model(ModelObj * model, unsigned int sklAnimCount, unsigned int texAnimCount, unsigned int shuAnimCount, unsigned int visAnimCount, unsigned int shaAnimCount);
    void init(ResArchive * archive, sead::PtrArrayImpl<ResArchive> *archives, sead::Heap *heap);
    void update(); //updates animations
};

struct Model2Thing {
    float _0;
    float _4;
    float _8;
    float _C;
    char _10;
    char _11;
    char _12;
    char _13;
};

class Model2 : public Model {
public:
    Model2Thing _30;
    unsigned int _44;

    Model2(ModelObj * model, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
    void init(ResArchive * archive, sead::PtrArrayImpl<ResArchive> *archives, sead::Heap *heap);
    void update();
};

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

void drawModel(void *drawer, Model *model);

#ifdef __cplusplus
}
#endif // __cplusplus
