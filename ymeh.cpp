/*CLI management*/
#include<CLI11.hpp>

/*io*/
#include<iostream>
#include<cstdlib>

/*string management*/
#include<string>

void ytdlpLogic(std::string rootPlaylistPath, std:string youtubeLink, std::string archiveFile, std::string browser, bool cookies)
{
	if(cookies==true)
	{
		system(

			"yt-dlp --extractor-args youtubetab:skip=authcheck --yes-playlist --embed-thumbnail --embed-metadata --cookies-from-browser "+browser+" -N 4 -i --geo-bypass --retry 10	-x --audio-format mp3 --ignore-errors -f bestaudio --paths "+rootPlaylistPath+"	-o '%(playlist)s/%(title)s.%(ext)s - %(id)s' "+youtubeLink+" --download-archive "+archiveFile
		);
	}
	else if(cookies==false && browser.empty())
	{
		system(

			"yt-dlp --extractor-args youtubetab:skip=authcheck --yes-playlist --embed-thumbnail --embed-metadata -N 4 -i --geo-bypass --retry 10 -x --audio-format mp3 --ignore-errors -f bestaudio --paths "+rootPlaylistPath+" -o '%(playlist)s/%(title)s.%(ext)s - %(id)s' "+youtubeLink+" --download-archive "+archiveFile
		);
	}
	else if(cookies==true && browser.empty())
	{
		system(

			"yt-dlp --extractor-args youtubetab:skip=authcheck --yes-playlist --embed-thumbnail --embed-metadata --cookies-from-browser firefox -N 4 -i --geo-bypass --retry 10	-x --audio-format mp3 --ignore-errors -f bestaudio --paths "+rootPlaylistPath+"	-o '%(playlist)s/%(title)s.%(ext)s - %(id)s' "+youtubeLink+" --download-archive "+archiveFile
		);
	}
}

int main(int argc, char** argv)
{
//CLI parser declarations
	CLI::App dmeh("general media handler", argv[0]);

	CLI::App* ytdlp= dmeh.add_subcommand("ytdlp","using ytdlp as downloader");
	ytdlp->get_formatter()->label("Positionals","Arguments");
	
	//main ytdlp arguments
		std::string browser
		ytdlp->add_option("-b, --browser, browser",browser,"the URL of the youtube playlist");

		std::string youtubeLink;
		ytdlp->add_option("-l, --link, youtube_link",youtubeLink,"the URL of the youtube playlist")->required();

		std::string rootPlaylistPath;
		ytdlp->add_option("-rp, --rootpath, root_playlist_path",rootPlaylistPath,"the directory where the playlists will be downloaded")->required();

		std::string archiveFile;
		ytdlp->add_option("-af, --archivefile, archive_file",archiveFile,"where the video IDs will be stored to not repeat downloads")->required();

		ytdlp->footer(
			"Example (Command line):\n
			dmeh \"chromium\" \"https://youtube.com...\" \"/home/user/Music\" \"archive.txt\"\n
			Interactive mode:\n
			simply run dmeh without arguments to be prompted with a standard walkthrough, using a default preset \n"
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
            std::cout<< "youtube playlist link: ";
            std::getline(std::cin, youtubeLink);
            std::cout<< "root playlist path: ";
            std::getline(std::cin, rootPlaylistPath);
            std::cout<< "archive file path: ";
            std::getline(std::cin, archiveFile);
			std::cout<< "the name of the browser you're using: ";
			std::getline(std::cin, browser);


			//TODO: ytdlp logic here
			ytdlpLogic(
				
				rootPlaylistPath,
				youtubeLink,
				archiveFile,
				browser,
				true
			);
        }
        return 0;
    }

	if(ytdlp->parsed())
	{
        std::cout<< "Running Playlist Tool:\n"
                 << "  Link:    "<< youtubeLink<<"\n"
                 << "  Root:    "<< rootPlaylistPath<<"\n"
                 << "  Archive: "<< archiveFile<<"\n";
    }
	/*
	else if(spotifycli->parsed())
	{
    	TODO:
    }
	*/
	
	return 0;
}
