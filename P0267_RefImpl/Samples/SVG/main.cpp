#include <iostream>
#include <fstream>
#include <io2d.h>
#include "svg.h"
#include "window.h"

using namespace std;
using namespace std::experimental;
using namespace std::experimental::io2d;

static bool RunCLI( const string &path_in, const string &path_out ) {
    ifstream file(path_in);
    if( !file.is_open() ) {
        cerr << "Failed to input an input file." << endl;
        return false;
    }
    
    auto str = string{ istreambuf_iterator<char>(file), istreambuf_iterator<char>() };
    
    try {
        if( auto image = RenderSVG(str) )
            image->save(path_out, image_file_format::png);
        else {
            cerr << "Failed to render SVG." << endl;
            return false;
        }
    }
    catch (exception const & e) {
        cerr << "Error loading SVG: " << e.what() << endl;
        return false;
    }
    return true;
}

int main(int argc, char **argv) {
    if( argc < 2 ) {
        cout << "Usage: svg input_file.svg [output_file.png]" << endl;
        return 0;
    }
    
    string path_in = argv[1];
    if( argc == 3 ) {
        string path_out = argv[2];
        return RunCLI(path_in, path_out) ? 0 : 1;
    }
    else {
        RunWindowed(path_in);
        return 0;
    }
}
