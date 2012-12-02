/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef XEEN_CHARACTERS_H
#define XEEN_CHARACTERS_H

#include "xeen/utility.h"

#include "common/scummsys.h"
#include "common/stream.h"
#include "common/ptr.h"

namespace XEEN
{
    class Game;
    class CCFileData;
    class Sprite;
    class Party;

    enum Sex {MALE, FEMALE};
    inline const char* getSexName(Sex sex)
    {
        return (sex == MALE) ? "Male" : "Female";
    }

    enum Race {HUMAN, ELF, DWARF, GNOME, HALFORC};

    inline const char* getRaceName(Race race)
    {
        switch(race)
        {
            case HUMAN: return "Human";
            case ELF: return "Elf";
            case DWARF: return "Dwarf";
            case GNOME: return "Gnome";
            case HALFORC: return "Half-orc";
            default: return "BAD RACE VALUE";
        }
    }


    enum Side {CLOUDS, DARKSIDE};
    enum Class {KNIGHT, PALADIN, ARCHER, CLERIC, SORCERER, ROBBER, NINJA, BARBARIAN, DRUID, RANGER};
    
    inline const char* getClassName(Class clazz)
    {
        switch(clazz)
        {
            case KNIGHT: return "Knight";
            case PALADIN: return "Paladin";
            case ARCHER: return "Archer";
            case CLERIC: return "Cleric";
            case SORCERER: return "Sorcerer";
            case ROBBER: return "Robber";
            case NINJA: return "Ninja";
            case BARBARIAN: return "Barbarian";
            case DRUID: return "Druid";
            case RANGER: return "Ranger";
            default: return "BAD CLASS VALUE";
        }
    }    

    struct Statistic
    {
        int8 real;
        int8 temp;
        
        Statistic() : real(0), temp(0) {}
        Statistic(int8 realv, int8 tempv) : real(realv), temp(tempv) {}
        Statistic(Common::ReadStream& stream) : real(stream.readByte()), temp(stream.readByte()) {}
        
        int16 getValue() const { return real + temp; }
        void modifyReal(int8 value) { real += value; }
        void modifyTemp(int8 value) { temp += value; }
        void resetTemp() { temp = 0; }
    };

    enum Stat { MIGHT, INTELLECT, PERSONALITY, ENDURANCE, SPEED, ACCURACY, LUCK, STAT_COUNT };

    // Stats for a single playable character
    class Character : public Validateable
    {
        friend class Party;
    
        private:
            Character(Common::ScopedPtr<CCFileData>& data, Sprite* faceSprite);
        
        public:
            const Statistic& getStat(Stat stat) const;
        
        public:
            Sprite* face;
        
            char name[16];
            Sex sex;
            Race race;
            Side saveSide;
            Class profession;
            
            int8 actemp;
            
            int8 level[2];
            
            int8 dbday;
            int8 agetemp;
            
            int8 skills[18];
            int8 awards[64];
            int8 spells[39];

            // Beacon
            uint8 beaconMap;
            uint8 beaconX;
            uint8 beaconY;
            Side beaconSide;

            uint8 hasSpells;
            uint8 currentSpell;
            uint8 quickOption;

            // Items
            uint8 weapons[36];
            uint8 armor[36];
            uint8 accessories[36];
            uint8 misc[36];
            
            
            int8 resistences[12];            
            int8 conditions[16];
            
            int8 unknown[3];

            int16 hp;
            int16 sp;
            int16 bday2;
            
            uint32 experience;
            
            uint8 adventureSpell;
            uint8 combatSpell;
            
        private:
            Statistic _statistics[STAT_COUNT];
    };
}

#endif // XEEN_CHARACTERS_H
