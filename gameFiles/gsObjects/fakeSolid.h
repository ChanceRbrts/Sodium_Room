#ifndef dwr_fakesolid
#define dwr_fakesolid

#include "../instancelev.h"

/**
 * An object made up of tiny particles.
 * These particles separate when the player is far if the instance is solid.
 * These particles separate when the player is near if the instance is not solid.
 */
class FakeSolid : public Instance{
    private:
        /// The vertices that make up the instance.
        std::vector<float> vertices;
        /// The color array for the vertices.
        std::vector<float> colors;
        /// Offsets in animation to keep things from looking too organized
        std::vector<float> offsets;
        /// The texture coordinates for each of the vertices.
        std::vector<float> texts;
        /// Whether or not we have created the shader for this object.
        bool loadedShader;
        /// If this is true, it swaps the behavior of the particles for if the player is/isn't solid.
        bool swap;
        /// The player coordinates
        float pX, pY;
        /// The animation time for the shader.
        float time;
        /// The colors of the last frame. (Used to see if we need to change the color array)
        float lastR, lastG, lastB;
        /**
         * Check to see if we need to create the shader for our FakeSolid
         * @param gls GLUtil's shader functions.
         */
        void checkShader(GLShaders* gls);
    public:
        /**
         * Constructor for the FakeSolid
         * @param X The left-most coordinate of the solid (World coords)
         * @param Y The up-most coordinate of the solid (World coords)
         */
        FakeSolid(float X, float Y);
        /// Deconstruction of the FakeSolid
        ~FakeSolid();
        /**
         * Drawing code for the FakeSolid
         * @param gld The GLUtil's draw functions.
         * @param gls The GLUtil's shader functions.
         */
        void draw(GLDraw* gld, GLShaders* gls);
        /**
         * This updates the FakeSolid, doing animation and checking where the player is.
         * @param deltaTime The time in between the previous frame and this frame.
         * @param keyPressed The array of keys pressed this frame.
         * @param keyHeld The array of the keys that are held down. 
         * @param player The player of the game.
         */
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
};

/**
 * An object that creates a ton of FakeSolids based on a level.
 */
class FakeSolids : public InstanceLev{
    public:
        /**
         * Constructor for FakeSolids
         * @param textureMap The level filepath of the fakesolid.
         */
        FakeSolids(std::string textureMap);
        /**
         * Just makes it so this object wants to be removed.
         * @param deltaTime The time in between the previous frame and this frame. Here for consistency.
         */
        void fUpdate(double deltaTime);
};

#endif