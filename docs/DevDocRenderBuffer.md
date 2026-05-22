

### 🛠️ Feature-Analyse: RenderBuffer-Optimierung

| Punkt | Details |
| :--- | :--- |
| **Welches Problem löst es?** | Verhindert Thread-Interferenzen (Race Conditions) zwischen Simulation und Renderer. Zudem wird der Allokations-Overhead minimiert, indem Speicher durch `swap` wiederverwendet wird, statt ihn in jedem Frame neu zu reservieren. |
| **Welche Alternativen gab es?** | 1. **Direktes Locking:** Renderer sperrt die Registry (führt zu niedrigen FPS). <br> 2. **Triple Buffering:** Eliminiert Wartezeiten komplett, ist aber speicherintensiver. <br> 3. **Lock-free Queues:** Schwerer zu sortieren für GPU-Batching. |
| **Warum dieser Weg?** | **Double-Buffering mit Pointer-Swap** ist der Industriestandard für die Entkopplung. Es hält die Mutex-Sperrzeit extrem kurz und ermöglicht das Sortieren der Draw-Calls (State-Minimierung) ohne den Simulations-Thread zu blockieren. |
| **Performance-Kosten?** | Minimaler CPU-Overhead für `std::sort` und den Pointer-Swap. Etwas mehr Speicherbedarf, da wir zwei Buffer (Front/Back) für die Draw-Commands vorhalten. |
| **Wo sind die Grenzen?** | Es entsteht eine Latenz von genau einem Frame (der Renderer sieht den Stand des letzten fertigen Snapshots). Bei plötzlichen Massen-Spawns von Entities muss der Vektor einmalig vergrößert werden. |

---

### 📊 Ablauf-Visualisierung (PlantUML)


[grafk](docs/GrafikRenderBuffer.puml)


---

### 💡 Profi-Tipp für deine Begründung (Vorbereitung auf Monat 1-3)
Wenn dich jemand fragt: *"Warum sortierst du im Sim-Thread und nicht im Render-Thread?"*
**Deine Antwort:** *"Der Render-Thread soll nur für das 'Füttern' der GPU zuständig sein. Durch das Sortieren im Sim-Thread nutzen wir die Parallelität der CPU aus. Da der Snapshot dort ohnehin vorbereitet wird, minimieren wir die State-Changes (Shader-Wechsel) für den Renderer, bevor dieser überhaupt den ersten Draw-Call absetzt."*

Soll ich als nächstes das **Component Grouping** im ECS angehen, damit das Sammeln der Daten (`updateReadBuffer`) noch schneller wird?