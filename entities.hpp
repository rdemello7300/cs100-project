#ifndef __ENTITIES_HPP__
#define __ENTITIES_HPP__

#include <string>
#include <iostream>
#include "attacks.hpp"
#include "items/protoITEMS/protoITEMS.hpp"
#include "items/protoITEMS/storage.hpp"

using namespace std;
class Storage;

class Entity {
    protected:
        int health;
        int strength;
        bool defend = false;
        bool dodge = false;
        bool dodgeAttempt = false;
    public:
        virtual void setHealth(int) = 0;
        int getHealth() {return health;}
        void setStrength(int newStrength){strength = newStrength;}
        int getStrength(){return strength;}
        void setDefend(bool def){defend = def;}
        bool getDefend(){return defend;}
        void setDodgeAttempt(bool is_dodge){dodgeAttempt = is_dodge;}
        virtual void attack(Entity*) = 0; //calculates how much damage to give to enemy
        virtual void takeAttack(int) = 0; //calculates how much of the above damage to intake
};

class Monster : public Entity {
    private:
        void takeAttack(int damage)
        {
            if (defend)
            {
                setHealth(damage / 2);
                cout << "BLOCKED" << endl;
                cout << "Damage dealt: " << damage / 2 << endl;
                defend = false;
            }
            
            else
            {
                setHealth(damage);
                cout << "Damage dealt: " << damage << endl;
            }
        }
    public:
        Monster(int h = 100, int s = 15){health = h; strength = s;}
        void attack(Entity* player){
            defend = false;
            player->takeAttack( this->getStrength() );
        }
        void setHealth(int damage)
        {
            health -= damage;
            if (health < 0)
                health = 0;
        }
};

class Character : public Entity {
    private:
        int defense;
        int speed;
        CharacterAttack* attackType = nullptr;
        string attackString;
        void takeAttack(int);
	Weapon* weapon = nullptr;//
        Storage* store;//
    public:
        Character();
        ~Character();
        void setHealth(int damage)
        {
            health -= damage;
            if (health > 100)
                health = 100;
            if (health < 0)
                health = 0;
        }
        void setDefense(int d){ defense = d; }
        int getDefense(){ return defense; }
        void setSpeed(int s){ speed = s; }
        int getSpeed(){ return speed; }
        void setDodge(bool dod){ dodge = dod; }
        bool getDodge(){ return dodge; }
        void setAttackType(CharacterAttack*);
        CharacterAttack* getAttackType() { return attackType; }
        void setAttackString(string s){ attackString = s; }
        string getAttackString(){ return attackString; }
        void attack(Entity* enemy);

	void changeWeapon();//
        void unEquip();//
        void storeItem(Item*);
        void ShowStorage(std::ostream& cout);
        bool PotionHeal();
        void setWeapon(Weapon* w){ weapon = w; }
        Weapon* getWeapon(){return weapon;}
        Storage* getStorage(){return store;}
	      void refillPotion();
};

#endif //__ENTITIES_HPP__
