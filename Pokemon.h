#ifndef POKEMONV0_5_POKEMON_H
#define POKEMONV0_5_POKEMON_H

#include <utility>
#include <vector>
#include <string>

///Enum, consisted of different types of pokemon
enum Type {
    Water = 0,
    Earth = 1,
    Air = 2,
    Fire = 3,
    Ice = 4,
    Steel = 5
};

class Pokemon;

/*!
*Class, that is responsible for Special Move during battles
*/
class SpecialMove {
private:
    std::string name;
    int maxTurns;
    int realTurnsPlayed; // >= 1, 1 is a turn when you used Special Move
    int maxUses;
    int realUses;
    int buffStrength;
    int debuffStrength;
    int buffHP;
    float buffDexterity;
    float debuffDexterity;
    bool active;
    Pokemon *attackingPokemon;
    Pokemon *defendingPokemon;

public:
    ///Default constructor to create empty special move
    SpecialMove();

    ///Constructor with all parameters to create working special move
    SpecialMove(const std::string &name,
                const int &maxTurns,
                const int &realTurnsPlayed,
                const int &maxUses,
                const int &realUses,
                const int &buffStrength,
                const int &debuffStrength,
                const int &buffHP,
                const float &buffDexterity,
                const float &debuffDexterity);

    /// Executing special power, putting the effect of special power on attacking/defending pokemon
    /// \param attackingPokemon - Pokemon, that is performing special power
    /// \param defendingPokemon - Pokemon, that is against attacking pokemon right now
    auto execute(Pokemon *attackingPokemon, Pokemon *defendingPokemon) -> void;

    /// Nullifies the effect of the special power
    /// \param attackingPokemon - Pokemon, that was performing special power
    /// \param defendingPokemon  - Pokemon, that was against attacking pokemon
    auto undo(Pokemon *attackingPokemon, Pokemon *defendingPokemon) -> void;

    /// Returns a name of special power
    /// \return string, name of special power
    auto getName() -> std::string;

    /// Returns amount of real uses of special power by Player
    /// \return int - amount of real uses
    auto getUses() const -> int;

    /// Returns max amount of uses of special power
    /// \return int - amount of max uses
    auto getMaxUses() const -> int;

    /// Checks if special power is active or not
    /// \return true if special power is active, otherwise false
    auto getActive() const -> bool;

    ///Update effect of special move, nullifies the effect if enough turns passed
    auto update() -> void;

};

///Class, that is responsible for Pokemons instances
class Pokemon {
private:
    std::string name;
    Type type;
    SpecialMove specialMove;
    int strength;
    int healthPoints;
    int exp;
    int expToLevelUp;
    float dexterity; // 0 -> 1;
    bool fainted;

    /// Executing default attack via decreasing health points of opponent's pokemon
    /// \param defendingPokemon - pokemon, that is taking damage
    /// \param damage - int, amount of damage
    ///\return int- amount of damage dealt, if the defending pokemon didn't dodge
    auto damage(Pokemon *defendingPokemon, int damage) -> int;

public:
    ///Default constructor to create empty Pokemon
    Pokemon();

    ///Constructor with all parameters to create specific Pokemon
    Pokemon(const std::string &name,
            const Type &type,
            const int &strength,
            const int &healthPoints,
            const int &exp,
            const float &dexterity,
            const bool &fainted,
            const SpecialMove &specialMove);

    /// Executing default attack via counting amount of damage
    /// \param defendingPokemon - pokemon against the pokemon, that is using attack
    /// \return int - amount of dealt damage
    auto attackMove(Pokemon *defendingPokemon) -> int;

    /// Executing the special attack
    /// \param attackingPokemon - Pokemon, that used the special ability
    /// \param defendingPokemon - Pokemon, that suffering consequences(gets debuff)
    auto specialAttackMove(Pokemon *attackingPokemon, Pokemon *defendingPokemon) -> void;

    ///Checks, if the Pokemon has enough experience to evolve, evolve if it's true
    auto checkEvolution() -> void;

    ///Evolving Pokemon, giving player options to choose, which attribute to upgrade
    auto evolve() -> void;

    /// Increasing Pokemon's strength
    /// \param buffStrength - int,amount of on how much the strength will be increased
    auto buffStrength(int buffStrength) -> void;

    /// Increasing Pokemon's dexterity
    /// \param buffDexterity - float, amount of on how much the dexterity will be increased
    auto buffDexterity(float buffDexterity) -> void;

    /// Decreasing Pokemon's strength
    /// \param debuffStrength - int, amount on how much the strength will be decreased
    auto debuffStrength(int debuffStrength) -> void;

    /// Decreasing Pokemon's dexterity
    /// \param debuffDexterity - float, amount on how much the dexterity will be decreased
    auto debuffDexterity(float debuffDexterity) -> void;

    /// Increasing Pokemon's health points
    /// \param buffHP - int, amount on how much the health will be increased
    auto buffHP(int buffHP) -> void;

    /// Returns Pokemon's name
    /// \return string - pokemon's name
    auto getName() -> std::string;

    /// Returns Pokemon's type
    /// \return type - enum, from which it is possible to understand, whether the pokemon has a weakness towards enemy or not
    auto getType() -> Type;

    /// Returns Pokemon's special move
    /// \return reference to SpecialMove of Pokemon
    auto getSpecialMove() -> SpecialMove &;

    /// Returns information about the Pokemon as string
    /// \return string - name, type, health, strength, dexterity
    auto getInfo() -> std::string;

    /// Returns Pokemon's health points
    /// \return - int - amount of pokemon's health points
    auto getHP() const -> int;

    /// Returns Pokemon's strength
    /// \return int- amount of pokemon's strength
    auto getStrength() const -> int;

    /// Returns information about has the Pokemon fainted or not
    /// \return true if Pokemon is fainted, otherwise false
    auto isFainted() const -> bool;

    /// Returns Pokemon's dexterity
    /// \return float - amount of pokemon's dexterity
    auto getDexterity() -> float;

    /// Returns Pokemon's experience
    /// \return int - amount of pokemon's experience
    auto getExp() -> int;
};


#endif //POKEMONV0_5_POKEMON_H
