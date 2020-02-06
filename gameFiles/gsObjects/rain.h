#ifndef dwr_rain
#define dwr_rain

#include "../instance.h"
#include "../player.h"

/**
 * This is a rain object.
 * This rains until it hits a solid object, but passes through grates.
 * The tricky thing about rain is it also acts kind of like a teleporter.
 * In other words, the player when touching the rain will be turned into rain,
 * to reform into the player at the end of the rain.
 */

class Rain : public Instance {
    private:
        bool shaderCheck, hardMode;
        float startY, lastDY;
        float time;
        std::vector<float> vertices;
        std::vector<float> colors;
        void initShaders(GLShaders* gls);
    public:
        Rain(double X, double Y, double W, bool hard);
        ~Rain();
        /**
        * Updates the rain's particle effects, and moves the "player" object down.
        */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        /**
         * Deal with player collisions (and create the fake player)
         */
        void collided(Instance* o, double deltaTime);
        /**
         * Updates the height and width
         */
        void fUpdate(double deltaTime);
        /**
         * Deals with drawing the rain.
         */
        void draw(GLDraw* gld, GLShaders* gls);
};

class RainPlayer : public Instance{
    private:
        Player* p;
        bool backTogether;
        double time;
        double timeApart;
        double maxTime;
        double maxTimeApart;
        std::vector<float> vertices;
        std::vector<float> colors;
        // std::vector<float> texs;
    public:
        RainPlayer(Player* pl);
        ~RainPlayer();
        /**
         * Updates the height and width
         */
        void fUpdate(double deltaTime);
        /**
         * Deals with drawing the rain.
         */
        void draw(GLDraw* gld, GLShaders* gls);
};

#endif