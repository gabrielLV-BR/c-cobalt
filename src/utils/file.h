#if !defined(FILE_H)
#define FILE_H

//TODO maybe change this for other OSes
#define NEW_LINE "\n"

long read_from_file(const char* path, char** buff);
int get_file_dir(const char* path, char** buff);

#endif // FILE_H
