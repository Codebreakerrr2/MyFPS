#include <gtest/gtest.h>

#include "asset_manager/EntityManager.h"


TEST(EnitityManager,CreatingEntity) {

    Manager::EntityManager entityManager;
    Manager::EntityID id1= entityManager.CreateEntity("first");
    Manager::EntityID id2=  entityManager.CreateEntity("second");
    Manager::EntityID id3=entityManager.CreateEntity("third");
    // first test Enitity is saved
    Engine::Entity* first = entityManager.GetEntity("first");
    Engine::Entity* firstByID = entityManager.GetEntity(id1);



    EXPECT_EQ(entityManager.GetAllEntities().size(), 3);
    EXPECT_EQ(first,firstByID);

    entityManager.DestroyEntity(id1);
    EXPECT_EQ(entityManager.GetAllEntities().size(), 2);

    entityManager.DestroyAllEntities();
    EXPECT_EQ(entityManager.GetAllEntities().size(), 0);



    //
}
