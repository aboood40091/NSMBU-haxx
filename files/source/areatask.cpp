#include "areatask.h"
#include "level.h"

#define COLLISION_DRAW 0

extern f32 PlayerJumpArc;
extern f32 MiniPlayerJumpArc;
extern f32 PlayerJumpMax;
extern f32 PlayerDescentRate;

void AreaTask::readHaxxOptions()
{
    this->wrapFlag = 0;

    Level::Area* area = Level::instance()->getArea(LevelInfo::instance()->area);
    Level::Area::Options* areaOptions = reinterpret_cast<Level::Area::Options*>(area->blocks[1]);

    if (areaOptions->wrapByte & 1)
        this->wrapFlag = 1;

    if (areaOptions->wrapByte & 2)
    {
        PlayerJumpArc = 0.5f;
        MiniPlayerJumpArc = 0.5f;
        PlayerJumpMax = 4.5f;
        PlayerDescentRate = -2.0f;
    }

    else
    {
        PlayerJumpArc = 2.5f;
        MiniPlayerJumpArc = 2.5f;
        PlayerJumpMax = 3.628f;
        PlayerDescentRate = -4.0f;
    }
}

#if COLLISION_DRAW

#define COLLISION_DRAW_DIAGONAL 0

#include <gfx/seadGraphicsContext.h>
#include <gfx/seadPrimitiveRenderer.h>

#include "agl/renderinfo.h"
#include "activecollider.hpp"
#include "actormgr.h"
#include "collider.h"
#include "collisionmgr.h"
//#include "math.h"

#include "log.h"

static inline void drawLine(const Vec2& point1, const Vec2& point2, const sead::Color4f& color, const float lineThickness)
{
    // TODO: Line thickness
    Vec3 _p1(point1.x, point1.y, 4000.f);
    Vec3 _p2(point2.x, point2.y, 4000.f);
    sead::PrimitiveRenderer::instance()->drawLine(_p1, _p2, color, color);
}

#endif // COLLISION_DRAW

void AreaTask::debugDraw(const agl::lyr::RenderInfo& renderInfo)
{
    drawLayer3D(renderInfo);

#if COLLISION_DRAW
    sead::GraphicsContext context;
    context.setDepthTestEnable(true);
    context.setDepthWriteEnable(true);
    context.setDepthFunc(sead::Graphics::cDepthFunc_LessEqual);
    context.setCullingMode(sead::Graphics::cCullingMode_None);
    context.setBlendEnable(false);
    context.apply();

    sead::PrimitiveRenderer::instance()->setCamera(*renderInfo.camera);
    sead::PrimitiveRenderer::instance()->setProjection(*renderInfo.projection);
    sead::PrimitiveRenderer::instance()->begin();

    static const sead::Color4f colorRed(1.0f, 0.0f, 0.0f, 1.0f);
    static const sead::Color4f colorGreen(0.0f, 1.0f, 0.0f, 1.0f);
    static const sead::Color4f colorBlue(0.0f, 0.0f, 1.0f, 1.0f);
    static const sead::Color4f colorCyan(0.0f, 1.0f, 1.0f, 1.0f);
    static const sead::Color4f colorYellow(1.0f, 1.0f, 0.0f, 1.0f);
    static const sead::Color4f colorMagenta(1.0f, 0.0f, 1.0f, 1.0f);
    static const sead::Color4f colorBlack(0.0f, 0.0f, 0.0f, 1.0f);
    static const sead::Color4f colorWhite(1.0f, 1.0f, 1.0f, 1.0f);

    ActiveCollider::List::Node* aColliderNode;
    aColliderNode = ActiveColliderMgr::instance->activeList.first;

    while (aColliderNode != nullptr)
    {
        ActiveCollider* aCollider = aColliderNode->owner;
        if ((aCollider->info._1C & 0x800) == 0)
        {
            Rect rect;
            aCollider->getRect(rect);

            if (aCollider->info.shape == ActiveCollider::ShapeRectangle)
            {
                Vec2 point1 = rect.getTL();
                Vec2 point2 = rect.getTR();
                Vec2 point3 = rect.getBR();
                Vec2 point4 = rect.getBL();

                drawLine(point1, point2, colorRed, 1.0f);
                drawLine(point2, point3, colorRed, 1.0f);
                drawLine(point3, point4, colorRed, 1.0f);
                drawLine(point1, point4, colorRed, 1.0f);
#if COLLISION_DRAW_DIAGONAL
                drawLine(point1, point3, colorRed, 1.0f); // Diagonal line
#endif // COLLISION_DRAW_DIAGONAL
            }

            else if (aCollider->info.shape == ActiveCollider::ShapeCircle)
            {
                f32 radiusX = rect.getHalfSizeX();
                f32 radiusY = rect.getHalfSizeY();
                const Vec2& bl = rect.getMin();

                if (radiusX != radiusY)
                {
                    LOG("WARNING: radiusX != radiusY; actor id: 0x%x, profile id: 0x%x\n", aCollider->owner->id, aCollider->owner->profile->id)
                }

                sead::PrimitiveRenderer::instance()->drawCircle32(
                    Vec3(bl.x + radiusX, bl.y + radiusX, 4000.f),
                    radiusX, colorRed
                );
            }
        }

        aColliderNode = aColliderNode->next;
    }

    aColliderNode = ActiveColliderMgr::instance->list4.first;

    while (aColliderNode != nullptr)
    {
        ActiveCollider* aCollider = aColliderNode->owner;

        Rect rect;
        aCollider->getRect(rect);

        if (aCollider->info.shape == ActiveCollider::ShapeRectangle)
        {
            Vec2 point1 = rect.getTL();
            Vec2 point2 = rect.getTR();
            Vec2 point3 = rect.getBR();
            Vec2 point4 = rect.getBL();

            drawLine(point1, point2, colorRed, 1.0f);
            drawLine(point2, point3, colorRed, 1.0f);
            drawLine(point3, point4, colorRed, 1.0f);
            drawLine(point1, point4, colorRed, 1.0f);
#if COLLISION_DRAW_DIAGONAL
            drawLine(point1, point3, colorRed, 1.0f); // Diagonal line
#endif // COLLISION_DRAW_DIAGONAL
        }

        else if (aCollider->info.shape == ActiveCollider::ShapeCircle)
        {
            f32 radiusX = rect.getHalfSizeX();
            f32 radiusY = rect.getHalfSizeY();
            const Vec2& bl = rect.getMin();

            if (radiusX != radiusY)
            {
                LOG("WARNING: radiusX != radiusY; actor id: 0x%x, profile id: 0x%x\n", aCollider->owner->id, aCollider->owner->profile->id)
            }

            sead::PrimitiveRenderer::instance()->drawCircle32(
                Vec3(bl.x + radiusX, bl.y + radiusX, 4000.f),
                radiusX, colorRed
            );
        }

        aColliderNode = aColliderNode->next;
    }

    ColliderBase::List* activeList = &ColliderMgr::instance()->lists[0];
    ColliderBase::List::Node* node = activeList->first;

    while (node != nullptr)
    {
        ColliderBase* colliderBase = node->owner;
        if (sead::IsDerivedTypes<CircularCollider, ColliderBase>(colliderBase))
        {
            CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

            sead::PrimitiveRenderer::instance()->drawCircle32(
                Vec3(collider->ownerInfo.position->x + collider->distToCenter.x + collider->_160.x, collider->ownerInfo.position->y + collider->distToCenter.y + collider->_160.y, 4000.f),
                collider->radius, colorBlue
            );
        }

        else if (sead::IsDerivedTypes<SolidOnTopCollider, ColliderBase>(colliderBase))
        {
            SolidOnTopCollider* collider = static_cast<SolidOnTopCollider*>(colliderBase);
            if (collider->points.getSize() < 2)
                continue;

            const Vec2 center = *(const Vec2*)collider->ownerInfo.position + collider->distToCenter;

            for (int i = 0; i < collider->nodes1.getSize(); i++)
            {
                const ColliderBase::Node& node = collider->nodes1[i];
                drawLine(center + node.sensor.p1, center + node.sensor.p2, colorGreen, 1.0f);
            }
        }

        else if (sead::IsDerivedTypes<ShapedCollider, ColliderBase>(colliderBase))
        {
            ShapedCollider* collider = static_cast<ShapedCollider*>(colliderBase);
            if (collider->points.getSize() < 2)
                continue;

            const Vec2 center = *(const Vec2*)collider->ownerInfo.position + collider->distToCenter;

            for (int i = 0; i < collider->nodes1.getSize(); i++)
            {
                const ColliderBase::Node& node = collider->nodes1[i];
                drawLine(center + node.sensor.p1, center + node.sensor.p2, colorBlue, 1.0f);
            }

#if COLLISION_DRAW_DIAGONAL
            // If it's a rectangle, draw a diagonal line
            if (collider->points.getSize() >= 4 && !(collider->points.getSize() & 1))
            {
                const ColliderBase::Node& node1 = collider->nodes1[0];
                const ColliderBase::Node& node2 = collider->nodes1[collider->points.getSize() / 2 - 1];
                drawLine(center + node1.sensor.p1, center + node2.sensor.p2, colorBlue, 1.0f);
            }
#endif // COLLISION_DRAW_DIAGONAL
        }

        else // EllipticalCollider and ClimbableCollider
        {
            LOG("Found unknown collider for actor with id: 0x%x, profile id: 0x%x\n", colliderBase->owner->id, colliderBase->owner->profile->id)
        }

        node = node->next;
    }

    ActorBuffer* actors = &ActorMgr::instance->actors;
    for (int i = 0; i < actors->buffer.getSize(); i++)
    {
        Actor* actor = sead::DynamicCast<Actor, Base>(actors->buffer[i]);
        if (actor == NULL || !actor->isVisible || actor->isDeleted)
            continue;

        CollisionMgr* collisionMgr = actor->getCollisionMgr();
        if (collisionMgr == NULL || collisionMgr->position == NULL)
            continue;

        for (int j = 0; j < 4; j++)
        {
            const CollisionMgr::Sensor* sensor = collisionMgr->getSensor(j);
            if (sensor == nullptr)
                continue;

            f32 p1 = sensor->p1;
            f32 p2 = sensor->p2;

            if (p1 == p2)
            {
                p1 -= 0.5f;
                p2 += 0.5f;
            }

            if (j < 2)
            {
                Vec2 point1(collisionMgr->position->x + sensor->distanceFromCenter, collisionMgr->position->y + p1);
                Vec2 point2(collisionMgr->position->x + sensor->distanceFromCenter, collisionMgr->position->y + p2);

                drawLine(point1, point2, colorYellow, 1.0f);
            }

            else
            {
                Vec2 point1(collisionMgr->position->x + p1, collisionMgr->position->y + sensor->distanceFromCenter);
                Vec2 point2(collisionMgr->position->x + p2, collisionMgr->position->y + sensor->distanceFromCenter);

                drawLine(point1, point2, (j == 2) ? colorWhite : colorCyan, 1.0f);
            }
        }
    }

    sead::PrimitiveRenderer::instance()->end();
#endif // COLLISION_DRAW
}
