#include "Pokemon.h"

#include "Engine.h"

///Default constructor
Pokemon::Pokemon() {}

Pokemon::Pokemon(const std::string &name,
                 const Type &type,
                 const int &strength,
                 const int &healthPoints,
                 const int &exp,
                 const float &dexterity,
                 const bool &fainted,
                 const SpecialMove &specialMove)
        : name(name), type(type), strength(strength), healthPoints(healthPoints), exp(exp), dexterity(dexterity),
          fainted(fainted), specialMove(specialMove), expToLevelUp(100) {
}

auto Pokemon::attackMove(Pokemon *defendingPokemon) -> int {
    Type attackingType = this->getType();
    Type defendingType = defendingPokemon->getType();
    auto dealtDamage = int();
    if (Engine::lookForStrength(attackingType, defendingType)) {
        dealtDamage = this->damage(defendingPokemon, this->strength * 2);
    } else {
        if (Engine::lookForWeakness(attackingType, defendingType)) {
            dealtDamage = this->damage(defendingPokemon, this->strength / 2);
        } else {
            dealtDamage = this->damage(defendingPokemon, this->strength);
        }
    }
    return dealtDamage;
}

auto Pokemon::specialAttackMove(Pokemon *attackingPokemon, Pokemon *defendingPokemon) -> void {
    this->specialMove.execute(attackingPokemon, defendingPokemon);
}

auto Pokemon::damage(Pokemon *defendingPokemon, int damage) -> int {
    srand(time(0) + rand());
    auto temp = float(static_cast<float>(rand() % 101) / 100);
    if (temp >= defendingPokemon->dexterity) {
        defendingPokemon->healthPoints -= damage;

        if (defendingPokemon->healthPoints <= 0) {
            defendingPokemon->fainted = true;
        }

        if (defendingPokemon->isFainted()) {
            this->exp += 35;
        }
        return damage;
    } else {
        return 0;
    }
}

void Pokemon::buffStrength(int buffStrength) { this->strength += buffStrength; }

void Pokemon::buffDexterity(float buffDexterity) { this->dexterity += buffDexterity; }

auto Pokemon::debuffStrength(int debuffStrength) -> void { this->strength -= debuffStrength; }

auto Pokemon::debuffDexterity(float debuffDexterity) -> void { this->dexterity -= debuffDexterity; }

auto Pokemon::buffHP(int buffHP) -> void { this->healthPoints += buffHP; }

auto Pokemon::getName() -> std::string { return this->name; }

auto Pokemon::getType() -> Type { return this->type; }

auto Pokemon::getSpecialMove() -> SpecialMove & { return this->specialMove; }

auto Pokemon::getExp() -> int {
    return this->exp;
}

auto Pokemon::getInfo() -> std::string {
    return "\n\tName: " + this->name +
           "\n\tType: " + typesAsStrings.at(this->type) +
           "\n\tHealth: " + std::to_string(this->healthPoints) +
           "\n\tStrength: " + std::to_string(this->strength) +
           "\n\tDexterity: " + std::to_string(this->dexterity) + "\n";
}

auto Pokemon::getHP() const -> int {
    return this->healthPoints;
}

auto Pokemon::getDexterity() -> float {
    return this->dexterity;
}

auto Pokemon::isFainted() const -> bool {
    return this->fainted;
}

auto Pokemon::getStrength() const -> int {
    return this->strength;
}

auto Pokemon::checkEvolution() -> void {
    if (this->exp >= this->expToLevelUp) {
        this->evolve();
    }
}

auto Pokemon::evolve() -> void {
    int choice;
    std::string answer;
    std::cout << "Congratulations! Your " << this->getName() << " evolved!\n";
    for (int i = 0; i < 2; i++) {
        std::cout << "Choose 2 attributes to upgrade:\n\tStrength: +2\n\tHP: +5\n\tDexterity: +10%\n\nYour choice";

        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "Choose 2 attributes to upgrade:\n\tStrength: +2\n\tHP: +5\n\tDexterity: +10%\n\nYour choice";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                choice = std::stoi(answer);
            }
        }

        choice = std::stoi(answer);

        while (choice > 3 || choice <= 0) {
            std::cout << "You input wrong number! Try again!\n"
                      << "Choose 2 attributes to upgrade:\n\tStrength: +2\n\tHP: +5\n\tDexterity: +10%\n\nYour choice";

            std::cin >> answer;

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout
                        << "Choose 2 attributes to upgrade:\n\tStrength: +2\n\tHP: +5\n\tDexterity: +10%\n\nYour choice";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    choice = std::stoi(answer);
                }
            }

            choice = std::stoi(answer);
        }

        switch (choice) {
            case 1: {
                this->strength += 2;
                break;
            }
            case 2: {
                this->healthPoints += 5;
                break;
            }
            case 3: {
                this->dexterity += 0.1f;
                break;
            }
        }
    }

    this->exp = 0;
    this->expToLevelUp *= 1.35;
}

SpecialMove::SpecialMove() {}

SpecialMove::SpecialMove(const std::string &name,
                         const int &maxTurns,
                         const int &realTurnsPlayed,
                         const int &maxUses,
                         const int &realUses,
                         const int &buffStrength,
                         const int &debuffStrength,
                         const int &buffHP,
                         const float &buffDexterity,
                         const float &debuffDexterity)
        : name(name), maxTurns(maxTurns), realTurnsPlayed(realTurnsPlayed), maxUses(maxUses), realUses(realUses),
          buffStrength(buffStrength), debuffStrength(debuffStrength), buffHP(buffHP),
          buffDexterity(buffDexterity), debuffDexterity(debuffDexterity), active(false) {

}

auto SpecialMove::execute(Pokemon *attackPokemon, Pokemon *defendPokemon) -> void {
    if (!this->active) {
        if (realUses < maxUses) {
            this->active = true;

            this->attackingPokemon = attackPokemon;
            this->defendingPokemon = defendPokemon;

            realUses++;
            attackPokemon->buffStrength(buffStrength);
            attackPokemon->buffDexterity(buffDexterity);

            defendPokemon->debuffStrength(debuffStrength);
            defendPokemon->debuffDexterity(debuffDexterity);

            realTurnsPlayed = 1;
        } else {
            std::cout << "You used all special moves!\n";
        }
    } else {
        std::cout << "Special move is in action!\n";
    }
}

auto SpecialMove::undo(Pokemon *attackPokemon, Pokemon *defendPokemon) -> void {
    defendPokemon->buffStrength(debuffStrength);
    defendPokemon->buffDexterity(debuffDexterity);

    attackPokemon->debuffStrength(buffStrength);
    attackPokemon->debuffDexterity(buffDexterity);

    this->active = false;

    realTurnsPlayed = 0;
}

auto SpecialMove::update() -> void {
    if (this->active) {
        if (this->realTurnsPlayed > this->maxTurns) {
            this->undo(this->attackingPokemon, this->defendingPokemon);
        } else {
            attackingPokemon->buffHP(this->buffHP);
        }

        this->realTurnsPlayed++;
    }
}

auto SpecialMove::getName() -> std::string {
    return this->name;
}

auto SpecialMove::getUses() const -> int {
    return this->realUses;
}

auto SpecialMove::getMaxUses() const -> int {
    return this->maxUses;
}


auto SpecialMove::getActive() const -> bool {
    return this->active;
}
