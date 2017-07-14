                                 cSID by Hermit
                                ================


 I never planned to create a SID-player for commandline, but I ended up so. :)
cSID is a cross-platform commandline SID-player based on the code of my other
project called jsSID. Some people asked at CSDB if I could make a C/C++ port
to run on native machine, and DefleMask guys started to port jsSID to C++, and
got involved by helping them, actually finishing the work as I know this
engine the best as the original author. This was last year, and beside other 
projects, I ported the CPU emulation and player engine as well to C. Some guys
also asked for a shared library (.dll/.so) that they can use in their non-GPL
licensed or closed-source programs. I haven't made a shared library yet but
it wouldn't be hard to make one from this C code if someone wants. Actually
this program is nothing more than CPU and a SID functions that are periodically
called by the audio-callback. I used SDL-1.2 audio routines for this task now.
That means you can easily compile cSID on platforms other than Linux if you
want...

Usage is simple, you can get a clue about required commandline parameters if
you run 'csid' without any. If you write irrelevant values for a SID they get
ignored. (E.g. subtune-number larger than present in .sid file).
You can type 0 in the place of SID model if you don't want to explicitly set
it but want to tell the playtime to cSID. Otherwise, type 8580 or 6581, and
it will have precedence over the SID-models originally asked by the .sid file.
If you want to play the tune infinitely, don't give playtime and it will play
till you press Enter. 
 As you can give the playtime in seconds, you can play more SID files from a
simple bash/batch script after each other, or you can use cSID as a backend for
a GUI program you develop... (This is the gnu/unix idea of apps I guess...)
 When a tune plays you can see some important information about played .sid.

Some 'extra' features:
-2SID and 3SID tunes are playable (in mono)
-Illegal opcodes are now fully supported (except nonsense NOP variants and JAM)
-22x oversampling at 44.1kHz, more at more (actually sound engine runs at 1MHz)

Proper cycle-based CIA and VIC IRQ emulation is still not implemented, but got
mimiced in a way that most of the SID files can be played, expect digi-tunes,
where more complex CIA routines are used. So the SID() function doesn't contain
digi-playback related code either. Maybe in later versions if there will be any.

So don't expect a full SID-playback environment from cSID, but think of it as
a high-quality sounding but really small (26kbyte) standalone player, which can
run without dependencies (except SDL_sound). Who knows, it might be your only
option sometimes, when you don't have GUI and bloatware on your system.

      2017 Hermit Software (Mihaly Horvath) - http://hermit.sidrip.com
