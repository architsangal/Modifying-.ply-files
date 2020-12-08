#ifndef FILEHANDLER_H
#define FILEHANDLER_H

// this is the base files made by the leader of the group and some changes by other members
class FileHandler
{
	protected:
		FileHandler();
		virtual ~FileHandler();
		virtual void read() = 0;
		virtual void write() = 0;
		virtual void modify() = 0;
};

#endif