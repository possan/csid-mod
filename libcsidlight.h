#ifndef _CSID_H_
#define _CSID_H_

#define MAX_DATA_LEN 65536

#define SIDMODEL_8580 8580
#define SIDMODEL_6581 6581

#define DEFAULT_SAMPLERATE 44100
#define DEFAULT_SIDMODEL SIDMODEL_6581

extern void libcsidlight_init(int samplerate, int sidmodel);

extern int libcsidlight_load(unsigned char *buffer, int bufferlen, int subtune);

extern const char *libcsidlight_getauthor();
extern const char *libcsidlight_getinfo();
extern const char *libcsidlight_gettitle();

extern void libcsidlight_render(unsigned short *output, int numsamples);

#endif