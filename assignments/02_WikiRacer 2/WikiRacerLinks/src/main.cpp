#include <iostream>
#include <fstream>
#include <unordered_set>
#include <set>
#include <sstream>

using std::cout;            using std::endl;
using std::string;          using std::unordered_set;

/*
 * Note that you have to pass in the file as a single string
 * into the findWikiLinks function!
 * So we have to turn the passed-in file into a single string...
 * does that sound familiar at all?
 */
unordered_set<string> findWikiLinks(const string& page_html) {
    // TODO: delete this return statement and implement the
    //       function!
    unordered_set<string> wikiLinks;
    string startPattern = "<a href=\"/wiki/";
    char endPattern = '\"';
    auto iter1 = page_html.begin(); auto iter2 = page_html.end();
    while (iter1 != iter2) {
        iter1 = std::search(iter1, iter2, startPattern.begin(), startPattern.end());
        if (iter1 == iter2) break;
        auto end = std::find(iter1 + startPattern.length(), iter2, endPattern);
        string page_name = string(iter1 + startPattern.length(), end);
        if (std::all_of(page_name.begin(), page_name.end(), [](char character) {return (character != '#' && character != ':');})) {
            wikiLinks.insert(string(iter1 + startPattern.length(), end));
        }
        iter1 = end + 1;
    }
    return wikiLinks;
}

int main() {
    /* Note if your file reading isn't working, please go to the
     * projects tab on the panel on the left, and in the run section,
     * uncheck the "Run in terminal" box and re-check it. This
     * should fix things.
     */

    cout << "Enter a file name: ";
    string filename;
    getline(std::cin, filename);
    string page_html;

    // TODO: Create a filestream from the filename, and convert it into
    //       a single string of data called page_html (declared above)

    // Write code here
    std::ifstream file(filename, std::ifstream::in);
    if (!file.is_open()) {
        std::cerr << "failed to open file!" << endl;
        return 1;
    }
    std::stringstream s;
    s << file.rdbuf();
    page_html = s.str();
    // cout << page_html;

    unordered_set<string> validLinks = findWikiLinks(page_html);

    // TODO: Print out the validLinks set above.
    //       You can print it out in any format; this is just for you
    //       to be able to compare your results with the [output] results
    //       under the /res folder.

    // Write code here
    // for (string link : validLinks) {
    //     cout << link << endl;
    // }
    std::set<string> result;
    for (string link : validLinks) {
        result.insert(link);
    }
    for (string link : result) {
        cout << link << endl;
    }

    return 0;
}
