#include "Editor.hpp"
#include "error.hpp"
#include "nlohmann/json.hpp"
#include<iostream>
#include<fstream>
#include<unistd.h>

/*NEW command's usage:
 *> new [newfilename]
 */

namespace mann = nlohmann;

inline bool exits(const char* filename)
{
	/*stupid C++ STDlib*/
	/*Ans finally I decided to use POSIX*/
	return (access(filename,F_OK) == 0);
}

/*I want this function:
 *You can create a file,and write a Makefile target
 *along with it.That will be convenient.
 */

int main(int argc,char **argv)
{
	std::string file,comment;
	std::fstream fio;
	mann::json text;

	/*Load new file name*/
	if(argc == 1 || argc > 2) {
		std::cout << "Enter your new file name:";
		std::cin >> file;
	} else
		file = argv[1];
	if(exits(file.c_str())) {
		msgErr("Your file has already created.");
		return 1;
	}

	/*TODO:file writing and reading is so much,how to
	 *deal with fio.bad() and fio.fail()?
	 */

	/*check if Openfile.json exits*/
	if(!exits("Openfile.json")) {
		fio.open("Openfile.json",std::fstream::out);
		fio << "{\"source-file-list\":[]}";
		fio.close();
	}

	/*change Openfile.json*/
	fio.open("Openfile.json",std::fstream::in);
	fio >> text;
	text["source-file-list"].push_back(file);
	fio.close();

	/*write to Openfile.json*/
	fio.open("Openfile.json",std::fstream::out);
	fio << text.dump(4);
	fio.close();

	/*create file*/
	fio.open(file,std::fstream::out);
	fio << "";
	fio.close();

	return 0;
}
