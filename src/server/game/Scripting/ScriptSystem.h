/*
 * Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/>
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 * Copyright (C) 2005-2016 MaNGOS <http://getmangos.com/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 3 of the License, or (at your
 * option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SC_SYSTEM_H
#define SC_SYSTEM_H

#include "ScriptMgr.h"
#include <ace/Singleton.h>

#define TEXT_SOURCE_RANGE -1000000                          //the amount of entries each text source has available

/// @todo find better namings and definitions.
//N=Neutral, A=Alliance, H=Horde.
//NEUTRAL or FRIEND = Hostility to player surroundings (not a good definition)
//ACTIVE or PASSIVE = Hostility to environment surroundings.
enum eEscortFaction
{
    FACTION_ESCORT_A_NEUTRAL_PASSIVE    = 10,
    FACTION_ESCORT_H_NEUTRAL_PASSIVE    = 33,
    FACTION_ESCORT_N_NEUTRAL_PASSIVE    = 113,

    FACTION_ESCORT_A_NEUTRAL_ACTIVE     = 231,
    FACTION_ESCORT_H_NEUTRAL_ACTIVE     = 232,
    FACTION_ESCORT_N_NEUTRAL_ACTIVE     = 250,

    FACTION_ESCORT_N_FRIEND_PASSIVE     = 290,
    FACTION_ESCORT_N_FRIEND_ACTIVE      = 495,

    FACTION_ESCORT_A_PASSIVE            = 774,
    FACTION_ESCORT_H_PASSIVE            = 775,

    FACTION_ESCORT_N_ACTIVE             = 1986,
    FACTION_ESCORT_H_ACTIVE             = 2046
};

struct ScriptPointMove
{
    uint32 uiCreatureEntry;
    uint32 uiPointId;
    float  fX;
    float  fY;
    float  fZ;
    uint32 uiWaitTime;
};

typedef std::vector<ScriptPointMove> ScriptPointVector;

class SystemMgr
{
        friend class ACE_Singleton<SystemMgr, ACE_Null_Mutex>;
        SystemMgr() { }
        ~SystemMgr() { }

    public:
        typedef std::unordered_map<uint32, ScriptPointVector> PointMoveMap;

        //Database
        void LoadScriptWaypoints();

        ScriptPointVector const& GetPointMoveList(uint32 creatureEntry) const
        {
            PointMoveMap::const_iterator itr = m_mPointMoveMap.find(creatureEntry);

            if (itr == m_mPointMoveMap.end())
                return _empty;

            return itr->second;
        }

    protected:
        PointMoveMap    m_mPointMoveMap;                    //coordinates for waypoints

    private:
        static ScriptPointVector const _empty;
};

#define sScriptSystemMgr ACE_Singleton<SystemMgr, ACE_Null_Mutex>::instance()

#endif
