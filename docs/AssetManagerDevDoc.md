# Anforderungsspezifikation – Asset Manager (please See Update 9.03.2026)

Beim Entwickeln des Asset Managers sind die folgenden Anforderungen zwingend einzuhalten.  
Eine Nichtbeachtung kann zur Ablehnung durch den Administrator führen

Vorschläge gerne gesehen!
---

## Grundlage

1. **Eindeutige Identifikation**  
   Jedes Asset muss eindeutig identifizierbar sein (z. B. über eine ID oder einen eindeutigen Schlüssel).

2. **Zentrale Verwaltung**  
   Alle Assets müssen über den Asset Manager verwaltet werden.  
   Die Verantwortung für Assets liegt ausschließlich beim Asset Manager.

---

## Performance-Anforderungen

1. **Referenzzählung**  
   Assets, die nicht mehr verwendet werden, sollen automatisch aus dem Speicher entfernt werden.

2. **Lazy Loading**  
   Assets werden erst geladen, wenn sie tatsächlich benötigt werden.

3. **Asynchrones Laden**  
   Das Laden von Assets soll unabhängig vom Hauptthread erfolgen, sodass der Programmablauf nicht blockiert wird.

---

## Exception- und Robustheitsanforderungen

1. **Kein nullptr**  
   Der Asset Manager darf kein unkontrolliertes `nullptr` zurückgeben.  
   Fehlerzustände müssen intern korrekt behandelt werden.

2. **Exception Handling**  
   Der Asset Manager darf keine Exceptions nach außen werfen.  
   Alle Fehler sind intern abzufangen, um Systemabstürze zu verhindern.



# UPDATE  9.03.2026

Ich habe festgestellt, dass Entity als Struct, in dem alles in einem Struct gepackt wird (z. B. Shader, Material, Name usw.), das Rendern stark unoptimiert macht. Schon bei 5000 Entities muss ich mit Performance-Beeinträchtigungen rechnen.

Der Hintergrund ist, dass so ein Struct immer Rohpointer speichern muss. Außerdem ist Data Alignment gerade nicht seine Stärke, und es kommt immer wieder zu Cache Misses oder dazu, dass unnötig viele Daten in den Cache geladen werden, obwohl man sie gar nicht braucht.

Also ist Entity als Objekt gar nicht so eine gute Idee.

Ich überlege deshalb, Entity nur als eine ID zu machen und stattdessen Arrays zu verwenden, z. B.:
- Array of Shaders
- Array of Materials
- Array of Names
- usw.

Dann mappt man die Entities einfach darauf. Dadurch ist Entity im Grunde nur noch ein Mapping, und man muss die Sachen nicht unbedingt direkt speichern.

**Zum Beispiel:**
Ein Shader für '1000' Entities.
Mit Entity als Objekt müsste ich '1000'-mal einen Rohpointer speichern.
 
Mit Mapping hat man einfach '1000' Entities, die auf einen Shader-Index gemappt sind, und fertig.

Das gibt auch eine gewisse Flexibilität, aber ich muss dafür sehr viel refaktorieren.
Der Editor, der Renderer, eigentlich alles müsste verändert werden.

Trotzdem glaube ich, dass ich das machen muss um später es nicht zu bereuen.