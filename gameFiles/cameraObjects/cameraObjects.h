#ifndef dwr_camera_object
#define dwr_camera_object

#include "instance.h"

class Camera {
    private:
        /// These deal with the position of the camera.
        double x, y;
        double tarX, tarY;
    public:
        Camera();
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
        virtual void modifyCamera(Camera* c, double deltaTime){};
};

class OneWayCameraObject : public CameraObject {
    private:
        float x, y;
        float w;
        int dir;
    public:
        OneWayCameraObject(double X, double Y, double W, int direction);
        void modifyCamera(Camera* c, double deltaTime);
};

#endif