
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

#include <sys/types.h>

#include <SDL/SDL_config.h>
#include <SDL/SDL.h>
#include <SDL/SDL_audio.h>

#include <libcsid.h>

void sdl_callback(void* userdata, unsigned char *stream, int bytes) {
  libcsid_render((unsigned short *)stream, bytes / 2);
}

int main (int argc, char *argv[])
{
  int samplerate = DEFAULT_SAMPLERATE;
  int subtune = 0;
  int sidmodel = 0;
  int tunelength = -1;
  unsigned char filedata[MAX_DATA_LEN] = {0, };

  // open and process the file
  if (argc < 2) {
    printf("\nUsage: csid <filename.sid> [subtune_number [SID_modelnumber [seconds]]]\n\n");
    return 1;
  }

  if (argc >= 3) {
    sscanf(argv[2], "%d", &subtune);
    subtune --;
    if (subtune < 0 || subtune > 63) {
      subtune = 0;
    }
  }

  if (argc >= 4) {
    sscanf(argv[3], "%d", &sidmodel);
    if (sidmodel != SIDMODEL_6581 && sidmodel != SIDMODEL_8580) {
      sidmodel = DEFAULT_SIDMODEL;
    }
  } else {
    sidmodel = DEFAULT_SIDMODEL;
  }

  if (argc >= 5) {
    sscanf(argv[4], "%d", &tunelength);
  }

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {
    fprintf(stderr, "Couldn't initialize SDL: %s\n", SDL_GetError());
    return 1;
  }

  SDL_AudioSpec soundspec = {0, };
  soundspec.freq = samplerate;
  soundspec.channels = 1;
  soundspec.format = AUDIO_S16;
  soundspec.samples = 32768;
  soundspec.userdata = NULL;
  soundspec.callback = sdl_callback;
  if (SDL_OpenAudio(&soundspec, NULL) < 0) {
    fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
    return 2;
  }

  libcsid_init(samplerate, sidmodel);

  FILE *f = fopen(argv[1], "rb");
  if (f == NULL) {
    fprintf(stderr, "File not found.\n");
    return 1;
  }

  fseek(f, 0, SEEK_END);
  int datalen = ftell(f);
  fseek(f, 0, SEEK_SET);
  fread(filedata, 1, datalen, f);
  printf("\n%d bytes read (%s subtune %d)", datalen, argv[1], subtune + 1);
  fclose(f);

  libcsid_load(filedata, datalen, subtune);

  printf("\nTitle: %s    ", libcsid_gettitle());
  printf("Author: %s    ", libcsid_getauthor());
  printf("Info: %s", libcsid_getinfo());

  SDL_PauseAudio(0);

  fflush(stdin);
  if (tunelength != -1) {
    sleep(tunelength);
  } else {
    printf("Press Enter to abort playback...\n");
    getchar();
  }

  SDL_PauseAudio(1);
  SDL_CloseAudio();
  return 0;
}

