#ifndef dos_gamestate
#define dos_gamestate

#include <string>
#include <map>
#include <cmath>

#define SAV_ERR -1
#define SAV_BOOL 0
#define SAV_INT 1
#define SAV_DOUBLE 2

/**
 * The format of the saved variables in the game state.
 */
struct saveVar{
    /// Whether or not the variable is saved in the save file. (False by default)
    bool save;
    /// The type of the variable being stored.
    int type;
    /// The actual variable being stored.
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
 */
class GameState{
    private:
        /// The map of variables that make up the game state.
        static std::map<std::string, saveVar> stateMap;
        /**
         * A helper function to check if a key is in the map.
         * @param key The key to check.
         * @return Whether or not the key is in the game state.
         */
        static bool hasValue(std::string key);
    public:
        /// Returns an empty GameState map.
        static std::map<std::string, saveVar> emptyMap();
        /**
         * TODO: This loads a file into the game state.
         * @param fileName The name of the file to load.
         * @return A code seeing if the loading was successful.
         */
        static int loadFile(std::string fileName);
        /**
         * TODO: This writes the game state into a file.
         * @param fileName The name of the file to save into.
         * @return A code seeing if the saving was successful.
         */
        static int saveFile(std::string fileName);
        /**
         * This checks the type of the data stored in the game state.
         * @param key The key in which the data is stored.
         * @return A SAV_ code representing the type of data stored.
         */
        static int getType(std::string key);
        /**
         * This gets the data stored in the game state.
         * @param key The key in which the data is stored.
         * @return A saveVar that represents the data stored.
         */
        static saveVar getSave(std::string key);
        /**
         * Gets the data stored as a boolean.
         * @param key The key in which the data is stored.
         * @return A boolean that represents the data stored.
         */
        static bool getSaveB(std::string key);
        /**
         * Gets the data stored as an integer.
         * @param key The key in which the data is stored.
         * @return An integer that represents the data stored.
         */
        static int getSaveI(std::string key);
        /**
         * Gets the data stored as a double.
         * @param key The key in which the data is stored.
         * @return A double that represents the data stored.
         */
        static double getSaveD(std::string key);
        /**
         * Makes it so the data can be stored in a savefile.
         * @param key The key in which the data is stored.
         * @return A SAV_ code representing the type of data stored.
         */
        static int makePermament(std::string key){ return setPermanent(key, true); };
        /**
         * Sets the parameter for whether or not to save the data in a savefile.
         * @param key The key in which the data is stored.
         * @param toSave Whether or not to save this data into a savefile.
         * @return A SAV_ code representing the type of data stored.
         */
        static int setPermanent(std::string key, bool toSave);
        /**
         * Save some data into the savefile. (Bool/Int/Double supported)
         * @param key The key to save the data with.
         * @param value The data to store.
         */
        static void setSave(std::string key, bool value){ setSaveB(key, value); };
        /**
         * Save a boolean into the savefile.
         * @param key The key to save the data with.
         * @param value The boolean to store.
         */
        static void setSaveB(std::string, bool value);
        /**
         * Save some data into the savefile. (Bool/Int/Double supported)
         * @param key The key to save the data with.
         * @param value The data to store.
         */
        static void setSave(std::string key, int value){ setSaveI(key, value); };
        /**
         * Save an integer into the savefile.
         * @param key The key to save the data with.
         * @param value The integer to store.
         */
        static void setSaveI(std::string key, int value);
        /**
         * Save some data into the savefile. (Bool/Int/Double supported)
         * @param key The key to save the data with.
         * @param value The data to store.
         */
        static void setSave(std::string key, double value){ setSaveD(key, value); };
        /**
         * Save an double into the savefile.
         * @param key The key to save the data with.
         * @param value The double to store.
         */
        static void setSaveD(std::string key, double value);
};

#endif