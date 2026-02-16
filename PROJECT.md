# MyFPS - Projekt-Übersicht

## Projekt-Status

**Aktueller Branch**: `dev`  
**Target Platform**: Windows (primäre Plattform)  
**Development Platforms**: Windows, macOS (für Entwicklung/Testing)  
**Build-Status**: ✅ Erfolgreich (macOS, Windows)  
**Code-Qualität**: 7.5/10

**Hinweis**: Das Projekt ist primär für Windows entwickelt, kompiliert aber auch auf macOS für Entwicklung und Testing.

## Projekt-Struktur

```
MyFPS/
├── src/
│   ├── engine/          # Rendering, Input, Physics, Shader, Mesh, Camera
│   ├── game/            # Player, Enemy (Gameplay-Layer)
│   ├── world/           # Map-System (minimal)
│   ├── math/            # Vec2/3/4, Mat4 (Math-Library)
│   └── network/         # UDP-Networking (nur Windows)
├── include/             # Header-Dateien
├── assets/
│   └── shaders/         # GLSL Shader
└── glfw/                # Vendor-Dependency
```

## Aktuelle Features

### ✅ Implementiert
- OpenGL 3.3 Rendering (GLFW + GLAD)
- Entity-System (Transform + Material)
- Shader-System (Vertex + Fragment)
- Mesh-System (VAO/VBO/EBO)
- Camera-System (FPS + Third-Person)
- Player-Movement (WASD + Maus)
- Math-Library (Vec2/3/4, Mat4)
- Cross-Platform Development (Windows + macOS)

### ⚠️ Teilweise implementiert
- Enemy-System (Struktur vorhanden, Rendering fehlt)
- Physics-System (Basis vorhanden, wenig genutzt)
- Map-System (Interface vorhanden, Implementierung fehlt)
- Networking (nur Windows)

### ❌ Nicht implementiert
- Asset-Manager
- Config-System
- Logging-System
- Unit-Tests

## Bekannte Probleme

Siehe [TODO.md](./TODO.md) für vollständige Liste.

### Kritisch
1. Enemy-Bewegung funktioniert nicht korrekt
2. Enemy-Rendering ist leer
3. Map-System ist leer

### Wichtig
1. Memory-Management könnte moderner sein
2. Globale Variablen sollten reduziert werden
3. Error-Handling könnte besser sein

## Nächste Meilensteine

### Milestone 1: Bug-Fixes (Kurzfristig)
- [ ] Enemy-Bug fixen
- [ ] Enemy-Rendering implementieren
- [ ] Map-System implementieren

### Milestone 2: Code-Qualität (Mittelfristig)
- [ ] Memory-Management modernisieren
- [ ] Error-Handling verbessern
- [ ] Code-Dokumentation hinzufügen

### Milestone 3: Features (Langfristig)
- [ ] Config-System
- [ ] Asset-Manager
- [ ] Unit-Tests
- [ ] ~~Networking für macOS/Linux~~ (Nicht nötig - Windows ist Zielplattform)

## Entwicklung

### Workflow
- **main**: Stabiler Stand
- **dev**: Entwicklungs-Branch
- **feature/***: Feature-Branches

### Code-Formatierung
- `.clang-format` für einheitliche Formatierung
- `.editorconfig` für Editor-Einstellungen

### Build
```bash
mkdir build && cd build
cmake ..
cmake --build .
cd bin && ./MyFPS
```

## Mitwirkende

- Entwickler 1 (CLion)
- Entwickler 2 (Cursor)

## Ressourcen

- [README.md](./README.md) - Build-Anleitung
- [TODO.md](./TODO.md) - Task-Liste
- [.clang-format](./.clang-format) - Code-Formatierung

---

**Letzte Aktualisierung**: 2026-02-16
