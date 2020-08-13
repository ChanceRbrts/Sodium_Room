#ifndef dos_obj_arc
#define dos_obj_arc

#include "../main/shaderBox.h"
#include <math.h>

/**
 * A representation of data of an arc.
 */
struct ArcInfo{
    /// The id of the arc.
    int id;
    /// The color of the arc.
    double r, g, b;
    /// Whether or not the arc makes everything monocolor.
    bool monocolor;
    /// Whether or not the arc makes everything act with "default behavior." (Usually false)
    bool defBehavior;
};

/**
 * A "light" that turns everything into a tinted or monocolor scene.
 */
class Arc{
    protected:
        /// The center of the arc.
        double x, y;
        /// The radius of the arc.
        double r;
        /// The color of the arc.
        double rCol, gCol, bCol;
        /// The opaqueness of the arc.
        double alpha;
        /// The maximum radius that an arc can be.
        double maxR;
        /// The angle in radians that the arc stretches across. (From d1-d2)
        double d1, d2;
        /// Whether or not the Arc is directly connected to its shaderbox.
        bool connected;
        /// Whether or not the Arc makes everything monocolor or just tints everything.
        bool monocolor;
        /// Whether or not the arc makes everything act with "default behavior." (Usually false)
        bool defBehavior;
    public:
        /**
         * The constructor of the arc.
         * (X, Y, and R are in unit coordinates (Multiplied by 32 pixels))
         * @param X The center of the arc horizontally.
         * @param Y The center of the arc vertically.
         * @param R The maximum radius of the arc.
         * @param D1 The angle in which the arc starts (In radians)
         * @param D2 The angle in which the arc ends (In radians)
         * @param RC The red color of the arc.
         * @param GC The green color of the arc.
         * @param BC The blue color of the arc.
         * @param mono Whether or not the Arc makes everything monocolor or just tints everything.
         */
        Arc(double X, double Y, double R, double D1, double D2, double RC, double GC, double BC, bool mono);
        /// The deconstructor of the arc.
        ~Arc();
        /// @param c Whether or not the arc is now connected to the shaderbox.
        void changeConnection(bool c){ connected = c; }
        /// @returns The center of the arc horizontally. (In pixels)
        double getX(){return x;};
        /// @return The center of the arc vertically. (In pixels)
        double getY(){return y;};
        /**
         * Changes the position of the arc.
         * @param X The new x position of the center. (In pixels)
         * @param Y The new y position of the center. (In pixels)
         */
        void setPosition(double X, double Y);
        /// @return The radius of the arc. (In pixels)
        double getR(){return r;};
        /**
         * Changes the radius of the arc.
         * @param R The new radius of the arc. (Up to the maximum radius of the arc)
         */
        void setR(double R);
        
        /// @return The angle where the arc starts (In radians)
        double getD1(){return d1;};
        /// @return The angle where the arc ends (In radians)
        double getD2(){return d2;};
        /// @return The opaqueness of the arc.
        double getAlpha(){return alpha;}
        /**
         * Change the angle that the arc is at.
         * @param D1 The new starting angle of the arc in radians.
         * @param D2 The new ending angle of the arc in radians.
         */
        void setAngle(double D1, double D2);
        /**
         * This sets up the shaderbox drawing code.
         * @param glu The GLUtil to use for drawing.
         * @param mainTex The texture that has already been drawn before the arcs.
         * @param drawTo The shaderbox that the arc is being drawn to.
         * @param fromTex The textures that contain the information from the previous arcs.
         * @param fromAlpha The opaqueness texture from the previous arcs.
         */
        void draw(GLUtil* glu, ShaderBox* mainTex, DualSBox drawTo, int fromTex, int fromAlpha);
        /**
         * This changes the color of the arc.
         * @param R The new red color of the arc.
         * @param G The new green color of the arc.
         * @param B The new blue color of the arc.
         */
        void setColor(double R, double G, double B);
        /**
         * This changes the opaqueness of the arc.
         * @param A The new opaqueness of the arc.
         */
        void setAlpha(double A);
        /**
         * Make this arc exhibit default behavior onto instances when colliding onto them.
         * (Use sparingly)
         */
        void makeDefault();
        /**
         * Create a data representation of the arc.
         * @param id The ID to use for the arc.
         * @return The data representation of the arc.
         */
        ArcInfo getInfo(int id);
};

#endif