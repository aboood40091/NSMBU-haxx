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

    Level::Area* area = Level::instance->getArea(LevelInfo::instance->area);
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

#include "agl/renderinfo.h"
#include "actormgr.h"
#include "collider.h"
#include "collisionmgr.h"
#include "math.h"

#include "log.h"

void drawLine(const Vec2& position, const f32 rotation, const sead::Color4f& color, const float lineLength, const float lineThickness)
{
    Vec3 scale(lineLength, lineThickness, 1.0f);
    Vec3 rot(0.0f, 0.0f, rotation);
    Vec3 pos(position.x + (lineLength * cos(rotation)) / 2, position.y + (lineLength * sin(rotation)) / 2, 4000.f);

    Mtx34 mtx;
    Mtx34::makeSRT(mtx, scale, rot, pos);
    sead::PrimitiveRenderer::instance->mRendererImpl->drawQuadImpl(mtx, color, color);
}

void drawLine(const Vec2& point1, const Vec2& point2, const sead::Color4f& color, const float lineThickness)
{
    f32 length = sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));

    const Vec2& leftPoint = (point1.x < point2.x) ? point1 : point2;
    const Vec2& rightPoint = (&leftPoint == &point1) ? point2 : point1;
    f32 angle = atan2(rightPoint.y - leftPoint.y, rightPoint.x - leftPoint.x);

    drawLine(leftPoint, angle, color, length, lineThickness);
}
#endif // COLLISION_DRAW

void AreaTask::debugDraw(const agl::lyr::RenderInfo& renderInfo)
{
    drawLayer3D(renderInfo);

#if COLLISION_DRAW
    sead::PrimitiveRenderer::instance->setCamera(*renderInfo.camera);
    sead::PrimitiveRenderer::instance->setProjection(*renderInfo.projection);
    sead::PrimitiveRenderer::instance->begin();

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
                Vec2 point1(rect.left, rect.top);
                Vec2 point2(rect.right, rect.top);
                Vec2 point3(rect.right, rect.bottom);
                Vec2 point4(rect.left, rect.bottom);

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
                f32 radius = (rect.right - rect.left) / 2.0f;

                sead::PrimitiveRenderer::instance->drawCircle32(
                    Vec3(rect.left + radius, rect.bottom + radius, 4000.f),
                    radius, colorRed
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
            Vec2 point1(rect.left, rect.top);
            Vec2 point2(rect.right, rect.top);
            Vec2 point3(rect.right, rect.bottom);
            Vec2 point4(rect.left, rect.bottom);

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
            f32 radius = (rect.right - rect.left) / 2.0f;

            sead::PrimitiveRenderer::instance->drawCircle32(
                Vec3(rect.left + radius, rect.bottom + radius, 4000.f),
                radius, colorRed
            );
        }

        aColliderNode = aColliderNode->next;
    }

    ColliderBase::List* activeList = &ColliderMgr::instance->lists[0];
    ColliderBase::List::Node* node = activeList->first;

    while (node != nullptr)
    {
        ColliderBase* colliderBase = node->owner;
        if (sead::IsDerivedFrom<CircularCollider, ColliderBase>(colliderBase))
        {
            CircularCollider* collider = static_cast<CircularCollider*>(colliderBase);

            sead::PrimitiveRenderer::instance->drawCircle32(
                Vec3(collider->ownerInfo.position->x + collider->distToCenter.x + collider->_160.x, collider->ownerInfo.position->y + collider->distToCenter.y + collider->_160.y, 4000.f),
                collider->radius, colorBlue
            );
        }

        else if (sead::IsDerivedFrom<SolidOnTopCollider, ColliderBase>(colliderBase))
        {
            SolidOnTopCollider* collider = static_cast<SolidOnTopCollider*>(colliderBase);
            if (collider->points.mSize < 2)
                continue;

            const Vec2 center = Vec2(*collider->ownerInfo.position) + collider->distToCenter;

            for (int i = 0; i < collider->nodes1.mSize; i++)
            {
                const ColliderBase::Node& node = collider->nodes1[i];
                drawLine(center + node.sensor.p1, center + node.sensor.p2, colorGreen, 1.0f);
            }
        }

        else if (sead::IsDerivedFrom<ShapedCollider, ColliderBase>(colliderBase))
        {
            ShapedCollider* collider = static_cast<ShapedCollider*>(colliderBase);
            if (collider->points.mSize < 2)
                continue;

            const Vec2 center = Vec2(*collider->ownerInfo.position) + collider->distToCenter;

            for (int i = 0; i < collider->nodes1.mSize; i++)
            {
                const ColliderBase::Node& node = collider->nodes1[i];
                drawLine(center + node.sensor.p1, center + node.sensor.p2, colorBlue, 1.0f);
            }

#if COLLISION_DRAW_DIAGONAL
            // If it's a rectangle, draw a diagonal line
            if (collider->points.mSize >= 4 && !(collider->points.mSize & 1))
            {
                const ColliderBase::Node& node1 = collider->nodes1[0];
                const ColliderBase::Node& node2 = collider->nodes1[collider->points.mSize / 2 - 1];
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
    for (int i = 0; i < actors->buffer.mSize; i++)
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

    sead::PrimitiveRenderer::instance->end();
#endif // COLLISION_DRAW
}
