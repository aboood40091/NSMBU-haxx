#pragma once

/*
    TODO: finish this
    Most of the structures here
    were taken from Newer U.
*/

#include <sead/heap.h>
#include <rect.h>
#include <vec.h>

class PhysicsCollider;
typedef void (*PhysicsColliderCallback)(PhysicsCollider *self, void *other, unsigned int);

struct ColliderNodeInfo {
    char _0[0x20];
};

struct ColliderRect{
    Vec2 topLeftPos;
    Vec2 bottomRightPos;
};

struct RectColliderParam {
    //TODO: use ColliderRect instead
	float _0[4];
	float _10[4];
	unsigned int rotation;
};

/*
struct SemiSolidShapedColliderParam {
    Vec2 _0;
    Vec2 _8;
    ColliderRect *rect;
    void *_14[4];
    unsigned int _20;
    unsigned int rotation;
};
*/

struct SemiSolidShapedColliderParam {
	float _0[4];
	float *stuff;
	unsigned int rot;
};

class PhysicsCollider : public sead::IDisposer {
	public:
	char _10[0xC * 8];
	Rect rect;
	Vec2 _80;
	unsigned int _88;
	unsigned int _8C;
	StageActor *owner;
	unsigned int _94;
	unsigned int _98;
	unsigned int _9C;
	unsigned int _A0;
	unsigned int _A4;
	unsigned int _A8;
	Vec2 _AC[6];
	char _DC;
	char _DD;
	char _DE;
	char _DF;
	unsigned int _E0;
	float _E4[4];
	unsigned int rotation;
	unsigned int _F8;
	char _FC[0xC * 4];
	unsigned int _12C;
	unsigned int _130;
	unsigned int _134;
	PhysicsColliderCallback collCB1;
	PhysicsColliderCallback collCB2;
	PhysicsColliderCallback collCB3;
	unsigned int _144;
	unsigned int _148;
	unsigned int _14C;
	unsigned int _150;
	unsigned int _154;

	PhysicsCollider();

	virtual ~PhysicsCollider();
	virtual bool checkDerivedRuntimeTypeInfo(void *);
	virtual void vf1C(); //deleted
	virtual bool vf24(unsigned int *, unsigned int);
	virtual void vf2C(); //deleted
	virtual void vf34() = 0;
	virtual void vf3C() = 0;
	virtual bool vf44(void *, unsigned short *, Vec2 *, Vec2 *, unsigned int) = 0;
	virtual bool vf4C(void *, Vec2 *, Vec2 *, unsigned int, void *) = 0;
	virtual bool vf54(char *, Vec2 *) = 0;
	virtual void vf5C() = 0; //pure, deleted by subclasses
	virtual void vf64();
	virtual void vf6C() = 0;
	virtual void vf74(unsigned int *) = 0; //unsigned int[2]
	virtual bool vf7C(Vec2 *) = 0;
};

class ShapedCollider : public PhysicsCollider {
public:
    char _158[0x18];

	void setRect(Vec2 *topLeft, Vec2 *bottomRight);
	ShapedCollider(unsigned int, Vec2 *, ColliderNodeInfo *, ColliderNodeInfo *);

	~ShapedCollider();
	bool checkDerivedRuntimeTypeInfo(void *);
	//bool vf24(unsigned int *, unsigned int);
	void vf34();
	void vf3C();
	bool vf44(void *, unsigned short *, Vec2 *, Vec2 *, unsigned int);
	bool vf4C(void *, Vec2 *, Vec2 *, unsigned int, void *);
	bool vf54(char *, Vec2 *);
	void vf5C(); //deleted
	void vf64();
	void vf6C();
	void vf74(unsigned int *);
	bool vf7C(Vec2 *);
};

class RectCollider : public ShapedCollider {
public:
    Vec2 nodes[4];
    ColliderNodeInfo nodesInfos1[4];
    ColliderNodeInfo nodesInfos2[4];

    inline RectCollider() : ShapedCollider(4, nodes, nodesInfos1, nodesInfos2) {} // Constructor

    void init(StageActor *, RectColliderParam *, unsigned int, unsigned int);

	~RectCollider(); // Destructor
    bool checkDerivedRuntimeTypeInfo(void *);
	//bool vf24(unsigned int *, unsigned int);
	bool vf54(char *, Vec2 *);
};

class SemiSolidShapedCollider : public PhysicsCollider {
public:
    unsigned int _158[2];
    unsigned int _160[2];
    unsigned int _168[2];
    unsigned int _16C;
    float _170;

    SemiSolidShapedCollider();

    void init(StageActor *, SemiSolidShapedColliderParam *, unsigned int, unsigned int);

    ~SemiSolidShapedCollider();
    bool checkDerivedRuntimeTypeInfo(void *);
    //bool vf24(unsigned int *, unsigned int);
    void vf34();
    void vf3C();
    bool vf44(void *, unsigned short *, Vec2 *, Vec2 *, unsigned int);
    bool vf4C(void *, Vec2 *, Vec2 *, unsigned int, void *);
    bool vf54(char *, Vec2 *);
    void vf5C(); //deleted
    void vf64();
    void vf6C();
    void vf74(unsigned int *);
    bool vf7C(Vec2 *);
};

#ifdef __cplusplus
extern "C" {
#endif

void doRegister(void *physicsCollisionMgr, PhysicsCollider* collider);

#ifdef __cplusplus
}
#endif
