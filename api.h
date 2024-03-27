#pragma once
#include "cpr/cpr.h"
#include "json.hpp"
static void Auth() {
	nlohmann::json AuthResult;
	std::string body = R"({"client_id":)" + api_v2_client_id + R"(, "client_secret":")" + api_v2_client_secret + R"(", "grant_type":"client_credentials", "scope":"public"})";
	auto r = cpr::Post(cpr::Url{ "https://osu.ppy.sh/oauth/token" },
		cpr::Body{
		body
	},
		cpr::Header{ { "Content-Type", "application/json" } });
	AuthResult = nlohmann::json::parse(r.text);
	api_v2_auth_token = "Bearer " + AuthResult.value("access_token", "");
	AuthResult.clear();
}