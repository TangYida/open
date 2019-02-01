#include "nlohmann/json.hpp"
#include "Editor.hpp"
#include "error.hpp"
#include<iostream>
#include<fstream>
#include<string>

namespace mann = nlohmann;

int main(int argc,char** argv)
{

	/*choose Opening vim version*/
	Editor editor;
	if(argc > 1)
		editor.load(argv[0]);

	/*init file writing ofstream*/
	std::ifstream fin;
	fin.open("Openfile.json");
	if(!fin.is_open()) {
		msgErr("Cannot open Openfile.json.");
		return 1;
	}

	/*Load Openfile.json*/
	mann::json text;
	fin >> text;

	/*Do it*/
	editor.open(text["source-file-list"].begin(),
			text["source-file-list"].end(),"-O");
	return 0;
}
