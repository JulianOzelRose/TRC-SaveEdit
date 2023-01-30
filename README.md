# TRC-SaveEdit
This is a standalone save game editor for Tomb Raider: Chronicles. It has been tested and works on both the multi-patched verison of the game, as well as the Steam version. To download the program, simply navigate to the x64/Release folder on this repo, then download TRC-SaveEdit.exe. You can run the .exe from anywhere on your computer. It is not necessary to launch the file with administrator privileges. To select a save game to modify, click 'Browse', then navigate to your save game folder. If you are running the Steam version, your game directory should be under 'Steam\steamapps\common\Tomb Raider (V) Chronicles'.

From there, you can give yourself extra ammo, extra weapons, extra medipacks, and more. You can give yourself guns that are "enabled" on a given level -- but unfortunately, certain guns had to be disabled for certain levels in this editor. This is because enabling guns that aren't supposed to be used on certain levels will crash the game. For example, trying to use a hacked save game file with an HK gun in inventory on Streets of Rome, will result in the game crashing.

### Screenshot of TRC-SaveEdit
![TRC-SaveEdit](https://user-images.githubusercontent.com/95890436/215334144-c576f363-bd15-41e5-b5ee-02aab905b4bb.PNG)


## Tomb Raider: Chronicles Save Game Hex Table ##
| **File Offset**     | **Variable**              |
| :---                | :---                      |
| 0x000               | Level Name                |
| 0x04B               | Number of Saves           |
| 0x16F               | Pistols                   |
| 0x170               | Uzi                       |
| 0x171               | Shotgun                   |
| 0x172               | Grappling Gun             |
| 0x173               | HK Gun                    |
| 0x174               | Revolver                  |
| 0x178               | Crowbar                   |
| 0x194               | Small Medipacks           |
| 0x196               | Large Medipacks           |
| 0x198               | Flares                    |
| 0x19C               | Uzi Ammo                  |
| 0x19E               | Deagle/Revolver Ammo      |
| 0x1A0               | Shotgun Normal Ammo       |
| 0x1A2               | Shotgun Wideshot Ammo     |
| 0x1A4               | HK Ammo                   |
| 0x1A6               | Grappling Gun Ammo        |
| 0x1C3               | Number of Secrets         |

For the weapons variables, a value of ```0``` means disabled, and a value of ```09``` will enable the weapon in inventory. For the HK and revolver guns,
a value of ```0D``` will enable the gun along with the sight attached to it. Setting values like health and ammo to ```FFFF``` will make them unlimited.
