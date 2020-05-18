#ifndef dos_gamestate
#define dos_gamestate

#include <string>
#include <map>
#include <cmath>

#define SAV_ERR -1
#define SAV_BOOL 0
#define SAV_INT 1
#define SAV_DOUBLE 2

struct saveVar{
    bool save;
    int type;
    union {
        bool b;
        int i;
        double d;
    } data;
};

/**
 * Static Singleton Class to Deal with Game State
 * The purpose of this is to have a map that corresponds with a static game state.
 * This also allows for saving and loading files.
 * TODO: Add documentation to everything.
 */
class GameState{
    private:
        static std::map<std::string, saveVar> stateMap;
        static bool hasValue(std::string key);
    public:
        static std::map<std::string, saveVar> emptyMap();
        static int loadFile(std::string fileName);
        static int saveFile(std::string fileName);
        static int getType(std::string key);
        static saveVar getSave(std::string key);
        static bool getSaveB(std::string key);
        static int getSaveI(std::string key);
        static double getSaveD(std::string key);
        static void setSave(std::string key, bool value){ setSaveB(key, value); };
        static void setSaveB(std::string, bool value);
        static void setSave(std::string key, int value){ setSaveI(key, value); };
        static void setSaveI(std::string key, int value);
        static void setSave(std::string key, double value){ setSaveD(key, value); };
        static void setSaveD(std::string key, double value);
};

#endif