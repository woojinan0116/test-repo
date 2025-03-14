안우진 202402678 컴퓨터공학부

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

class Monster;

class Character {
    char* name;
    int level;
    int health;
    int attackPower;
    static int characterCount;
    int experience;

public:
    Character(const char* name, int level, int health, int attackPower)
        : level(level), health(health), attackPower(attackPower), experience(0) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        characterCount++;
    }

    ~Character() {
        delete[] name;
        characterCount--;
    }

    Character(const Character& other)
        : level(other.level), health(other.health), attackPower(other.attackPower), experience(other.experience) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
        characterCount++;
    }

    void printStatus() const {
        cout << "Character: " << name << ", Level: " << level << ", Health: " << health
            << ", Attack Power: " << attackPower << ", Experience: " << experience << endl;
    }

    static void printCharacterCount() {
        cout << "Character Count: " << characterCount << endl;
    }

    void attack(Monster& target);

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    void heal(int amount) {
        health += amount;
    }

    void gainExperience(int exp) {
        experience += exp;
        if (experience >= level * 30) {
            experience -= level * 30;
            level++;
            attackPower += 5;
            health += 20;
            cout << name << " leveled up! Now Level " << level << ", Attack Power + 5" << ", Health + 20" << endl;
        }
    }

    void useItem(const class Item& item);

    const char* getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }
};

int Character::characterCount = 0;

class Monster {
    char* name;
    int health;
    int attackPower;
    int experience;

public:
    Monster(const char* name, int health, int attackPower, int experience)
        : health(health), attackPower(attackPower), experience(experience) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
    }

    ~Monster() {
        delete[] name;
    }

    Monster(const Monster& other)
        : health(other.health), attackPower(other.attackPower), experience(other.experience) {
        this->name = new char[strlen(other.name) + 1];
        strcpy(this->name, other.name);
    }

    void printStatus() const {
        cout << "Monster: " << name << ", Health: " << health << ", Attack Power: " << attackPower << endl;
    }

    void takeDamage(int damage) {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isDefeated() const {
        return health <= 0;
    }

    void attack(Character& target) {
        cout << name << " attacks " << target.getName() << " for " << attackPower << " damage!" << endl;
        target.takeDamage(attackPower);
    }

    int getExperience() const {
        return experience;
    }

    const char* getName() const {
        return name;
    }

    int getHealth() const {
        return health;
    }

    void increaseAttackPower(int amount) {
        attackPower += amount;
        cout << name << "'s attack power increased by " << amount << "! New Attack Power: " << attackPower << endl;
    }

};

void Character::attack(Monster& target) {
    cout << "" << endl;
    cout << name << " attacks " << target.getName() << " for " << attackPower << " damage!" << endl;
    target.takeDamage(attackPower);

    if (target.isDefeated()) {
        cout << target.getName() << " has been defeated!" << endl;
        cout << name << " gains " << target.getExperience() << " experience points!" << endl;
        gainExperience(target.getExperience());
    }
    else {
        cout << target.getName() << "'s remaining health: " << target.getHealth() << endl;
    }
}

class Item {
    char* itemName;
    int power;
    bool isHealingItem;

public:
    Item(const char* itemName, int power, bool isHealingItem)
        : power(power), isHealingItem(isHealingItem) {
        this->itemName = new char[strlen(itemName) + 1];
        strcpy(this->itemName, itemName);
    }

    ~Item() {
        delete[] itemName;
    }

    Item(const Item& other)
        : power(other.power), isHealingItem(other.isHealingItem) {
        this->itemName = new char[strlen(other.itemName) + 1];
        strcpy(this->itemName, other.itemName);
    }

    void printInfo() const {
         cout << "Item: \"" << itemName << "\", Effect: " << power
                << (isHealingItem ? " (Healing)" : " (Attack Power Boost)") << endl;
       

    }

    int use() const {   
        return power;
    }

    bool getIsHealingItem() const {
        return isHealingItem;
    }
};

void Character::useItem(const Item& item) {
    if (item.getIsHealingItem()) {
        heal(item.use());
        cout << name << " used a healing item! Recovered " << item.use() << " health." << endl;
    }
    else {
        attackPower += item.use();
        cout << name << " used an attack boost item! Attack Power increased by " << item.use() << "." << endl;
    }
}

int main() {
    Character* warrior = new Character("Warrior", 1, 100, 20);
    Monster* monsters[3] = {
        new Monster("Slime #1", 32, 11, 11),
        new Monster("Slime #2", 31, 10, 12),
        new Monster("Slime #3", 35, 12, 15)
    };

    cout << " --- Harder Mode --- " << endl;
    for (int i = 0; i < 3; i++) {
        monsters[i]->increaseAttackPower(2); // °ø°Ý·Â +2
    }

    Item* healthPotion = new Item("Health Potion", 20, true);
    Item* attackPotion = new Item("Attack Boost Potion", 5, false);

    Character::printCharacterCount();
    warrior->printStatus();
    for (int i = 0; i < 3; i++) {
        monsters[i]->printStatus();
    }
    healthPotion->printInfo();
    attackPotion->printInfo();

    


    cout << "--- Battle Begins! ---" << endl;

    warrior->useItem(*attackPotion);
   
    for (int i = 0; i < 3; i++) {
        while (!monsters[i]->isDefeated() && warrior->getHealth() > 0) {
          
            if (warrior->getHealth() <= 80) {
                warrior->useItem(*healthPotion);
            }

            warrior->attack(*monsters[i]);
            if (!monsters[i]->isDefeated()) {
                monsters[i]->attack(*warrior);
            }
        }
    }
    
    cout << "" << endl;
    cout << "--- End of Battle! ---" << endl;
    warrior->printStatus();
    Character::printCharacterCount();

    
    delete warrior;
    for (int i = 0; i < 3; i++) {
        delete monsters[i];
    }
    delete healthPotion;
    delete attackPotion;

    return 0;
}
