# Portakal

Portakal is a wannabe proprietary game engine which is created by Roveldo. The engine itself and all the scripting and pipelinging api will purely C++.
Portakal aims to offer entirely scriptable game engine api thus enabling user to mold the engine for their needs.

Supported compilers
- [X] MSVC
- [ ] GNU
- [ ] Clang

Supported platforms
- [X] Windows
- [ ] Linux
- [ ] Mac
- [ ] Android
- [ ] IOS

Supported graphics APIs:

- [ ] OpenGL
- [ ] OpenGL-ES
- [ ] Directx 11
- [X] Directx 12
- [ ] Vulkan
- [ ] Metal

Scriptable APIs:

- [ ] Graphics APIS
- [X] Runtime resource API
- [ ] Editor GUI
- [X] Editor resource API
- [X] Editor asset importer pipeline
- [X] Editor asset authorization tools
- [X] Editor asset processor pipeline
- [X] Editor asset serialization pipeline
- [X] Editor asset visualization
- [ ] Runtime scripting API
- [ ] Editor scripting API

## Programmable graphics APIs

Portakal designed to leveraging injecting user implementation of the graphics APIs.
For example if built-in graphics api's wont expose some RTX features, you can create dedicated implementation for those endpoints.

## Runtime resource API

Portakal's runtime resource system is enum-agnostic, which means you can create new resource variants without the restrictions of the predefined enums.
Let's imagine your company produceses some next generation audio formats, you can simply create a resource which targets your specific file extensions.

## Editor GUI

Portakal offers you to implement your own choice of Immediate GUI style library, by default Portakal only supports IMGUI.
If you are not happy with the ImGui you can simple write your GUI behaviour to override the Portakal's default ImGui implementation.

## Editor resource API

Portakal enables you create your editor-only resource types inside the editor. This simply enables you to create wide range of tools for specific resource types and file formats.

## Editor asset importer pipeline

Portakal has customizable asset import pipeline. You can simply inject your own importer to the pipeline for specific resource types and extensions.
For example if your want to create a copy of the every text file you import, you can easily create this behaviour and inject into the importer pipeline to be executed.
Another example would be creating a custom importer for texture atlases, when you import a texture you can create a sprite atlas automatically.

## Editor asset authorization tools

Portakal encourages you to create your authorization tools for per resource type. You can decide which options you want to tweak for target resource type. 
For example you can create a texture authorization tool which enables you to change the format of the texture directly in the editor.

## Editor asset processor pipeline

Portakal also provides the means to inject behaviours before and after the a resource is imported.
For example for every text file imported you want to edit and add specific word to end of the each text file you imported.

## Editor asset serialization pipeline

Portakal allows you to get your hands dirty and make your serialization and deserialization algorithms upon loading and writing assets to game-ready build pipeline.
Let's say you have a better mesh compression system which enables you to load the levels faster, then feel free to override the specific resource type's asset serialization behaviour.

## Editor asset visualization

Portakal lets you to define your own visualization for your assets in the editor's domain observer window. You can define your own Icon behaviour.

## Runtime scripting API

Portakal accepts user created runtime scripts.

## Runtime scripting API

Portakal accepts user created editor scripts.

