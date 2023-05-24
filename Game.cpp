#include "Game.h"

Game::Game(Player &mainCharacter, std::vector<Player> enemies)
        : mainCharacter(mainCharacter), enemies(enemies) {
}

Game::Game() = default;

auto Game::getEnemies() -> std::vector<Player>& {
    return this->enemies;
}

auto Game::getMainChar() -> Player& {
    return this->mainCharacter;
}

auto Game::getEnemy() -> Player& {
    return this->enemy;
}

auto Game::areEnemyPokemonsFainted() -> bool {
    return this->enemy.checkIfPokemonsFainted();
}

auto Game::updateEnemy() -> void {
    this->enemy = this->enemies.at(this->numberOfEnemy);
    this->numberOfEnemy++;
}

auto Game::setSameEnemy() -> void {
    this->enemy = this->enemies.at(this->numberOfEnemy - 1);
}

