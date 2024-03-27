#pragma once
#include <string>
#include <vector>

std::tuple<std::string, std::string, bool> get_command(int id)
{
    switch (id)
    {
        case 0: return {"help", "h", false};
        case 1: return {"help_", "h_", false};
        case 2: return {"api", "api", false};
        case 3: return {"runtime", "ri", false};
        case 4: return {"database", "db", false};
        case 5: return {"export", "ex", false};
        case 6: return {"import", "im", false};
    }
 
   
}
static int tuple_size = 8;
std::tuple<std::string> get_command_description(int id)
{
    switch (id)
    {
        case 0: return {"This command"};
        case 1: return {"Bot owner commands"};
        case 2: return {"Perform api_v1 requests"};
        case 3: return {"Runtime Info"};
        case 4: return {"Database Info"};
        case 5: return {"Export specific database table."};
        case 6: return {"Replace entire database from import."};
    }
 
   
}

void parse_command(std::string messageID, std::string channelID, std::string authorID, std::string authorUsername, std::string messageContent){
    
}
