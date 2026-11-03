# ============================================================================
# PURPOSE:
# This script reads RSS feeds (URLs) from the "RSS_FEED" environment variable.
# It parses the XML content, searches for a specific phrase (given as a command-line argument),
# and prints the titles of matching news articles.
#
# WHAT IT TEACHES:
# 1. urllib.request: Fetching data from the web.
# 2. os.environ: Reading environment variables passed from the C program.
# 3. minidom: Parsing XML data.
# 4. re (Regular Expressions): Searching for text patterns.
# ============================================================================

import urllib.request  # Python 3 module for opening URLs
import os              # Module to interact with the operating system (read environment variables)
import re              # Module for regular expressions (searching text)
import sys             # Module to access command-line arguments and exit
import getopt          # Module to parse command-line options
from xml.dom import minidom # Module to parse XML documents

# Function to print usage instructions
def usage():
    print("Usage:\npython rssgossip.py [-uh] <search-regexp>")

# 1. Parse command-line options.
# "uh" means -u and -h are valid flags. ["urls", "help"] are long versions.
try:
    opts, args = getopt.getopt(sys.argv[1:], "uh", ["urls", "help"])
except getopt.GetoptError as err:
    print(str(err))  # Print error message if invalid option
    usage()
    sys.exit(2)      # Exit the program with an error code

include_urls = False
# 2. Loop through the parsed options.
for o, a in opts:
    if o == "-u":
        include_urls = True  # If -u is passed, we will also print the article URL
    elif o in ("-h", "--help"):
        usage()              # If -h is passed, show usage and exit
        sys.exit()
    else:
        assert False, "unhandled option"

# 3. Ensure a search phrase was provided.
if len(args) == 0:
    usage()
    sys.exit(1)

# 4. Compile the search phrase into a regular expression.
# re.IGNORECASE makes the search case-insensitive.
searcher = re.compile(args[0], re.IGNORECASE)

# 5. Get the RSS feed URLs from the environment variable.
# os.environ['RSS_FEED'] gets the value. .split() separates multiple URLs by spaces.
for url in os.environ['RSS_FEED'].split():
    try:
        # 6. Fetch the URL content.
        feed = urllib.request.urlopen(url)
        
        # 7. Parse the XML content.
        dom = minidom.parse(feed)
        
        # 8. Find all <title> tags in the XML.
        for node in dom.getElementsByTagName('title'):
            # Get the text inside the title tag.
            txt = node.firstChild.wholeText
            
            # 9. Check if the search phrase exists in the title.
            if searcher.search(txt):
                # Print the matching title.
                print(txt)
                
                # If -u flag was passed, print the link as well.
                if include_urls:
                    p = node.parentNode
                    link = p.getElementsByTagName('link')[0].firstChild.wholeText
                    print("\t%s" % link)
                    
    except Exception as e:
        # Print an error message if the URL cannot be fetched or parsed.
        print(f"Error fetching {url}: {e}")
        sys.exit(1)
