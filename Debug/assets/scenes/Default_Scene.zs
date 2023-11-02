Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, 0]
Entities:
  - Tag:
      Tag: Player
      ID: 9999
    Transform:
      Position: [40.4425926, 4.57553673, 0]
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
      ContinuousCollision: true
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
      ChildrenCount: 0
      Children:
        {}
    Camera:
      Maincamera: true
  - Tag:
      Tag: Player
      ID: 9997
    Transform:
      Position: [112.999985, 0, 0]
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
      Position: [40.4425926, 4.57553673, 0]
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
      ClassName: NONE
  - Tag:
      Tag: Player
      ID: 9995
    Transform:
      Position: [40.4425926, 4.57553673, 0]
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