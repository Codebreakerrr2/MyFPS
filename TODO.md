# MyFPS - Task List / TODO

Diese Datei enthält alle offenen Tasks und Verbesserungen für das MyFPS-Projekt.

## 🔴 Kritisch (Priorität 1) - Muss gefixt werden

### Enemy-Bug fixen
- [ ] **Bug**: Enemy-Bewegung funktioniert nicht korrekt (`src/game/Enemy.cpp`)
  - Problem: `speed` wird lokal überschrieben, nicht pro Enemy gespeichert
  - Lösung: `speed` und `direction` als Member-Variablen in `Enemy` struct hinzufügen
  - Datei: `include/game/Enemy.h`, `src/game/Enemy.cpp`

### Leere Funktionen implementieren
- [ ] **Enemy Rendering**: `Game::RenderEnemies()` ist leer
  - Gegner sollten gerendert werden (ähnlich wie Entities)
  - Datei: `src/game/Enemy.cpp`

- [ ] **Enemy Damage**: `Game::TakeDamage()` ist leer
  - Schaden sollte verarbeitet werden, Health reduzieren, Tod prüfen
  - Datei: `src/game/Enemy.cpp`

- [ ] **Map System**: `World::Map.cpp` ist komplett leer
  - Map-Loading, Rendering, Kollisionsprüfung implementieren
  - Datei: `src/world/Map.cpp`

---

## 🟡 Wichtig (Priorität 2) - Sollte gefixt werden

### Memory-Management verbessern
- [ ] Raw-Pointer durch Smart-Pointer ersetzen
  - `Shader*`, `Entity*`, `Player*`, `Camera*` → `std::shared_ptr` oder `std::unique_ptr`
  - Oder Ownership klar dokumentieren

### Globale Variablen reduzieren
- [ ] `window` in `Renderer.cpp` → Singleton oder Dependency-Injection
- [ ] `meshes` in `Mesh.cpp` → Klasse statt static
- [ ] `enemies` in `Enemy.cpp` → Klasse statt global

### Error-Handling verbessern
- [ ] OBJ-Loading: Besseres Error-Handling statt stillem Fehlschlagen
- [ ] Shader-Compilation: Programm sollte bei kritischen Fehlern stoppen
- [ ] Logging-System einführen (z.B. spdlog oder einfaches File-Logging)

### Code-Klarheit
- [ ] Kommentar "REDUNDANT MESHLOAD EVENTUELL LÖSCHEN" klären
  - Entweder Funktion löschen oder Kommentar entfernen
  - Datei: `src/engine/Mesh.cpp` Zeile 10, 35

---

## 🟢 Nice-to-have (Priorität 3) - Kann später gemacht werden

### Performance-Optimierungen
- [ ] Uniform-Location-Caching in Shader-System
  - Uniform-Locations einmal cachen statt jedes Frame neu zu suchen
  - Datei: `src/engine/Shader.cpp`

- [ ] Mesh-Pooling für häufig verwendete Meshes
  - Datei: `src/engine/Mesh.cpp`

### Features
- [ ] ~~Networking für macOS/Linux portieren~~ (Nicht nötig - Windows ist Zielplattform)
  - Networking bleibt Windows-only (WinSock2)
  - macOS wird nur für Entwicklung/Testing verwendet

- [ ] Config-System für hardcodierte Werte
  - Fenstergröße, Player-Height, Player-Speed auslagern
  - Datei: `src/main.cpp`, neue Datei `include/config.h`

- [ ] Asset-Manager für besseres Resource-Management
  - Shader, Meshes, Texturen zentral verwalten

### Code-Qualität
- [ ] Doxygen-Kommentare für alle öffentlichen APIs
- [ ] Unit-Tests für Math-Library (Vec, Mat4)
- [ ] CI/CD Pipeline (GitHub Actions / GitLab CI)

### Dokumentation
- [ ] README erweitern mit:
  - Architektur-Übersicht
  - Code-Struktur
  - Contributing Guidelines
  - API-Dokumentation

---

## ✅ Erledigt

- [x] Include-Pfade für case-sensitive Filesystems korrigiert
- [x] `.clang-format` für Code-Formatierung hinzugefügt
- [x] `.editorconfig` für Editor-Einstellungen hinzugefügt
- [x] `.gitignore` für CLion/Cursor aktualisiert
- [x] Projekt plattformunabhängig gemacht (macOS/Linux Support)
- [x] README mit Build-Anleitung erstellt
- [x] GLFW als Vendor-Dependency hinzugefügt

---

## 📝 Notizen

- Player-Height `5.5f` ist ungewöhnlich hoch - sollte überprüft werden
- `phong.vert/frag` Shader existiert, wird aber nicht verwendet
- `bild.vert/frag` Shader existiert - Zweck unklar

---

## 🎯 Nächste Schritte

1. Enemy-Bug fixen (kritisch)
2. Enemy-Rendering implementieren
3. Map-System implementieren
4. Memory-Management modernisieren

---

**Letzte Aktualisierung**: 2026-02-16
**Branch**: `dev`
