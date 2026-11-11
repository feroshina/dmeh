#!/usr/bin/bash

if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    echo "Usage: $0 [playlist_link] [root_file_path] [archive_file]"
    echo ""
    echo "Arguments:"
    echo "  playlist_link    the URL of the youtube playlist"
    echo "  root_file_path   the directory where playlist folders will be created"
    echo "  archive_file     the text file path used to log downloaded videos (prevents redownloads)"
    echo ""
    echo "Example (Command line):"
    echo "  $0 \"https://youtube.com...\" \"/home/user/Music\" \"archive.txt\""
    echo ""
    echo "Interactive mode:"
    echo "  Simply run '$0' without arguments to be prompted step-by-step."
    exit 0
fi

RUN_DIRECTLY=false

LINK="${1:-}"
FILE_PATH="${2:-}"
ARCHIVE_FILE="${3:-}"

if [[ -n "$LINK" && -n "$FILE_PATH" && -n "$ARCHIVE_FILE" ]]; then
    RUN_DIRECTLY=true
else
    if [[ -z "$LINK" ]]; then
        echo "youtube playlist link?: "
        read LINK
    fi
    if [[ -z "$FILE_PATH" ]]; then
        echo "root file path for all playlists?: "
        read FILE_PATH
    fi
    if [[ -z "$ARCHIVE_FILE" ]]; then
        echo "archive file name/path?: "
        read ARCHIVE_FILE
    fi
fi

EXECUTE=false

if [ "$RUN_DIRECTLY" = true ]; then
    EXECUTE=true
else
    echo " "
    echo "YT link: $LINK"
    echo "Archive file: $ARCHIVE_FILE"
    echo "Base File path: $FILE_PATH"
    echo "Is that correct?(y/N): "
    read CONFIRMATION
    if [[ "$CONFIRMATION" == "y" || "$CONFIRMATION" == "Y" ]]; then
        EXECUTE=true
    fi
fi

if [ "$EXECUTE" = true ]; then
    yt-dlp --extractor-args youtubetab:skip=authcheck --yes-playlist --embed-thumbnail --embed-metadata \
    --cookies-from-browser firefox -N 4 -i --geo-bypass --retry 10 \
    -x --audio-format mp3 --ignore-errors -f bestaudio \
    --paths "$FILE_PATH" \
    -o "%(playlist)s/%(title)s.%(ext)s - %(id)s" \
    "$LINK" --download-archive "$ARCHIVE_FILE"
fi
