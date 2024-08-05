Scene: assets\scenes\Game.zs
BackgroundColor: [0, 0, 0, 1]
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
      ChildrenCount: 2
      Children:
        0: 9993
        1: 9999
    Camera:
      Maincamera: true
  - Tag:
      Tag: Ball
      ID: 9984
    Transform:
      Position: [0, -3.5999999, 1]
      Rotation: 0
      Scale: [0.300000012, 0.300000012]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
    RigidBody2D:
      AngularDamping: 0
      LinearDamping: 0
      Restitution: 1
      Density: 1
      Friction: 0
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: true
    Circle2DCollider:
      Radius: 0.150000006
      Offset: [0, 0]
    NativeScript:
      ClassName: Ball
  - Tag:
      Tag: Platform
      ID: 9994
    Transform:
      Position: [0, -4, 1]
      Rotation: 0
      Scale: [2.5, 0.25]
      Parent: 9999
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 10
      Friction: 1
      BodyType: Dynamic
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.5, 0.25]
      Offset: [0, 0]
    NativeScript:
      ClassName: Platform
  - Tag:
      Tag: Cage
      ID: 9999
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9985
      ChildrenCount: 1
      Children:
        0: 9994
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Edge2DCollider:
      Vertices:
        - [-9.60000038, -5.4000001]
        - [-9.60000038, 5.4000001]
        - [9.60000038, 5.4000001]
        - [9.60000038, -5.4000001]
      Offset: [0, 0]
      PreviousGhost: [0, 0]
      NextGhost: [0, 0]
  - Tag:
      Tag: Blocks
      ID: 9998
    Transform:
      Position: [0, 0, 1]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
      ChildrenCount: 8
      Children:
        0: 9987
        1: 9986
        2: 9974
        3: 9964
        4: 9954
        5: 9944
        6: 9934
        7: 9924
  - Tag:
      Tag: Block
      ID: 9997
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9996
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9995
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9992
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9991
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9990
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9989
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9988
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9987
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9987
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9988
        1: 9989
        2: 9990
        3: 9991
        4: 9992
        5: 9995
        6: 9996
        7: 9997
  - Tag:
      Tag: row
      ID: 9986
    Transform:
      Position: [0, -0.5, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9983
        1: 9982
        2: 9981
        3: 9980
        4: 9979
        5: 9977
        6: 9976
        7: 9975
  - Tag:
      Tag: Block
      ID: 9983
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9982
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9981
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9980
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9979
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9977
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9976
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9975
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9986
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.588235319, 0.588235319, 0.392156869, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9974
    Transform:
      Position: [0, -1, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9973
        1: 9972
        2: 9971
        3: 9970
        4: 9969
        5: 9968
        6: 9967
        7: 9966
  - Tag:
      Tag: Block
      ID: 9973
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0923250169, 0.421232879, 0.150897577, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9972
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9971
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9970
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9969
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9968
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9967
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9966
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9974
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.0941176489, 0.419607848, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9964
    Transform:
      Position: [0, -1.5, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9963
        1: 9962
        2: 9961
        3: 9960
        4: 9959
        5: 9957
        6: 9956
        7: 9955
  - Tag:
      Tag: Block
      ID: 9963
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.585616469, 0.206570208, 0.206570208, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9962
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9961
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9960
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9959
    Transform:
      Position: [1.20000267, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9957
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9956
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9955
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9964
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.58431375, 0.20784314, 0.20784314, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9954
    Transform:
      Position: [0, -2, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9953
        1: 9952
        2: 9951
        3: 9949
        4: 9948
        5: 9947
        6: 9946
        7: 9945
  - Tag:
      Tag: Block
      ID: 9953
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.16579096, 0.389336467, 0.520547986, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9952
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9951
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9949
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9948
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9947
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9946
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9945
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9954
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.164705887, 0.388235301, 0.521568656, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9944
    Transform:
      Position: [0, -2.5, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9943
        1: 9942
        2: 9941
        3: 9940
        4: 9939
        5: 9937
        6: 9936
        7: 9935
  - Tag:
      Tag: Block
      ID: 9943
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619863033, 0.205913395, 0.546146035, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9942
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9941
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9940
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9939
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9937
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9936
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9935
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9944
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.619607866, 0.20784314, 0.545098066, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9934
    Transform:
      Position: [0, -3, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9933
        1: 9932
        2: 9931
        3: 9930
        4: 9929
        5: 9927
        6: 9926
        7: 9925
  - Tag:
      Tag: Block
      ID: 9933
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376712322, 0.228968129, 0.149652824, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9932
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9931
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9930
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9929
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9927
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9926
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9925
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9934
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.376470596, 0.227450982, 0.149019614, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: row
      ID: 9924
    Transform:
      Position: [0, -3.5, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9998
      ChildrenCount: 8
      Children:
        0: 9916
        1: 9915
        2: 9923
        3: 9922
        4: 9921
        5: 9920
        6: 9919
        7: 9917
  - Tag:
      Tag: Block
      ID: 9923
    Transform:
      Position: [8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.277999371, 0.169074878, 0.363013685, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9922
    Transform:
      Position: [6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9921
    Transform:
      Position: [3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9920
    Transform:
      Position: [-6, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9919
    Transform:
      Position: [1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9917
    Transform:
      Position: [-1.20000005, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9916
    Transform:
      Position: [-3.5999999, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Block
      ID: 9915
    Transform:
      Position: [-8.39999962, 5.1500001, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9924
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.278431386, 0.168627456, 0.36470589, 1]
      Sprite:
        TexturePath: assets\textures\block.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    RigidBody2D:
      AngularDamping: 0.800000012
      LinearDamping: 0.899999976
      Restitution: 0
      Density: 1
      Friction: 1
      BodyType: Static
      FixedRotation: false
      ContinuousCollision: false
    Box2DCollider:
      HalfSize: [2.4000001, 0.5]
      Offset: [0, 0]
  - Tag:
      Tag: Background
      ID: 9993
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: 9985
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [0.333333343, 0.333333343, 0.333333343, 1]
      Sprite:
        TexturePath: assets\textures\background.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]