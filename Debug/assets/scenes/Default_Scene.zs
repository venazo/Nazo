Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, -10]
Entities:
  - Tag:
      Tag: new GameObject
      ID: 9999
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
      ChildrenCount: 4
      Children:
        0: 9997
        1: 9996
        2: 9995
        3: 9994
    Grid:
      Gridsize: 1
  - Tag:
      Tag: GridObject
      ID: 9997
    Transform:
      Position: [1.5, -0.5, 0]
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
      GridPosition: [1, -1]
  - Tag:
      Tag: GridObject
      ID: 9996
    Transform:
      Position: [1.5, 0.5, 0]
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
      GridPosition: [1, 0]
  - Tag:
      Tag: GridObject
      ID: 9995
    Transform:
      Position: [2.5, 0.5, 0]
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
      GridPosition: [2, 0]
  - Tag:
      Tag: GridObject
      ID: 9994
    Transform:
      Position: [2.5, -0.5, 0]
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
      GridPosition: [2, -1]