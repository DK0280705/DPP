/************************************************************************************
 *
 * D++, A Lightweight C++ library for Discord
 *
 * Copyright 2021 Craig Edwards and D++ contributors 
 * (https://github.com/brainboxdotcc/DPP/graphs/contributors)
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ************************************************************************************/
#include <dpp/discord.h>
#include <dpp/event.h>
#include <string>
#include <iostream>
#include <fstream>
#include <dpp/discordclient.h>
#include <dpp/discord.h>
#include <dpp/cache.h>
#include <dpp/stringops.h>
#include <nlohmann/json.hpp>
#include <dpp/discordevents.h>

using json = nlohmann::json;

namespace dpp { namespace events {

using namespace dpp;

/**
 * @brief Handle event
 * 
 * @param client Websocket client (current shard)
 * @param j JSON data for the event
 * @param raw Raw JSON string
 */
void guild_member_remove::handle(DiscordClient* client, json &j, const std::string &raw) {
	json d = j["d"];

	dpp::guild_member_remove_t gmr(client, raw);

	gmr.removing_guild = dpp::find_guild(SnowflakeNotNull(&d, "guild_id"));
	gmr.removed = dpp::find_user(SnowflakeNotNull(&(d["user"]), "id"));

	if (client->creator->dispatch.guild_member_remove)
		client->creator->dispatch.guild_member_remove(gmr);

	if (gmr.removing_guild && gmr.removed) {
		auto i = gmr.removing_guild->members.find(gmr.removed->id);
		if (i != gmr.removing_guild->members.end()) {
			delete i->second;
			gmr.removing_guild->members.erase(i);
		}
	}
}

}};