#include "cubiko.h"

#define SAND_MAX_HEIGHT 90
#define SAND_MIN_HEIGHT 1
#define SAND_INCREMENT 1

// ******* Time Select ******* //

class timeField {
    private:
        int x;
        int y;
        int amount;
        bool selected;

    public:
        timeField(int x, int y);
        int get_x() const;
        int get_y() const;
        int get_amount() const;
        bool get_selected() const;
        void set_amount(int amount);
        void set_selected(bool selected);
        void update();
        void draw();
};

// ******* Hourglass ******* //

class bottomSandPool {
    private:
        int x;
        int y;
        int h;
    
    public:
        bottomSandPool();
        int get_y() const;
        int get_h() const;
        void set_y(int y);
        void set_h(int h);
        void update();
        void draw();
};

class topSandPool {
    private:
        int x;
        int y;
        int h;

    public:
        topSandPool();
        int get_y() const;
        int get_h() const;
        void set_y(int y);
        void set_h(int h);
        void update();
        void draw();
};

class sandGrain {
    private:
        int x;
        int y;
        int r;
        int x_speed;
        int y_speed;
    
    public:
        sandGrain();
        void update();
        void draw();
        bool collided(bottomSandPool p);
};

class sandBottle {
    private:
        int x;
        int y;
        int w;
        int h;
        sandGrain grains[10];
        int grain_count;
        topSandPool topPool;
        bottomSandPool bottomPool;
    
    public:
        sandBottle();
        void update();
        void bottle_flip();
        void draw();
        void generate_grain();
        void dequeue_grain(int i);
};