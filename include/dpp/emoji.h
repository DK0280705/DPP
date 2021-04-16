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
#pragma once
#include <dpp/discord.h>
#include <dpp/json_fwd.hpp>

namespace dpp {

#define MAX_EMOJI_SIZE 256 * 1024

enum emoji_flags {
	e_require_colons = 0b00000001,
	e_managed =        0b00000010,
	e_animated =       0b00000100,
	e_available =      0b00001000,
};

class emoji : public managed {
public:
	std::string name;
	snowflake user_id;
	uint8_t flags;
	std::string* image_data;
	
	emoji();
	~emoji();

	/** Read class values from json object
	 * @param j A json object to read from
	 * @return A reference to self
	 */
	emoji& fill_from_json(nlohmann::json* j);

	/**
	 * @brief Build the json for this object
	 * 
	 * @param with_id include the id in the JSON
	 * @return std::string json data
	 */
	std::string build_json(bool with_id = false) const;

	/**
	 * @brief Emoji requires colons
	 * 
	 * @return true Requires colons
	 * @return false Does not require colons
	 */
	bool requires_colons() const;

	/**
	 * @brief Emoji is managed
	 * 
	 * @return true Is managed
	 * @return false Is not managed
	 */
	bool is_managed() const;

	/**
	 * @brief Emoji is animated
	 * 
	 * @return true Is animated
	 * @return false Is noy animated
	 */
	bool is_animated() const;

	/**
	 * @brief Is available
	 * 
	 * @return true Is available
	 * @return false Is unavailable
	 */
	bool is_available() const;

	/**
	 * @brief Load an image into the object as base64
	 * 
	 * @param image_blob Image binary data
	 * @param type Type of image
	 * @return emoji& Reference to self
	 */
	emoji& load_image(const std::string &image_blob, image_type type);
};

/**
 * @brief Group of emojis
 */
typedef std::unordered_map<snowflake, emoji> emoji_map;

};
