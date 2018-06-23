#!/usr/bin/env fontforge
# Quick and dirty hack: converts a font to truetype (.ttf)
# Originally found at http://www.stuermer.ch/blog/convert-otf-to-ttf-font-on-ubuntu.html , with minor modifications made
Print("Opening "+$1);
Open($1);
Print("Saving "+$1:r+".ttf");
Generate($1:r+".ttf");
Quit(0); 
