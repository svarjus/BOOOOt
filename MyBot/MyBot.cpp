
#include "MyBot.h"
#include <dpp/dpp.h>

#include "pch.h"
/* Be sure to place your token in the line below.
 * Follow steps here to get a token:
 * https://dpp.dev/creating-a-bot-application.html
 * When you invite the bot, be sure to invite it with the 
 * scopes 'bot' and 'applications.commands', e.g.
 * https://discord.com/oauth2/authorize?client_id=940762342495518720&scope=bot+applications.commands&permissions=139586816064
 */
const std::string    BOT_TOKEN    = "MTA1MDM1MTEzMzE1MzA0NjU5OA.GOl40P.m7oQvun6fShzZUjavCK4M7nBRZIjdNirgbGb74";

int main()
{
    WebPageData = FetchURLData("http://16.170.254.129/bans.json");
    std::vector<std::string> tokens;

    //WebPageData.erase(WebPageData.begin(), WebPageData.begin() + 1500);
    GetAllData(tokens);

    /* Create bot cluster */
    dpp::cluster bot(BOT_TOKEN);

    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    ///* Handle slash command */
    //bot.on_slashcommand([tokens](const dpp::slashcommand_t& event) {

    //     std::string name = event.command.get_command_name();
    //     if (name.find("aaaa") != std::string::npos) {

    //         if (name.size() == 4) {

    //             event.reply("Enter a number!");
    //          }
    //         else {

    //             

    //           //  event.reply("Pong!");
    //         }
    //    }
    //});
    dpp::commandhandler command_handler(&bot);
    command_handler.add_prefix(".").add_prefix("/");



    /* Register slash command here in on_ready */
    bot.on_ready([&bot, &command_handler, &tokens](const dpp::ready_t& event) {

        command_handler.add_command(
            /* Command name */
            "bbbb",

            /* Parameters */
            {
                {"testparameter", dpp::param_info(dpp::pt_string, true, "Optional test parameter") }
            },

            /* Command handler */
            [&command_handler, &tokens](const std::string& command, const dpp::parameter_list_t& parameters, dpp::command_source src) {
                std::string got_param;
                if (!parameters.empty()) {
                    got_param = std::get<std::string>(parameters[0].second);
                }

                int count = 0;
                try {
                    count = std::stoi(got_param);

                    if (count < 0 || count >= tokens.size()) {
                        command_handler.reply(dpp::message(std::format("must be in the range of 0 to {}", tokens.size())), src);

                    }
                    else
                        command_handler.reply(dpp::message(std::format("index {} out of {}: {}", count, tokens.size(), tokens[count])), src);

                    // event.reply(std::format("total bans: {}", tokens.size()));
                }
                catch (std::exception& ex) {
                    command_handler.reply(dpp::message("epic number failure!"), src);
                }


                //command_handler.reply(dpp::message("Pong! -> " + got_param), src);
            },

            /* Command description */
                "A test ping command",

                /* Guild id (omit for a global command) */
                1005801374644178944);

        command_handler.register_commands();


        /* Wrap command registration in run_once to make sure it doesnt run on every full reconnection */
        if (dpp::run_once<struct register_bot_commands>()) {
            bot.global_command_create(dpp::slashcommand("aaaa", "Ping pong!", bot.me.id));
        }
    });

    /* Start the bot */
    bot.start(false);

    return 0;
}
