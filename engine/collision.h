#ifndef __ENGINE_COLLISION_H__
#define __ENGINE_COLLISION_H__

typedef float (*DistanceFuncT)(PtrT object, Vector3D *point);

typedef struct CollisionActor {
  PtrT object;
  DistanceFuncT *distance;
} CollisionActorT;

bool DetectCollision(CollisionActorT *actor,
                     Vector3D *before, Vector3D *after);

#endif
