You can follow ScummGEN's advancement on this page.


---


## November 13, 2009 ##

Eight months since the last update ! Wow, time flies too quickly... Anyway, here is an update concerning what happened to the project for the past three seasons.

First of all, there hasn't been a lot of progress concerning editors. This is for me not as interesting as the rest of the project, and I keep postponing this task. Also, it is not very hard to manually edit XML files and add BMP files to the game folder hierarchy, which is why this part of ScummGEN is not as important in my opinion. I have modified the build system to allow the use of editors though, and made some heavy code changes in order to be able to load and save a whole game to disk.

The compiler has been improved a lot. I added a few new statements (enums, do/while loops) and new declaration types (actors, verbs, classes). Some other bugs were fixed making the compiler in a perfectly usable state.

The room palettes can now be optimized if certain objects use already existing colors. This functionality is critical as SCUMM v6 is limited to 256 colors.

The greatest addition to the project is probably "libscumm", a set of functions allowing scripts to call SCUMM opcodes at a higher level. Previously, if one wanted to use SCUMM opcodes, including asm statements in scripts was needed. Now, it is easy to do anything SCUMM-specific from scripts. For instance, Room\_load(_roomName_) will load a new room - pretty straightforward isn't it ?

A greater list of bugs have been fixed, but no need to enter into details here. I have been busy working on my own game using ScummGEN, making it easy to spot those and fix them. If you have questions or comments about the project, don't hesitate to shoot me an email !

## March 23, 2009 ##

Happy new year to everyone ! Yes, I'm a bit late, sorry about that. These past months have seen a lot of improvements for the project.

I improved the compiler quite a bit to allow the use of lists. This is a feature that I really wanted to add some time ago but never really found the time to develop. Strings were already working but adding a lot of those would eat memory in ScummVM - this is now fixed. Increment and decrement operators can now be used in scripts which makes for loops more C-like. Lastly, "verb" statements were added to the compiler, which is essential to the usage of object scripts.

Concerning the SCUMM blocks, RLE compression was added to the costumes generation. I also solved a bug in CHAR blocks which now allows users to properly change font colors through scripts.

Finally, a lot of work was done concerning the build system. I changed almost all the classes to allow them to be created and deleted at any point in time. Before, the application would start and create all the game types by loading XML files, BMP files, WAV files etc. Now when game types are created, they are empty - the purpose of this is to allow editors to create new objects, rooms or costumes, and build the whole game whenever the user clicks on a "build button".

I could continue working on small things concerning the generated blocks, but I think that it's now time to start working on editors. The choice made for the project is to go with GTK+, a library which can be used in Windows, Linux and MacOSX. Expect to see some progress on this soon !

## December 30, 2008 ##

Alright, I thought I would try to add news at least once a month, I didn't have much time left ;) If you've been following the SVN status, you've seen that a lot of progress has been made since the last entry to this page. I'll try to describe what I've done, what I've understood, and what I'm planning to work on.

Last time I posted here, I could display an actor in a room, but this actor couldn't really walk in it. This month I implemented an A`*` algorithm to precalculate all the paths between the boxes actors can walk in and store it in a BOXM block need by SCUMM - this means actors now can actually walk in a predefined map.

Talking about actors, I changed the way costumes are parsed and it will be a lot easier for me to create an appropriate editor. I now find it easy to change animations from scripts, meaning that it should be a breeze to do it for you ;)

I also worked on generating palettes in an efficient way. When adding a global costume or object for a game, you won't need to manually edit all the room background palettes to be able to display those correctly as this is now done automatically.

The compiler has also been improved as I added for loops, inline functions, and a few operators like different kinds of incrementation. Room names, costume names, object names and many more can also be used directly inside scripts instead of just using their corresponding ID - this means that you'll be able to load rooms by simply using a function like Room\_load(myRoom) instead of Room\_load(4) for example. This obviously makes things easier :)

Games without music are not really fun. This month I worked on adding MIDI music to the resources - it works fine, but the format of the MIDI files have to be very specific (it's called MIDI format 2) and this format is not used a lot by sequencers. Zaarin (from mixnmojo) is helping me to create a small converter for translating MIDI format 1 into MIDI format 2. This means that common MIDI files will be able to be played in your games.

Last but not least, I added autotools for the project. This is a commonly used build system and even though it's not SCUMM related at all, it's worth talking about as this will allow the project to be compiled easily for different platforms, such as Windows.

Okay, I'm sure I forgot a few things, but that's it for today... I could talk about fonts which are now saved correcly into resource files, and that even though I can display text, I still have problems changing the text color. More on this later !

## November 24, 2008 ##

This is the first entry to the status page. I just updated the SVN today with all the work I did during the last four months. I didn't want to update it before as I was constantly changing the folder hierarchy and reorganizing the project architecture.

Even though the SVN doesn't contain any example yet (which means it's hard to try to run the project and have valid resource files generated), it's still interesting to mention the new grammar subfolder which contains a work-in-progress ScummGEN script compiler. A lot of ideas have been taken from ScummC, even though there are a few important differences worth noticing - I'll make a wiki page on this later.

As far as the features are concerned, I seriously started playing with SCUMM - using the compiler you can display characters, draw text, play sounds from the MONSTER.SOU file, have fun with palette cycling, interact with the game using your mouse and keyboard, and a lot of other stuff I forgot. The raw SCUMM opcodes are not always easy to understand which is why I'm creating, along with the compiler, an application programming interface (using ScummGEN's language) which will have clear function names so that people will easily be able to code something without looking at weird documentation all the time ;)