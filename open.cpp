#include"nlohmann/json.hpp"
#include<iostream>
#include<fstream>
#include<cstdlib>
#include<string>
#include<vector>
#include<map>

namespace mann = nlohmann;

class Editor
{
private:
	const std::string _name;
public:
	Editor(std::string nn): _name(nn){}
	~Editor() = default;

	inline int open(std::string openFile,
			std::string mode) const
	{
		std::string command{_name + ' ' + mode + ' ' + openFile};
		return system(command.c_str());
	}
	/*TODO:int open(std::string openfile,
	  	enum Kind mode) const;*/
};

int main(int argc,char** argv)
{

	/*choose Opening vim version*/
	const Editor editor (
		"gvim"
	);

	/*init file writing ofstream*/
	std::ifstream fin;
	if(argc > 1)
		fin.open(argv[0]);
	else
		fin.open("Openfile.json");
	if(!fin.is_open()) {
		std::cerr << "***ERROR***: Cannot open Openfile.json.\n";
		exit(1);
	}

	/*Load Openfile.json*/
	mann::json text;
	fin >> text;

	/*do it*/
	for(auto srcFile : text["source-file-list"])
		if(editor.open(srcFile,"--remote-silent -c :vsp"))
			std::cerr << "***ERROR***: Cannot open source file"
				<< srcFile << "\n";
	for(auto hdrFile: text["header-file-list"])
		if(editor.open(hdrFile,"--remote-silent -c :vsp"))
			std::cerr << "***ERROR***: Cannot open header file"
				<< hdrFile << "\n";
	return 0;
}
