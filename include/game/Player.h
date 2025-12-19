namespace Game {

    struct Player {
        float x,y,z;
        int meshID;
        int health;
    };

    extern Player player;

    void InitPlayer();
    void UpdatePlayer(float deltaTime);
    void RenderPlayer();

    int GetHealth();
    void TakeDamage(int amount);

    void FireWeapon();
    void ReloadWeapon();

    float GetX();
    float GetY();
    float GetZ();
    void SetPosition(float x, float y, float z);
}
