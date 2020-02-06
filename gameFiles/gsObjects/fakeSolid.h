#ifndef dwr_fakesolid
#define dwr_fakesolid

#include "../instance.h"

class FakeSolid : public Instance{
    private:
        std::vector<float> vertices;
        std::vector<float> colors;
        std::vector<float> offsets;
        bool loadedShader;
        bool swap;
        float pX, pY, time;
        void checkShader(GLShaders* gls);
    public:
        FakeSolid(float X, float Y);
        ~FakeSolid();
        void draw(GLDraw* gld, GLShaders* gls);
        void update(double deltaTime, bool* keyPressed, bool* keyHeld, Instance* player);
};

class FakeSolids : public Instance{
    public:
        FakeSolids(std::string textureMap);
};

#endif