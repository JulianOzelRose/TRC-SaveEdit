/*
	Julian O. Rose
	TRC-SaveEditUI.h
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
		String^ ssSavefileName;
		String^ ssLvlName;
		String^ saveFileName;
		// Offsets
		const int saveNumOffset = 0x04B;
		const int pistolsOffset = 0x16F;
		const int uziOffset = 0x170;
		const int shotgunOffset = 0x171;
		const int grapplingGunOffset = 0x172;
		const int hkOffset = 0x173;
		const int revolverOffset = 0x174;
		const int crowbarOffset = 0x178;
		const int smallMedipackOffset = 0x194;
		const int lrgMedipackOffset = 0x196;
		const int numFlaresOffset = 0x198;
		const int uziAmmoOffset = 0x19C;
		const int revolverAmmoOffset = 0x19E;
		const int shotgunNormalAmmoOffset = 0x1A0;
		const int shotgunWideshotAmmoOffset = 0x1A2;
		const int hkAmmoOffset = 0x1A4;
		const int grapplingGunAmmoOffset = 0x1A6;
		const int numSecretsOffset = 0x1C3;
		// Health
		int healthOffset = -1;
		int MIN_HEALTH_OFFSET = 0;
		int MAX_HEALTH_OFFSET = 1;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::TrackBar^ healthBar;
	private: System::Windows::Forms::Label^ healthLabel;
	private: System::Windows::Forms::Label^ healthErrorLabel;

	private: System::Windows::Forms::CheckBox^ pistolsCheckBox;
	public:
		SaveEditUI(void)
		{
			InitializeComponent();

			numSavesTxtBox->Enabled = false;
			numSecretsTxtBox->Enabled = false;
			smallMedipacksTxtBox->Enabled = false;
			lrgMedipacksTxtBox->Enabled = false;
			revolverCheckBox->Enabled = false;
			revolverAmmoTxtBox->Enabled = false;
			uziCheckBox->Enabled = false;
			uziAmmoTxtBox->Enabled = false;
			shotgunCheckBox->Enabled = false;
			shotgunNormalAmmoTxtBox->Enabled = false;
			shotgunWideshotAmmoTxtBox->Enabled = false;
			grapplingGunCheckBox->Enabled = false;
			grapplingGunAmmoTxtBox->Enabled = false;
			hkCheckBox->Enabled = false;
			hkAmmoTxtBox->Enabled = false;
			crowbarCheckBox->Enabled = false;
			pistolsCheckBox->Enabled = false;
			numFlaresTxtBox->Enabled = false;
			healthBar->Enabled = false;
			healthErrorLabel->Visible = false;
			healthLabel->Visible = true;
		}

		void SetSaveFileName(String^ fileName)
		{
			ssSavefileName = fileName;
		}

		String^ GetSaveFileName()
		{
			return ssSavefileName;
		}

		int GetSaveFileData(int offset)
		{
			std::fstream saveFile(marshal_as<std::string>(GetSaveFileName()), std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekp(offset);
			int iData = saveFile.get();
			saveFile.close();
			return iData;
		}

		void WriteToSaveFile(int offset, int value)
		{
			std::fstream saveFile(marshal_as<std::string>(GetSaveFileName()), std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekg(offset, std::ios::beg);
			char cData[1] = { value };
			saveFile.write(cData, sizeof(cData));
			saveFile.close();
		}

		void WriteValue(int offset, int value)
		{
			if (value > 255)
			{
				int firstHalf = value / 256;
				int secondHalf = value % 256;

				WriteToSaveFile(offset + 1, firstHalf);
				WriteToSaveFile(offset, secondHalf);
			}
			else
			{
				WriteToSaveFile(offset, value);
				WriteToSaveFile(offset + 1, 0);
			}
		}

		int GetValue(int offset)
		{
			int value = 0;

			if (GetSaveFileData(offset + 1) == 0)
			{
				value = GetSaveFileData(offset);
			}
			else
			{
				int firstHalf = GetSaveFileData(offset + 1);
				int secondHalf = GetSaveFileData(offset);
				value = firstHalf * 256 + secondHalf;
			}

			return value;
		}

		void GetLvlName()
		{
			std::ifstream saveFile(marshal_as<std::string>(GetSaveFileName()));
			std::string sData;

			if (saveFile.good()) getline(saveFile, sData);

			saveFile.close();

			ssLvlName = gcnew String(sData.c_str());

			lvlNameTxtBox->Clear();
			lvlNameTxtBox->AppendText(ssLvlName);
		}

		void GetNumSecrets()
		{
			int numSecrets = GetSaveFileData(numSecretsOffset);

			numSecretsTxtBox->Clear();
			numSecretsTxtBox->AppendText(numSecrets.ToString());
		}

		void GetSaveNum()
		{
			int saveNum = GetValue(saveNumOffset);

			numSavesTxtBox->Clear();
			numSavesTxtBox->AppendText(saveNum.ToString());
		}

		void GetNumFlares()
		{
			int numFlares = GetValue(numFlaresOffset);

			numFlaresTxtBox->Clear();
			numFlaresTxtBox->AppendText(numFlares.ToString());
		}

		void GetNumSmallMedipacks()
		{
			int numSmallMedipacks = GetValue(smallMedipackOffset);

			smallMedipacksTxtBox->Clear();
			smallMedipacksTxtBox->AppendText(numSmallMedipacks.ToString());
		}

		void GetNumLrgMedipacks()
		{
			int numLrgMedipacks = GetValue(lrgMedipackOffset);

			lrgMedipacksTxtBox->Clear();
			lrgMedipacksTxtBox->AppendText(numLrgMedipacks.ToString());
		}

		void GetShotgunNormalAmmo()
		{
			int shotgunNormalAmmo = GetValue(shotgunNormalAmmoOffset);

			shotgunNormalAmmoTxtBox->Clear();
			shotgunNormalAmmoTxtBox->AppendText((shotgunNormalAmmo / 6).ToString());
		}

		void GetShotgunWideshotAmmo()
		{
			int shotgunWideshotAmmo = GetValue(shotgunWideshotAmmoOffset);

			shotgunWideshotAmmoTxtBox->Clear();
			shotgunWideshotAmmoTxtBox->AppendText((shotgunWideshotAmmo / 6).ToString());
		}

		void GetUziAmmo()
		{
			int uziAmmo = GetValue(uziAmmoOffset);

			uziAmmoTxtBox->Clear();
			uziAmmoTxtBox->AppendText(uziAmmo.ToString());
		}

		void GetHKAmmo()
		{
			int hkAmmo = GetValue(hkAmmoOffset);

			hkAmmoTxtBox->Clear();
			hkAmmoTxtBox->AppendText(hkAmmo.ToString());
		}

		void GetGrapplingGunAmmo()
		{
			int grapplingGunAmmo = GetValue(grapplingGunAmmoOffset);

			grapplingGunAmmoTxtBox->Clear();
			grapplingGunAmmoTxtBox->AppendText(grapplingGunAmmo.ToString());
		}

		void GetRevolverAmmo()
		{
			int revolverAmmo = GetValue(revolverAmmoOffset);

			revolverAmmoTxtBox->Clear();
			revolverAmmoTxtBox->AppendText(revolverAmmo.ToString());
		}

		bool IsKnownByteFlagPattern(int byteFlag1, int byteFlag2)
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
			if (byteFlag1 == 0x12 && byteFlag2 == 0x12) return true;	// Swimming (with suit)
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
				int byteFlag1 = GetSaveFileData(offset - 7);
				int byteFlag2 = GetSaveFileData(offset - 6);

				if (IsKnownByteFlagPattern(byteFlag1, byteFlag2))
				{
					int healthValue = GetValue(offset);

					if (healthValue > 0 && healthValue <= 1000)
					{
						return offset;
					}
				}
			}

			return -1;
		}

		void GetHealthValue()
		{
			const int maxHealth = 1000;
			healthOffset = GetHealthOffset();
			int health = GetValue(healthOffset);

			if (healthOffset == -1)
			{
				healthBar->Enabled = false;
				healthErrorLabel->Visible = true;
				healthBar->Value = 0;
				healthLabel->Visible = false;
			}
			else
			{
				healthBar->Enabled = true;
				double healthPercentage = static_cast<double>(health) / maxHealth * 100.0;
				healthBar->Value = static_cast<int>(std::round(healthPercentage));
				healthLabel->Visible = true;
				healthLabel->Text = healthPercentage.ToString("0.0") + "%";
			}
		}

		void GetLvlInfo()
		{
			if (ssLvlName == "Streets of Rome")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x4F4;
				MAX_HEALTH_OFFSET = 0x4F8;
			}

			else if (ssLvlName == "Trajan`s markets")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x542;
				MAX_HEALTH_OFFSET = 0x5D7;
			}

			else if (ssLvlName == "The Colosseum")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = true;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x4D2;
				MAX_HEALTH_OFFSET = 0x7FF;
			}

			else if (ssLvlName == "The base")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = true;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x556;
				MAX_HEALTH_OFFSET = 0x707;
			}

			else if (ssLvlName == "The submarine")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x520;
				MAX_HEALTH_OFFSET = 0x59A;
			}

			else if (ssLvlName == "Deepsea dive")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x644;
				MAX_HEALTH_OFFSET = 0x6DE;
			}

			else if (ssLvlName == "Sinking submarine")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = true;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x5D2;
				MAX_HEALTH_OFFSET = 0x66B;
			}

			else if (ssLvlName == "Gallows tree")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x4F0;
				MAX_HEALTH_OFFSET = 0x52D;
			}

			else if (ssLvlName == "Labyrinth")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x538;
				MAX_HEALTH_OFFSET = 0x61A;
			}

			else if (ssLvlName == "Old mill")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x512;
				MAX_HEALTH_OFFSET = 0x624;
			}

			else if (ssLvlName == "The 13th floor")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = true;
				hkAmmoTxtBox->Enabled = true;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x52A;
				MAX_HEALTH_OFFSET = 0x53A;
			}

			else if (ssLvlName == "Escape with the iris")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = true;
				hkAmmoTxtBox->Enabled = true;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x6F6;
				MAX_HEALTH_OFFSET = 0xC20;
			}

			else if (ssLvlName == "Red alert!")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = false;
				uziAmmoTxtBox->Enabled = false;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = true;
				grapplingGunAmmoTxtBox->Enabled = true;
				hkCheckBox->Enabled = true;
				hkAmmoTxtBox->Enabled = true;
				crowbarCheckBox->Enabled = false;
				pistolsCheckBox->Enabled = false;
				numFlaresTxtBox->Enabled = false;
				MIN_HEALTH_OFFSET = 0x52E;
				MAX_HEALTH_OFFSET = 0x58A;
			}

			else
			{
				// For custom levels, health offset range here is a vague estimate
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
				uziCheckBox->Enabled = true;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = true;
				shotgunNormalAmmoTxtBox->Enabled = true;
				shotgunWideshotAmmoTxtBox->Enabled = true;
				grapplingGunCheckBox->Enabled = true;
				grapplingGunAmmoTxtBox->Enabled = true;
				hkCheckBox->Enabled = true;
				hkAmmoTxtBox->Enabled = true;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
				numFlaresTxtBox->Enabled = true;
				MIN_HEALTH_OFFSET = 0x4F0;
				MAX_HEALTH_OFFSET = 0x6FF;
			}
		}

		void GetWeaponsInfo()
		{
			int uziVal = GetSaveFileData(uziOffset);
			int shotgunVal = GetSaveFileData(shotgunOffset);
			int grapplingGunVal = GetSaveFileData(grapplingGunOffset);
			int hkVal = GetSaveFileData(hkOffset);
			int revolverVal = GetSaveFileData(revolverOffset);
			int crowbarVal = GetSaveFileData(crowbarOffset);
			int pistolsVal = GetSaveFileData(pistolsOffset);

			if (uziVal == 0x9) uziCheckBox->Checked = true;
			else uziCheckBox->Checked = false;

			if (shotgunVal == 0x9) shotgunCheckBox->Checked = true;
			else shotgunCheckBox->Checked = false;

			if (grapplingGunVal == 0xD) grapplingGunCheckBox->Checked = true;
			else grapplingGunCheckBox->Checked = false;

			if (hkVal == 0x9 || hkVal == 0xD) hkCheckBox->Checked = true;
			else hkCheckBox->Checked = false;

			if (revolverVal == 0x9 || revolverVal == 0xD) revolverCheckBox->Checked = true;
			else revolverCheckBox->Checked = false;

			if (crowbarVal == 0x9 || crowbarVal == 0x1) crowbarCheckBox->Checked = true;
			else crowbarCheckBox->Checked = false;

			if (pistolsVal == 0x9) pistolsCheckBox->Checked = true;
			else pistolsCheckBox->Checked = false;
		}

	private: System::Windows::Forms::TextBox^ smallMedipacksTxtBox;
	public:
	public:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ lrgMedipacksTxtBox;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ numSecretsTxtBox;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ revolverAmmoTxtBox;
	private: System::Windows::Forms::TextBox^ numSavesTxtBox;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ uziAmmoTxtBox;
	private: System::Windows::Forms::TextBox^ hkAmmoTxtBox;
	private: System::Windows::Forms::TextBox^ shotgunWideshotAmmoTxtBox;
	private: System::Windows::Forms::TextBox^ shotgunNormalAmmoTxtBox;
	private: System::Windows::Forms::TextBox^ numFlaresTxtBox;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::Button^ saveButton;

	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::CheckBox^ revolverCheckBox;
	private: System::Windows::Forms::CheckBox^ shotgunCheckBox;
	private: System::Windows::Forms::CheckBox^ hkCheckBox;
	private: System::Windows::Forms::CheckBox^ uziCheckBox;
	private: System::Windows::Forms::CheckBox^ grapplingGunCheckBox;
	private: System::Windows::Forms::TextBox^ consoleTxtBox;
	private: System::Windows::Forms::CheckBox^ crowbarCheckBox;
	private: System::Windows::Forms::TextBox^ grapplingGunAmmoTxtBox;

	protected:
		~SaveEditUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ fileTxtBox;
	private: System::Windows::Forms::TextBox^ lvlNameTxtBox;
	private: System::Windows::Forms::Button^ browseButton;





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
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->fileTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->lvlNameTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->browseButton = (gcnew System::Windows::Forms::Button());
			this->smallMedipacksTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->lrgMedipacksTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->numSecretsTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->revolverAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->numSavesTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->uziAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->hkAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->shotgunWideshotAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->shotgunNormalAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->numFlaresTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->saveButton = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->pistolsCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->grapplingGunAmmoTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->grapplingGunCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->shotgunCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->crowbarCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->hkCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->uziCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->revolverCheckBox = (gcnew System::Windows::Forms::CheckBox());
			this->consoleTxtBox = (gcnew System::Windows::Forms::TextBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->healthErrorLabel = (gcnew System::Windows::Forms::Label());
			this->healthLabel = (gcnew System::Windows::Forms::Label());
			this->healthBar = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->healthBar))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(11, 17);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(26, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"File:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(15, 22);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(38, 13);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Name:";
			// 
			// fileTxtBox
			// 
			this->fileTxtBox->Location = System::Drawing::Point(37, 14);
			this->fileTxtBox->Name = L"fileTxtBox";
			this->fileTxtBox->ReadOnly = true;
			this->fileTxtBox->Size = System::Drawing::Size(307, 20);
			this->fileTxtBox->TabIndex = 2;
			// 
			// lvlNameTxtBox
			// 
			this->lvlNameTxtBox->Location = System::Drawing::Point(57, 19);
			this->lvlNameTxtBox->Name = L"lvlNameTxtBox";
			this->lvlNameTxtBox->ReadOnly = true;
			this->lvlNameTxtBox->Size = System::Drawing::Size(161, 20);
			this->lvlNameTxtBox->TabIndex = 3;
			this->lvlNameTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// browseButton
			// 
			this->browseButton->Location = System::Drawing::Point(349, 12);
			this->browseButton->Name = L"browseButton";
			this->browseButton->Size = System::Drawing::Size(75, 23);
			this->browseButton->TabIndex = 4;
			this->browseButton->Text = L"Browse";
			this->browseButton->UseVisualStyleBackColor = true;
			this->browseButton->Click += gcnew System::EventHandler(this, &SaveEditUI::browseButton_Click);
			// 
			// smallMedipacksTxtBox
			// 
			this->smallMedipacksTxtBox->Location = System::Drawing::Point(176, 25);
			this->smallMedipacksTxtBox->Name = L"smallMedipacksTxtBox";
			this->smallMedipacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->smallMedipacksTxtBox->TabIndex = 5;
			this->smallMedipacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 28);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Small Medipacks:";
			// 
			// lrgMedipacksTxtBox
			// 
			this->lrgMedipacksTxtBox->Location = System::Drawing::Point(176, 50);
			this->lrgMedipacksTxtBox->Name = L"lrgMedipacksTxtBox";
			this->lrgMedipacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->lrgMedipacksTxtBox->TabIndex = 7;
			this->lrgMedipacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(18, 52);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(92, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Large Medipacks:";
			// 
			// numSecretsTxtBox
			// 
			this->numSecretsTxtBox->Location = System::Drawing::Point(445, 19);
			this->numSecretsTxtBox->Name = L"numSecretsTxtBox";
			this->numSecretsTxtBox->Size = System::Drawing::Size(42, 20);
			this->numSecretsTxtBox->TabIndex = 9;
			this->numSecretsTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(393, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(46, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Secrets:";
			// 
			// revolverAmmoTxtBox
			// 
			this->revolverAmmoTxtBox->Location = System::Drawing::Point(122, 72);
			this->revolverAmmoTxtBox->Name = L"revolverAmmoTxtBox";
			this->revolverAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->revolverAmmoTxtBox->TabIndex = 11;
			this->revolverAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// numSavesTxtBox
			// 
			this->numSavesTxtBox->Location = System::Drawing::Point(323, 19);
			this->numSavesTxtBox->Name = L"numSavesTxtBox";
			this->numSavesTxtBox->Size = System::Drawing::Size(42, 20);
			this->numSavesTxtBox->TabIndex = 13;
			this->numSavesTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(244, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(75, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Save Number:";
			// 
			// uziAmmoTxtBox
			// 
			this->uziAmmoTxtBox->Location = System::Drawing::Point(122, 94);
			this->uziAmmoTxtBox->Name = L"uziAmmoTxtBox";
			this->uziAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->uziAmmoTxtBox->TabIndex = 15;
			this->uziAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// hkAmmoTxtBox
			// 
			this->hkAmmoTxtBox->Location = System::Drawing::Point(122, 116);
			this->hkAmmoTxtBox->Name = L"hkAmmoTxtBox";
			this->hkAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->hkAmmoTxtBox->TabIndex = 17;
			this->hkAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunWideshotAmmoTxtBox
			// 
			this->shotgunWideshotAmmoTxtBox->Location = System::Drawing::Point(191, 160);
			this->shotgunWideshotAmmoTxtBox->Name = L"shotgunWideshotAmmoTxtBox";
			this->shotgunWideshotAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunWideshotAmmoTxtBox->TabIndex = 19;
			this->shotgunWideshotAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunNormalAmmoTxtBox
			// 
			this->shotgunNormalAmmoTxtBox->Location = System::Drawing::Point(122, 160);
			this->shotgunNormalAmmoTxtBox->Name = L"shotgunNormalAmmoTxtBox";
			this->shotgunNormalAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunNormalAmmoTxtBox->TabIndex = 20;
			this->shotgunNormalAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// numFlaresTxtBox
			// 
			this->numFlaresTxtBox->Location = System::Drawing::Point(176, 76);
			this->numFlaresTxtBox->Name = L"numFlaresTxtBox";
			this->numFlaresTxtBox->Size = System::Drawing::Size(42, 20);
			this->numFlaresTxtBox->TabIndex = 23;
			this->numFlaresTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(18, 75);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(38, 13);
			this->label12->TabIndex = 24;
			this->label12->Text = L"Flares:";
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->numSecretsTxtBox);
			this->groupBox2->Controls->Add(this->label5);
			this->groupBox2->Controls->Add(this->numSavesTxtBox);
			this->groupBox2->Controls->Add(this->label7);
			this->groupBox2->Controls->Add(this->lvlNameTxtBox);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Location = System::Drawing::Point(9, 42);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(493, 51);
			this->groupBox2->TabIndex = 26;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Level";
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->label12);
			this->groupBox3->Controls->Add(this->smallMedipacksTxtBox);
			this->groupBox3->Controls->Add(this->numFlaresTxtBox);
			this->groupBox3->Controls->Add(this->label3);
			this->groupBox3->Controls->Add(this->lrgMedipacksTxtBox);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Location = System::Drawing::Point(9, 101);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(224, 114);
			this->groupBox3->TabIndex = 27;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Items";
			// 
			// saveButton
			// 
			this->saveButton->Enabled = false;
			this->saveButton->Location = System::Drawing::Point(427, 12);
			this->saveButton->Name = L"saveButton";
			this->saveButton->Size = System::Drawing::Size(75, 23);
			this->saveButton->TabIndex = 28;
			this->saveButton->Text = L"Save";
			this->saveButton->UseVisualStyleBackColor = true;
			this->saveButton->Click += gcnew System::EventHandler(this, &SaveEditUI::saveButton_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->pistolsCheckBox);
			this->groupBox4->Controls->Add(this->grapplingGunAmmoTxtBox);
			this->groupBox4->Controls->Add(this->grapplingGunCheckBox);
			this->groupBox4->Controls->Add(this->shotgunCheckBox);
			this->groupBox4->Controls->Add(this->crowbarCheckBox);
			this->groupBox4->Controls->Add(this->hkCheckBox);
			this->groupBox4->Controls->Add(this->uziCheckBox);
			this->groupBox4->Controls->Add(this->revolverCheckBox);
			this->groupBox4->Controls->Add(this->shotgunNormalAmmoTxtBox);
			this->groupBox4->Controls->Add(this->shotgunWideshotAmmoTxtBox);
			this->groupBox4->Controls->Add(this->revolverAmmoTxtBox);
			this->groupBox4->Controls->Add(this->hkAmmoTxtBox);
			this->groupBox4->Controls->Add(this->uziAmmoTxtBox);
			this->groupBox4->Location = System::Drawing::Point(239, 101);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(263, 187);
			this->groupBox4->TabIndex = 29;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Weapons";
			// 
			// pistolsCheckBox
			// 
			this->pistolsCheckBox->AutoSize = true;
			this->pistolsCheckBox->Location = System::Drawing::Point(10, 48);
			this->pistolsCheckBox->Name = L"pistolsCheckBox";
			this->pistolsCheckBox->Size = System::Drawing::Size(56, 17);
			this->pistolsCheckBox->TabIndex = 23;
			this->pistolsCheckBox->Text = L"Pistols";
			this->pistolsCheckBox->UseVisualStyleBackColor = true;
			// 
			// grapplingGunAmmoTxtBox
			// 
			this->grapplingGunAmmoTxtBox->Location = System::Drawing::Point(122, 138);
			this->grapplingGunAmmoTxtBox->Name = L"grapplingGunAmmoTxtBox";
			this->grapplingGunAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->grapplingGunAmmoTxtBox->TabIndex = 22;
			this->grapplingGunAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// grapplingGunCheckBox
			// 
			this->grapplingGunCheckBox->AutoSize = true;
			this->grapplingGunCheckBox->Location = System::Drawing::Point(10, 140);
			this->grapplingGunCheckBox->Name = L"grapplingGunCheckBox";
			this->grapplingGunCheckBox->Size = System::Drawing::Size(97, 17);
			this->grapplingGunCheckBox->TabIndex = 4;
			this->grapplingGunCheckBox->Text = L"Grappling Gun:";
			this->grapplingGunCheckBox->UseVisualStyleBackColor = true;
			// 
			// shotgunCheckBox
			// 
			this->shotgunCheckBox->AutoSize = true;
			this->shotgunCheckBox->Location = System::Drawing::Point(10, 163);
			this->shotgunCheckBox->Name = L"shotgunCheckBox";
			this->shotgunCheckBox->Size = System::Drawing::Size(69, 17);
			this->shotgunCheckBox->TabIndex = 3;
			this->shotgunCheckBox->Text = L"Shotgun:";
			this->shotgunCheckBox->UseVisualStyleBackColor = true;
			// 
			// crowbarCheckBox
			// 
			this->crowbarCheckBox->AutoSize = true;
			this->crowbarCheckBox->Location = System::Drawing::Point(10, 25);
			this->crowbarCheckBox->Name = L"crowbarCheckBox";
			this->crowbarCheckBox->Size = System::Drawing::Size(65, 17);
			this->crowbarCheckBox->TabIndex = 21;
			this->crowbarCheckBox->Text = L"Crowbar";
			this->crowbarCheckBox->UseVisualStyleBackColor = true;
			// 
			// hkCheckBox
			// 
			this->hkCheckBox->AutoSize = true;
			this->hkCheckBox->Location = System::Drawing::Point(10, 117);
			this->hkCheckBox->Name = L"hkCheckBox";
			this->hkCheckBox->Size = System::Drawing::Size(44, 17);
			this->hkCheckBox->TabIndex = 2;
			this->hkCheckBox->Text = L"HK:";
			this->hkCheckBox->UseVisualStyleBackColor = true;
			// 
			// uziCheckBox
			// 
			this->uziCheckBox->AutoSize = true;
			this->uziCheckBox->Location = System::Drawing::Point(10, 94);
			this->uziCheckBox->Name = L"uziCheckBox";
			this->uziCheckBox->Size = System::Drawing::Size(44, 17);
			this->uziCheckBox->TabIndex = 1;
			this->uziCheckBox->Text = L"Uzi:";
			this->uziCheckBox->UseVisualStyleBackColor = true;
			// 
			// revolverCheckBox
			// 
			this->revolverCheckBox->AutoSize = true;
			this->revolverCheckBox->Location = System::Drawing::Point(10, 71);
			this->revolverCheckBox->Name = L"revolverCheckBox";
			this->revolverCheckBox->Size = System::Drawing::Size(111, 17);
			this->revolverCheckBox->TabIndex = 0;
			this->revolverCheckBox->Text = L"Revolver/Deagle:";
			this->revolverCheckBox->UseVisualStyleBackColor = true;
			// 
			// consoleTxtBox
			// 
			this->consoleTxtBox->Location = System::Drawing::Point(9, 296);
			this->consoleTxtBox->Name = L"consoleTxtBox";
			this->consoleTxtBox->ReadOnly = true;
			this->consoleTxtBox->Size = System::Drawing::Size(494, 20);
			this->consoleTxtBox->TabIndex = 30;
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->healthErrorLabel);
			this->groupBox1->Controls->Add(this->healthLabel);
			this->groupBox1->Controls->Add(this->healthBar);
			this->groupBox1->Location = System::Drawing::Point(9, 221);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(224, 67);
			this->groupBox1->TabIndex = 31;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Health";
			// 
			// healthErrorLabel
			// 
			this->healthErrorLabel->AutoSize = true;
			this->healthErrorLabel->ForeColor = System::Drawing::SystemColors::ControlText;
			this->healthErrorLabel->Location = System::Drawing::Point(33, 50);
			this->healthErrorLabel->Name = L"healthErrorLabel";
			this->healthErrorLabel->Size = System::Drawing::Size(136, 13);
			this->healthErrorLabel->TabIndex = 32;
			this->healthErrorLabel->Text = L"Unable to find health bytes.";
			// 
			// healthLabel
			// 
			this->healthLabel->AutoSize = true;
			this->healthLabel->Location = System::Drawing::Point(181, 24);
			this->healthLabel->Name = L"healthLabel";
			this->healthLabel->Size = System::Drawing::Size(30, 13);
			this->healthLabel->TabIndex = 1;
			this->healthLabel->Text = L"0.0%";
			// 
			// healthBar
			// 
			this->healthBar->Location = System::Drawing::Point(5, 20);
			this->healthBar->Maximum = 100;
			this->healthBar->Name = L"healthBar";
			this->healthBar->Size = System::Drawing::Size(179, 45);
			this->healthBar->TabIndex = 0;
			this->healthBar->Scroll += gcnew System::EventHandler(this, &SaveEditUI::healthBar_Scroll);
			// 
			// SaveEditUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(508, 323);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->consoleTxtBox);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->saveButton);
			this->Controls->Add(this->browseButton);
			this->Controls->Add(this->fileTxtBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"SaveEditUI";
			this->Text = L"Tomb Raider Chronicles - Savegame Editor";
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->healthBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void browseButton_Click(System::Object^ sender, System::EventArgs^ e) {
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
				fileTxtBox->Clear();
				fileTxtBox->AppendText(GetSaveFileName());
				myStream->Close();

				saveButton->Enabled = true;
				numSavesTxtBox->Enabled = true;
				numSecretsTxtBox->Enabled = true;
				smallMedipacksTxtBox->Enabled = true;
				lrgMedipacksTxtBox->Enabled = true;
				healthBar->Enabled = true;
				healthErrorLabel->Visible = false;
				healthLabel->Visible = true;

				GetLvlName();
				GetLvlInfo();
				GetNumSmallMedipacks();
				GetNumLrgMedipacks();
				GetNumSecrets();
				GetRevolverAmmo();
				GetSaveNum();
				GetUziAmmo();
				GetHKAmmo();
				GetShotgunNormalAmmo();
				GetShotgunWideshotAmmo();
				GetNumFlares();
				GetGrapplingGunAmmo();
				GetWeaponsInfo();
				GetHealthValue();

				consoleTxtBox->Clear();
				consoleTxtBox->AppendText("Loaded save file: " + openFileDialog1->SafeFileName);
			}
		}
	}
	private: System::Void saveButton_Click(System::Object^ sender, System::EventArgs^ e) {
		int newSmallMedipackVal = int::Parse(smallMedipacksTxtBox->Text);
		int newLrgMedipackVal = int::Parse(lrgMedipacksTxtBox->Text);
		int newFlaresVal = int::Parse(numFlaresTxtBox->Text);
		int newSaveNumVal = int::Parse(numSavesTxtBox->Text);
		int newSecretsVal = int::Parse(numSecretsTxtBox->Text);
		double newHealthPercentage = (double)healthBar->Value;

		int newRevolverAmmoVal = int::Parse(revolverAmmoTxtBox->Text);
		int newUziAmmoVal = int::Parse(uziAmmoTxtBox->Text);
		int newHkAmmoVal = int::Parse(hkAmmoTxtBox->Text);
		int newGrapplingGunVal = int::Parse(grapplingGunAmmoTxtBox->Text);
		int newShotgunNormalAmmoVal = int::Parse(shotgunNormalAmmoTxtBox->Text);
		int newShotgunWideshotAmmoVal = int::Parse(shotgunWideshotAmmoTxtBox->Text);

		if (newSmallMedipackVal > 65535) newSmallMedipackVal = 65535;
		if (newLrgMedipackVal > 65535) newLrgMedipackVal = 65535;
		if (newFlaresVal > 65535) newFlaresVal = 65535;
		if (newSecretsVal > 36) newSecretsVal = 36;

		if (newRevolverAmmoVal > 65535) newRevolverAmmoVal = 65535;
		if (newUziAmmoVal > 65535) newUziAmmoVal = 65535;
		if (newHkAmmoVal > 65535) newHkAmmoVal = 65535;
		if (newGrapplingGunVal > 65535) newGrapplingGunVal = 65535;
		if (newShotgunNormalAmmoVal > 10922) newShotgunNormalAmmoVal = 10922;
		if (newShotgunWideshotAmmoVal > 10922) newShotgunWideshotAmmoVal = 10922;

		WriteValue(hkAmmoOffset, newHkAmmoVal);
		WriteValue(smallMedipackOffset, newSmallMedipackVal);
		WriteValue(lrgMedipackOffset, newLrgMedipackVal);
		WriteValue(saveNumOffset, newSaveNumVal);
		WriteValue(numFlaresOffset, newFlaresVal);
		WriteValue(revolverAmmoOffset, newRevolverAmmoVal);
		WriteValue(uziAmmoOffset, newUziAmmoVal);
		WriteValue(shotgunNormalAmmoOffset, newShotgunNormalAmmoVal * 6);
		WriteValue(shotgunWideshotAmmoOffset, newShotgunWideshotAmmoVal * 6);
		WriteValue(grapplingGunAmmoOffset, newGrapplingGunVal);
		WriteToSaveFile(numSecretsOffset, newSecretsVal);

		if (uziCheckBox->Enabled && uziCheckBox->Checked) WriteToSaveFile(uziOffset, 0x9);
		else WriteToSaveFile(uziOffset, 0);

		if (revolverCheckBox->Enabled && revolverCheckBox->Checked) WriteToSaveFile(revolverOffset, 0x9);
		else WriteToSaveFile(revolverOffset, 0);

		if (shotgunCheckBox->Enabled && shotgunCheckBox->Checked) WriteToSaveFile(shotgunOffset, 0x9);
		else WriteToSaveFile(shotgunOffset, 0);

		if (grapplingGunCheckBox->Enabled && grapplingGunCheckBox->Checked) WriteToSaveFile(grapplingGunOffset, 0xD);
		else WriteToSaveFile(grapplingGunOffset, 0);

		if (hkCheckBox->Enabled && hkCheckBox->Checked) WriteToSaveFile(hkOffset, 0x9);
		else WriteToSaveFile(hkOffset, 0);

		if (pistolsCheckBox->Enabled && pistolsCheckBox->Checked) WriteToSaveFile(pistolsOffset, 0x9);
		else WriteToSaveFile(pistolsOffset, 0);

		if (crowbarCheckBox->Enabled && crowbarCheckBox->Checked) WriteToSaveFile(crowbarOffset, 0x9);
		else WriteToSaveFile(crowbarOffset, 0);

		const int maxHealth = 1000;
		healthOffset = GetHealthOffset();
		int newHealth = (int)(newHealthPercentage / 100.0 * maxHealth);
		if (healthOffset != -1) WriteValue(healthOffset, newHealth);

		MessageBox::Show("Save file patched!", "SUCCESS");
		consoleTxtBox->Clear();
		consoleTxtBox->AppendText("Patched save file!");
	}
	private: System::Void healthBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		double healthPercentage = (double)healthBar->Value;
		healthLabel->Text = healthPercentage.ToString("0.0") + "%";
	}
	};
}
