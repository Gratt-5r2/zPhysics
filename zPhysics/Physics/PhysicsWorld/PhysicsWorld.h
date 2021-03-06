// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
  class zPhysicalWorld {
    Array<zPhysicalObjectBase*> ObjectList;
    btRigidBody* RigidBody;
    btSoftRigidDynamicsWorld* World;
    btDispatcher* Dispatcher;
    btCollisionConfiguration* CollisionConfiguration;
    btBroadphaseInterface* BroadphaseInterface;
    btConstraintSolver* ConstraintSolver;
  public:

    zPhysicalWorld();
    void InitializeWorldMesh();
    void AddObject( zPhysicalObjectBase* object );
    void RemoveObject( zPhysicalObjectBase* object );
    void DoPhysics( const float& time = 0.16f );
    btSoftRigidDynamicsWorld* GetDynamicsWorld();
    virtual ~zPhysicalWorld();
  };
}