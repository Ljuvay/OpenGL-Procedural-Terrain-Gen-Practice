# Procedural Terrain Generator

An early learning project from November 2025, built while I was learning OpenGL and modern C++. I've since moved on to [TEngine](https://github.com/Ljuvay/TEngine), where my current work lives. This repo is kept as a record of how my work has progressed.

## What it does

- Generates infinite-style terrain from multi-octave Perlin noise (6 octaves, 0.45 persistence), with a random seed each run.
- Splits the world into chunks. Each chunk builds its own vertex grid and triangle indices on the CPU and uploads them to the GPU as a VAO/VBO/EBO.
- Streams chunks in around the camera as you move, capped at a fixed number of new chunks per frame.
- Colors terrain by height in the fragment shader (sand, grass, rock, snow).
- Uses C++ move semantics so chunks can live in containers without duplicating GPU buffer handles.

## Limitations

- **Performance:** it runs laggy. There's no frustum culling and no level of detail, so every chunk in range is drawn at full resolution. Chunk generation also happens on the main thread, and chunks are never unloaded from memory.
- **Architecture:** the terrain, chunk, and rendering code is tightly coupled and was organized ad hoc as I learned.
- **Visuals:** no lighting or normals, so the terrain is colored by height only.

## What I learned

This was my first personal C++ project, and I went almost straight from rendering a cube to generating terrain. (The default `Chunk` constructor, which still draws a cube, is left over from that.) I learned a lot about C++ and OpenGL, and the project showed me where I needed to improve: graphics performance (culling, LOD) and code architecture. Frustum culling and terrain LOD are now on TEngine's roadmap because of this project.

## Credits

- `Shader.h/.cpp` and `Camera.h/.cpp` are from the LearnOpenGL textbook.
- `Noise.h/.cpp` are from other GitHub users (credited in the files).
- AI tools (ChatGPT, Microsoft Copilot) helped with debugging and learning.

## Screenshots

<img width="1919" height="1024" alt="Procedural terrain with height-based coloring, November 2025" src="https://github.com/user-attachments/assets/8496cc17-c2c9-417e-b1a3-d783ec05cee1" />
<img width="1919" height="1031" alt="Procedural terrain from a second angle, November 2025" src="https://github.com/user-attachments/assets/9bbcce9b-f249-43ee-93f6-0c18e4734d59" />

https://github.com/user-attachments/assets/57b7832c-091d-4f3a-b13d-a4d4c0921596
