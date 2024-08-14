Scene: assets/scenes/Default_Scene.zs
BackgroundColor: [0, 0, 0, 1]
Gravity: [0, -10]
Entities:
  - Tag:
      Tag: Titlescreen
      ID: 9999
    Transform:
      Position: [0, 0, 0]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
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
    NativeScript:
      ClassName: Titlescreen
  - Tag:
      Tag: maincamera
      ID: 9998
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
      Tag: Title
      ID: 9997
    Transform:
      Position: [-5.6500001, -1, 2]
      Rotation: 0
      Scale: [1, 1]
      Parent: -1
      ChildrenCount: 0
      Children:
        {}
    Text:
      Content: Breakout
      Font: assets\fonts\breakoutFont.ttf
      Scale: 64
      Color: [1, 1, 1, 1]