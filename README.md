# MyFPS Engine 🚀

Eine hochperformante, von Grund auf in C++ entwickelte Game Engine mit Fokus auf datenorientiertem Design (ECS) und moderner Rendering-Architektur.

---

## 📽️ Showcase

| Feature                                | Vorschau |
|:---------------------------------------| :--- |
| **Rendering Pipeline and hot loading** | ![Renderer Demo](assets/demos/render_hot_load.gif) |

---

## 🌟 Kern-Features

### ⚡ Data-Oriented ECS (Entity Component System)
Das Herzstück der Engine ist eine maßgeschneiderte ECS-Architektur:
- **Sparse Sets:** Blitzschneller O(1) Zugriff auf Komponenten bei gleichzeitig dichter Speicherung für maximale Cache-Lokalität.
- **Cache-Optimiert:** Minimale Cache-Misses beim Iterieren über 100.000+ Entities.
- **Typ-Sicherheit:** Modere C++ Template-Metaprogrammierung für typsicheren Komponentenzugriff.

### 🎨 Moderne Rendering-Pipeline
- **Frontend/Backend Entkopplung:** Ein dedizierter `RenderBuffer` mit Double-Buffering trennt Spiellogik vom Rendering-Thread.
- **State Sorting:** Automatische Sortierung von Draw-Calls nach Shader und Material, um OpenGL-State-Changes zu minimieren.
- **Viewport Management:** Flexibles System für mehrere Viewports (z.B. für Editor-Overlays oder Splitscreen).

### 🛠️ Weitere Systeme
- **Custom Math Library:** Eigene Implementierung von `Vec3`, `Mat4`, `Quaternions` und Kollisionsgeometrie.
- **Input System:** Abstrahiertes Keyboard- und Mouse-Handling.
- **Camera System:** Flexibler Fly-Camera Controller mit Perspektiv- und Orthogonal-Projektion.

---

## 🏗️ Architektur-Überblick


---

## 🚀 Tech Stack
- **Sprache:** C++20
- **Grafik-API:** OpenGL 4.x
- **Windowing:** GLFW & GLAD
- **Build-System:** CMake

---

## 🛠️ Installation & Build

### Voraussetzungen
- CMake (3.20+)
- Ein C++20 fähiger Compiler (MinGW, MSVC, Clang)

### Build-Vorgang
```powershell
mkdir build
cd build
cmake ..
cmake --build . --target Game
```

---

## 📈 Roadmap (WIP)
- [ ] **Physics Engine:** Integration von AABB und OBB Kollisionsabfragen.
- [ ] **OpenGL Instancing:** Performance-Boost für massenhaft identische Objekte.
- [ ] **PBR Rendering:** Physically Based Rendering für realistische Materialien.
- [ ] **Editor Integration:** ImGui-basiertes Tooling zur Manipulation von Entities in Echtzeit.


---

## 📝 Lizenz


---
*Entwickelt mit Fokus auf Performance und technischem Tiefgang.*


