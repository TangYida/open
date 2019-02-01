#ifndef ERROR_H
#define ERROR_H

inline void msgErr(char* msg)
{
	std::cerr << "***ERROR***: "
		<< msg << "\n";
}

#endif
