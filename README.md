# IL2CPP Scanner for DX11 <img src="https://i.imgur.com/k7Vr4yV.png" width="40" height="40">

[![Github All Releases](https://img.shields.io/github/downloads/ImAxel0/IL2CPP_Scanner_DX11/total.svg)]()
[![Github All Releases](https://img.shields.io/github/v/release/ImAxel0/IL2CPP_Scanner_DX11)]()

### <ins>Project archived because I consider it unstable and ahead of a possible release of a better version in the future</ins> [(sneak peek)](https://youtu.be/qwHQ73sW3UM)

An in game GUI tool based on [IL2CPP_Resolver](https://github.com/sneakyevil/IL2CPP_Resolver) made to modify il2cpp Unity games.

![IL2CPP Scanner](https://i.imgur.com/Fi5w9e7.png)

## Disclaimer
The software is provided as is and was made as a personal project, crashes can occur at any time.

## Compatibility
Works with Unity il2ccp games running on DirectX11.

Game must be set to borderless window or windowed mode!

## Features
- Find active GameObjects
- Find GameObject components and children components
- Find and tweak component fields, currently supported field types are:
    - integers
    - float
    - bool
- List component properties (can't do anything with them at the moment)

## How to use
The tool is meant to be used along with dnSpy/ILSpy to previously know what to search for. This means you will need to dump the GameAssembly.dll with any il2cpp dumper.

1. Download the latest version from the releases page
2. Run the game
3. Inject IL2CPP Scanner.dll in the game process with any injector

To show/hide the menu press the insert key

### Basic Usage (find a GameObject individually)
1. Specify a module name
2. Search an active GameObject
3. Load the GameObject components (children components are excluded)
4. Play with the component fields

### Searching all GameObjects in a specific module
1. Specify a module name
2. Search all active GameObjects in the specified module name
3. Load the selected GameObject components (children components are included)
4. Play with the component fields

### Finding components in namespaces (in children of a gameobject)
1. Specify a module name
2. Specify a namespace containing the children component
3. Search for an active GameObject which children contain the desidered component
4. Play with the children component fields

### Usage video example on the game "Sons of the Forest"
[![Video example](https://i.imgur.com/b3adTug.png)](https://youtu.be/TqL_u4I1ot8)

### Credits
Thanks to [sneakyevil](https://github.com/sneakyevil) for [IL2CPP_Resolver](https://github.com/sneakyevil/IL2CPP_Resolver)
