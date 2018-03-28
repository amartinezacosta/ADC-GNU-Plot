#include "serial.h"

HANDLE comm;

int SerialOpen(char *Port, int BaudRate)
{
   comm = CreateFile(Port,
                     GENERIC_READ|GENERIC_WRITE,
                     0,
                     0,
                     OPEN_EXISTING,
                     0,
                     0);

   if(comm == INVALID_HANDLE_VALUE)
   {
      return 0;
   }

   DCB params = {0};
   params.DCBlength = sizeof(params);

   params.BaudRate = BaudRate;
   params.ByteSize = 8;
   params.StopBits = ONESTOPBIT;
   params.Parity = NOPARITY;

   SetCommState(comm, &params);

   return 1;
}

int SerialWrite(char *Data, int Size)
{
   int written = 0;

   WriteFile(comm, Data, Size, &written, NULL);

   return written;
}

int SerialRead(char *Data, int Size)
{
   int read = 0;

   ReadFile(comm, Data, Size, &read, NULL);

   return read;
}
