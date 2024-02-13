/*
	Julian O. Rose
	TRC-SaveEdit
	1-29-2023
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>

namespace TRCSaveEdit {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace msclr::interop;

	public ref class SaveEditUI : public System::Windows::Forms::Form
	{
	private:
		// Strings
		String^ strSavefileName;
		String^ strLvlName;

		// Offsets
		const int saveNumOffset = 0x04B;
		const int pistolsOffset = 0x16F;
		const int uziOffset = 0x170;
		const int shotgunOffset = 0x171;
		const int grapplingGunOffset = 0x172;
		const int hkOffset = 0x173;
		const int revolverOrDeagleOffset = 0x174;
		const int crowbarOffset = 0x178;
		const int smallMedipackOffset = 0x194;
		const int largeMedipackOffset = 0x196;
		const int numFlaresOffset = 0x198;
		const int uziAmmoOffset = 0x19C;
		const int revolverOrDeagleAmmoOffset = 0x19E;
		const int shotgunNormalAmmoOffset = 0x1A0;
		const int shotgunWideshotAmmoOffset = 0x1A2;
		const int hkAmmoOffset = 0x1A4;
		const int grapplingGunAmmoOffset = 0x1A6;
		const int numSecretsOffset = 0x1C3;

		// Health
		const int MIN_HEALTH_VALUE = 0;
		const int MAX_HEALTH_VALUE = 1000;
		int MIN_HEALTH_OFFSET = 0;
		int MAX_HEALTH_OFFSET = 1;
		int healthOffset = -1;
	private: System::Windows::Forms::GroupBox^ grpHealth;
	private: System::Windows::Forms::TrackBar^ trbHealth;
	private: System::Windows::Forms::Label^ lblHealth;
	private: System::Windows::Forms::Label^ lblHealthError;
	private: System::Windows::Forms::StatusStrip^ ssrStatusStrip;






	private: System::Windows::Forms::ToolStripStatusLabel^ slblStatus;
	private: System::Windows::Forms::CheckBox^ chkPistols;


	public:
		SaveEditUI(void)
		{
			InitializeComponent();
		}

		void SetSaveFileName(String^ fileName)
		{
			strSavefileName = fileName;
		}

		String^ GetSaveFileName()
		{
			return strSavefileName;
		}

		int ReadByte(int offset)
		{
			std::fstream saveFile(marshal_as<std::string>(GetSaveFileName()), std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekp(offset);
			int iData = saveFile.get();
			saveFile.close();
			return iData;
		}

		int ReadUInt16(int offset)
		{
			int value = 0;

			if (ReadByte(offset + 1) == 0)
			{
				value = ReadByte(offset);
			}
			else
			{
				int upperByte = ReadByte(offset + 1);
				int lowerByte = ReadByte(offset);
				value = upperByte * 256 + lowerByte;
			}

			return value;
		}

		void WriteByte(int offset, int value)
		{
			std::fstream saveFile(marshal_as<std::string>(GetSaveFileName()), std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekg(offset, std::ios::beg);
			char cData[1] = { value };
			saveFile.write(cData, sizeof(cData));
			saveFile.close();
		}

		void WriteUInt16(int offset, int value)
		{
			if (value > 255)
			{
				int upperByte = value / 256;
				int lowerByte = value % 256;

				WriteByte(offset + 1, upperByte);
				WriteByte(offset, lowerByte);
			}
			else
			{
				WriteByte(offset, value);
				WriteByte(offset + 1, 0);
			}
		}

		void DisplayLvlName()
		{
			std::ifstream saveFile(marshal_as<std::string>(GetSaveFileName()));
			std::string sData;

			if (saveFile.good()) getline(saveFile, sData);

			saveFile.close();

			strLvlName = gcnew String(sData.c_str());
			txtLvlName->Clear();
			txtLvlName->AppendText(strLvlName);
		}

		void DisplayNumSecrets()
		{
			int numSecrets = ReadByte(numSecretsOffset);
			txtNumSecrets->Clear();
			txtNumSecrets->AppendText(numSecrets.ToString());
		}

		void DisplaySaveNum()
		{
			int saveNum = ReadUInt16(saveNumOffset);
			txtNumSaves->Clear();
			txtNumSaves->AppendText(saveNum.ToString());
		}

		void DisplayNumFlares()
		{
			int numFlares = ReadUInt16(numFlaresOffset);
			txtNumFlares->Clear();
			txtNumFlares->AppendText(numFlares.ToString());
		}

		void DisplayNumSmallMedipacks()
		{
			int numSmallMedipacks = ReadUInt16(smallMedipackOffset);
			txtSmallMedipacks->Clear();
			txtSmallMedipacks->AppendText(numSmallMedipacks.ToString());
		}

		void DisplayNumLargeMedipacks()
		{
			int numLargeMedipacks = ReadUInt16(largeMedipackOffset);
			txtLargeMedipacks->Clear();
			txtLargeMedipacks->AppendText(numLargeMedipacks.ToString());
		}

		void DisplayShotgunNormalAmmo()
		{
			int shotgunNormalAmmo = ReadUInt16(shotgunNormalAmmoOffset);
			txtShotgunNormalAmmo->Clear();
			txtShotgunNormalAmmo->AppendText((shotgunNormalAmmo / 6).ToString());
		}

		void DisplayShotgunWideshotAmmo()
		{
			int shotgunWideshotAmmo = ReadUInt16(shotgunWideshotAmmoOffset);
			txtShotgunWideshotAmmo->Clear();
			txtShotgunWideshotAmmo->AppendText((shotgunWideshotAmmo / 6).ToString());
		}

		void DisplayUziAmmo()
		{
			int uziAmmo = ReadUInt16(uziAmmoOffset);
			txtUziAmmo->Clear();
			txtUziAmmo->AppendText(uziAmmo.ToString());
		}

		void DisplayHKAmmo()
		{
			int hkAmmo = ReadUInt16(hkAmmoOffset);
			txtHkAmmo->Clear();
			txtHkAmmo->AppendText(hkAmmo.ToString());
		}

		void DisplayGrapplingGunAmmo()
		{
			int grapplingGunAmmo = ReadUInt16(grapplingGunAmmoOffset);
			txtGrapplingGunAmmo->Clear();
			txtGrapplingGunAmmo->AppendText(grapplingGunAmmo.ToString());
		}

		void DisplayRevolverOrDeagleAmmo()
		{
			int revolverOrDeagleAmmo = ReadUInt16(revolverOrDeagleAmmoOffset);
			txtRevolverOrDeagleAmmo->Clear();
			txtRevolverOrDeagleAmmo->AppendText(revolverOrDeagleAmmo.ToString());
		}

		bool IsKnownByteFlagPattern(byte byteFlag1, byte byteFlag2)
		{
			if (byteFlag1 == 0x01 && byteFlag2 == 0x02) return true;	// Finishing running
			if (byteFlag1 == 0x02 && byteFlag2 == 0x02) return true;	// Standing
			if (byteFlag1 == 0x03 && byteFlag2 == 0x47) return true;	// Running jump
			if (byteFlag1 == 0x09 && byteFlag2 == 0x09) return true;	// Freefalling
			if (byteFlag1 == 0x13 && byteFlag2 == 0x13) return true;	// Climbing up a ledge
			if (byteFlag1 == 0x17 && byteFlag2 == 0x02) return true;	// Crouch-rolling
			if (byteFlag1 == 0x18 && byteFlag2 == 0x18) return true;	// Sliding down a ledge
			if (byteFlag1 == 0x19 && byteFlag2 == 0x19) return true;	// Doing a backflip
			if (byteFlag1 == 0x21 && byteFlag2 == 0x21) return true;	// In water but not underwater
			if (byteFlag1 == 0x47 && byteFlag2 == 0x47) return true;	// Crouching
			if (byteFlag1 == 0x47 && byteFlag2 == 0x57) return true;	// Squatting
			if (byteFlag1 == 0x49 && byteFlag2 == 0x49) return true;	// Sprinting
			if (byteFlag1 == 0x0D && byteFlag2 == 0x12) return true;	// Swimming
			if (byteFlag1 == 0x12 && byteFlag2 == 0x12) return true;	// Swimming (with diving suit)
			if (byteFlag1 == 0x0D && byteFlag2 == 0x0D) return true;	// Underwater
			if (byteFlag1 == 0x50 && byteFlag2 == 0x50) return true;	// Crouching forward
			if (byteFlag1 == 0x59 && byteFlag2 == 0x16) return true;	// Searching a container
			if (byteFlag1 == 0x59 && byteFlag2 == 0x15) return true;	// Searching a cabinet
			if (byteFlag1 == 0x59 && byteFlag2 == 0x10) return true;	// About to search a container
			if (byteFlag1 == 0x27 && byteFlag2 == 0x10) return true;	// Picking up an item
			if (byteFlag1 == 0x29 && byteFlag2 == 0x00) return true;	// Pulling a lever
			if (byteFlag1 == 0x28 && byteFlag2 == 0x10) return true;	// Pushing a button
			if (byteFlag1 == 0x23 && byteFlag2 == 0x11) return true;	// Diving
			if (byteFlag1 == 0x1C && byteFlag2 == 0x0F) return true;	// In air or jumping straight up
			if (byteFlag1 == 0x51 && byteFlag2 == 0x50) return true;	// Crawling
			if (byteFlag1 == 0x2B && byteFlag2 == 0x16) return true;	// Placing an item in a recepticle
			if (byteFlag1 == 0x62 && byteFlag2 == 0x15) return true;	// Activating a switch

			return false;
		}

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

		void DisplayHealthValue()
		{
			healthOffset = GetHealthOffset();

			if (healthOffset == -1)
			{
				trbHealth->Enabled = false;
				lblHealthError->Visible = true;
				lblHealth->Visible = false;
				trbHealth->Value = 0;
			}
			else
			{
				int health = ReadUInt16(healthOffset);
				double healthPercentage = static_cast<double>(health) / MAX_HEALTH_VALUE * 100.0;
				trbHealth->Enabled = true;
				lblHealth->Visible = true;
				lblHealthError->Visible = false;
				trbHealth->Value = static_cast<int>(std::round(healthPercentage));
				lblHealth->Text = healthPercentage.ToString("0.0") + "%";
			}
		}

		void SetLvlParams()
		{
			if (strLvlName == "Streets of Rome")
			{
				chkRevolverOrDeagle->Enabled = true;
				txtRevolverOrDeagleAmmo->Enabled = true;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = true;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				chkRevolverOrDeagle->Text = "Revolver:";
				MIN_HEALTH_OFFSET = 0x4F4;
				MAX_HEALTH_OFFSET = 0x4F8;
			}
			else if (strLvlName == "Trajan`s markets")
			{
				chkRevolverOrDeagle->Enabled = true;
				txtRevolverOrDeagleAmmo->Enabled = true;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = true;
				chkShotgun->Enabled = true;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				chkRevolverOrDeagle->Text = "Revolver:";
				MIN_HEALTH_OFFSET = 0x542;
				MAX_HEALTH_OFFSET = 0x5D7;
			}
			else if (strLvlName == "The Colosseum")
			{
				chkRevolverOrDeagle->Enabled = true;
				txtRevolverOrDeagleAmmo->Enabled = true;
				chkUzi->Enabled = true;
				txtUziAmmo->Enabled = true;
				chkShotgun->Enabled = true;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				chkRevolverOrDeagle->Text = "Revolver:";
				MIN_HEALTH_OFFSET = 0x4D2;
				MAX_HEALTH_OFFSET = 0x7FF;
			}
			else if (strLvlName == "The base")
			{
				chkRevolverOrDeagle->Enabled = true;
				txtRevolverOrDeagleAmmo->Enabled = true;
				chkUzi->Enabled = true;
				txtUziAmmo->Enabled = true;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				chkRevolverOrDeagle->Text = "Desert Eagle:";
				MIN_HEALTH_OFFSET = 0x556;
				MAX_HEALTH_OFFSET = 0x707;
			}
			else if (strLvlName == "The submarine")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = true;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				MIN_HEALTH_OFFSET = 0x520;
				MAX_HEALTH_OFFSET = 0x5D2;
			}
			else if (strLvlName == "Deepsea dive")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = true;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				MIN_HEALTH_OFFSET = 0x644;
				MAX_HEALTH_OFFSET = 0x6DE;
			}
			else if (strLvlName == "Sinking submarine")
			{
				chkRevolverOrDeagle->Enabled = true;
				txtRevolverOrDeagleAmmo->Enabled = true;
				chkUzi->Enabled = true;
				txtUziAmmo->Enabled = true;
				chkShotgun->Enabled = true;
				txtShotgunNormalAmmo->Enabled = true;
				txtShotgunWideshotAmmo->Enabled = true;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = true;
				txtNumFlares->Enabled = true;
				MIN_HEALTH_OFFSET = 0x5CC;
				MAX_HEALTH_OFFSET = 0x66B;
			}
			else if (strLvlName == "Gallows tree")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x4F0;
				MAX_HEALTH_OFFSET = 0x52D;
			}
			else if (strLvlName == "Labyrinth")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x538;
				MAX_HEALTH_OFFSET = 0x61A;
			}
			else if (strLvlName == "Old mill")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = false;
				txtHkAmmo->Enabled = false;
				chkCrowbar->Enabled = true;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x512;
				MAX_HEALTH_OFFSET = 0x624;
			}
			else if (strLvlName == "The 13th floor")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = true;
				txtHkAmmo->Enabled = true;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x52A;
				MAX_HEALTH_OFFSET = 0x53A;
			}
			else if (strLvlName == "Escape with the iris")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = false;
				txtGrapplingGunAmmo->Enabled = false;
				chkHkGun->Enabled = true;
				txtHkAmmo->Enabled = true;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x6F6;
				MAX_HEALTH_OFFSET = 0xC47;
			}
			else if (strLvlName == "Red alert!")
			{
				chkRevolverOrDeagle->Enabled = false;
				txtRevolverOrDeagleAmmo->Enabled = false;
				chkUzi->Enabled = false;
				txtUziAmmo->Enabled = false;
				chkShotgun->Enabled = false;
				txtShotgunNormalAmmo->Enabled = false;
				txtShotgunWideshotAmmo->Enabled = false;
				chkGrapplingGun->Enabled = true;
				txtGrapplingGunAmmo->Enabled = true;
				chkHkGun->Enabled = true;
				txtHkAmmo->Enabled = true;
				chkCrowbar->Enabled = false;
				chkPistols->Enabled = false;
				txtNumFlares->Enabled = false;
				MIN_HEALTH_OFFSET = 0x52C;
				MAX_HEALTH_OFFSET = 0x5D6;
			}
		}

		void DisplayWeaponsInfo()
		{
			chkUzi->Checked = ReadByte(uziOffset) != 0;
			chkShotgun->Checked = ReadByte(shotgunOffset) != 0;
			chkGrapplingGun->Checked = ReadByte(grapplingGunOffset) != 0;
			chkHkGun->Checked = ReadByte(hkOffset) != 0;
			chkRevolverOrDeagle->Checked = ReadByte(revolverOrDeagleOffset) != 0;
			chkCrowbar->Checked = ReadByte(crowbarOffset) != 0;
			chkPistols->Checked = ReadByte(pistolsOffset) != 0;
		}
	private: System::Windows::Forms::TextBox^ txtSmallMedipacks;
	public:


	private: System::Windows::Forms::Label^ lblSmallMedipacks;
	private: System::Windows::Forms::TextBox^ txtLargeMedipacks;
	public:
	public:


	private: System::Windows::Forms::Label^ lblLargeMedipacks;
	private: System::Windows::Forms::TextBox^ txtNumSecrets;


	private: System::Windows::Forms::Label^ lblSecrets;
	private: System::Windows::Forms::TextBox^ txtRevolverOrDeagleAmmo;



	private: System::Windows::Forms::TextBox^ txtNumSaves;

	private: System::Windows::Forms::Label^ lblSaveNumber;
	private: System::Windows::Forms::TextBox^ txtUziAmmo;
	private: System::Windows::Forms::TextBox^ txtHkAmmo;
	private: System::Windows::Forms::TextBox^ txtShotgunWideshotAmmo;




	private: System::Windows::Forms::TextBox^ txtShotgunNormalAmmo;

	private: System::Windows::Forms::TextBox^ txtNumFlares;

	private: System::Windows::Forms::Label^ lblFlares;

	private: System::Windows::Forms::GroupBox^ grpLevel;
	private: System::Windows::Forms::GroupBox^ grpItems;
	private: System::Windows::Forms::Button^ btnSave;



	private: System::Windows::Forms::GroupBox^ grpWeapons;
	private: System::Windows::Forms::CheckBox^ chkRevolverOrDeagle;

	private: System::Windows::Forms::CheckBox^ chkShotgun;




	private: System::Windows::Forms::CheckBox^ chkHkGun;

	private: System::Windows::Forms::CheckBox^ chkUzi;
	private: System::Windows::Forms::CheckBox^ chkGrapplingGun;



	private: System::Windows::Forms::CheckBox^ chkCrowbar;


	private: System::Windows::Forms::TextBox^ txtGrapplingGunAmmo;


	protected:
		~SaveEditUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ lblFile;
	private: System::Windows::Forms::Label^ lblLvlName;

	private: System::Windows::Forms::TextBox^ txtFilePath;
	private: System::Windows::Forms::TextBox^ txtLvlName;

	protected:

	protected:



	private: System::Windows::Forms::Button^ btnBrowse;






	private:
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(SaveEditUI::typeid));
			this->lblFile = (gcnew System::Windows::Forms::Label());
			this->lblLvlName = (gcnew System::Windows::Forms::Label());
			this->txtFilePath = (gcnew System::Windows::Forms::TextBox());
			this->txtLvlName = (gcnew System::Windows::Forms::TextBox());
			this->btnBrowse = (gcnew System::Windows::Forms::Button());
			this->txtSmallMedipacks = (gcnew System::Windows::Forms::TextBox());
			this->lblSmallMedipacks = (gcnew System::Windows::Forms::Label());
			this->txtLargeMedipacks = (gcnew System::Windows::Forms::TextBox());
			this->lblLargeMedipacks = (gcnew System::Windows::Forms::Label());
			this->txtNumSecrets = (gcnew System::Windows::Forms::TextBox());
			this->lblSecrets = (gcnew System::Windows::Forms::Label());
			this->txtRevolverOrDeagleAmmo = (gcnew System::Windows::Forms::TextBox());
			this->txtNumSaves = (gcnew System::Windows::Forms::TextBox());
			this->lblSaveNumber = (gcnew System::Windows::Forms::Label());
			this->txtUziAmmo = (gcnew System::Windows::Forms::TextBox());
			this->txtHkAmmo = (gcnew System::Windows::Forms::TextBox());
			this->txtShotgunWideshotAmmo = (gcnew System::Windows::Forms::TextBox());
			this->txtShotgunNormalAmmo = (gcnew System::Windows::Forms::TextBox());
			this->txtNumFlares = (gcnew System::Windows::Forms::TextBox());
			this->lblFlares = (gcnew System::Windows::Forms::Label());
			this->grpLevel = (gcnew System::Windows::Forms::GroupBox());
			this->grpItems = (gcnew System::Windows::Forms::GroupBox());
			this->btnSave = (gcnew System::Windows::Forms::Button());
			this->grpWeapons = (gcnew System::Windows::Forms::GroupBox());
			this->chkPistols = (gcnew System::Windows::Forms::CheckBox());
			this->txtGrapplingGunAmmo = (gcnew System::Windows::Forms::TextBox());
			this->chkGrapplingGun = (gcnew System::Windows::Forms::CheckBox());
			this->chkShotgun = (gcnew System::Windows::Forms::CheckBox());
			this->chkCrowbar = (gcnew System::Windows::Forms::CheckBox());
			this->chkHkGun = (gcnew System::Windows::Forms::CheckBox());
			this->chkUzi = (gcnew System::Windows::Forms::CheckBox());
			this->chkRevolverOrDeagle = (gcnew System::Windows::Forms::CheckBox());
			this->grpHealth = (gcnew System::Windows::Forms::GroupBox());
			this->lblHealthError = (gcnew System::Windows::Forms::Label());
			this->lblHealth = (gcnew System::Windows::Forms::Label());
			this->trbHealth = (gcnew System::Windows::Forms::TrackBar());
			this->ssrStatusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->slblStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->grpLevel->SuspendLayout();
			this->grpItems->SuspendLayout();
			this->grpWeapons->SuspendLayout();
			this->grpHealth->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHealth))->BeginInit();
			this->ssrStatusStrip->SuspendLayout();
			this->SuspendLayout();
			// 
			// lblFile
			// 
			this->lblFile->AutoSize = true;
			this->lblFile->Location = System::Drawing::Point(11, 17);
			this->lblFile->Name = L"lblFile";
			this->lblFile->Size = System::Drawing::Size(26, 13);
			this->lblFile->TabIndex = 0;
			this->lblFile->Text = L"File:";
			// 
			// lblLvlName
			// 
			this->lblLvlName->AutoSize = true;
			this->lblLvlName->Location = System::Drawing::Point(15, 22);
			this->lblLvlName->Name = L"lblLvlName";
			this->lblLvlName->Size = System::Drawing::Size(38, 13);
			this->lblLvlName->TabIndex = 1;
			this->lblLvlName->Text = L"Name:";
			// 
			// txtFilePath
			// 
			this->txtFilePath->Location = System::Drawing::Point(37, 14);
			this->txtFilePath->Name = L"txtFilePath";
			this->txtFilePath->ReadOnly = true;
			this->txtFilePath->Size = System::Drawing::Size(307, 20);
			this->txtFilePath->TabIndex = 2;
			// 
			// txtLvlName
			// 
			this->txtLvlName->Location = System::Drawing::Point(57, 19);
			this->txtLvlName->Name = L"txtLvlName";
			this->txtLvlName->ReadOnly = true;
			this->txtLvlName->Size = System::Drawing::Size(161, 20);
			this->txtLvlName->TabIndex = 3;
			this->txtLvlName->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// btnBrowse
			// 
			this->btnBrowse->Location = System::Drawing::Point(349, 12);
			this->btnBrowse->Name = L"btnBrowse";
			this->btnBrowse->Size = System::Drawing::Size(75, 23);
			this->btnBrowse->TabIndex = 4;
			this->btnBrowse->Text = L"Browse";
			this->btnBrowse->UseVisualStyleBackColor = true;
			this->btnBrowse->Click += gcnew System::EventHandler(this, &SaveEditUI::btnBrowse_Click);
			// 
			// txtSmallMedipacks
			// 
			this->txtSmallMedipacks->Location = System::Drawing::Point(169, 25);
			this->txtSmallMedipacks->Name = L"txtSmallMedipacks";
			this->txtSmallMedipacks->Size = System::Drawing::Size(42, 20);
			this->txtSmallMedipacks->TabIndex = 5;
			this->txtSmallMedipacks->Text = L"0";
			this->txtSmallMedipacks->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtSmallMedipacks_KeyPress);
			// 
			// lblSmallMedipacks
			// 
			this->lblSmallMedipacks->AutoSize = true;
			this->lblSmallMedipacks->Location = System::Drawing::Point(18, 28);
			this->lblSmallMedipacks->Name = L"lblSmallMedipacks";
			this->lblSmallMedipacks->Size = System::Drawing::Size(90, 13);
			this->lblSmallMedipacks->TabIndex = 6;
			this->lblSmallMedipacks->Text = L"Small Medipacks:";
			// 
			// txtLargeMedipacks
			// 
			this->txtLargeMedipacks->Location = System::Drawing::Point(169, 50);
			this->txtLargeMedipacks->Name = L"txtLargeMedipacks";
			this->txtLargeMedipacks->Size = System::Drawing::Size(42, 20);
			this->txtLargeMedipacks->TabIndex = 7;
			this->txtLargeMedipacks->Text = L"0";
			this->txtLargeMedipacks->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtLargeMedipacks_KeyPress);
			// 
			// lblLargeMedipacks
			// 
			this->lblLargeMedipacks->AutoSize = true;
			this->lblLargeMedipacks->Location = System::Drawing::Point(18, 52);
			this->lblLargeMedipacks->Name = L"lblLargeMedipacks";
			this->lblLargeMedipacks->Size = System::Drawing::Size(92, 13);
			this->lblLargeMedipacks->TabIndex = 8;
			this->lblLargeMedipacks->Text = L"Large Medipacks:";
			// 
			// txtNumSecrets
			// 
			this->txtNumSecrets->Location = System::Drawing::Point(436, 19);
			this->txtNumSecrets->Name = L"txtNumSecrets";
			this->txtNumSecrets->Size = System::Drawing::Size(42, 20);
			this->txtNumSecrets->TabIndex = 9;
			this->txtNumSecrets->Text = L"0";
			this->txtNumSecrets->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtNumSecrets_KeyPress);
			// 
			// lblSecrets
			// 
			this->lblSecrets->AutoSize = true;
			this->lblSecrets->Location = System::Drawing::Point(384, 22);
			this->lblSecrets->Name = L"lblSecrets";
			this->lblSecrets->Size = System::Drawing::Size(46, 13);
			this->lblSecrets->TabIndex = 10;
			this->lblSecrets->Text = L"Secrets:";
			// 
			// txtRevolverOrDeagleAmmo
			// 
			this->txtRevolverOrDeagleAmmo->Location = System::Drawing::Point(158, 72);
			this->txtRevolverOrDeagleAmmo->Name = L"txtRevolverOrDeagleAmmo";
			this->txtRevolverOrDeagleAmmo->Size = System::Drawing::Size(42, 20);
			this->txtRevolverOrDeagleAmmo->TabIndex = 11;
			this->txtRevolverOrDeagleAmmo->Text = L"0";
			this->txtRevolverOrDeagleAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtRevolverOrDeagleAmmo_KeyPress);
			// 
			// txtNumSaves
			// 
			this->txtNumSaves->Location = System::Drawing::Point(318, 19);
			this->txtNumSaves->Name = L"txtNumSaves";
			this->txtNumSaves->Size = System::Drawing::Size(42, 20);
			this->txtNumSaves->TabIndex = 13;
			this->txtNumSaves->Text = L"0";
			this->txtNumSaves->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtNumSaves_KeyPress);
			// 
			// lblSaveNumber
			// 
			this->lblSaveNumber->AutoSize = true;
			this->lblSaveNumber->Location = System::Drawing::Point(239, 22);
			this->lblSaveNumber->Name = L"lblSaveNumber";
			this->lblSaveNumber->Size = System::Drawing::Size(75, 13);
			this->lblSaveNumber->TabIndex = 14;
			this->lblSaveNumber->Text = L"Save Number:";
			// 
			// txtUziAmmo
			// 
			this->txtUziAmmo->Location = System::Drawing::Point(158, 94);
			this->txtUziAmmo->Name = L"txtUziAmmo";
			this->txtUziAmmo->Size = System::Drawing::Size(42, 20);
			this->txtUziAmmo->TabIndex = 15;
			this->txtUziAmmo->Text = L"0";
			this->txtUziAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtUziAmmo_KeyPress);
			// 
			// txtHkAmmo
			// 
			this->txtHkAmmo->Location = System::Drawing::Point(158, 116);
			this->txtHkAmmo->Name = L"txtHkAmmo";
			this->txtHkAmmo->Size = System::Drawing::Size(42, 20);
			this->txtHkAmmo->TabIndex = 17;
			this->txtHkAmmo->Text = L"0";
			this->txtHkAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtHkAmmo_KeyPress);
			// 
			// txtShotgunWideshotAmmo
			// 
			this->txtShotgunWideshotAmmo->Location = System::Drawing::Point(206, 160);
			this->txtShotgunWideshotAmmo->Name = L"txtShotgunWideshotAmmo";
			this->txtShotgunWideshotAmmo->Size = System::Drawing::Size(42, 20);
			this->txtShotgunWideshotAmmo->TabIndex = 19;
			this->txtShotgunWideshotAmmo->Text = L"0";
			this->txtShotgunWideshotAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtShotgunWideshotAmmo_KeyPress);
			// 
			// txtShotgunNormalAmmo
			// 
			this->txtShotgunNormalAmmo->Location = System::Drawing::Point(158, 160);
			this->txtShotgunNormalAmmo->Name = L"txtShotgunNormalAmmo";
			this->txtShotgunNormalAmmo->Size = System::Drawing::Size(42, 20);
			this->txtShotgunNormalAmmo->TabIndex = 20;
			this->txtShotgunNormalAmmo->Text = L"0";
			this->txtShotgunNormalAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtShotgunNormalAmmo_KeyPress);
			// 
			// txtNumFlares
			// 
			this->txtNumFlares->Location = System::Drawing::Point(169, 76);
			this->txtNumFlares->Name = L"txtNumFlares";
			this->txtNumFlares->Size = System::Drawing::Size(42, 20);
			this->txtNumFlares->TabIndex = 23;
			this->txtNumFlares->Text = L"0";
			this->txtNumFlares->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtNumFlares_KeyPress);
			// 
			// lblFlares
			// 
			this->lblFlares->AutoSize = true;
			this->lblFlares->Location = System::Drawing::Point(18, 75);
			this->lblFlares->Name = L"lblFlares";
			this->lblFlares->Size = System::Drawing::Size(38, 13);
			this->lblFlares->TabIndex = 24;
			this->lblFlares->Text = L"Flares:";
			// 
			// grpLevel
			// 
			this->grpLevel->Controls->Add(this->txtNumSecrets);
			this->grpLevel->Controls->Add(this->lblSecrets);
			this->grpLevel->Controls->Add(this->txtNumSaves);
			this->grpLevel->Controls->Add(this->lblSaveNumber);
			this->grpLevel->Controls->Add(this->txtLvlName);
			this->grpLevel->Controls->Add(this->lblLvlName);
			this->grpLevel->Location = System::Drawing::Point(9, 42);
			this->grpLevel->Name = L"grpLevel";
			this->grpLevel->Size = System::Drawing::Size(493, 51);
			this->grpLevel->TabIndex = 26;
			this->grpLevel->TabStop = false;
			this->grpLevel->Text = L"Level";
			// 
			// grpItems
			// 
			this->grpItems->Controls->Add(this->lblFlares);
			this->grpItems->Controls->Add(this->txtSmallMedipacks);
			this->grpItems->Controls->Add(this->txtNumFlares);
			this->grpItems->Controls->Add(this->lblSmallMedipacks);
			this->grpItems->Controls->Add(this->txtLargeMedipacks);
			this->grpItems->Controls->Add(this->lblLargeMedipacks);
			this->grpItems->Location = System::Drawing::Point(9, 101);
			this->grpItems->Name = L"grpItems";
			this->grpItems->Size = System::Drawing::Size(224, 114);
			this->grpItems->TabIndex = 27;
			this->grpItems->TabStop = false;
			this->grpItems->Text = L"Items";
			// 
			// btnSave
			// 
			this->btnSave->Enabled = false;
			this->btnSave->Location = System::Drawing::Point(427, 12);
			this->btnSave->Name = L"btnSave";
			this->btnSave->Size = System::Drawing::Size(75, 23);
			this->btnSave->TabIndex = 28;
			this->btnSave->Text = L"Save";
			this->btnSave->UseVisualStyleBackColor = true;
			this->btnSave->Click += gcnew System::EventHandler(this, &SaveEditUI::btnSave_Click);
			// 
			// grpWeapons
			// 
			this->grpWeapons->Controls->Add(this->chkPistols);
			this->grpWeapons->Controls->Add(this->txtGrapplingGunAmmo);
			this->grpWeapons->Controls->Add(this->chkGrapplingGun);
			this->grpWeapons->Controls->Add(this->chkShotgun);
			this->grpWeapons->Controls->Add(this->chkCrowbar);
			this->grpWeapons->Controls->Add(this->chkHkGun);
			this->grpWeapons->Controls->Add(this->chkUzi);
			this->grpWeapons->Controls->Add(this->chkRevolverOrDeagle);
			this->grpWeapons->Controls->Add(this->txtShotgunNormalAmmo);
			this->grpWeapons->Controls->Add(this->txtShotgunWideshotAmmo);
			this->grpWeapons->Controls->Add(this->txtRevolverOrDeagleAmmo);
			this->grpWeapons->Controls->Add(this->txtHkAmmo);
			this->grpWeapons->Controls->Add(this->txtUziAmmo);
			this->grpWeapons->Location = System::Drawing::Point(239, 101);
			this->grpWeapons->Name = L"grpWeapons";
			this->grpWeapons->Size = System::Drawing::Size(263, 190);
			this->grpWeapons->TabIndex = 29;
			this->grpWeapons->TabStop = false;
			this->grpWeapons->Text = L"Weapons";
			// 
			// chkPistols
			// 
			this->chkPistols->AutoSize = true;
			this->chkPistols->Location = System::Drawing::Point(10, 48);
			this->chkPistols->Name = L"chkPistols";
			this->chkPistols->Size = System::Drawing::Size(56, 17);
			this->chkPistols->TabIndex = 23;
			this->chkPistols->Text = L"Pistols";
			this->chkPistols->UseVisualStyleBackColor = true;
			// 
			// txtGrapplingGunAmmo
			// 
			this->txtGrapplingGunAmmo->Location = System::Drawing::Point(158, 138);
			this->txtGrapplingGunAmmo->Name = L"txtGrapplingGunAmmo";
			this->txtGrapplingGunAmmo->Size = System::Drawing::Size(42, 20);
			this->txtGrapplingGunAmmo->TabIndex = 22;
			this->txtGrapplingGunAmmo->Text = L"0";
			this->txtGrapplingGunAmmo->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SaveEditUI::txtGrapplingGunAmmo_KeyPress);
			// 
			// chkGrapplingGun
			// 
			this->chkGrapplingGun->AutoSize = true;
			this->chkGrapplingGun->Location = System::Drawing::Point(10, 140);
			this->chkGrapplingGun->Name = L"chkGrapplingGun";
			this->chkGrapplingGun->Size = System::Drawing::Size(97, 17);
			this->chkGrapplingGun->TabIndex = 4;
			this->chkGrapplingGun->Text = L"Grappling Gun:";
			this->chkGrapplingGun->UseVisualStyleBackColor = true;
			// 
			// chkShotgun
			// 
			this->chkShotgun->AutoSize = true;
			this->chkShotgun->Location = System::Drawing::Point(10, 163);
			this->chkShotgun->Name = L"chkShotgun";
			this->chkShotgun->Size = System::Drawing::Size(69, 17);
			this->chkShotgun->TabIndex = 3;
			this->chkShotgun->Text = L"Shotgun:";
			this->chkShotgun->UseVisualStyleBackColor = true;
			// 
			// chkCrowbar
			// 
			this->chkCrowbar->AutoSize = true;
			this->chkCrowbar->Location = System::Drawing::Point(10, 25);
			this->chkCrowbar->Name = L"chkCrowbar";
			this->chkCrowbar->Size = System::Drawing::Size(65, 17);
			this->chkCrowbar->TabIndex = 21;
			this->chkCrowbar->Text = L"Crowbar";
			this->chkCrowbar->UseVisualStyleBackColor = true;
			// 
			// chkHkGun
			// 
			this->chkHkGun->AutoSize = true;
			this->chkHkGun->Location = System::Drawing::Point(10, 117);
			this->chkHkGun->Name = L"chkHkGun";
			this->chkHkGun->Size = System::Drawing::Size(67, 17);
			this->chkHkGun->TabIndex = 2;
			this->chkHkGun->Text = L"HK Gun:";
			this->chkHkGun->UseVisualStyleBackColor = true;
			// 
			// chkUzi
			// 
			this->chkUzi->AutoSize = true;
			this->chkUzi->Location = System::Drawing::Point(10, 94);
			this->chkUzi->Name = L"chkUzi";
			this->chkUzi->Size = System::Drawing::Size(44, 17);
			this->chkUzi->TabIndex = 1;
			this->chkUzi->Text = L"Uzi:";
			this->chkUzi->UseVisualStyleBackColor = true;
			// 
			// chkRevolverOrDeagle
			// 
			this->chkRevolverOrDeagle->AutoSize = true;
			this->chkRevolverOrDeagle->Location = System::Drawing::Point(10, 71);
			this->chkRevolverOrDeagle->Name = L"chkRevolverOrDeagle";
			this->chkRevolverOrDeagle->Size = System::Drawing::Size(111, 17);
			this->chkRevolverOrDeagle->TabIndex = 0;
			this->chkRevolverOrDeagle->Text = L"Revolver/Deagle:";
			this->chkRevolverOrDeagle->UseVisualStyleBackColor = true;
			// 
			// grpHealth
			// 
			this->grpHealth->Controls->Add(this->lblHealthError);
			this->grpHealth->Controls->Add(this->lblHealth);
			this->grpHealth->Controls->Add(this->trbHealth);
			this->grpHealth->Location = System::Drawing::Point(9, 221);
			this->grpHealth->Name = L"grpHealth";
			this->grpHealth->Size = System::Drawing::Size(224, 70);
			this->grpHealth->TabIndex = 31;
			this->grpHealth->TabStop = false;
			this->grpHealth->Text = L"Health";
			// 
			// lblHealthError
			// 
			this->lblHealthError->AutoSize = true;
			this->lblHealthError->ForeColor = System::Drawing::SystemColors::ControlText;
			this->lblHealthError->Location = System::Drawing::Point(34, 50);
			this->lblHealthError->Name = L"lblHealthError";
			this->lblHealthError->Size = System::Drawing::Size(136, 13);
			this->lblHealthError->TabIndex = 32;
			this->lblHealthError->Text = L"Unable to find health bytes.";
			this->lblHealthError->Visible = false;
			// 
			// lblHealth
			// 
			this->lblHealth->AutoSize = true;
			this->lblHealth->Location = System::Drawing::Point(181, 24);
			this->lblHealth->Name = L"lblHealth";
			this->lblHealth->Size = System::Drawing::Size(30, 13);
			this->lblHealth->TabIndex = 1;
			this->lblHealth->Text = L"0.0%";
			// 
			// trbHealth
			// 
			this->trbHealth->Location = System::Drawing::Point(6, 20);
			this->trbHealth->Maximum = 100;
			this->trbHealth->Name = L"trbHealth";
			this->trbHealth->Size = System::Drawing::Size(179, 45);
			this->trbHealth->TabIndex = 0;
			this->trbHealth->Scroll += gcnew System::EventHandler(this, &SaveEditUI::trbHealth_Scroll);
			// 
			// ssrStatusStrip
			// 
			this->ssrStatusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->slblStatus });
			this->ssrStatusStrip->Location = System::Drawing::Point(0, 299);
			this->ssrStatusStrip->Name = L"ssrStatusStrip";
			this->ssrStatusStrip->Size = System::Drawing::Size(508, 22);
			this->ssrStatusStrip->SizingGrip = false;
			this->ssrStatusStrip->TabIndex = 32;
			this->ssrStatusStrip->Text = L"statusStrip";
			// 
			// slblStatus
			// 
			this->slblStatus->Name = L"slblStatus";
			this->slblStatus->Size = System::Drawing::Size(0, 17);
			// 
			// SaveEditUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(508, 321);
			this->Controls->Add(this->ssrStatusStrip);
			this->Controls->Add(this->grpHealth);
			this->Controls->Add(this->grpWeapons);
			this->Controls->Add(this->btnSave);
			this->Controls->Add(this->btnBrowse);
			this->Controls->Add(this->txtFilePath);
			this->Controls->Add(this->lblFile);
			this->Controls->Add(this->grpLevel);
			this->Controls->Add(this->grpItems);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"SaveEditUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Tomb Raider: Chronicles - Savegame Editor";
			this->grpLevel->ResumeLayout(false);
			this->grpLevel->PerformLayout();
			this->grpItems->ResumeLayout(false);
			this->grpItems->PerformLayout();
			this->grpWeapons->ResumeLayout(false);
			this->grpWeapons->PerformLayout();
			this->grpHealth->ResumeLayout(false);
			this->grpHealth->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trbHealth))->EndInit();
			this->ssrStatusStrip->ResumeLayout(false);
			this->ssrStatusStrip->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnBrowse_Click(System::Object^ sender, System::EventArgs^ e) {
		Stream^ myStream;
		OpenFileDialog^ openFileDialog1 = gcnew OpenFileDialog;

		openFileDialog1->InitialDirectory = "c:\\";
		openFileDialog1->Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
		openFileDialog1->FilterIndex = 2;
		openFileDialog1->RestoreDirectory = true;

		if (openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			if ((myStream = openFileDialog1->OpenFile()) != nullptr)
			{
				SetSaveFileName(openFileDialog1->FileName);
				txtFilePath->Clear();
				txtFilePath->AppendText(GetSaveFileName());
				myStream->Close();

				DisplayLvlName();
				SetLvlParams();
				DisplayNumSmallMedipacks();
				DisplayNumLargeMedipacks();
				DisplayNumSecrets();
				DisplayRevolverOrDeagleAmmo();
				DisplaySaveNum();
				DisplayUziAmmo();
				DisplayHKAmmo();
				DisplayShotgunNormalAmmo();
				DisplayShotgunWideshotAmmo();
				DisplayNumFlares();
				DisplayGrapplingGunAmmo();
				DisplayWeaponsInfo();
				DisplayHealthValue();

				btnSave->Enabled = true;

				slblStatus->Text = "Loaded save file: " + openFileDialog1->SafeFileName;
			}
		}
	}
	private: System::Void btnSave_Click(System::Object^ sender, System::EventArgs^ e) {
		// Adjust invalid entries
		if (txtSmallMedipacks->Text == "") txtSmallMedipacks->Text = "0";
		if (txtLargeMedipacks->Text == "") txtLargeMedipacks->Text = "0";
		if (txtNumFlares->Text == "") txtNumFlares->Text = "0";
		if (txtNumSaves->Text == "") txtNumSaves->Text = "0";
		if (txtNumSecrets->Text == "") txtNumSecrets->Text = "0";
		if (txtRevolverOrDeagleAmmo->Text == "") txtRevolverOrDeagleAmmo->Text = "0";
		if (txtUziAmmo->Text == "") txtUziAmmo->Text = "0";
		if (txtHkAmmo->Text == "") txtHkAmmo->Text = "0";
		if (txtGrapplingGunAmmo->Text == "") txtGrapplingGunAmmo->Text = "0";
		if (txtShotgunNormalAmmo->Text == "") txtShotgunNormalAmmo->Text = "0";
		if (txtShotgunWideshotAmmo->Text == "") txtShotgunWideshotAmmo->Text = "0";

		// Parse new values
		int newSmallMedipackVal = int::Parse(txtSmallMedipacks->Text);
		int newLargeMedipackVal = int::Parse(txtLargeMedipacks->Text);
		int newFlaresVal = int::Parse(txtNumFlares->Text);
		int newSaveNumVal = int::Parse(txtNumSaves->Text);
		int newSecretsVal = int::Parse(txtNumSecrets->Text);
		double newHealthPercentage = (double)trbHealth->Value;
		int newRevolverOrDeagleAmmoVal = int::Parse(txtRevolverOrDeagleAmmo->Text);
		int newUziAmmoVal = int::Parse(txtUziAmmo->Text);
		int newHkAmmoVal = int::Parse(txtHkAmmo->Text);
		int newGrapplingGunVal = int::Parse(txtGrapplingGunAmmo->Text);
		int newShotgunNormalAmmoVal = int::Parse(txtShotgunNormalAmmo->Text);
		int newShotgunWideshotAmmoVal = int::Parse(txtShotgunWideshotAmmo->Text);

		if (newSmallMedipackVal > 65535)
		{
			txtSmallMedipacks->Text = "65535";
			newSmallMedipackVal = 65535;
		}

		if (newLargeMedipackVal > 65535)
		{
			txtLargeMedipacks->Text = "65535";
			newLargeMedipackVal = 65535;
		}

		if (newFlaresVal > 65535)
		{
			txtNumFlares->Text = "65535";
			newFlaresVal = 65535;
		}

		if (newSaveNumVal > 65535)
		{
			txtNumSaves->Text = "65535";
			newSaveNumVal = 65535;
		}

		if (newSecretsVal > 36)
		{
			txtNumSecrets->Text = "36";
			newSecretsVal = 36;
		}

		if (newRevolverOrDeagleAmmoVal > 65535)
		{
			txtRevolverOrDeagleAmmo->Text = "65535";
			newRevolverOrDeagleAmmoVal = 65535;
		}

		if (newUziAmmoVal > 65535)
		{
			txtUziAmmo->Text = "65535";
			newUziAmmoVal = 65535;
		}

		if (newHkAmmoVal > 65535)
		{
			txtHkAmmo->Text = "65535";
			newHkAmmoVal = 65535;
		}

		if (newGrapplingGunVal > 65535)
		{
			txtGrapplingGunAmmo->Text = "65535";
			newGrapplingGunVal = 65535;
		}

		if (newShotgunNormalAmmoVal > 10922)
		{
			txtShotgunNormalAmmo->Text = "10922";
			newShotgunNormalAmmoVal = 10922;
		}

		if (newShotgunWideshotAmmoVal > 10922)
		{
			txtShotgunWideshotAmmo->Text = "10922";
			newShotgunWideshotAmmoVal = 10922;
		}

		WriteUInt16(hkAmmoOffset, newHkAmmoVal);
		WriteUInt16(smallMedipackOffset, newSmallMedipackVal);
		WriteUInt16(largeMedipackOffset, newLargeMedipackVal);
		WriteUInt16(saveNumOffset, newSaveNumVal);
		WriteUInt16(numFlaresOffset, newFlaresVal);
		WriteUInt16(revolverOrDeagleAmmoOffset, newRevolverOrDeagleAmmoVal);
		WriteUInt16(uziAmmoOffset, newUziAmmoVal);
		WriteUInt16(shotgunNormalAmmoOffset, newShotgunNormalAmmoVal * 6);
		WriteUInt16(shotgunWideshotAmmoOffset, newShotgunWideshotAmmoVal * 6);
		WriteUInt16(grapplingGunAmmoOffset, newGrapplingGunVal);
		WriteByte(numSecretsOffset, newSecretsVal);

		if (chkUzi->Enabled && chkUzi->Checked) WriteByte(uziOffset, 0x9);
		else WriteByte(uziOffset, 0);

		if (chkRevolverOrDeagle->Enabled && chkRevolverOrDeagle->Checked) WriteByte(revolverOrDeagleOffset, 0xD);
		else WriteByte(revolverOrDeagleOffset, 0);

		if (chkShotgun->Enabled && chkShotgun->Checked) WriteByte(shotgunOffset, 0x9);
		else WriteByte(shotgunOffset, 0);

		if (chkGrapplingGun->Enabled && chkGrapplingGun->Checked) WriteByte(grapplingGunOffset, 0xD);
		else WriteByte(grapplingGunOffset, 0);

		if (chkHkGun->Enabled && chkHkGun->Checked) WriteByte(hkOffset, 0x9);
		else WriteByte(hkOffset, 0);

		if (chkPistols->Enabled && chkPistols->Checked) WriteByte(pistolsOffset, 0x9);
		else WriteByte(pistolsOffset, 0);

		if (chkCrowbar->Enabled && chkCrowbar->Checked) WriteByte(crowbarOffset, 0x9);
		else WriteByte(crowbarOffset, 0);

		healthOffset = GetHealthOffset();
		int newHealth = (int)(newHealthPercentage / 100.0 * MAX_HEALTH_VALUE);
		if (healthOffset != -1) WriteUInt16(healthOffset, newHealth);

		MessageBox::Show("Save file patched!", "Success", MessageBoxButtons::OK, MessageBoxIcon::Information);

		slblStatus->Text = "Patched save file!";
	}
	private: System::Void trbHealth_Scroll(System::Object^ sender, System::EventArgs^ e) {
		double healthPercentage = (double)trbHealth->Value;
		lblHealth->Text = healthPercentage.ToString("0.0") + "%";
	}
	private: System::Void txtNumSaves_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtNumSecrets_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtSmallMedipacks_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtLargeMedipacks_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtNumFlares_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtRevolverOrDeagleAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtUziAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtHkAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtGrapplingGunAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtShotgunNormalAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	private: System::Void txtShotgunWideshotAmmo_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsControl(e->KeyChar) && !Char::IsDigit(e->KeyChar))
		{
			e->Handled = true;
		}
	}
	};
}
