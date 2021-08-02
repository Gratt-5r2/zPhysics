// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
  zPhysicalWorld::zPhysicalWorld() {
    CollisionConfiguration = new btDefaultCollisionConfiguration();
    Dispatcher = new btCollisionDispatcher( CollisionConfiguration );
    BroadphaseInterface = new btDbvtBroadphase();
    ConstraintSolver = new btSequentialImpulseConstraintSolver();
    World = new btDiscreteDynamicsWorld( Dispatcher, BroadphaseInterface, ConstraintSolver, CollisionConfiguration );

    World->setGravity( btVector3( 0.0, -9.832, 0.0 ) );
  }


  inline bool IsIgnorePoly( zCPolygon* poly ) {
    if( poly->material ) {
      if( poly->material->noCollDet )
        return true;

      if( poly->material->matGroup == zMAT_GROUP_WATER )
        return true;

      if( poly->material->IsPortalMaterial() )
        return true;
    }
    
    return false;
  }


  void zPhysicalWorld::InitializeWorldMesh() {
    btTransform btTrafo;
    btTrafo.setIdentity();
    btTrafo.setOrigin( btVector3( 0.0, 0.0, 0.0 ) );

    btTriangleMesh* meshInterface = new btTriangleMesh();

    oCWorld* world = ogame->GetGameWorld();
    zCMesh* worldMesh = world->bspTree.mesh;
    for( int i = 0; i < worldMesh->numPoly; i++ ) {

      zCPolygon* poly = worldMesh->polyList ?
         worldMesh->polyList[i] :
        &worldMesh->polyArray[i];

      if( IsIgnorePoly( poly ) )
        continue;

      int vertNum = poly->polyNumVert;
      if( vertNum == 3 ) {
        meshInterface->addTriangle(
          btVector3( poly->vertex[0]->position.ToBtVector3() ),
          btVector3( poly->vertex[1]->position.ToBtVector3() ),
          btVector3( poly->vertex[2]->position.ToBtVector3() )
        );
      }
      else {
        for( int j = 0; j < vertNum - 2; j++ ) {
          meshInterface->addTriangle(
            btVector3( poly->vertex[    0]->position.ToBtVector3() ),
            btVector3( poly->vertex[j + 1]->position.ToBtVector3() ),
            btVector3( poly->vertex[j + 2]->position.ToBtVector3() )
          );
        }
      }
    }

    btBvhTriangleMeshShape* triangleMeshShape = new btBvhTriangleMeshShape( meshInterface, true, true );

    btMotionState* motionState = new btDefaultMotionState( btTrafo );
    btRigidBody::btRigidBodyConstructionInfo rigidBodyInfo( 0.0, motionState, triangleMeshShape );
    btRigidBody* body = new btRigidBody( rigidBodyInfo );
    World->addRigidBody( body );
    RigidBody = body;
  }


  void zPhysicalWorld::AddObject( zPhysicalObjectBase* object ) {
    object->AddRef();
    ObjectList += object;
    btRigidBody* rigidBody = object->GetRigidBody();
    if( rigidBody )
      World->addRigidBody( rigidBody );
  }


  void zPhysicalWorld::RemoveObject( zPhysicalObjectBase* object ) {
    ObjectList -= object;
    btRigidBody* rigidBody = object->GetRigidBody();
    if( rigidBody )
      World->removeRigidBody( rigidBody );

    object->Release();
  }


  void zPhysicalWorld::DoPhysic( const float& time ) {
    static float fixedFrameTime = 1.0f / 60.0f;
    float timeStep = fixedFrameTime * time;
    World->stepSimulation( timeStep, 1, timeStep );
  }


  zPhysicalWorld::~zPhysicalWorld() {
    ObjectList.ReleaseData();
    ObjectList.Clear();

    delete Dispatcher;
    delete CollisionConfiguration;
    delete ConstraintSolver;
    delete BroadphaseInterface;
    delete World;
    delete RigidBody;
  }
}