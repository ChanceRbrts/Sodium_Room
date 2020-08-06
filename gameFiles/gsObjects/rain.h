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
        /// Whether or not we need to check if we have created a shader for this object.
        bool shaderCheck;
        /// Whether or not we've had an update frame yet.
        bool loadedIn;
        /// The current behavior of the rain (0->Default, 1->Instant, 2->Upside-Down)
        int rainMode;
        /// Used with having the rain fall.
        float startY, lastDY;
        /// Time for the animation of rain.
        float time;
        /// The different vertices that make up the lines for the rain.
        std::vector<float> vertices;
        /// The different colors that are coordinates to the vertices.
        std::vector<float> colors;
        /**
         * Initializes shaders if they haven't been initialized yet.
         * @param gls The GLUtil's shader functions.
         */
        void initShaders(GLShaders* gls);
    protected:
        /**
         * Initializes the drawing layers.
         * This is special since we need to draw rain on 2 different layers.
         * @return The layers to draw to.
         */
        std::vector<int> initLayers();
    public:
        /**
         * Constructor for the Rain
         * @param X The left-most coordinate of the rain (In world coords)
         * @param Y The y-coord of where the rain starts (In world coords)
         * @param W The width of the rain object (In world coords)
         * @param mode The default mode of the rain (0->Default, 1->Instant, 2->Upside-Down) 
         */
        Rain(double X, double Y, double W, int mode);
        /// Deconstructor of the Rain
        ~Rain();
        /**
         * Updates the rain's particle effects, and moves the "player" object down.
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld);
        /**
         * Deal with player collisions (and create the fake player)
         * @param o The instance that collided with the player.
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void collided(Instance* o, double deltaTime);
        /**
         * Updates the height and width
         * @param deltaTime The time in between the previous frame and this frame.
         */
        void fUpdate(double deltaTime);
        /**
         * Deals with drawing the rain.
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         * @param layer The layer that is currently being drawn to.
         */
        void draw(GLDraw* gld, GLShaders* gls, int layer);
};

/**
 * This is a helper instance for the rain.
 * When the player turns into rain, this instance does the animation of the player turning into rain.
 */
class RainPlayer : public Instance{
    private:
        /// The current player.
        Player* p;
        /// Whether the animation has the player getting back together
        bool backTogether;
        /// The time going down.
        double time;
        /// The amount of spacing apart.
        double timeApart;
        /// The max time going down. (Used for animation)
        double maxTime;
        /// The max amount of spacing apart.
        double maxTimeApart;
        /// The different vertices that represent the player turning into rain.
        std::vector<float> vertices;
        /// The colors of the vertices of the player.
        std::vector<float> colors;
        // std::vector<float> texs;
    protected:
        /**
         * Initializes the drawing layers.
         * This is special since we need to draw rain on 2 different layers.
         * @return The layers to draw to.
         */
        std::vector<int> initLayers();
    public:
        /**
         * The constructor of the RainPlayer
         * @param pl The player that we're turning into rain
         * @param gDown Whether or not the player is heading down
         */
        RainPlayer(Player* pl, bool gDown);
        /// The deconstructor of the RainPlayer
        ~RainPlayer();
        /**
         * Updates the height and width
         * @param deltaTime The time in between this frame and the previous frame.
         */
        void fUpdate(double deltaTime);
        /**
         * Deals with drawing the rain.
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         * @param layer The layer that is currently being drawn to.
         */
        void draw(GLDraw* gld, GLShaders* gls, int layer);
};

#endif