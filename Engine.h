#ifndef POKEMONV0_5_ENGINE_H
#define POKEMONV0_5_ENGINE_H


#include "Game.h"
#include <unordered_map>
#include <fstream>

///
/// Class responsible for main logic within game
///
class Engine {
private:
    ///Holds the current game
    static Game game;

public:
    ///Default constructor to create empty space for Engine
    Engine();

    ///Creates new game depending on value of difficulty
    /// \param difficulty - int
    auto createBaseGame(const int &difficulty) -> void;

    ///Returns weakness map for all types
    ///\return unordered_map of type to vector of types
    auto static getWeaknessesMap() -> std::unordered_map<Type, std::vector<Type>>;

    /// Returns strength map for all types
    /// \return unordered_map of type to vector of types
    auto static getStrengthMap() -> std::unordered_map<Type, std::vector<Type>>;

    /// Looking if attacking pokemon has a weakness towards defending pokemon
    /// \param attackingType - type of attacking pokemon
    /// \param defendingType - type of defending pokemon
    /// \return true if attacking pokemon is weak to defending pokemon, otherwise false
    auto static lookForWeakness(Type &attackingType, Type &defendingType) -> bool;

    /// Looking if attacking pokemon has a strength towards defending pokemon
    /// \param attackingType - type of attacking pokemon
    /// \param defendingType - type of defending pokemon
    /// \return true if attacking pokemon is strong to defending pokemon, otherwise false
    auto static lookForStrength(Type &attackingType, Type &defendingType) -> bool;

    /// Gives battle choice for main player
    /// \return int - chosen action by the main player
    auto static giveBattleChoice() -> int;

    /// Updates the game after every battle, regardless the outcome
    /// \param enemyToFight - enemy to fight in the next battle
    /// \return int - outcome of the round
    auto static update(Player enemyToFight) -> int;

    ///Prints rules for the game
    auto static getHelp() -> void;

    ///Starts the main process of the game
    auto startGame() -> void;

    ///Loads the game from the file
    auto loadGame(std::ifstream &fileToLoadFrom) -> void;

    ///Save the current state of the game to the file
    static auto saveGame() -> void;
};

///Unordered map of types and the types, towards which they are weak
const static std::unordered_map<Type, std::vector<Type>> weakness = {
        {Water, std::vector<Type>{Water}},
        {Earth, std::vector<Type>{Air}},
        {Air,   std::vector<Type>{Earth, Steel}},
        {Fire,  std::vector<Type>{Water, Earth}},
        {Ice,   std::vector<Type>{Water, Fire, Ice}},
        {Steel, std::vector<Type>{Fire, Steel}}
};
///Unordered map of types and the types, towards which they are strong
const static std::unordered_map<Type, std::vector<Type>> strength = {
        {Water, std::vector<Type>{Earth, Fire}},
        {Earth, std::vector<Type>{Fire, Ice, Steel}},
        {Air,   std::vector<Type>{Ice}},
        {Fire,  std::vector<Type>{Ice, Steel}},
        {Ice,   std::vector<Type>{Earth}},
        {Steel, std::vector<Type>{Water, Air}}
};
///Unordered map for string values of corresponding types
const static std::unordered_map<Type, std::string> typesAsStrings = {
        {Fire,  "Fire"},
        {Water, "Water"},
        {Ice,   "Ice"},
        {Air,   "Air"},
        {Earth, "Earth"},
        {Steel, "Steel"},
};
///Vector of strings, consisted from the names of Enemies
const static std::vector<std::string> names = {"Liam", "Olivia", "Noah", "Emma", "Lucas", "Isabella", "Oliver",
                                               "Amelia", "James", "Ava"};


#endif //POKEMONV0_5_ENGINE_H
