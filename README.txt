

This is ZiiWakeBreaker, a port by Jay Vaughan of w1xer.at, of the
excellent OpenGL ES 1.x compatible demo project "WakeBreaker", by 
Peter Angstadt.

This project is being released to the Plaszma Developer Community
in order to stimulate further 3d-based development that really
puts Plaszma and Zii- devices to interesting use.  This project
contains a complete game engine which uses the Plaszma hardware, 
and can function as a test bed for those exploring Plaszma.

Essentially this project consists of 2 major code-bases and a little
glue/hack code as well.

In the wakebreaker/ subdirectory you will find the classes for the
WakeBreaker project, which are well-written and quite self-explanator,
using mostly basic OpenGL ES 1.x calls to render a full 3D world
and game engine, including textures and modesl, and in this 
ZiiWakeBreaker workspace, which is set up for plasmasdk-0.92.02, 
you will find the Plaszma-based support code, which handles all of 
the setup and application-specific messages related to integration 
with Plaszma.

To use this codebase, you must first add it to your Plaszma workspace
in Eclipse, and then run the prebuild.sh script to generate the
build.arm directory appropriately configured for your Plaszma build
environment.  DON'T FORGET TO SET THE APPHOME VARIABLE TO YOUR
CHOSEN LOCATION FOR THIS WORKSPACE!

Some interesting things to take note of with regards to this project:

** The original wakebreaker sources are almost pristine
** Use of the Plaszma hardware API to gain touch and Accelerator
information for user feedback is supported. (BUT: Accel handler
is currently a bit borked, will be fixed in the next release)
** An additional overlay "HUD" was added to the game, using the
Plaszma window classes, to put up the control surface.  This
HUD was generated using a set of tools in HUDCairoGenerator,
which has its own documentation.


TODO:
	** Fix acceleration
	** Add sound
	** Handle screen rotation and resize
	** Streamline the HUDCairoGenerator toolkit so that its
	a bit more useful and better optimized
	** Make the game a little more interesting (?? perhaps not ??)

	
CONTACT:

Plaszma Port-related issues:
	Jay Vaughan (ibisum@gmail.com) - torpor on the ZiiLabs Dev Forum
	
"Wakebreaker - The Game" issues:	
	Peter Angstadt - see wakebreaker/ sources for details
	