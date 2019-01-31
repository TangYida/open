#include "Editor.hpp"
#include "nlohmann/json.hpp"
#include<iostream>
#include<fstream>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

/*NEW command's usage:
 *>new [newfilename]\n
 */

namespace mann = nlohmann;

int main(int argc,char **argv)
{
	std::string file;

	/*Load new file name*/
	if(argc == 1) {
		std::cout << "Enter your new file name:";
		std::cin >> file;
	} else
		file = argv[0];

	mann::json text;

	/*Read and change*/
	std::ifstream fin("Openfile.json");
	fin >> text;
	text["source-file-list"].push_back(file);

	/*write*/
	std::ofstream fout("Openfile.json");
	fout << text.dump(8);

	/*create*/
	constexpr int FLAGS = O_CREAT | O_EXCL,
		MODE = S_IRWXU;
	if(open(file.c_str(),FLAGS,MODE) == -1) {
		std::cerr << "***ERROR***: Create file error.\n";
		return 1;
	}

	return 0;
}
