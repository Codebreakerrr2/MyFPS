## MyFPS

MyFPS is a small first-person shooter prototype written in C++17 using OpenGL and GLFW.  
It has a lightweight engine layer (rendering, input, math, physics) and a simple game layer (player, enemies), plus optional UDP networking (currently Windows-only).

### Requirements

- **C++17** compatible compiler
- **CMake ≥ 3.20**
- **GLFW** and **GLAD** are included as part of this repository
- **Windows**: required for networking (WinSock2).  
- **macOS / Linux**: rendering and gameplay work; networking sources are excluded from the build.

### Building

From the project root:

```bash
cd /Users/Admin/MyFPS   # or the path where you cloned this repo
mkdir -p build
cd build
cmake ..
cmake --build .
```

On **Windows**, this builds `bin/MyFPS.exe` and enables UDP networking.  
On **macOS / Linux**, this builds `bin/MyFPS` without networking; the rest of the game runs normally.

### Running

After a successful build:

```bash
cd build/bin
./MyFPS    # or MyFPS.exe on Windows
```

Assets (shaders, models, etc.) are copied automatically to `build/bin/assets` by CMake.

### Models / Assets

`src/main.cpp` expects the following OBJ models (relative to the project root):

- `assets/models/Anime_charcter.obj`
- `assets/models/building.obj`

Create the `assets/models` directory and place your OBJ files there (or adjust the paths in `src/main.cpp` to match your own models). If a model cannot be loaded, the game will print an error message to the console but will still run.

### Controls (default)

- **W / A / S / D**: Move the player
- **Mouse**: Look around
- **Left Shift**: Sprint
- **Esc**: Quit

### Notes

- Networking (client/server, UDP) is implemented with WinSock2 and is only compiled on Windows.
- Physics and world/level systems are intentionally minimal and can be expanded.
