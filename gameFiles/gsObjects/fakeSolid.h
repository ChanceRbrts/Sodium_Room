#ifndef dwr_fakesolid
#define dwr_fakesolid

#include "../instancelev.h"

class FakeSolid : public Instance{
    private:
        std::vector<float> vertices;
        std::vector<float> colors;
        std::vector<float> offsets;
        std::vector<float> texs;
        bool loadedShader;
        bool swap;
        float pX, pY, time;
        float lastR, lastG, lastB;
        void checkShader(GLShaders* gls);
    public:
        FakeSolid(float X, float Y);
        ~FakeSolid();
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
};

class FakeSolids : public InstanceLev{
    public:
        FakeSolids(std::string textureMap);
        void fUpdate(double deltaTime);
};

#endif