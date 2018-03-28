#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>
#include "serial.h"

#define SAMPLE_POINTS 500

int main(int argc, char const *argv[]) {
   FILE *plot = fopen("plot.dat", "w");
   FILE *gnuplot = _popen("gnuplot -persist", "w");

   if(argc < 2)
   {
      printf("Usage: [Port Number]");
      return 0;
   }

   const char *Port = argv[1];

   if(!SerialOpen(Port, CBR_115200))
   {
      printf("Failed to Open Port\n");
      return 0;
   }

   uint16_t ADC_Data[SAMPLE_POINTS];
   int index = 0;
   fprintf(gnuplot, "set xrange [0:500]\n");
   fprintf(gnuplot, "set yrange [0:16384]\n");

   while(1)
   {
      SerialRead((char*)&ADC_Data[index], 2);
      printf("%i\r\n", ADC_Data[index]);
      index = (index + 1) % SAMPLE_POINTS;
      fprintf(gnuplot, "plot '-'\n");
      for(int i = 0; i < index; i++)
      {
         fprintf(gnuplot, "%i %i\r\n", index, ADC_Data[i]);
      }
      fprintf(gnuplot, "e\n");
      fflush(gnuplot);
   }

   fclose(gnuplot);

   return 1;
}
