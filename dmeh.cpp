/*CLI management*/
#include<CLI/CLI.hpp>

/*io*/
#include<iostream>
#include<cstdlib>

/*string management*/
#include<string>


void verboseYtdlpLogic(std::string rootPlaylistPath, std::string youtubeLink, std::string archiveFile, std::string browser, bool cookies)
{
	std::string mainCommand=
		"yt-dlp --extractor-args "
		"youtubetab:skip=authcheck "
		"--yes-playlist "
		"--embed-thumbnail "
		"--embed-metadata "
		"-N 4 "
		"-i "
		"--geo-bypass "
		"--retry 10"
		"-x --audio-format mp3 "
		"--ignore-errors"
		"-f bestaudio";

	std::string buffer;
	if(cookies==true && !browser.empty())
	{
		buffer= mainCommand+"--cookies-from-browser \""+browser+"\" --paths \""+rootPlaylistPath+"\" -o '%(playlist)s/%(title)s - %(id)s' \""+youtubeLink+"\" --download-archive \""+archiveFile+"\"";
		system(buffer.c_str());
	}
	else if(cookies==false && browser.empty())
	{
		buffer= mainCommand+"--paths \""+rootPlaylistPath+"\" -o '%(playlist)s/%(title)s - %(id)s' \""+youtubeLink+"\" --download-archive \""+archiveFile+"\"";
		system(buffer.c_str());
	}
	else if(cookies==true && browser.empty())
	{
		buffer= mainCommand+"--cookies-from-browser firefox --paths \""+rootPlaylistPath+"\" -o '%(playlist)s/%(title)s - %(id)s' \""+youtubeLink+"\" --download-archive \""+archiveFile+"\"";
		system(buffer.c_str());
	}
}

void verboseSpotdlLogic(std::string rootPlaylistPath, std::string spotifyLink, std::string archiveFile, std::string browser, bool cookies)
{
	
}

int main(int argc, char** argv)
{
//CLI parser declarations
	CLI::App dmeh("general media handler", argv[0]);

	CLI::App* ytdlp= dmeh.add_subcommand("ytdlp","using ytdlp as downloader");
	ytdlp->get_formatter()->label("Positionals","Arguments");
	
	CLI::App* spotdl= dmeh.add_subcommand("spotdl","using spotdl as downloader");
	spotdl->get_formatter()->label("Positionals","Arguments");
	//main ytdlp arguments
		std::string youtubeLink;
		ytdlp->add_option("-l, --link",youtubeLink,"the URL of the youtube playlist\n")->required();

		std::string rootPlaylistPath;
		ytdlp->add_option("-p, --folderpath",rootPlaylistPath,"the directory where the playlists will be downloaded\n")->required();

		std::string archiveFile;
		ytdlp->add_option("-a, --archivefile",archiveFile,"where the video IDs will be stored to not repeat downloads\n")->required();

		std::string browser;
		ytdlp->add_option("-b, --browser",browser,"specify the browser to be used, getting the cookies from said browser\n");

		bool verbose{false};
		ytdlp->add_option("-v, --verbose",verbose,"makes the ytdlp process visible, useful for slow internet when cookies stop working before the download finishes\n");
   
		bool cookies{false};
		ytdlp->add_option("-c, --cookies", cookies,"enables cookies\n");

		ytdlp->footer(
			"Example (Command line):\n"
			"\tdmeh ytdlp https://youtube.com/1234 /home/user/Music ~archive.txt\n"
			"Interactive mode:\n"
			"\tsimply run dmeh without arguments to be prompted with a standard walkthrough, using a default preset\n"
		);
	
	//main spotdl arguments
		

//interactive mode
	if(argc== 1)
	{
        std::cout<< "select tool: ytdlp(1)";
        std::string tool;
        std::getline(std::cin, tool);

		if(tool== "1")
		{
            std::cout<< "youtube playlist link: \n";
            std::getline(std::cin, youtubeLink);
            std::cout<< "root playlist path: \n";
            std::getline(std::cin, rootPlaylistPath);
            std::cout<< "archive file path: \n";
            std::getline(std::cin, archiveFile);
			std::cout<< "the file name of the browser you're using e.g \"/usr/bin/->firefox<-\": \n";
			std::getline(std::cin, browser);

			std::cout<<"remember to open your browser with youtube open, preferably with your account logged in!\npress enter when you're done\n";
			
			std::string dump;
			std::getline(std::cin, dump);

			verboseYtdlpLogic
			(	
				rootPlaylistPath,
				youtubeLink,
				archiveFile,
				browser,
				true
			);
        }
		else
		{
			std::cout<<"tool not specified.";	
		}
		return 0;
    }
//CLI mode
	CLI11_PARSE(dmeh, argc, argv);
	dmeh.require_subcommand(1);
	if(ytdlp->parsed())
	{
        std::cout<< "running dmeh:\n"
                 << "  link:         "<< youtubeLink<<"\n"
                 << "  root path:    "<< rootPlaylistPath<<"\n"
                 << "  archive path: "<< archiveFile<<"\n";
		
		if(verbose==true)
		{
			verboseYtdlpLogic(
				
				rootPlaylistPath,
				youtubeLink,
				archiveFile,
				browser,
				cookies
			);
		}
    }
	// else if(spotifydlp->parsed())
	// {
    // 	TODO:
    // }

	return 0;
}
