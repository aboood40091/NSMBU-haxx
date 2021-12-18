#ifndef SEAD_PROJECTION_H_
#define SEAD_PROJECTION_H_

#include <gfx/seadGraphics.h>
#include <math/seadMatrix.h>
#include <math/seadVector.h>
#include <prim/seadRuntimeTypeInfo.h>

namespace sead {

class Camera;
class Viewport;

template <typename T>
class Ray;

class Projection
{
    SEAD_RTTI_BASE(Projection)

public:
    enum Type
    {
        cType_Perspective = 0,
        cType_Ortho       = 1,
        cType_Undefined   = 2
    };

public:
    Projection();
    virtual ~Projection();

    virtual Type getProjectionType() const = 0;
    virtual void doUpdateMatrix(Matrix44f* dst) const = 0;
    virtual void doUpdateDeviceMatrix(Matrix44f* dst, const Matrix44f& src, Graphics::DevicePosture pose) const;
    virtual void doScreenPosToCameraPosTo(Vector3f* dst, const Vector3f& screen_pos) const = 0;

    const Matrix44f& getProjectionMatrix() const;
    Matrix44f& getProjectionMatrixMutable();

    const Matrix44f& getDeviceProjectionMatrix() const;

    void cameraPosToScreenPos(Vector3f* dst, const Vector3f& camera_pos) const;
    void screenPosToCameraPos(Vector3f* dst, const Vector3f& screen_pos) const;
    void screenPosToCameraPos(Vector3f* dst, const Vector2f& screen_pos) const;

    void project(Vector2f* dst, const Vector3f& camera_pos, const Viewport& viewport) const;
    void unproject(Vector3f* dst, const Vector3f& screen_pos, const Camera& camera) const;
    void unprojectRay(Ray<Vector3f>* dst, const Vector3f& screen_pos, const Camera& camera) const;

private:
    void updateMatrixImpl_() const;

protected:
    mutable bool mDirty;
    mutable bool mDeviceDirty;
    Matrix44f mMatrix;
    Matrix44f mDeviceMatrix;
    Graphics::DevicePosture mDevicePosture;
    f32 mDeviceZScale;
    f32 mDeviceZOffset;
};
#ifdef cafe
static_assert(sizeof(Projection) == 0x94, "sead::Projection size mismatch");
#endif // cafe

} // namespace sead

#endif // SEAD_PROJECTION_H_
