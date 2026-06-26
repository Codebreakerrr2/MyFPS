## AABB

# Anforderung:
   Kollision check von 2 Objekten in 3d in hinsicht auf AABB
    durch Raycast Obejkte auswählen können


# Aufgabe Unterteilung 
    AABB_ADT und AABB_System

# AABB_ADT
    datastrctures:
    AABB: MIN MAX
   
    

    Algos:
    
    // im prinzip erzeugung von AABB durch calcAABB aus mesh
    calcAABB(Mesh) -> AABB

    TransformAABB(AABB,Transform) -> AABB

    intersect(AABB,AABB) -> bool

    intersect(AABB,Ray) -> bool

# AABB_System
    das System nutzt die ADT um Anforderungen gerecht zu werden.
    beziehungsweise AABB_System bietet schnittstellen etc und ist der sichtbare teil und kennt transform etc z.b
    was genau noch macht das System so anders dass es den mehrwert gibt dass er existiert?
    insgesamt kombiniert er glaube ich vieles.

    Datenstrukturen:
     AABB_component: WorldAABB, Dirty

    
     AABBQueryItem
   entity: EntityID
   box: AABB

 CollisionEvent
   entityA: EntityID
   entityB: EntityID

RaycastHit
   entity: EntityID
   distance: float 
    Ray: Vec
     
     schnittstellen:
     getKollisions(AABBS-Snapshot?) -> List of collision Pair oder collision event
     find nearRayIntersect(Ray,all the AABB or Entity?)  -> one Enitty or one AABB 
    
Invariante:
min <= max
dirty = false dann worldaabb muss neu berechnet werden also konsistent bleioben
dirty wird von regsitry gesetzt. 


betrifft Module:
Types.h ComponentToType must get a case for AABB
Types.h GetComponentName also
Registery muss include the AABB pool aswell
pool.h getpoolname must include aabb aswell i dont know why i just dont wanna touch that shit anymore but its ok to review everytime i land there haha
in Types.h ComponentType AABB already exits as enum 