
#include <dpp/dpp.h>
#include <thread>
#include "config.h"
#include "commands.h"
#include "json.hpp"
#include "api.h"
#include <chrono>

bool doAuth = false;

long authSeconds = 1;
void authTask(dpp::cluster& bot) {
	bot.start_timer([&bot](dpp::timer h) {
		if (doAuth) { //should not execute at very first launch of task, bc i already did Auth()
			Auth();
			bot.message_create(dpp::message(1222115685824729128, "Auth Token refreshed."));
		}
		else {
			authSeconds = 14400;
			bot.message_create(dpp::message(1222115685824729128, "Auth Task started, for every 4h | 14400 Seconds."));
			doAuth = true;
		}
		bot.stop_timer(h);
		authTask(bot);
		}, authSeconds);
}

int main() {
/* Create bot cluster */
	dpp::cluster bot(bot_token, dpp::i_default_intents | dpp::i_message_content);

	// Start auth task
	authTask(bot);
    
	bot.on_log(dpp::utility::cout_logger());

	bot.on_ready([&bot](const dpp::ready_t& event) {
		dpp::activity activity(dpp::activity_type::at_game, "-help", "", "");
		dpp::presence presence(dpp::presence_status::ps_online, activity);
		bot.set_presence(presence);
        bot.message_create(dpp::message(logging_channel_id, "Bot Launched >> Username: " + bot.me.username));
		bot.message_create(dpp::message(logging_channel_id, "Acquiring Auth Token"));
		Auth();
		bot.message_create(dpp::message(logging_channel_id, "Auth Token acquired."));
		});

bot.on_message_create([&bot](const dpp::message_create_t& event) {
			if (event.msg.author.is_bot()) return; // ignore bots
			parse_command(event.msg.id.str(), event.msg.channel_id.str(), event.msg.author.id.str(),event.msg.author.username,event.msg.content);
			});

    bot.start(dpp::st_wait);
}

