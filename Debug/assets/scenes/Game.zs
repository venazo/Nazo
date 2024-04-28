Scene: assets\scenes\Game.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, -10]
Entities:
  - Tag:
      Tag: Grid
      ID: 9999
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
      ChildrenCount: 12
      Children:
        0: 9990
        1: 9991
        2: 9992
        3: 9989
        4: 9987
        5: 9996
        6: 9986
        7: 9993
        8: 9997
        9: 9988
        10: 9995
        11: 9994
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Mass: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Edge2DCollider:
      Vertices:
        - [6, -2]
        - [-6, -2]
      Offset: [0, 0]
      PreviousGhost: [7, -2]
      NextGhost: [-7, -2]
    Grid:
      Gridsize: 1
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
      Tag: GridObject
      ID: 9990
    Transform:
      Position: [-4.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-5, -3]
  - Tag:
      Tag: GridObject
      ID: 9991
    Transform:
      Position: [-3.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-4, -3]
  - Tag:
      Tag: GridObject
      ID: 9992
    Transform:
      Position: [-2.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-3, -3]
  - Tag:
      Tag: GridObject
      ID: 9989
    Transform:
      Position: [-1.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-2, -3]
  - Tag:
      Tag: GridObject
      ID: 9987
    Transform:
      Position: [-0.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-1, -3]
  - Tag:
      Tag: GridObject
      ID: 9996
    Transform:
      Position: [0.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [0, -3]
  - Tag:
      Tag: GridObject
      ID: 9986
    Transform:
      Position: [1.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [1, -3]
  - Tag:
      Tag: GridObject
      ID: 9993
    Transform:
      Position: [2.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [2, -3]
  - Tag:
      Tag: GridObject
      ID: 9997
    Transform:
      Position: [3.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [3, -3]
  - Tag:
      Tag: GridObject
      ID: 9988
    Transform:
      Position: [4.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [4, -3]
  - Tag:
      Tag: GridObject
      ID: 9995
    Transform:
      Position: [5.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [5, -3]
  - Tag:
      Tag: GridObject
      ID: 9994
    Transform:
      Position: [-5.5, -2.5, 0]
      Rotation: 0
      Scale: [1.5625, 1.5625]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\test.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    GridObject:
      GridPosition: [-6, -3]
  - Tag:
      Tag: player
      ID: 9984
    Transform:
      Position: [0, 1.4823668, 0]
      Rotation: 0
      Scale: [0.100000001, 0.100000001]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\duolingo.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Mass: 0.100000001
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: true
    Box2DCollider:
      HalfSize: [0.920000017, 0.920000017]
      Offset: [0, 0]
    NativeScript:
      ClassName: DemoScript