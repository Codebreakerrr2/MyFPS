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

## Umsetzung
 Ich denke, ich mache alles über Pools.

Für alle wichtigen Systeme braucht man ja Daten. Für jedes System gibt es ab jetzt eine Datenkomponente. Diese Komponente stellt alle notwendigen Daten für das System zur Verfügung, z. B. den Renderer, damit er cache-freundlich arbeiten kann.

Alle Pools werden über eine zentrale Registry verwaltet. Die Registry ist unter anderem zuständig für:

- Löschen von Entities
- Konsistenz der Pools
- Erzeugung von Entities
- Laden von Daten / Assets

Später kann man dann, je nach Performance, auch andere Features einbauen, aber erstmal werden nur die notwendigen Operationen implementiert.

## UPDATE 10.03.2026

- Ich habe aktuell hashmaps in pools um entity auf component zu mappen, das ist zwar ok aber hashmap hat viel overhead, ausserdem es ist nicht cache freundlich und viel zu viel speicher last, bucket lits hash function etc... 
also ich denke so mache ich das:
wir haben 3 arrays componnent, entites und lookup. wir bauen eine bijektive abbildung zwischen component entites und speichern in lookup entities ID als Index. dadurch kein hashmap overhead kein hin und her und super cache freundlich. cache ist unser hotspot. 


- ich merke sparse Array ist zwar gut aber wenn ein pool z.b Shader keinen entity hat und wir bei entity 10000 angekommen sind dann müssen wir sparse[10000] Valid Index setzen. und der rest von 0-9999 invalid Index das ist Speicehr Verschwendung also nicht alle pools sparse benutzen.

- ## UPDATE 12.03.2026
# Registry ? Gedanken strukturiert

## 1. Allgemeine Idee der Registry

- An der Registry wird gerade gearbeitet.
- Die Registry ist ähnlich wie eine API für andere Systeme.
- Andere Systeme greifen über die Registry auf Assets zu.

**Beispiele für Assets:**
- Shader
- Material
- Entity
- Transform


## 2. Erste Aufgabe

- Zuerst müssen die genauen Aufgaben der Registry aufgelistet werden.
- Danach kann man sich mit den Funktionsdefinitionen beschäftigen.


## 3. Grundfunktionen der Registry

Die Registry soll in der Lage sein:

- Assets zu erstellen
- Assets zu löschen
- Assets zugreifbar zu machen
- die interne Konsistenz der Pools zu gewährleisten


## 4. Assets erstellen

Beim Erstellen von Assets muss man wahrscheinlich jedes Asset einzeln betrachten.

**Beispiel:**
- Shader Asset erstellen

Aktuell ist das System aber so gebaut, dass:

- keine einzelnen Komponenten erstellt werden können

Stattdessen:

- Es wird immer eine Entity erstellt
- Diese Entity hat dann eine bestimmte Komponente oder nicht

**Beispiel:**

- Eine Entity hat einen Shader
- Eine Entity hat keinen Shader

Also:

? Für jeden Shader oder anderes Asset existiert immer eine Entity.


## 5. Gewünschte Flexibilität

Es wäre gut, wenn man sagen könnte:

- Erstelle eine Entity mit Shader
- Erstelle eine Entity mit Transform
- Erstelle eine Entity mit Material

Also beim Erstellen direkt bestimmen können:

- welche Komponenten die Entity bekommt.


## 6. Zweck der Entities

Man könnte zusätzlich festlegen:

- ob die Entity für Rendering gedacht ist
- oder für Physik

Also eine Art Verwendungszweck der Entity.


## 7. Veränderbarkeit von Assets

Man könnte auch Funktionen haben, die verhindern, dass bestimmte Komponenten verändert werden.

**Zum Beispiel:**

- Material eines Objekts nicht verändern
- Shader nicht verändern
- Transform nicht verändern

Das wäre nützlich für den Editor, damit man bestimmte Dinge kontrolliert ändern kann.

- ## UPDATE 16.03.2026

Also nochmal zur Erfrischung. dieses ECS system habe ich aus einem wichtigem Grund und zwar dass man entites einfach masken kann mit einem gewissen profil. man braucht keine klassen mehr und auch kein Objekt Entity. Objekt Entity war auch problem weil nicht
jede Entity alle attribute beinhaltet und es für cpu schnell uneffizient wird, weil er unnötige daten lesen muss. 
genau also aufgezählt heisst es,
1. CPU EFFIZIENZ weil keine unnötige Attributen
2. Felixibilitat von Entity Typen durch mappen 
3. keine riesige Entity Objekt. 

eigentlich unabdingbar.

was kommt nun, 
ich habe überlegt und auch gelesen was ich letztes mal geschrieben hatte. Das Problem dass ich gemerkt habe war, dass ich Shader in pool packe, das ist aber riesen memory verschwendung weil dann musste ich für jede Entity quasi den Shader neu compileiren und erzeugen.
deswegen greifen ich auf die alte idee von Asset Manager z.b Shader Manager. Mein ecs system zusammen mit dem Registery beinhalten information aber keine wirklcihe assets. eine Manager für jeden Assettype macht sinn auf jeden fall.

 ## UPDATE 17.03.2026

 So ich möchte nun etwas grobe Sicht geben zu den aktuellen Überlegungen.
 Ich habe ja pools, Registery.  die sind eigentlcih nur ja wie soll ich das sagen einfach eine schicht von inforamtion also so eine organisationsschciht und diese schicht stellt einfach sicher dass alles richtig get referenziert usw wird. die eignetlcih daten liegen in assetmanagers. und genau also registry ist das api und pools sind einfach information behälter für diese api und die wirklciehn daten leigen wo anders. 

 ich habe total mein kopf druber zerbrochen jetzt wie ich z.b pools die einfach nur values speicher wie Transform von pools die wirkilch assets speichern, von einandner unterscheide. weil ich will nicht jetzt jede shader als komponent speichern. da kam die idee von einem struct dass ShaderId behält und wir das einfach in registry dann auflösen, dafür muss aber registry den assetmanager kennen, was aber viel geiler wäre ist dass registry einfach handels bekommt und dann durch handels values holt und keine ahnung über assetmanager hat das ist aber so eine komplikation an sich es abstrahiert bisschen für registry aber ich weiss nicht ob das wirklcih nötig ist. ich wette es hat einen vorteil weil ohne handel muss registry dann immer eine implementation haben für jeden asset type und muss dessen assetmanager kennnen um ID aufzulösen. wenn wir aber ein tempalte assethandler haben dann ist die get funktion für alle pools die assetmanager brauchen gleich und pools die nicht assetmanager brauchen haben dann halt kein handler overhead und die sind dann anders. 

 ubersicht
 2 pool arten 
 - 1 die mit handel
 - 2 die mit einfachen values

 handel wird als template geschrieben.
 registry kennt dann halt nur die funktion von handel und weiss nichts uber assetmanagers
 