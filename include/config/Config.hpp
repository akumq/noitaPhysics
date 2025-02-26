#ifndef CONFIG_H
#define CONFIG_H

class Config {

    public: 
        static constexpr float CELL_SIZE = 4.0f;

        static constexpr float WIDTH = 1000;
        static constexpr int HEIGHT = 1000;

        static constexpr float GRAVITY = 9.81f;
        static constexpr float TIME_STEP = 0.01f; 


        static constexpr float MOUSE_RADIUS_BASE = 10.0f;
        static constexpr float MOUSE_RADIUS_MAX= 50.0f;
        static constexpr float MOUSE_RADIUS_MIN = 1.0f;
        static constexpr float MOUSE_RADIUS_STEP= 1.0f;


        static constexpr float WATER_MASS = 1.0f;

        static constexpr int CORROSIVE_TICK = 1000;

};


#endif // CONFIG_H