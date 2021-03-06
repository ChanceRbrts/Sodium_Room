#ifndef dwr_camera_object
#define dwr_camera_object

#include "../instance.h"

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
        void finishMovement(double deltaTime, bool loaded);
};

class CameraObject {
    public:
        CameraObject();
        virtual ~CameraObject(){};
        virtual void setPosition(double X, double Y, bool relative){};
        virtual pointDouble interactWithPlayer(double cX, double cY, double W, double H, Instance* p, double deltaTime){
            return (pointDouble){cX, cY, 0};
        };
        virtual void modifyCamera(Camera* c, double deltaTime, double W, double H){};
        virtual void bisectObject(bool horizontal, float splitLocation, float offset){};
};

class OneWayCameraObject : public CameraObject {
    private:
        double x, y;
        double w;
        double openH, closeH;
        int dir;
        bool snap, work, prevWork;
    public:
        /**
         * Constructor for a One Way Camera Object
         * @param X The left-most position in unit coords.
         * @param Y The up-most position in unit coords.
         * @param W The width/height of the object in unit coords (Depends on direction)
         * @param direction 0: +Y Check, 1: +X Check, 2: -Y Check, 3: -X Check
         */
        OneWayCameraObject(double X, double Y, double W, int direction);
        /**
         * Constructor for a One Way Camera Object
         * @param X The left-most position in unit coords.
         * @param Y The up-most position in unit coords.
         * @param W The width/height of the object in unit coords (Depends on direction)
         * @param removeH The additional height/width the player needs to travel to remove the camera restriction.
         * @param addH The additional height/width the player needs to travel to add the camera restriction back.
         * @param direction 0: +Y Check, 1: +X Check, 2: -Y Check, 3: -X Check. This also affects which direction removeH and addH are going.
         * @param snapback Whether or not the camera object tries to snap back to position once the camera restriction is added back in.
         */
        OneWayCameraObject(double X, double Y, double W, double removeH, double addH, int direction, bool snapback);
        pointDouble interactWithPlayer(double cX, double cY, double W, double H, Instance* p, double deltaTime);
        void modifyCamera(Camera* c, double deltaTime, double W, double H);
        void bisectObject(bool horizontal, float splitLocation, float offset);
        void setPosition(double X, double Y, bool relative);
        void changeX(double X);
        void changeY(double Y);
        void setPosValues(OneWayCameraObject* o);
};

#endif