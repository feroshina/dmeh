/*io*/
#include<iostream>

/*string management*/
#include<string_view>

void help(char* argument[])
{
    if(std::string_view(argument[1]) == "-h" || std::string_view(argument[1]) == "--help")
    {
        std::cout<<
        R"(
Usage: ymeh [playlist_link] [root_file_path] [archive_file]

Arguments:
playlist_link    the URL of the youtube playlist
root_file_path   the directory where playlist folders will be created
archive_file     the text file path used to log downloaded videos (prevents redownloads)

Example (Command line):
"https://youtube.com..." "/home/user/Music" "archive.txt"

Interactive mode:
simply run ymeh without arguments to be prompted step-by-step.
        )";
    }
}

int main(int argc, char* argv[])
{
    bool runDirectly=false;
    
    char* link=       argv[1];
    char* filePath=   argv[2];
    char* archiveFile=argv[3];

    /*argument 1 case*/
    help(argv);

    if(argc==1){runDirectly=true;}

    //TODO: 
}
