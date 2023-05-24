#include "Player.h"
#include <vector>

Player::Player() = default;

Player::Player(std::string name, Alliance alliance, std::vector<Pokemon> &pokemons)
        : name(name), alliance(alliance), pokemons(pokemons) {
    // std::cout << this->name << "'s alliance:" << this->alliance << "\nPokemons:\n" << this->pokemonsToString();
}

auto Player::pokemonsToString() -> std::string {
    std::string stringOfPokemons = "\t";
    for (auto i: this->pokemons) {
        stringOfPokemons += i.getName() + ", ";
    }

    stringOfPokemons += "\n\n";

    return stringOfPokemons;
}

auto Player::checkIfPokemonsFainted() -> bool {
    for (const auto& x: this->pokemons) {
        if (!x.isFainted())
            return false;
    }

    return true;
}

auto Player::getName() -> std::string {
    return this->name;
}

auto Player::getPokemons() -> std::vector<Pokemon> & {
    return this->pokemons;
}

auto Player::setActivePokemon(Pokemon *pokemon) -> void {
    this->activePokemon = pokemon;
}

auto Player::getActivePokemon() -> Pokemon * {
    return this->activePokemon;
}

