#ifndef POKEMONV0_5_GAME_H
#define POKEMONV0_5_GAME_H


#include <vector>
#include <tuple>
#include "Player.h"

///Class, that is responsible for holding current state of the game
class Game {
private:
    Player mainCharacter;
    std::vector<Player> enemies;
    Player enemy;
    int numberOfEnemy = 0;

public:
    ///Default constructor to create empty space for Game
    Game();

    ///Constructor with all parameters to create working Game
    Game(Player &mainCharacter, std::vector<Player> enemies);

    /// Returns reference to instance of the main Player
    /// \return Player - main player
    auto getMainChar() -> Player &;

    /// Returns enemies of the main player
    /// \return reference to vector of enemies
    auto getEnemies() -> std::vector<Player> &;

    /// Returns enemy, that player is playing against
    /// \return class Player - the opponent that player is playing against
    auto getEnemy() -> Player &;

    /// Returns information, whether all enemy's pokemons are fainted or not
    /// \return true if Pokemons are fainted, otherwise false
    auto areEnemyPokemonsFainted() -> bool;

    ///Changes current enemy to the next one to fight
    auto updateEnemy() -> void;

    ///Set the same enemy as the enemy for the next fight
    auto setSameEnemy() -> void;
};


#endif //POKEMONV0_5_GAME_H
