#ifndef EDITOR_H
#define EDITOR_H
#include "nlohmann/json.hpp"
#include<cstdlib>
#include<unistd.h>
#include<string>
#include<iostream>
namespace mann = nlohmann;

class Editor
{
private:
	std::string _name;
	inline void _system(const char* command)
	{
		/*Why not std::system(char*) ?Reasons:
		 *The std::system would create a new child thread
		 *to run my command.But it is unuseful.So I write 
		 *a stupid _system(char*) to repalace
		 *TODO:But in this case it might not be cross-platform.
		 *TODO:Can it be morer clever?
		 */
		execl("/bin/sh","sh","-c",command,NULL);
	}
public:
	Editor(std::string nn): _name(nn){}
	Editor(): _name("vim"){}
	~Editor() = default;

	inline int open(std::string openFile,
			std::string mode) 
	{
		std::string command{_name + ' ' + mode + ' ' + openFile};
		_system(command.c_str());
	}
	inline int open(mann::json::iterator fileBegin,
			mann::json::iterator fileEnd,
			std::string mode)
	{
		std::string command{_name + ' ' + mode};
		for(auto iter = fileBegin;iter != fileEnd;iter++)
			command += ' ' + (std::string)*iter;
		_system(command.c_str());
	}
	/*TODO:int open(std::string openfile,
	  	enum Kind mode) const;*/
	
	inline void load(std::string name)
	{_name = name;}

	inline std::string editorName()
	{return _name;}
};

#endif
