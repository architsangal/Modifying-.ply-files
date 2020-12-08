#ifndef FILEHANDLER_H
#define FILEHANDLER_H

class FileHandler
{
	public:
		FileHandler();
		virtual ~FileHandler();
		virtual void read() = 0;
		virtual void write() = 0;
		virtual void modify() = 0;
};

#endif