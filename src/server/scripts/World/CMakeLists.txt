# Copyright (C) 2011-2016 Project SkyFire <http://www.projectskyfire.org/
# Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
  World/achievement_scripts.cpp
  World/areatrigger_scripts.cpp
  World/argent_tournament.cpp
  World/boss_emerald_dragons.cpp
  World/chat_log.cpp
  World/darkmoon_island.cpp
  World/duel_scripts.cpp
  World/fangs_of_father_scripts.cpp
  World/go_scripts.cpp
  World/guards.cpp
  World/project_scripts.cpp
  World/item_scripts.cpp
  World/mob_generic_creature.cpp
  World/npc_innkeeper.cpp
  World/npc_professions.cpp
  World/npc_taxi.cpp
  World/npcs_special.cpp
  World/tarecgosa_scripts.cpp
  World/BrawlersGuild/brawlers_guild.cpp
  World/BrawlersGuild/brawlers_guild.h
  World/transmog_scripts.cpp
)

message("  -> Prepared: World")
