#include <iostream>
#include "entities.hpp"
#include "attacks.hpp"
#include "items/protoITEMS/storage.hpp"

Character::Character(){
    health = 100;
    strength = 10;
    defense = 5;
    speed = 5;
    heals = 3;
    store = new Storage();
}

Character::~Character(){ 
	delete attackType;
	delete store;
        if(weapon != nullptr)
	   delete weapon;
 }

void Character::takeAttack(int damage){
    if (defend)
    {
        defend = false;
        damage /= 2;
        if (damage - getDefense() <= 0)
        {
            cout << "BLOCKED" << endl;
            cout << "Damage taken: 0" << endl;
            return;
        }
        setHealth(damage - getDefense());
        cout << "BLOCKED" << endl;
        cout << "Damage taken: " << damage - getDefense() << endl;
        return;
    }
    else
    {
        if (dodge)
        {
            dodge = false;
            dodgeAttempt = false;
            cout << "DODGE SUCCESSFUL" << endl;
            cout << "Damage taken: 0" << endl;
            return;
        }
        else
        {
            if (dodgeAttempt)
            {
                dodgeAttempt = false;
                cout << "DODGE FAILED" << endl;
            }
            
            if (damage - getDefense() <= 0)
            {
                cout << "Damage taken: 0" << endl;
                return;
            }
            setHealth(damage - getDefense());
            cout << "Damage taken: " << damage - getDefense() << endl;
        }
    }
}

void Character::setAttackType(CharacterAttack* newType){ 
    delete attackType;
    attackType = newType;
}

void Character::attack(Entity* enemy){
    defend = false;
   if(weapon != nullptr)
        enemy->takeAttack( attackType->attack(this) + weapon -> getDmg() );
   else  enemy->takeAttack( attackType->attack(this) );
}


int WarriorAttack::attack(Character* player){ 
    return player->getStrength() + 2; 
}

int KnightAttack::attack(Character* player){
    return player->getStrength() - (player->getDefense() / 2);
}

int HunterAttack::attack(Character* player){
    return player->getStrength() + (player->getSpeed() / 2); 
}

void Character::changeWeapon(){
    if(store ->weaponInStorage()){
        if(weapon != nullptr){ 
            unEquip();
        }
        store ->DisplayStorage(std::cout );
        std::cout<< "pick the number next to the item to get it: ";
        int choose;
        bool a = false;
        do{
            cin >> choose;
            if(choose - 1 < store ->getLength() && choose > 0 ){ 
                weapon =store ->getItem(choose);
                if(weapon == nullptr){
                    std::cout << "Invalid choice" << endl;
                }
                else a = true;
            }
            else std::cout << "Invalid choice, try again: " << endl;
        }while(a != true);
    }
    else std::cout << "No weapons in storage available" << endl;
}

void Character::unEquip()
{
    if(weapon == nullptr) std::cout << "No weapon equip" << endl;
    else{ 
        storeItem(weapon);
        weapon = nullptr;
    }
}
void Character::PotionHeal(Entity* person){
   if(store -> consumInStorage())
	store ->heal(person);
   else std::cout << "No potion in storage" << endl;
}

void Character::storeItem(Item* item){store ->add_Item(item);}
void Character::ShowStorage(std::ostream& cout){store ->DisplayStorage(cout);}
void Character::refillPotion()
{
   if(store -> consumInStorage()){
	store -> refill();
	std::cout << "Potions refilled" << endl;
   }
   else std::cout << "No potion in storage" << endl;
}
