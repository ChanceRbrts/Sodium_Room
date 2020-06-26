#ifndef dwr_camera_object
#define dwr_camera_object

#include "instance.h"

class Camera {
    private:
        /// These deal with the position of the camera.
        double x, y;
        double tarX, tarY;
        double diffX, diffY;
        double progressX, progressY;
        double animTime, maxAnimTime;
    public:
        Camera();
        void setPosition(double X, double Y);
        /// These are the velocities of the camera.
        double dX, dY;
        void setTarget(double targetX, double targetY);
        double getX(){ return x; };
        double getY(){ return y; };
        void moveCamera(Instance* player);
        void startMovement(double deltaTime);
        void finishMovement(double deltaTime);
};

class CameraObject {
    public:
        CameraObject();
        virtual void modifyCamera(Camera* c, double deltaTime, double W, double H){};
};

class OneWayCameraObject : public CameraObject {
    private:
        float x, y;
        float w;
        int dir;
    public:
        /**
         * Constructor for a One Way Camera Object
         * @param X The left-most position in unit coords.
         * @param Y The up-most position in unit coords.
         * @param W The width/height of the object in unit coords (Depends on direction)
         * @param direction 0: +Y Check, 1: +X Check, 2: -Y Check, 3: -X Check
         */
        OneWayCameraObject(double X, double Y, double W, int direction);
        void modifyCamera(Camera* c, double deltaTime, double W, double H);
};

#endif