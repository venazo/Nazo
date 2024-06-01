Scene: assets/scenes/Game.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, 0]
Entities:
  - Tag:
      Tag: Camera
      ID: 9985
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [19.2000008, 10.8000002]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    Camera:
      Maincamera: true
  - Tag:
      Tag: Ball
      ID: 9984
    Transform:
      Position: [0, -3.70000005, 0]
      Rotation: 0
      Scale: [0.300000012, 0.300000012]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Mass: 1
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: true
    Circle2DCollider:
      Radius: 0.150000006
      Offset: [0, 0]
  - Tag:
      Tag: Platform
      ID: 9994
    Transform:
      Position: [0, -4, 0]
      Rotation: 0
      Scale: [2.5, 0.25]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Mass: 1
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: true
    Box2DCollider:
      HalfSize: [2.5, 0.25]
      Offset: [0, 0]