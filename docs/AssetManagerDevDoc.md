# Anforderungsspezifikation – Asset Manager

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
