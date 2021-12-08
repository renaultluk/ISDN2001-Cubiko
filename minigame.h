class player {
    private:
        float x;
        float y;
        float baseline_y;
        float w;
        float h;
        float y_speed;
        bool jumped;
        lv_img sprites[4]; // 0,1 = running, 2 = jumping, 3 = dead
        int sprite_index;

    public:
        player();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        float get_y_speed() const;
        int get_sprite_index() const;
        void set_sprite_index(int);
        void update();
        void jump();
};

class gameMap {
    protected:
        float x;
        float y;
        float w;
        float h;
        lv_img sprites[4];
        int sprite_index;
        lv_img ground[4];
        int ground_index;
    
    public:
        gameMap();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        void update(float speed);
};

class background : public gameMap {
    public:
        background();
};

class obstacle {
    private:
        float x;
        float y;
        float w;
        float h;
        lv_img sprites[4];
        int sprite_index;
    
    public:
        obstacle();
        float get_x() const;
        float get_y() const;
        float get_w() const;
        float get_h() const;
        void update(int speed);
        bool collided(player p);
};

class Minigame {
  private:
    player current_player;
    gameMap current_map;
    background current_background;
    obstacle obstacles[10];
    int obstacle_count;
    float current_speed;
    float baseline_speed;
    int score;
    int level;
    int highscore;
    bool game_over;
    
  public:
    Minigame();
    void setup();
    void loop();
    void draw();
    void update();
    void gameOverScreen();
    void set_score(int score);
    void generate_obstacle();
    void dequeue_obstacle(int i);
};