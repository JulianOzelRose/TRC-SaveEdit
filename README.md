# TRC-SaveEdit
This is a standalone save game editor for Tomb Raider: Chronicles. It has been tested and works on both the multi-patched verison of the game, as well as the Steam version. To download the program, simply navigate to the **x64/Release** folder on this repo, then download **TRC-SaveEdit.exe**. You can run the .exe from anywhere on your computer. It is not necessary to launch the file with administrator privileges. To select a save game to modify, click **Browse**, then navigate to the game directory. Your game directory location depends on whether you installed by CD or through Steam.

Steam install directory: ```Program Files\Steam\steamapps\common\Tomb Raider (V) Chronicles\```

CD install directory: ```Program Files\Core Design\Tomb Raider Chronicles\```

Once you have selected a save game file, you can give yourself extra ammo, extra weapons, extra medipacks, and more. You can give yourself guns that are "enabled" on a given level -- but unfortunately, certain guns had to be disabled for certain levels in this editor. This is because enabling guns that aren't supposed to be used on certain levels will crash the game. For example, trying to use a hacked save game file with an HK gun in inventory on Streets of Rome, will result in the game crashing. Once you are finished entering the desired changes, click **Save** to apply them to the save file. To set medipacks or ammo to unlimited, set their values to 65,535. Shotgun ammo values higher than 5,461 will appear as negative in game.

#### Screenshot of TRC-SaveEdit
![TRC-SaveEdit-UI](https://github.com/JulianOzelRose/TRC-SaveEdit/assets/95890436/e92cc50a-1616-4c35-b189-6761cbb8ffb5)



## Offset table ##
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

For the weapons variables, a value of 0 means disabled, and a value of 0x9 will enable the weapon in inventory. For the HK and revolver guns,
a value of 0xD will enable the gun along with the sight attached to it. Setting values like health and ammo to 0xFFFF will make them unlimited.
The shotgun ammo variables on offsets ```0x1A0``` and ```0x1A2``` use a multiplier of 6. Meaning, a value of 36 in the save file will yield a value of 6 in game.
