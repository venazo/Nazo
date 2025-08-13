Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0.170000002, 0.170000002, 0.170000002, 1]
Gravity: [0, -10]
Entities:
  - Tag:
      Tag: Titlescreen
      ID: 9999
    Transform:
      Position: [0.79999876, 0, 0]
      Rotation: 0
      Scale: [5, 5]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    SpriteRenderer:
      Color: [1, 1, 1, 1]
      Sprite:
        TexturePath: assets\textures\Icon.png
        UV:
          0: [0, 0]
          1: [0, 1]
          2: [1, 1]
          3: [1, 0]
    NativeScript:
      ClassName: Titlescreen
  - Tag:
      Tag: maincamera
      ID: 9998
    Transform:
      Position: [-0.699999809, 0, 0]
      Rotation: 0
      Scale: [19.2000008, 10.2700005]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    Camera:
      Maincamera: true