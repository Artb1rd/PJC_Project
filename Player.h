#ifndef POKEMONV0_5_PLAYER_H
#define POKEMONV0_5_PLAYER_H
//Declaration

#include <iostream>
#include <vector>
#include "Pokemon.h"

///Enum, has the information whether the Player instance is friendly or enemy
enum Alliance {
    Friendly,
    Enemy
};

///Class, that is responsible for information about the player
class Player {
private:
    std::string name;
    Alliance alliance;
    std::vector<Pokemon> pokemons;
    Pokemon *activePokemon;

public:
    ///Default constructor to create empty space for Player
    Player();
    ///Constructor with all parameters to create working Player
    Player(std::string name, Alliance alliance, std::vector<Pokemon> &pokemons);

    /// Creates the string of the names of all Pokemons, that are in the Player's army
    /// \return string - names of all pokemons inside the vector of pokemons
    auto pokemonsToString() -> std::string;

    /// Checking, are all of the Pokemons inside Player's army is fainted
    /// \return true if Pokemons are fainted, otherwise false
    auto checkIfPokemonsFainted() -> bool;

    /// Returns the name of the Player
    /// \return string - name of the player
    auto getName() -> std::string;

    /// Returns the vector of Pokemons, that are in Player's army
    /// \return vector of Pokemons, that are in player's army
    auto getPokemons() -> std::vector<Pokemon> &;

    /// Returns the active Pokemon(the one, that is ready for making moves)
    /// \return Pokemon, that is active
    auto getActivePokemon() -> Pokemon *;

    /// Setting Pokemon from Player's army(vector of Pokemons) as an active Pokemon
    /// \param pokemon - Pokemon from vector of pokemons(Player's army)
    auto setActivePokemon(Pokemon *pokemon) -> void;
};


#endif //POKEMONV0_5_PLAYER_H
