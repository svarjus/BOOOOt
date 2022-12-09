
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
const std::string    BOT_TOKEN    = "";

std::vector<std::string> missing_ids;
std::string missing;
std::vector<std::string> old_tokens, new_tokens;
dpp::cluster bot(BOT_TOKEN);

inline std::string old_data, new_data;


void CheckSimilarity()
{   
    std::string uhhhhhh;

    bool first_time = true;

    while (true) {
        


        missing_ids.clear();
        missing.clear();
        new_tokens.clear();

        missing_ids.resize(1);
        missing.resize(1);
        new_tokens.resize(1);       
        old_tokens.clear();
        old_tokens.resize(1);

        new_data = FetchURLData("http://www.api.rugbug.net/bans");


        if (first_time) {
            old_data = new_data;
            first_time = false;
        }

        GetAllData(new_data, new_tokens);
        GetAllData(old_data, old_tokens);


        if (new_tokens.size() > old_tokens.size()) {
            for (size_t i = 0; i < new_tokens.size(); i++) {


                if (new_tokens[i].compare(old_tokens[i])) {

                    missing_ids.push_back(new_tokens[i]);

                    uhhhhhh = std::format("https://steamcommunity.com/profiles/{}\n", new_tokens[i]);

                    missing.insert(missing.end(), uhhhhhh.begin(), uhhhhhh.end());

                    bot.message_create(dpp::message(1050353603270942762, std::format("a new ban added! - {}\n", uhhhhhh)));
                    break;

                }
            }
        }
        else{
            for (size_t i = 0; i < old_tokens.size(); i++) {

                if (old_tokens[i].compare(new_tokens[i])) {

                    missing_ids.push_back(old_tokens[i]);

                    uhhhhhh = std::format("https://steamcommunity.com/profiles/{}\n", old_tokens[i]);

                    missing.insert(missing.end(), uhhhhhh.begin(), uhhhhhh.end());

                    bot.message_create(dpp::message(1050353603270942762, std::format("a ban has been removed! - {}\n", uhhhhhh)));
                    break;
                }
            }



        }

        missing = std::format("\ntotal missing ids: {}\n", missing_ids.size()-1);
        old_data = new_data;


        Sleep(60000);
    }

}


int main()
{

    std::thread(CheckSimilarity).detach();


    /* Output simple log messages to stdout */
    bot.on_log(dpp::utility::cout_logger());

    /* Handle slash command */
    bot.on_slashcommand([&](const dpp::slashcommand_t& event) {

         std::string name = event.command.get_command_name();
         if (name == "compare") {
//             event.reply(std::format("missing ids: {}", missing_ids.size()));
             if (!missing_ids.empty()) {

                 event.reply(missing);

             }
             else {
                 event.reply("everything is up to date");
             }

             //if (not_similar) {
             //    event.reply(std::format("https://steamcommunity.com/profiles/{} cannot be found!", missing));
             //}
             //else
             //    event.reply("ok!");
             

             //if (!tokens.empty())
             //    event.reply(tokens[0]);
             //else
             //    event.reply("AAAAAAAAAAAAAAAAAAAAAAAAAA");
        }
    });
    dpp::commandhandler command_handler(&bot);
    command_handler.add_prefix(".").add_prefix("/");



    /* Register slash command here in on_ready */
    bot.on_ready([&command_handler](const dpp::ready_t& event) {

        command_handler.add_command(
            /* Command name */
            "find_id",

            /* Parameters */
            {
                {"number", dpp::param_info(dpp::pt_string, true, "yep number") }
            },

            /* Command handler */
            [&command_handler](const std::string& command, const dpp::parameter_list_t& parameters, dpp::command_source src) {
                std::string got_param;
                if (!parameters.empty()) {
                    got_param = std::get<std::string>(parameters[0].second);
                }

                int count = 0;
                try {
                    count = std::stoi(got_param);

                    if (count < 0 || count >= new_tokens.size()) {
                        command_handler.reply(dpp::message(std::format("must be in the range of 0 to {}", new_tokens.size())), src);

                    }
                    else
                        command_handler.reply(dpp::message(std::format("https://steamcommunity.com/profiles/{}", new_tokens[count])), src);

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
            bot.global_command_create(dpp::slashcommand("compare", "ok", bot.me.id));
        }
    });

    /* Start the bot */
    bot.start(false);

    return 0;
}
