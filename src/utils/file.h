#if !defined(FILE_H)
#define FILE_H

long read_from_file(const char* path, char** buff);
int get_file_dir(const char* path, char** buff);

#endif // FILE_H
