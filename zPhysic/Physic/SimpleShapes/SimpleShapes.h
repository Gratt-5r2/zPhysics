// Supported with union (c) 2020 Union team
// Union HEADER file

namespace GOTHIC_ENGINE {
  class zPhysicalMesh : public zPhysicalObjectBase {
  protected:
    btRigidBody* RigidBody;
  public:

    virtual void SetVelocity( const zVEC3& vec );
    virtual btRigidBody* GetRigidBody();
    virtual ~zPhysicalMesh();
  };


  class zPhysicalSphere : public zPhysicalMesh {
  protected:
    btSphereShape* Sphere;
    zPhysicalSphere() {}
  public:

    static zPhysicalSphere* CreateSphere( float radius, const zVEC3& position = zVEC3( 0.0f, 0.0f, 0.0f ), float mass = 0.0f, bool useInertia = false );
    static zPhysicalSphere* CreateSphere( float radius, const zMAT4& trafo, float mass = 0.0f, bool useInertia = false );
  };


  class zPhysicalBox : public zPhysicalMesh {
  protected:
    btBoxShape* Box;
    zPhysicalBox() {}
  public:

    static zPhysicalBox* CreateBox( const zVEC3& halfExtents, const zVEC3& position = zVEC3( 0.0f, 0.0f, 0.0f ), float mass = 0.0f, bool useInertia = false );
    static zPhysicalBox* CreateBox( const zVEC3& halfExtents, const zMAT4& trafo, float mass = 0.0f, bool useInertia = false );
  };


  class zPhysicalCylinder : public zPhysicalMesh {
  protected:
    btCylinderShape* Cylinder;
    zPhysicalCylinder() {}
  public:

    static zPhysicalCylinder* CreateCylinder( const zVEC3& halfExtents, const zVEC3& position = zVEC3( 0.0f, 0.0f, 0.0f ), float mass = 0.0f, bool useInertia = false );
    static zPhysicalCylinder* CreateCylinder( const zVEC3& halfExtents, const zMAT4& trafo, float mass = 0.0f, bool useInertia = false );
  };


  class zPhysicalCone : public zPhysicalMesh {
  protected:
    btConeShape* Cone;
    zPhysicalCone() {}
  public:

    static zPhysicalCone* CreateCone( const float& radius, const float& height, const zVEC3& position = zVEC3( 0.0f, 0.0f, 0.0f ), float mass = 0.0f, bool useInertia = false );
    static zPhysicalCone* CreateCone( const float& radius, const float& height, const zMAT4& trafo, float mass = 0.0f, bool useInertia = false );
  };
}