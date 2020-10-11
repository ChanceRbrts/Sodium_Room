#ifndef dos_lev_map
#define dos_lev_map

#include "level.h"

/**
 * This represents a collection of levels
 * These levels get loaded in and out based on the location of the camera.
 * This could be a part of a super map, which is a map 
 * that's loaded with other maps to make a larger map.
 */
class Map{
   private:
      /// The x-coord of the map.
      double x;
      /// The y-coord of the map
      double y;
      /// Where the camera was previously in the X axis.
      double prevCX;
      /// Where the camera was previously in the Y axis.
      double prevCY;
      /// The width of the map.
      double w;
      /// The height of the map.
      double h;
      /// Whether or not this map has been loaded before.
      bool firstLoad;
      /// The list of levels that are in the map.
      std::vector<Level *> levels;
      /**
       * Gets the list of levels that are in an area that haven't been loaded in yet.
       * @param X The left-most position of the area to check for. (Pixel Coords)
       * @param Y The up-most position of the area to check for. (Pixel Coords)
       * @param W The width of the area to check for. (Pixel Coords)
       * @param H The height of the area to check for. (Pixel Coords)
       * @return The list of levels that are in the area that haven't been loaded in the level list.
       */
      std::vector<Level *> getUnloadedLevelsInArea(double X, double Y, double W, double H);
      /// The ID to the super map that this map belongs to.
      int superMapID;
      /**
       * Translates map coordinates to true coordinates. (Coords with gaps)
       * @param prevCoord The map coord to translate the gapped coordinates.
       * @param horizontal Whether or not to use the x-axis vs. the y-axis.
       * @param reverse If this is true, this goes from true coordinates to map coordinates.
       */
      double translateMapCoord(double prevCoord, bool horizontal, bool reverse);
      /// Using these as a sorted list of doubles.
      static std::map<double, double> horizontalMapGap;
      /// Using these as a sorted list of doubles.
      static std::map<double, double> verticalMapGap;
      static std::map<double, double> emptyMap();
   public:
      /**
       * Constructor for the map.
       * @param sID The ID for the super map this loads into.
       */
      Map(int sID);
      /// Deconstructor of the map.
      virtual ~Map(){};
      /**
       * Add a level to the map.
       * This also alters the bounds of the current map.
       * @param l The level to add.
       * @param X The x coordinate to add the level to.
       * @param Y The y coordinate to add the level to.
       */
      void addLevel(Level* l, double X, double Y);
      /**
       * Gives a list of levels to load in from this map.
       * @param glu The GLUtils, used to get the camera position and screen width.
       * @return A list of levels to load in from the map.
       */
      std::vector<Level *> updateLoadedLevels(GLUtil* glu);
      /**
       * Gives a list of levels to load in from this map.
       * @param X The x coordinate of the screen.
       * @param Y The y coordinate of the screen.
       * @param W The width of the screen.
       * @param H The height of the screen.
       * @return A list of levels to load in from the map.
       */
      std::vector<Level *> updateLoadedLevels(double X, double Y, double W, double H);
      /// @return The ID of the super map this belongs to.
      int getSuperMapID(){ return superMapID; };  
      /**
       * @param X The left-most coordinate of the area we're checking.
       * @param Y The up-most coordinate of the area we're checking.
       * @param W The width of the area we're checking.
       * @param H The height of the area we're checking.
       * @return Whether or not the map is in the area provided.
       */
      bool inBounds(double X, double Y, double W, double H);
      /**
       * Adds (to) a gap in the map.
       * @param P The point that the gap starts in map coords.
       * @param W The (added) width of the gap
       * @param horiz Whether or not the gap is on the X direction or the Y direction.
       * @param relative Whether or not W is relative to what's already in the gap.
       */
      static void addGap(double P, double W, bool horiz, bool relative);
};

#endif