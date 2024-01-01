# Tomb Raider: Chronicles - Savegame Editor
This is a standalone savegame editor for Tomb Raider: Chronicles. It has been tested and works with the Steam version of the game, as well as the multi-patched version. To download the editor, simply navigate to the [Release](https://github.com/JulianOzelRose/TRC-SaveEdit/tree/master/x64/Release) folder on this repo, then download ```TRC-SaveEdit.exe```. You can run the .exe from anywhere on your computer. It is not necessary to launch the file with administrator privileges. To select a savegame to modify, click ```Browse```, then navigate to your game directory. Your game directory location depends on whether you installed by CD or through Steam.

Steam install directory: ```C:\Program Files (x86)\Steam\steamapps\common\Tomb Raider (V) Chronicles\```

CD install directory: ```C:\Program Files (x86)\Core Design\Tomb Raider Chronicles\```

Once you have selected a savegame file, you can give yourself extra ammo, extra weapons, extra medipacks, and more. You can give yourself guns that are "enabled" on a given level -- but unfortunately, certain guns had to be disabled for certain levels in this editor. This is because enabling guns that aren't supposed to be used on certain levels will crash the game. For example, trying to use a hacked savegame file with an HK Gun in inventory on Streets of Rome will result in the game crashing. Once you are finished entering the desired changes, click ```Save``` to apply them to the savegame file. To set medipacks or ammo to unlimited, set their values to 65535. Shotgun ammo values higher than 5461 will appear as negative in game. Make sure
to backup your savegame files as a precaution.


![TRC-SaveEdit-UI](https://github.com/JulianOzelRose/TRC-SaveEdit/assets/95890436/aabb5128-c131-4f44-8c11-91c0ded866a8)




## Determining the correct health offset
The health data is stored dynamically. There can be anywhere from 1 to 20 unique health offsets per level. The offsets appear to shift based on level triggers, and they shift around a lot. Writing to the incorrect health offset may crash the game.
To get around this issue, this program uses a heuristic algorithm. It takes the health offset range unique to each level, then it loops through them and checks the surrounding data first.

Since the character animation data is always stored 6 bytes away
from the health, the algorithm checks the values 6 bytes from the health offset for known character animation byte flags. If a known pattern is found, it runs one more test to ensure validity by checking for an impossible health value (0 or greater than
1000). If it passes these checks, then it is returned as a valid health offset. Otherwise, an error code is returned. This method detects the correct health offset ~96% of the time.

```
int GetHealthOffset()
{
	for (int offset = MIN_HEALTH_OFFSET; offset <= MAX_HEALTH_OFFSET; offset++)
	{
		byte byteFlag1 = ReadByte(offset - 7);
		byte byteFlag2 = ReadByte(offset - 6);

		if (IsKnownByteFlagPattern(byteFlag1, byteFlag2))
		{
			int healthValue = ReadUInt16(offset);

			if (healthValue > MIN_HEALTH_VALUE && healthValue <= MAX_HEALTH_VALUE)
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
The shotgun ammo variables on offsets ```0x1A0``` and ```0x1A2``` use a multiplier of 6. Meaning, a value of 36 in the save file will yield a value of 6 in game.
All of the offsets are static across levels, with the exception of the health offsets, which are dynamically allocated.

#### General ####
| **File offset**         | **Type**         | **Variable**          |
| :---                	  | :---             | :---                  |
| 0x000     	          | String           | Level Name            |
| 0x04B                   | UInt16           | Save Number           |
| 0x16F     	          | BYTE             | Pistols               |
| 0x170     	          | BYTE  	     | Uzi                   |
| 0x171     	          | BYTE  	     | Shotgun               |
| 0x172     	          | BYTE  	     | Grappling Gun         |
| 0x173     	          | BYTE  	     | HK Gun                |
| 0x174     	          | BYTE  	     | Revolver/Deagle       |
| 0x175     	          | BYTE  	     | LaserSight            |
| 0x177     	          | BYTE  	     | Binoculars/Headset    |
| 0x178     	          | BYTE             | Crowbar               |
| 0x194     	          | UInt16  	     | Small Medipack        |
| 0x196     	          | UInt16  	     | Large Medipack        |
| 0x198     	          | UInt16  	     | Flares                |
| 0x19C     	          | UInt16           | Uzi Ammo              |
| 0x19E     	          | UInt16  	     | Revolver/Deagle Ammo  |
| 0x1A0     	          | UInt16  	     | Shotgun Normal Ammo   |
| 0x1A2     	          | UInt16  	     | Shotgun Wideshot Ammo |
| 0x1A4     	          | UInt16  	     | HK Ammo               |
| 0x1A6     	          | UInt16  	     | Grappling Gun Ammo    |
| 0x1C3     	          | BYTE    	     | Secrets               |

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
