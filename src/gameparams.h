// Luanti
// SPDX-License-Identifier: LGPL-2.1-or-later
// Copyright (C) 2010-2013 celeron55, Perttu Ahola <celeron55@gmail.com>

#pragma once

#include "irrlichttypes.h"
#include "content/subgames.h"
#include "log.h" // errorstream

// Information provided from "main"
// Start information for server or client
struct GameParams
{
	GameParams() = default;

	std::string world_path;
	SubgameSpec game_spec;
	bool is_dedicated_server;
	u16 socket_port;
};

enum class ELoginRegister {
	Any = 0,
	Login,
	Register
};

struct GameClientData
{
	bool isSinglePlayer() const { return mode == GM_SINGLEPLAYER; }
	bool isAnyServer() const
	{ return mode == GM_HOST_AND_JOIN || mode == GM_SINGLEPLAYER; }

	std::string name;
	std::string password;
	std::string address; //< non-empty when joining a server

	enum Mode {
		GM_SINGLEPLAYER,
		GM_HOST_AND_JOIN,
		GM_JOIN,
		GM_Undefined
	} mode = GM_Undefined;

	ELoginRegister allow_login_or_register = ELoginRegister::Any;
};

// Information provided by ClientLauncher
// Client-only data (joining or hosting server)
struct GameStartData : GameParams, GameClientData
{
	GameStartData() = default;

	// "world_path" must be kept in sync!
	WorldSpec world_spec;
};

/// Data provided to Lua for error reporting by the main menu
struct GameErrorData
{
	GameErrorData() = default;

	/// Raise and log an error
	/// @param msg Empty string means no error
	void setError(const std::string &msg, bool reconnect = false)
	{
		message = msg;
		reconnect_requested = reconnect;
		is_error = true;
		errorstream << msg << std::endl;
	}

	/// Show a disconnect / access-denied reason without framing it as an engine error
	/// @param msg Empty string means no message
	void setDisconnect(const std::string &msg, bool reconnect = false)
	{
		message = msg;
		reconnect_requested = reconnect;
		is_error = false;
		errorstream << msg << std::endl;
	}

	// Whether the server has requested a reconnect
	bool reconnect_requested = false;
	/// When false, the main menu shows a disconnect title instead of "An error occurred"
	bool is_error = true;
	std::string message;
};
