/*CLI management*/
#include<CLI11.hpp>

/*io*/
#include<iostream>

/*string management*/
#include<string>
#include<string_view>

int main(int argc, char** argv)
{
//CLI parser declarations
	CLI::App dmeh("general media handler", argv[0]);

	CLI::App* ytdlp= dmeh.add_subcommand("ytdlp","using ytdlp as downloader");
	ytdlp->get_formatter()->label("Positionals","Arguments");
	
	//main ytdlp arguments
	std::string youtubeLink;
	ytdlp->add_option("playlist_link",youtubeLink,"the URL of the youtube playlist")->required();

	std::string rootPlaylistPath;
	ytdlp->add_option("root_file_path",rootPlaylistPath,"the directory where the playlists will be downloaded")->required();

	std::string archiveFile;
	ytdlp->add_option("archive_file",archiveFile,"where the video IDs will be stored to not repeat downloads")->required();

	ytdlp->footer
	(
		R"(
Example (Command line):\n
	"https://youtube.com..." "/home/user/Music" "archive.txt"\n
Interactive mode:\n
	simply run dmeh without arguments to be prompted with a standard walkthrough, using a default preset \n)"
	);
	dmeh.require_subcommand(1);

//for the interactive part of the code
	if(argc== 1)
	{
        std::cout<< "select tool: ytdlp(1)";
        std::string tool;
        std::getline(std::cin, tool);

        if(tool== "1")
		{
            std::cout<< "enter youtube playlist link: ";
            std::getline(std::cin, youtubeLink);
            std::cout<< "enter root playlist path: ";
            std::getline(std::cin, rootPlaylistPath);
            std::cout<< "enter archive file path: ";
            std::getline(std::cin, archiveFile);
            
			//TODO: ytdlp logic here
        }
        return 0;
    }

	if(ytdlp->parsed())
	{
        std::cout<< "Running Playlist Tool:\n"
                 << "  Link:    " << youtubeLink 	   << "\n"
                 << "  Root:    " << rootPlaylistPath << "\n"
                 << "  Archive: " << archiveFile      << "\n";
    }
	/*
	else if(spotifycli->parsed())
	{
    	TODO:
    }
	*/
}
