# Tomb Raider: Chronicles - Savegame Editor
This is a standalone savegame editor for Tomb Raider: Chronicles. It has been tested and works with the Steam version of the game, as well as the CD and multi-patched versions. Scroll down to the next section below for
instructions on how to use this program. For a more robust and well-maintained savegame editor that supports the entire Tomb Raider classic series, check out [TR-SaveMaster](https://github.com/JulianOzelRose/TR-SaveMaster).

![TRC-SaveEdit-UI](https://github.com/user-attachments/assets/e3dacb7c-a5ed-4eda-9044-b20fe378b8c6)


## Installation and use
To download and use this savegame editor, simply navigate to the [Release](https://github.com/JulianOzelRose/TRC-SaveEdit/tree/master/x64/Release) folder on this repo, then download `TRC-SaveEdit.exe`. You can save and run the .exe from anywhere on your computer. It is not necessary to launch the file with administrator privileges. To select a savegame to modify, click "Browse", then navigate to your game directory. Your game directory location depends on whether you installed by CD or through Steam.

Steam install directory: `C:\Program Files (x86)\Steam\steamapps\common\Tomb Raider (V) Chronicles`

CD install directory: `C:\Program Files (x86)\Core Design\Tomb Raider Chronicles`

Once you have selected a savegame file, you can give yourself extra ammo, extra weapons, extra medipacks, and more. You can give yourself guns that are "enabled" on a given level -- but unfortunately, certain guns had to be disabled for certain levels in this editor. This is because enabling guns that aren't supposed to be used on certain levels will crash the game. For example, trying to use a hacked savegame file with an HK Gun in inventory on Streets of Rome will result in the game crashing. Once you are finished entering the desired changes, click "Save" to apply them to the savegame file. To set medipacks or ammo to unlimited, set their values to 65535. Shotgun ammo values higher than 5461 will appear as negative in game. Make sure
to backup your savegame files as a precaution.

## Determining the correct health offset
The health data is stored dynamically, with anywhere from 1 to 20 unique health offsets per level. These offsets appear to shift based on level triggers and change frequently. Writing to the incorrect health offset may cause the game to crash. To find
the correct health offset, this program uses a heuristic algorithm. It takes the health offset range unique to each level, then loops through them, performing two heuristic checks.

First, it checks for a valid health value (greater than 0 and less than or equal to 1000). If the first check is passed, it performs one more check by examining the surrounding data. Since the character animation data is always stored 6 bytes away from the health offset, the algorithm checks the values 6 bytes from the health offset for known character animation byte flags. If a known pattern is found, the offset is returned as a valid health offset. Otherwise, an error code is returned. This method detects the correct health offset approximately 96% of the time.

```
int GetHealthOffset()
{
	for (int offset = MIN_HEALTH_OFFSET; offset <= MAX_HEALTH_OFFSET; offset++)
	{
		int healthValue = ReadUInt16(offset);

		if (healthValue > MIN_HEALTH_VALUE && healthValue <= MAX_HEALTH_VALUE)
		{
			byte byteFlag1 = ReadByte(offset - 7);
			byte byteFlag2 = ReadByte(offset - 6);

			if (IsKnownByteFlagPattern(byteFlag1, byteFlag2))
			{
				return offset;
			}
		}
	}

	return -1;
}
```

## Offset tables ##
For the weapons variables, a value of 0 means disabled, and a value of 0x9 will enable the weapon in inventory. For the HK, grappling gun, revolver, and deagle,
a value of 0xD will enable the gun along with the sight attached to it. Setting values like ammo, medipacks, or flares to 0xFFFF (65535 in decimal) will make them unlimited.
The shotgun ammo variables on offsets `0x1A0` and `0x1A2` use a multiplier of 6. Meaning, a value of 36 in the save file will yield a value of 6 in game.
All of the offsets are static across levels, with the exception of the health offsets, which are dynamically allocated.

#### General ####
| **Offset**              | **Type**         | **Variable**          |
| :---                	  | :---             | :---                  |
| 0x000     	          | String           | Level Name            |
| 0x04B                   | Int32            | Save Number           |
| 0x16F     	          | UInt8            | Pistols               |
| 0x170     	          | UInt8 	     | Uzi                   |
| 0x171     	          | UInt8 	     | Shotgun               |
| 0x172     	          | UInt8 	     | Grappling Gun         |
| 0x173     	          | UInt8 	     | HK Gun                |
| 0x174     	          | UInt8 	     | Revolver/Deagle       |
| 0x175     	          | UInt8 	     | LaserSight            |
| 0x177     	          | UInt8 	     | Binoculars/Headset    |
| 0x178     	          | UInt8            | Crowbar               |
| 0x194     	          | UInt16  	     | Small Medipack        |
| 0x196     	          | UInt16  	     | Large Medipack        |
| 0x198     	          | UInt16  	     | Flares                |
| 0x19C     	          | UInt16           | Uzi Ammo              |
| 0x19E     	          | UInt16  	     | Revolver/Deagle Ammo  |
| 0x1A0     	          | UInt16  	     | Shotgun Normal Ammo   |
| 0x1A2     	          | UInt16  	     | Shotgun Wideshot Ammo |
| 0x1A4     	          | UInt16  	     | HK Ammo               |
| 0x1A6     	          | UInt16  	     | Grappling Gun Ammo    |
| 0x1C3     	          | UInt8   	     | Secrets               |
| 0x1EC                   | UInt8            | Level Index           |

#### Health ####
| **Level**           	| **Offset range**      |
| :---                	| :---                  |
| Streets of Rome     	| 0x4F4 - 0x4F8		|
| Trajan's Markets    	| 0x542 - 0x5D7		|
| The Colosseum	      	| 0x4D2 - 0x7FF		|
| The Base		| 0x556 - 0x707		|
| The Submarine		| 0x520 - 0x5D2		|
| Deepsea Dive		| 0x644 - 0x6DE		|
| Sinking Submarine	| 0x5CC - 0x66B		|
| Gallows Tree		| 0x4F0 - 0x52D		|
| Labyrinth		| 0x538 - 0x61A		|
| Old Mill		| 0x512 - 0x624		|
| The 13th Floor	| 0x52A - 0x53A		|
| Escape with the Iris	| 0x6F6 - 0xC47		|
| Red Alert!		| 0x52C - 0x5D6		|
