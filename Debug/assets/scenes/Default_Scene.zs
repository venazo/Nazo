Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, -100]
Entities:
  - Tag:
      Tag: Player
      ID: 9999
    Transform:
      Position: [1.44260788, -43.5383606, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 0.980392158, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 1.40129846e-45
      Mass: 1.00003052
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [64, 64]
      Offset: [0, 0]
      Origin: [0, 0]
    NativeScript:
      ClassName: DemoScript
  - Tag:
      Tag: camera
      ID: 9998
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [480, 270]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    Camera:
      Maincamera: true
  - Tag:
      Tag: Platform
      ID: 9994
    Transform:
      Position: [0, -100, 0]
      Rotation: 0
      Scale: [10000, 10]
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
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [10000, 10]
      Offset: [0, 0]
      Origin: [0, 0]
  - Tag:
      Tag: Circle
      ID: 9993
    Transform:
      Position: [-71.301239, 192.024429, 0]
      Rotation: 0
      Scale: [0.300000012, 0.300000012]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\Moon.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Mass: 1
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: false
    Circle2DCollider:
      Radius: 39
      Offset: [0, 0]
      Origin: [0, 0]