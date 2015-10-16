The following explains the design of ScummGEN.
The project can be seen as two main parts : the editors and the resource files assembler.


---


# Editors #

## Description ##

Currently, no editor has been made. In the future, ScummGEN will have a set of editors which will allow the user to create fully working SCUMM v6 games. Their role will be to easily create game contents and export them to a folder which will then be fed into the assembler described later.

## Folder hierarchy ##

Here is shown how the game folder (which might turn into some tar-like file in the future) created by the set of editors is organized. Words in bold represent folders, and parts in italics mean that they are in fact substituted with names specified through the editors.

  * **_game_**
    * game.xml
    * **charsets**
      * charsets.xml
      * **_charset_** `*`
        * charset.xml
        * charset.bmp
    * **rooms**
      * rooms.xml
      * **_room_** `*`
        * background.bmp
        * map.xml
        * palette.xml
        * room.xml
        * **costumes**
          * costumes.xml
          * **_costume_** `*`
            * costume.xml
            * **anims**
              * _anim_.xml `*`
            * **frames**
              * frame`_`_xxx_.bmp `*`
        * **objects**
          * objects.xml
          * **_object_** `*`
            * object.xml
            * images.xml
            * **_image_** `*`
              * image.bmp
              * **zplanes**
                * zplane`_`_xxx_.bmp `*`
        * **scripts**
          * scripts.xml
          * _script_.sgc `*`
        * **zplanes**
          * zplane`_`_xxx_.bmp `*`
    * **scripts**
      * scripts.xml
      * _script_.sgc `*`
    * **voices**
      * voices.xml
      * **_voice_** `*`
        * voice.wav
        * voice.xml

# Resource files assembler #

## Description ##

The resource files assembler is presently the only piece of software available from the source repository. It contains three main sub-parts which are executed sequentially : we first load the game folder, then we run the compiler, and finally we generate the resources.

## Loader ##

Once one is happy with his creation using the editors, it's now time to generate the game and launch it with ScummVM. The first thing we do here is to load the game folder which has been created by the editors. If you look into the _types_ directory of the source repository, you'll find a bunch of classes such as Game, Room, Object, etc. These are allocated while parsing the XML files, images and other data present in the game folder. We can consider these instances as a mirror to what has been designed using the editors - it contains the exact same information, but stored in a different way.

## Compiler ##

The scripts present in the game folder have not been parsed yet : this is the role of the compiler. In the _grammar_ source folder, you can see how ScummGEN parses the scripts you typed and understand what you are allowed to do (even though that requires some programming knowledge). It's also important to mention that this part has to be executed after loading the game folder, as all the names given to rooms, costumes or objects, can be used in the scripts you code, and ScummGEN has to be able to "translate" those. If any error is to be found while compiling scripts, it's reported in a file called _log.txt_. After all this process, the Game, Room and Object instances now contain pieces of SCUMM compiled code almost ready to be executed using ScummVM.

## Generator ##

At this time we have everything we need to generate the final resources - we just have to translate ScummGEN types into SCUMM v6 blocks. The _blocks_ sub-folder in the source repository is pretty self-explanatory : inside are present all the different kinds of blocks supported by SCUMM v6 games. Some are written to the index file, others to the MONSTER.SOU file, and all the rest to the main resource file. Each of those blocks takes as an input one of ScummGEN's types, accesses its data, and writes it into the corresponding file respecting SCUMM v6's resource files' format. The game is now ready to be launched using ScummVM.