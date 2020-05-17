#ifndef dos_gamestate
#define dos_gamestate

#include <string>
#include <map>

#define SAV_ERR -1
#define SAV_BOOL 0
#define SAV_INT 1
#define SAV_FLOAT 2
#define SAV_STRING 3

union saveData{
    bool b;
    int i;
    float f;
    std::string str;
};

struct saveVar{
    bool save;
    int type;
    saveData data;
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
    public:
        static std::map<std::string, saveVar> emptyMap();
        static int loadFile(std::string fileName);
        static int saveFile(std::string fileName);
        static int getType(std::string key);
        static saveVar getSave(std::string key);
        static bool getSaveB(std::string key);
        static int getSaveI(std::string key);
        static float getSaveF(std::string key);
        static std::string getSaveS(std::string key);
        static void setSave(std::string key, bool value){ setSaveB(key, value); };
        static void setSaveB(std::string, bool value);
        static void setSave(std::string key, int value){ setSaveI(key, value); };
        static void setSaveI(std::string key, int value);
        static void setSave(std::string key, float value){ setSaveF(key, value); };
        static void setSaveF(std::string key, float value);
        static void setSave(std::string key, std::string value){ setSaveS(key, value); };
        static void setSaveS(std::string key, std::string value);
};

#endif