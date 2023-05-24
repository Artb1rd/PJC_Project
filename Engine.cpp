
#include "Engine.h"
#include <unordered_map>
#include <random>
#include <fstream>
#include <iostream>
#include <chrono>

SpecialMove aurorasFountain = SpecialMove("Aurora's fountain", 2, 0, 3, 0, 0, 0, 5, 0.15f, 0);
SpecialMove blazeLaser = SpecialMove("Blaze laser", 3, 0, 2, 0, 1, 0, 0, 0, 0);
SpecialMove rockRumble = SpecialMove("Rock rumble", 2, 0, 3, 0, 0, 0, 0, 0, 0.25f);
SpecialMove windFury = SpecialMove("Wind fury", 2, 0, 1, 0, 5, 1, 0, 0, 0);
SpecialMove glacier = SpecialMove("Glacier", 2, 0, 2, 0, 0, 0, 0, 0.25f, 0);
SpecialMove steelWall = SpecialMove("Steel wall", 2, 0, 2, 0, 2, 0, 0, 0.1f, 0);

Pokemon vaporeon = Pokemon("Vaporeon", Water, 7, 50, 0, 0.15f, false, aurorasFountain);
Pokemon flareon = Pokemon("Flareon", Fire, 6, 45, 0, 0.10f, false, blazeLaser);
Pokemon glaceon = Pokemon("Glaceon", Ice, 4, 45, 0, 0.2f, false, glacier);
Pokemon pidgey = Pokemon("Pidgey", Air, 4, 40, 0, 0.15f, false, windFury);
Pokemon geodude = Pokemon("Geodude", Earth, 4, 55, 0, 0.1f, false, rockRumble);
Pokemon steelix = Pokemon("Steelix", Steel, 4, 50, 0, 0.1f, false, steelWall);
Pokemon magikarp = Pokemon("Magikarp", Water, 3, 40, 0, 0.2f, false, aurorasFountain);
Pokemon magmar = Pokemon("Magmar", Fire, 5, 45, 0, 0.1f, false, blazeLaser);
Pokemon rhydon = Pokemon("Rhydon", Earth, 4, 50, 0, 0.15f, false, rockRumble);
Pokemon krabby = Pokemon("Krabby", Water, 3, 55, 0, 0.2f, false, aurorasFountain);
Pokemon onix = Pokemon("Onix", Earth, 5, 50, 0, 0.0f, false, rockRumble);
Pokemon magneton = Pokemon("Magneton", Steel, 3, 50, 0, 0.15f, false, steelWall);
Pokemon rapidash = Pokemon("Rapidash", Fire, 5, 45, 0, 0.2f, false, blazeLaser);
Pokemon alolanNinetails = Pokemon("Alolan Ninetails", Ice, 5, 50, 0, 0.15f, false, glacier);
Pokemon zapdos = Pokemon("Zapdos", Air, 4, 45, 0, 0.25f, false, windFury);
Pokemon hooh = Pokemon("Ho-oh", Air, 3, 55, 0, 0.2f, false, windFury);

Game Engine::game;

int diff;

Engine::Engine() {

    std::cout
            << "Hello! Do you want to start new game or load from save file?\n\t1 - New game\n\t2 - Load\n\nYour choice:";
    int choice;
    std::string answer;
    std::cin >> answer;

    while (answer == "-h" || answer == "-help") {
        Engine::getHelp();
        std::cout
                << "Hello! Do you want to start new game or load from save file?\n\t1 - New game\n\t2 - Load\n\nYour choice:";

        std::cin >> answer;

        if (answer != "-h" && answer != "-help") {
            choice = stoi(answer);
        }
    }

    choice = stoi(answer);

    while (choice >= 3 || choice <= 0) {
        std::cout << "You have input wrong number! Try again!\n\t1 - New game\n\t2 - Load\n\nYour choice:";
        std::cin >> choice;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();
            std::cout << "You have input wrong number! Try again!\n\t1 - New game\n\t2 - Load\n\nYour choice:";

            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                choice = stoi(answer);
            }
        }
    }

    if (choice == 1) {
        std::cout << "Choose difficulty:\n\t1 - easy\n\t2 - medium\n\t3 - hard\n\nDifficulty:";
        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "Choose difficulty:\n\t1 - easy\n\t2 - medium\n\t3 - hard\n\nDifficulty:";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                diff = std::stoi(answer);
            }
        }

        diff = std::stoi(answer);

        while (diff >= 4 || diff <= 0) {
            std::cout
                    << "You input wrong number! Try again!\nChoose difficulty:\n\t1 - easy\n\t2 - medium\n\t3 - hard\n\nDifficulty:";
            std::cin >> answer;

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout << "Choose difficulty:\n\t1 - easy\n\t2 - medium\n\t3 - hard\n\nDifficulty:";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    diff = std::stoi(answer);
                }
            }
            diff = std::stoi(answer);
        }
        Engine::createBaseGame(diff);
    } else {
        std::ifstream loadFile;

        loadFile.open("save.txt", std::fstream::out);

        if (loadFile.is_open()) {
            Engine::loadGame(loadFile);
        }
    }
}

auto Engine::createBaseGame(const int &difficulty) -> void {
    std::string answer;
    std::string name;
    std::cout << "Hi! Input your name below!\nName: ";
    std::cin >> answer;

    while (answer == "-h" || answer == "-help") {
        Engine::getHelp();

        std::cout << "Hi! Input your name below!\nName: ";
        std::cin >> answer;

        if (answer != "-h" && answer != "-help") {
            name = answer;
        }
    }

    name = answer;

    std::vector<Pokemon> pokemons{vaporeon, flareon, glaceon, pidgey, geodude, steelix, magikarp, magmar, rhydon,
                                  krabby, onix, magneton, rapidash, alolanNinetails, zapdos, hooh};

    std::vector<Pokemon> playersPokemons;

    int pokemonsToChoose = 6;
    int chosenPokemon;
    bool isPokemonInArmy = false;
    for (int i = 0; i < 6; ++i) {
        std::cout << "Choose " << std::to_string(pokemonsToChoose - i)
                  << " Pokemons for your army!\nInput the number of pokemon you want to add!\nYou can't take one pokemon twice!\n\n";

        for (int j = 1; j < pokemons.size() + 1; j++) {
            std::cout << j << ") " << pokemons.at(j - 1).getInfo();
        }

        std::cout << "\nYour choice: ";
        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "Choose " << std::to_string(pokemonsToChoose - i)
                      << " Pokemons for your army!\nInput the number of pokemon you want to add!\nYou can't take one pokemon twice!\n\n";

            for (int j = 1; j < pokemons.size() + 1; j++) {
                std::cout << j << ") " << pokemons.at(j - 1).getInfo();
            }

            std::cout << "\nYour choice: ";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                chosenPokemon = std::stoi(answer);
            }
        }

        chosenPokemon = std::stoi(answer);

        while ((chosenPokemon <= 0 || chosenPokemon >= 17)) {
            std::cout << "You have input wrong number! Try again!\n";
            std::cout << "\nYour choice: ";
            std::cin >> answer;    //changed from chosenPokemon

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout << "You have input wrong number! Try again!\n";
                std::cout << "\nYour choice: ";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    chosenPokemon = std::stoi(answer);
                    answer = "";
                }
            }

            chosenPokemon = std::stoi(answer);
        }

        for (Pokemon x: playersPokemons) {
            if (x.getName() == pokemons.at(chosenPokemon - 1).getName()) {
                isPokemonInArmy = true;
                break;
            }
        }

        while (isPokemonInArmy) {
            std::cout << "This pokemon is already in your army! Choose another one!\nYour choice:";
            std::cin >> answer;

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout << "This pokemon is already in your army! Choose another one!\nYour choice:";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    chosenPokemon = std::stoi(answer);
                }
            }

            chosenPokemon = std::stoi(answer);

            while ((chosenPokemon <= 0 || chosenPokemon >= 17)) {
                std::cout << "You have input wrong number! Try again!\nYour choice:";
                std::cin >> answer;       //changed from chosenPokemon
                while (answer == "-h" || answer == "-help") {
                    Engine::getHelp();

                    std::cout << "You have input wrong number! Try again!\nYour choice:";
                    std::cin >> answer;

                    if (answer != "-h" && answer != "-help") {
                        chosenPokemon = std::stoi(answer);
                    }
                }

                chosenPokemon = std::stoi(answer);
            }

            isPokemonInArmy = false;
            for (Pokemon x: playersPokemons) {
                if (x.getName() == pokemons.at(chosenPokemon - 1).getName()) {
                    isPokemonInArmy = true;
                    break;
                }
            }
        }

        std::cout << "You have chosen " + pokemons.at(chosenPokemon - 1).getName() + "!\n";
        playersPokemons.push_back(pokemons.at(chosenPokemon - 1));
    }

    Player mainChar = Player(name, Friendly, playersPokemons);

    std::vector<Pokemon> enemiesPokemons;
    std::vector<Player> enemies;
    isPokemonInArmy = false;

    srand(time(nullptr));
    for (int i = 0; i < (2 + 2 * difficulty); i++) {
        for (int j = 0; j < (2 + 2 * difficulty); j++) {
            Pokemon chosenEnemyPokemon = pokemons.at(rand() % 16);

            for (Pokemon x: enemiesPokemons) {
                if (x.getName() == chosenEnemyPokemon.getName()) {
                    isPokemonInArmy = true;
                }
            }

            while (isPokemonInArmy) {
                chosenEnemyPokemon = pokemons.at(rand() % 16);

                isPokemonInArmy = false;
                for (Pokemon x: enemiesPokemons) {
                    if (x.getName() == chosenEnemyPokemon.getName()) {
                        isPokemonInArmy = true;
                    }
                }
            }

            enemiesPokemons.push_back(chosenEnemyPokemon);

        }
        enemies.push_back(Player(names.at(rand() % 10), Enemy, enemiesPokemons));
        enemiesPokemons.clear();
    }

    game = Game(mainChar, enemies);

    std::cout << "\n\n\nYour army: ";
    for (auto it = playersPokemons.begin(); it != playersPokemons.end(); ++it) {
        std::cout << it->getName();
        if (std::next(it) != playersPokemons.end()) {
            std::cout << ", ";
        }
    }

    Engine::startGame();
}

auto Engine::getWeaknessesMap() -> std::unordered_map<Type, std::vector<Type>> {
    return weakness;
}

auto Engine::getStrengthMap() -> std::unordered_map<Type, std::vector<Type>> {
    return strength;
}

auto Engine::lookForWeakness(Type &attackingType, Type &defendingType) -> bool {
    std::vector<Type> vector = getWeaknessesMap().at(attackingType);

    for (auto x: vector) {
        if (x == defendingType)
            return true;
    }

    return false;
}

auto Engine::lookForStrength(Type &attackingType, Type &defendingType) -> bool {
    std::vector<Type> vector = getStrengthMap().at(attackingType);

    for (auto x: vector) {
        if (x == defendingType)
            return true;
    }

    return false;
}

auto Engine::giveBattleChoice() -> int {
    int choice;
    std::string answer;

    Pokemon *activePokemon = game.getMainChar().getActivePokemon();
    Pokemon *enemyPokemon = game.getEnemy().getActivePokemon();

    std::cout << "\nYour pokemon: " << activePokemon->getName()
              << "\n\tHP: " << activePokemon->getHP()
              << "\n\tStrength: " << activePokemon->getStrength()
              << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
              << "/" << activePokemon->getSpecialMove().getMaxUses()
              << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
              << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
              << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
              << "\n\t3 - Change pokemon\n\nYour choice:";

    std::cin >> answer;

    while (answer == "-h" || answer == "-help") {
        Engine::getHelp();

        std::cout << "\nYour pokemon: " << activePokemon->getName()
                  << "\n\tHP: " << activePokemon->getHP()
                  << "\n\tStrength: " << activePokemon->getStrength()
                  << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                  << "/" << activePokemon->getSpecialMove().getMaxUses()
                  << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                  << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                  << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                  << "\n\t3 - Change pokemon\n\nYour choice:";
        std::cin >> answer;

        if (answer != "-h" && answer != "-help") {
            choice = std::stoi(answer);
        }
    }

    choice = std::stoi(answer);

    while (choice >= 4 || choice <= 0) {
        std::cout << "You input wrong number! Try again!\n";
        std::cout << "\nYour pokemon: " << activePokemon->getName()
                  << "\n\tHP: " << activePokemon->getHP()
                  << "\n\tStrength: " << activePokemon->getStrength()
                  << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                  << "/" << activePokemon->getSpecialMove().getMaxUses()
                  << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                  << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                  << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                  << "\n\t3 - Change pokemon\n\nYour choice:";

        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "You input wrong number! Try again!\n";
            std::cout << "\nYour pokemon: " << activePokemon->getName()
                      << "\n\tHP: " << activePokemon->getHP()
                      << "\n\tStrength: " << activePokemon->getStrength()
                      << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                      << "/" << activePokemon->getSpecialMove().getMaxUses()
                      << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                      << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                      << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                      << "\n\t3 - Change pokemon\n\nYour choice:";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                choice = std::stoi(answer);
            }
        }

        choice = std::stoi(answer);
    }

    while ((activePokemon->getSpecialMove().getUses() >= activePokemon->getSpecialMove().getMaxUses()) && choice == 2) {
        std::cout << "You used all of your special moves! Try again!\n";
        std::cout << "\nYour pokemon: " << activePokemon->getName()
                  << "\n\tHP: " << activePokemon->getHP()
                  << "\n\tStrength: " << activePokemon->getStrength()
                  << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                  << "/" << activePokemon->getSpecialMove().getMaxUses()
                  << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                  << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                  << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                  << "\n\t3 - Change pokemon\n\nYour choice:";

        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "You used all of your special moves! Try again!\n";
            std::cout << "\nYour pokemon: " << activePokemon->getName()
                      << "\n\tHP: " << activePokemon->getHP()
                      << "\n\tStrength: " << activePokemon->getStrength()
                      << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                      << "/" << activePokemon->getSpecialMove().getMaxUses()
                      << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                      << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                      << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                      << "\n\t3 - Change pokemon\n\nYour choice:";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                choice = std::stoi(answer);
            }
        }

        choice = std::stoi(answer);

        while (choice >= 4 || choice <= 0) {
            std::cout << "You input wrong number! Try again!\n";
            std::cout << "\nYour pokemon: " << activePokemon->getName()
                      << "\n\tHP: " << activePokemon->getHP()
                      << "\n\tStrength: " << activePokemon->getStrength()
                      << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                      << "/" << activePokemon->getSpecialMove().getMaxUses()
                      << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                      << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                      << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                      << "\n\t3 - Change pokemon\n\nYour choice:";

            std::cin >> answer;

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout << "You input wrong number! Try again!\n";
                std::cout << "\nYour pokemon: " << activePokemon->getName()
                          << "\n\tHP: " << activePokemon->getHP()
                          << "\n\tStrength: " << activePokemon->getStrength()
                          << "\n\tUses of special move: " << activePokemon->getSpecialMove().getUses()
                          << "/" << activePokemon->getSpecialMove().getMaxUses()
                          << "\n\nEnemy:" << enemyPokemon->getName() << "\nHP: " << enemyPokemon->getHP()
                          << "\n\nChoose action:\n\t1 - Regular attack\t2 - Special attack("
                          << game.getMainChar().getActivePokemon()->getSpecialMove().getName() << ")"
                          << "\n\t3 - Change pokemon\n\nYour choice:";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    choice = std::stoi(answer);
                }
            }

            choice = std::stoi(answer);
        }
    }

    return choice;
}

auto Engine::update(Player enemyToFight) -> int {
    // return 0, if won
    // return 1, if lost
    std::cout << "\n\nNow you fight against " << enemyToFight.getName() << "!\nChoose a pokemon to start fighting!\n\n";
    for (int i = 0; i < game.getMainChar().getPokemons().size(); i++) {
        std::cout << "\t" << i + 1 << ". " << game.getMainChar().getPokemons().at(i).getName() << "\n";
    }

    int pokemonChoice;
    std::string answer;

    std::cout << "\nYour choice:";
    std::cin >> answer;

    while (answer == "-h" || answer == "-help") {
        Engine::getHelp();

        std::cout << "\n\nNow you fight against " << enemyToFight.getName()
                  << "!\nChoose a pokemon to start fighting!\n\n";
        for (int i = 0; i < game.getMainChar().getPokemons().size(); i++) {
            std::cout << "\t" << i + 1 << ". " << game.getMainChar().getPokemons().at(i).getName() << "\n";
        }
        std::cout << "\nYour choice:";

        std::cin >> answer;

        if (answer != "-h" && answer != "-help") {
            pokemonChoice = std::stoi(answer);
        }
    }

    pokemonChoice = std::stoi(answer);

    while (pokemonChoice >= 7 || pokemonChoice <= 0) {
        std::cout << "You input wrong number! Try again!\nYour choice:";
        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "You input wrong number! Try again!\nYour choice:";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                pokemonChoice = std::stoi(answer);
            }
        }

        pokemonChoice = std::stoi(answer);
    }

    Pokemon *mainCharPokemon = &game.getMainChar().getPokemons().at(pokemonChoice - 1);
    Pokemon *enemyPokemon = &game.getEnemy().getPokemons().at(rand() % 4);

    game.getMainChar().setActivePokemon(mainCharPokemon);
    game.getEnemy().setActivePokemon(enemyPokemon);
    do {
        int choice;
        if (game.getMainChar().getActivePokemon()->isFainted()) {
            choice = 3;
        } else {
            choice = Engine::giveBattleChoice();
        }
        switch (choice) {
            case 1: {
                Pokemon *defendingPokemon = game.getEnemy().getActivePokemon();
                int damage = game.getMainChar().getActivePokemon()->attackMove(defendingPokemon);
                if (damage == 0){
                    std::cout<< "Unlucky! Enemy dodged!\n";
                }else{
                    std::cout<<"You damaged for " << damage << "!\n";
                }
                break;
            }
            case 2: {
                game.getMainChar().getActivePokemon()->specialAttackMove(game.getMainChar().getActivePokemon(),
                                                                         game.getEnemy().getActivePokemon());
                std::cout << "You used your special move: "
                          << game.getMainChar().getActivePokemon()->getSpecialMove().getName()
                          << "!\n";
                break;
            }
            case 3: {
                std::cout << "Choose a pokemon to change to!\n";
                int number = 1, pokemonToChangeTo;
                for (auto x: game.getMainChar().getPokemons()) {
                    if (!x.isFainted()) {
                        std::cout << number << ") " << x.getName() << "\n";
                    }
                    number++;
                }

                std::cout << "Your choice: ";
                std::cin >> pokemonToChangeTo;

                while (pokemonToChangeTo >= number || pokemonToChangeTo <= 0) {
                    std::cout << "You input wrong number! Try again!\nYour choice:";
                    std::cin >> pokemonToChangeTo;
                }

                while (game.getMainChar().getPokemons().at(pokemonToChangeTo - 1).isFainted()) {
                    std::cout << "This pokemon is fainted! Choose another one!\nYour choice:";
                    std::cin >> pokemonToChangeTo;

                    while (pokemonToChangeTo >= 7 || pokemonToChangeTo <= 0) {
                        std::cout << "You input wrong number! Try again!\nYour choice:";
                        std::cin >> pokemonToChangeTo;
                    }
                }

                game.getMainChar().setActivePokemon(&game.getMainChar().getPokemons().at(pokemonToChangeTo - 1));
                std::cout << "You changed your active pokemon to " << game.getMainChar().getActivePokemon()->getName()
                          << "\n";
                break;
            }
            default: {
                std::cout << "Dolboeb?";
            }
        }

        // Enemy move
        if (!game.getEnemy().getActivePokemon()->isFainted() &&
            !game.getEnemy().getActivePokemon()->getSpecialMove().getActive()
            && game.getEnemy().getActivePokemon()->getSpecialMove().getUses() <
               game.getEnemy().getActivePokemon()->getSpecialMove().getMaxUses()) {
            choice = 2;
        } else {
            if (game.getEnemy().getActivePokemon()->isFainted()) {
                std::cout<<game.getEnemy().getActivePokemon()->getName()<< " has fainted!\n";
                choice = 3;
            } else {
                choice = 1;
            }
        }

//        if (game.getEnemy().getActivePokemon()->isFainted()) {
//            choice = 3;
//        }
        switch (choice) {
            case 1: {
                Pokemon *activePokemon = game.getMainChar().getActivePokemon();
                int damage = game.getEnemy().getActivePokemon()->attackMove(activePokemon);
                if (damage == 0) {
                    std::cout << "Lucky! Your pokemon dodged!\n";
                } else {
                    std::cout << "Enemy damaged you for " << damage << "!\n";
                }
                break;
            }
            case 2: {
                game.getEnemy().getActivePokemon()->specialAttackMove(game.getEnemy().getActivePokemon(),
                                                                      game.getMainChar().getActivePokemon());
                std::cout << game.getEnemy().getName() << " used "
                          << game.getEnemy().getActivePokemon()->getSpecialMove().getName() << "!\n";
                break;
            }
            case 3: {
                if (game.getEnemy().checkIfPokemonsFainted())
                    break;

                int randomPokemon;
                do {
                    randomPokemon = rand() % 4;
                    game.getEnemy().setActivePokemon(&game.getEnemy().getPokemons().at(randomPokemon));
                } while (game.getEnemy().getPokemons().at(randomPokemon).isFainted());
                std::cout << game.getEnemy().getName() << " changed pokemon to "
                          << game.getEnemy().getActivePokemon()->getName() << "!\n";
                break;
            }
        }

        for (Pokemon &x: game.getMainChar().getPokemons()) {
            x.getSpecialMove().update();
            x.checkEvolution();
        }
        for (Pokemon &x: game.getEnemy().getPokemons()) {
            x.getSpecialMove().update();
        }
    } while (!game.getMainChar().checkIfPokemonsFainted() && !game.areEnemyPokemonsFainted());

    if (game.getMainChar().checkIfPokemonsFainted()) {
        return 1;
    } else if (game.areEnemyPokemonsFainted()) {
        return 0;
    }

    return -1;
}

auto Engine::startGame() -> void {
    std::string answer;
    int exitChoice;  //added
    for (int i = 0; i < game.getEnemies().size(); i++) {
        game.updateEnemy();
        int resultOfTheRound = Engine::update(game.getEnemy());

        do {
            if (resultOfTheRound == 0) {
                int saveChoice;
                std::cout << "Congratulations!\nDo you want to save your game?\n\t1 - yes\n\t2 - no\nYour choice:";
                std::cin >> answer;

                while (answer == "-h" || answer == "-help") {
                    Engine::getHelp();

                    std::cout << "Congratulations!\nDo you want to save your game?\n\t1 - yes\n\t2 - no\nYour choice:";
                    std::cin >> answer;

                    if (answer != "-h" && answer != "-help") {
                        saveChoice = std::stoi(answer);
                    }
                }

                saveChoice = std::stoi(answer);

                while (saveChoice >= 3 || saveChoice <= 0) {
                    std::cout << "You have input wrong number, try again!\n";
                    std::cout << "Do you want to save your game?\n\t1 - yes\n\t2 - no\nYour choice:";
                    std::cin >> answer;

                    while (answer == "-h" || answer == "-help") {
                        Engine::getHelp();

                        std::cout << "You have input wrong number, try again!\n";
                        std::cout << "Do you want to save your game?\n\t1 - yes\n\t2 - no\nYour choice:";
                        std::cin >> answer;

                        if (answer != "-h" && answer != "-help") {
                            saveChoice = std::stoi(answer);
                        }
                    }
                }

                saveChoice = std::stoi(answer);

                if (saveChoice == 1) {
                    saveGame();
                }
            } else {
                game.setSameEnemy();
                resultOfTheRound = Engine::update(game.getEnemy());
            }
        } while (resultOfTheRound != 0);

//        int exitChoice;  removed
        std::cout << "Do you want to play further or exit?\n\t1 - continue\n\t2 - exit\nYour choice:";
        std::cin >> answer;

        while (answer == "-h" || answer == "-help") {
            Engine::getHelp();

            std::cout << "Do you want to play further or exit?\n\t1 - continue\n\t2 - exit\nYour choice:";
            std::cin >> answer;

            if (answer != "-h" && answer != "-help") {
                exitChoice = std::stoi(answer);
            }
        }

        exitChoice = std::stoi(answer);

        while (exitChoice >= 3 || exitChoice <= 0) {
            std::cout
                    << "You input wrong number! Try again!\nDo you want to play further or exit?\n\t1 - continue\n\t2 - exit\nYour choice:";
            std::cin >> answer;

            while (answer == "-h" || answer == "-help") {
                Engine::getHelp();

                std::cout
                        << "You input wrong number! Try again!\nDo you want to play further or exit?\n\t1 - continue\n\t2 - exit\nYour choice:";
                std::cin >> answer;

                if (answer != "-h" && answer != "-help") {
                    exitChoice = std::stoi(answer);
                }
            }

            exitChoice = std::stoi(answer);
        }

        if (exitChoice == 2)
            break;
    }
    //added
    if(exitChoice==1){
        std::cout<<"Congratulations! You've survived and completed the game!\n";
    }
}

auto Engine::loadGame(std::ifstream &fileToLoad) -> void {
    // load game to this->game;

    std::string buff;

    std::getline(fileToLoad, buff);
    diff = std::stoi(buff);

    std::string name;
    std::getline(fileToLoad, buff);
    name = buff.substr(0, buff.length() - 1);

    std::string pokemonName, pokemonType, pokemonHP, pokemonStr, pokemonDex, pokemonFainted, pokemonExp, pokemonSpecialMove;
    Type type;
    int hp, str, exp;
    float dex;
    bool fainted;
    SpecialMove specialMove;

    Player mainChar;
    std::vector<Player> enemies;

    std::vector<Pokemon> mainCharPokemon;

    for (int i = 0; i < 6; i++) {
        std::getline(fileToLoad, buff);
        std::getline(fileToLoad, buff);
        pokemonName = buff.substr(buff.find(':') + 2);

        std::getline(fileToLoad, buff);
        pokemonType = buff.substr(buff.find(':') + 2);
        if (pokemonType == "Fire") {
            type = Fire;
        } else if (pokemonType == "Water") {
            type = Water;
        } else if (pokemonType == "Ice") {
            type = Ice;
        } else if (pokemonType == "Steel") {
            type = Steel;
        } else if (pokemonType == "Air") {
            type = Air;
        } else if (pokemonType == "Earth") {
            type = Earth;
        }

        std::getline(fileToLoad, buff);
        pokemonHP = buff.substr(buff.find(':') + 2);
        hp = std::stoi(pokemonHP);

        std::getline(fileToLoad, buff);
        pokemonStr = buff.substr(buff.find(':') + 2);
        str = std::stoi(pokemonStr);

        std::getline(fileToLoad, buff);
        pokemonDex = buff.substr(buff.find(':') + 2, buff.length() - 3);
        dex = std::stof(pokemonDex);

        std::getline(fileToLoad, buff);
        pokemonFainted = buff.substr(buff.find(':') + 2);
        fainted = (pokemonFainted == "1");

        std::getline(fileToLoad, buff);
        pokemonExp = buff.substr(buff.find(':') + 2);
        exp = std::stoi(pokemonExp);

        std::getline(fileToLoad, buff);
        pokemonSpecialMove = buff.substr(buff.find(':') + 2);
        if (pokemonSpecialMove == "Aurora's fountain") {
            specialMove = aurorasFountain;
        } else if (pokemonSpecialMove == "Blaze laser") {
            specialMove = blazeLaser;
        } else if (pokemonSpecialMove == "Rock rumble") {
            specialMove = rockRumble;
        } else if (pokemonSpecialMove == "Wind fury") {
            specialMove = windFury;
        } else if (pokemonSpecialMove == "Glacier") {
            specialMove = glacier;
        } else if (pokemonSpecialMove == "Steel wall") {
            specialMove = steelWall;
        }

        mainCharPokemon.push_back(Pokemon(pokemonName, type, str, hp, exp, dex, fainted, specialMove));
    }

    std::getline(fileToLoad, buff);

    mainChar = Player(name, Friendly, mainCharPokemon);

    // Enemies
    std::vector<Pokemon> enemyPokemons;

    std::getline(fileToLoad, buff); // "Enemies{" line

    for (int i = 0; i < 2 + 2 * diff; i++) {
        std::getline(fileToLoad, buff);
        name = buff.substr(0, buff.find('{'));

        for (int j = 0; j < 2 + 2 * diff; j++) {
            std::getline(fileToLoad, buff);
            std::getline(fileToLoad, buff);
            pokemonName = buff.substr(buff.find(':') + 2);

            std::getline(fileToLoad, buff);
            pokemonType = buff.substr(buff.find(':') + 2);
            if (pokemonType == "Fire") {
                type = Fire;
            } else if (pokemonType == "Water") {
                type = Water;
            } else if (pokemonType == "Ice") {
                type = Ice;
            } else if (pokemonType == "Steel") {
                type = Steel;
            } else if (pokemonType == "Air") {
                type = Air;
            } else if (pokemonType == "Earth") {
                type = Earth;
            }

            std::getline(fileToLoad, buff);
            pokemonHP = buff.substr(buff.find(':') + 2);
            hp = std::stoi(pokemonHP);

            std::getline(fileToLoad, buff);
            pokemonStr = buff.substr(buff.find(':') + 2);
            str = std::stoi(pokemonStr);

            std::getline(fileToLoad, buff);
            pokemonDex = buff.substr(buff.find(':') + 2, buff.length() - 3);
            dex = std::stof(pokemonDex) / 100;

            std::getline(fileToLoad, buff);
            pokemonFainted = buff.substr(buff.find(':') + 2);
            fainted = (pokemonFainted == "1");

            std::getline(fileToLoad, buff);
            pokemonExp = buff.substr(buff.find(':') + 2);
            exp = std::stoi(pokemonExp);

            std::getline(fileToLoad, buff);
            pokemonSpecialMove = buff.substr(buff.find(':') + 2);
            if (pokemonSpecialMove == "Aurora's fountain") {
                specialMove = aurorasFountain;
            } else if (pokemonSpecialMove == "Blaze laser") {
                specialMove = blazeLaser;
            } else if (pokemonSpecialMove == "Rock rumble") {
                specialMove = rockRumble;
            } else if (pokemonSpecialMove == "Wind fury") {
                specialMove = windFury;
            } else if (pokemonSpecialMove == "Glacier") {
                specialMove = glacier;
            } else if (pokemonSpecialMove == "Steel wall") {
                specialMove = steelWall;
            }

            enemyPokemons.push_back(Pokemon(pokemonName, type, str, hp, exp, dex, fainted, specialMove));
        }

        std::getline(fileToLoad, buff);

        enemies.push_back(Player(name, Enemy, enemyPokemons));
        enemyPokemons.clear();
    }

    game = Game(mainChar, enemies);

    fileToLoad.close();

    Engine::startGame();
}

auto Engine::saveGame() -> void {
    std::string fileName = "save.txt";

    std::ofstream file;
    file.open(fileName);

    if (file.is_open()) {
        file << diff << "\n";

        file << game.getMainChar().getName() << "{\n";

        for (Pokemon x: game.getMainChar().getPokemons()) {
            file << x.getInfo()
                 << "\tFainted: " << x.isFainted()
                 << "\n\tExp: " << x.getExp()
                 << "\n\tSpecalMove: " << x.getSpecialMove().getName() << "\n";
        }

        file << "}\n";

        file << "Enemies:{\n";

        for (Player x: game.getEnemies()) {
            file << "\t" << x.getName() << "{\n";

            for (Pokemon y: x.getPokemons()) {
                file << "\n\t\t\tName: " << y.getName()
                     << "\n\t\t\tType: " + typesAsStrings.at(y.getType())
                     << "\n\t\t\tHealth: " + std::to_string(y.getHP())
                     << "\n\t\t\tStrength: " + std::to_string(y.getStrength())
                     << "\n\t\t\tDexterity: " + std::to_string(y.getDexterity())
                     << "\n\t\t\tFainted: " << y.isFainted()
                     << "\n\t\t\tExp: " << y.getExp()
                     << "\n\t\t\tSpecialMove: " << y.getSpecialMove().getName() << "\n";
            }

            file << "}\n";
        }

        file.close();
    }
}

auto Engine::getHelp() -> void {
    std::cout << "\t>>>>>>Welcome to Pokemon Bloodbath<<<<<<\n\n"
                 "The rules of the game are simple: beat your opponent or be beaten!\n"
                 "At the beginning you need to choose your army of 6 loyal pokemons, who will be \n"
                 "ready to spill their blood for you in the violent slaughter to the death against \n"
                 "your enemies army. The amount of the pokemons in the enemy's army and the \n"
                 "amount of enemies will depend on the difficulty you choose:\n"
                 "\tEasy -  4 enemies and 4 pokemons in their army \n"
                 "\tMedium - 6 enemies and 6 pokemons in their army \n"
                 "\tHard - 8 enemies and 8 pokemons in their army \n"
                 "When it comes to battles you will have 3 options: attack normally, use special power, change your active pokemon \n\n"
                 "to another member of your army.\n"
                 "Experience is gained after killing opponent's pokemon(when it has fainted).\n"
                 "After falling below zero Health Points, the pokemon faints and cannot be used again till the end \n"
                 "on the battle.\n\n"
                 "Every pokemon has certain attributes defining its characteristics. The attributes are as following:\n"
                 "\tStrength - defines how much damage can pokemon deal with singular attack; \n"
                 "\tDexterity - defines the chance of dodging an incoming attack; \n"
                 "\tHealth Points - defines, how much damage pokemon can take before fainting; \n"
                 "\tSpecial power - defines the characteristics of special power for a pokemon and the \n"
                 "maximum number of uses during one battle; \n\n"
                 "Experience Points (EXP) - how many Experience points a creature can gain by \n"
                 "defeating the enemy. \n"
                 "Every pokemon also has a type (Water, Earth, Air, Fire, Ice, Steel) which impacts the \n"
                 "effectiveness of their attacks against other pokemons. \n"
                 "\t*Water: Lessened effectiveness against Water, increased effectiveness against Earth, Fire \n"
                 "\t*Earth: Lessened effectiveness against Air, increased effectiveness against Fire, Ice, Steel \n"
                 "\t*Air: Lessened effectiveness against Earth, Steel, increased effectiveness against Ice \n"
                 "\t*Fire: Lessened effectiveness against Water, Earth, increased effectiveness against Ice, Steel \n"
                 "\t*Ice: Lessened effectiveness against Water, Fire, Ice, increased effectiveness against Earth\n"
                 "\t*Steel: Lessened effectiveness against Fire, Steel, increased effectiveness against Water, Air \n"
                 "Feel free to use commands -h or -help to see these rules again! :) \n"
                 "\t>>>>>>Good luck and may the Pokemon God be on your side!<<<<<< \n";
}
