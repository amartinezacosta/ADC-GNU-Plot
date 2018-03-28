#include <windows.h>

int SerialOpen(char *Port, int BaudRate);
int SerialWrite(char *Data, int Size);
int SerialRead(char *Data, int Size);
