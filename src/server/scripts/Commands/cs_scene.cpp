/*
 * Copyright (C) 2008-2016 TrinityCore <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; either version 2 of the License, or (at your
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

#include "ScriptMgr.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "ObjectMgr.h"

class scene_commandscript : public CommandScript
{
public:
    scene_commandscript() : CommandScript("scene_commandscript") { }

    std::vector<ChatCommand> GetCommands() const override
    {
        static std::vector<ChatCommand> sceneCommandTable =
        {
            { "debug",          SEC_ADMINISTRATOR,  false,  &HandleDebugSceneCommand,       },
            { "play",           SEC_ADMINISTRATOR,  false,  &HandlePlaySceneCommand,        },
            { "playpackage",    SEC_ADMINISTRATOR,  false,  &HandlePlayScenePackageCommand, },
            { "cancel",         SEC_ADMINISTRATOR,  false,  &HandleCancelSceneCommand,      },
        };

        static std::vector<ChatCommand> commandTable =
        {
            { "scene",          SEC_ADMINISTRATOR,  true,   sceneCommandTable               },
        };

        return commandTable;
    }

    static bool HandleDebugSceneCommand(ChatHandler* handler, char const* /*args*/)
    {
        if (Player* player = handler->GetSession()->GetPlayer())
        {
            player->GetSceneMgr().ToggleDebugSceneMode();
            handler->PSendSysMessage(player->GetSceneMgr().IsInDebugSceneMode() ? LANG_COMMAND_SCENE_DEBUG_ON : LANG_COMMAND_SCENE_DEBUG_OFF);
        }

        return true;
    }

    static bool HandlePlaySceneCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char const* sceneIdStr = strtok((char*)args, " ");

        if (!sceneIdStr)
            return false;

        uint32 sceneId = atoi(sceneIdStr);
        Player* target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sObjectMgr->GetSceneTemplate(sceneId))
            return false;

        target->GetSceneMgr().PlayScene(sceneId);
        return true;
    }

    static bool HandlePlayScenePackageCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        char const* scenePackageIdStr = strtok((char*)args, " ");
        char const* flagsStr = strtok(NULL, "");

        if (!scenePackageIdStr)
            return false;

        uint32 scenePackageId = atoi(scenePackageIdStr);
        uint32 flags = flagsStr ? atoi(flagsStr) : SCENEFLAG_UNK16;
        Player* target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        if (!sSceneScriptPackageStore.HasRecord(scenePackageId))
            return false;

        target->GetSceneMgr().PlaySceneByPackageId(scenePackageId, flags);
        return true;
    }

    static bool HandleCancelSceneCommand(ChatHandler* handler, char const* args)
    {
        if (!*args)
            return false;

        Player* target = handler->getSelectedPlayer();

        if (!target)
        {
            handler->SendSysMessage(LANG_PLAYER_NOT_FOUND);
            handler->SetSentErrorMessage(true);
            return false;
        }

        uint32 id = atoi((char*)args);

        if (!sSceneScriptPackageStore.HasRecord(id))
            return false;

        target->GetSceneMgr().CancelSceneByPackageId(id);
        return true;
    }
};

void AddSC_scene_commandscript()
{
    new scene_commandscript();
}
