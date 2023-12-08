Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, -100]
Entities:
  - Tag:
      Tag: Player
      ID: 9999
    Transform:
      Position: [1.44260788, -43.4550247, 0]
      Rotation: 0
      Scale: [0.100000001, 0.100000001]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 0.980392158, 1]
      Sprite:
        TexturePath: assets\textures\duolingo.png
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
      ClassName: NONE
  - Tag:
      Tag: camera
      ID: 9998
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [480, 270]
      Parent: -1
      ChildrenCount: 1
      Children:
        0: 9995
    Camera:
      Maincamera: true
  - Tag:
      Tag: Player
      ID: 9997
    Transform:
      Position: [115.000031, -1.99999809, 0]
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
      LinearDamping: 2.80259693e-45
      Mass: 1.00000012
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: true
    Box2DCollider:
      HalfSize: [64, 64]
      Offset: [0, 0]
      Origin: [0, 0]
  - Tag:
      Tag: Player
      ID: 9996
    Transform:
      Position: [0.100008011, 57.8361282, 0]
      Rotation: 0
      Scale: [0.100000001, 0.100000001]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 0.984313726, 1]
      Sprite:
        TexturePath: assets\textures\duolingo.png
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
      ClassName: NONE
  - Tag:
      Tag: Player
      ID: 9995
    Transform:
      Position: [-112.517319, -0.506864071, 0]
      Rotation: -0.161438465
      Scale: [1, 1]
      Parent: 9998
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
      ContinuousCollision: true
    Box2DCollider:
      HalfSize: [64, 64]
      Offset: [0, 0]
      Origin: [0, 0]
    NativeScript:
      ClassName: DemoScript
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