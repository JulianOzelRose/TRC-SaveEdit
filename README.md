# Tomb Raider Chronicles - Savegame Editor
This is a standalone savegame editor for Tomb Raider Chronicles. It has been tested and works on both the multi-patched verison of the game, as well as the Steam version. To download the program, simply navigate to the [Release](https://github.com/JulianOzelRose/TRC-SaveEdit/tree/master/x64/Release) folder on this repo, then download ```TRC-SaveEdit.exe```. You can run the .exe from anywhere on your computer. It is not necessary to launch the file with administrator privileges. To select a save game to modify, click ```Browse```, then navigate to the game directory. Your game directory location depends on whether you installed by CD or through Steam.

Steam install directory: ```Program Files\Steam\steamapps\common\Tomb Raider (V) Chronicles\```

CD install directory: ```Program Files\Core Design\Tomb Raider Chronicles\```

Once you have selected a save game file, you can give yourself extra ammo, extra weapons, extra medipacks, and more. You can give yourself guns that are "enabled" on a given level -- but unfortunately, certain guns had to be disabled for certain levels in this editor. This is because enabling guns that aren't supposed to be used on certain levels will crash the game. For example, trying to use a hacked save game file with an HK gun in inventory on Streets of Rome, will result in the game crashing. Once you are finished entering the desired changes, click ```Save``` to apply them to the save file. To set medipacks or ammo to unlimited, set their values to 65535. Shotgun ammo values higher than 5461 will appear as negative in game. Make sure
to backup your savegame files as a precaution.

#### Screenshot of TRC-SaveEdit
![TRC-SaveEdit-UI](https://github.com/JulianOzelRose/TRC-SaveEdit/assets/95890436/db2c44a1-b1d8-4cdf-94be-bfe52f7205ba)

## Determining the correct health offset
The health data is stored dynamically. There can be anywhere from 1 to 20 unique health offsets per level. The offsets appear to shift based on level triggers, and they shift around a lot. Writing to the incorrect health offset may crash the game.
To get around this issue, this program uses a heuristic algorithm. It takes the health offset range unique to each level, then it loops through them and checks the surrounding data first.

Since the character movement data is always stored 6 bytes away
from the health, the algorithm checks the values 6 bytes from the health offset for known character movement byte flags. If a known pattern is found, it runs one more test to ensure validity by checking for an impossible health value (0 or greater than
1000). If it passes the check, then it is returned as a valid health offset. Otherwise, an error code is returned. This method detects the correct health offset ~96% of the time.

```
int GetHealthOffset()
{
	for (int offset = MIN_HEALTH_OFFSET; offset <= MAX_HEALTH_OFFSET; offset++)
	{
		int byteFlag1 = GetSaveFileData(offset - 7);
		int byteFlag2 = GetSaveFileData(offset - 6);

		if (IsKnownByteFlagPattern(byteFlag1, byteFlag2))
		{
			int healthValue = GetValue(offset);

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
For the weapons variables, a value of 0 means disabled, and a value of 0x9 will enable the weapon in inventory. For the HK and revolver guns,
a value of 0xD will enable the gun along with the sight attached to it. Setting values like health and ammo to 0xFFFF (65535 in decimal) will make them unlimited.
The shotgun ammo variables on offsets ```0x1A0``` and ```0x1A2``` use a multiplier of 6. Meaning, a value of 36 in the save file will yield a value of 6 in game.
All of the offsets are static across levels, with the exception of the health offsets.

#### General ####
| **File Offset**     | **Variable**              |
| :---                | :---                      |
| 0x000               | Level Name                |
| 0x04B               | Number of Saves           |
| 0x16F               | Pistols                   |
| 0x170               | Uzi                       |
| 0x171               | Shotgun                   |
| 0x172               | Grappling Gun             |
| 0x173               | HK Gun                    |
| 0x174               | Revolver/Deagle           |
| 0x178               | Crowbar                   |
| 0x194               | Small Medipacks           |
| 0x196               | Large Medipacks           |
| 0x198               | Flares                    |
| 0x19C               | Uzi Ammo                  |
| 0x19E               | Revolver/Deagle Ammo      |
| 0x1A0               | Shotgun Normal Ammo       |
| 0x1A2               | Shotgun Wideshot Ammo     |
| 0x1A4               | HK Ammo                   |
| 0x1A6               | Grappling Gun Ammo        |
| 0x1C3               | Number of Secrets         |

#### Health ####
| **Level**           	| **Offset range**      |
| :---                	| :---                  |
| Streets of Rome     	| 0x4F4 - 0x4F8		|
| Trajan's Markets    	| 0x542 - 0x5D7		|
| The Colosseum	      	| 0x4D2 - 0x7FF		|
| The Base		| 0x556 - 0x707		|
| The Submarine		| 0x520 - 0x59A		|
| Deepsea Dive		| 0x644 - 0x6DE		|
| Sinking Submarine	| 0x5D2 - 0x66B		|
| Gallows Tree		| 0x4F0 - 0x52D		|
| Labyrinth		| 0x538 - 0x61A		|
| Old Mill		| 0x512 - 0x624		|
| The 13th Floor	| 0x52A - 0x53A		|
| Escape with the Iris	| 0x6F6 - 0xC20		|
| Red Alert!		| 0x52E - 0x58A		|
