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
		String^ ssSavefileName;
	private: System::Windows::Forms::CheckBox^ pistolsCheckBox;
		   String^ ssLvlName;
	public:
		SaveEditUI(void)
		{
			InitializeComponent();
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
			int numSecrets = GetSaveFileData(0x1C3);

			numSecretsTxtBox->Clear();
			numSecretsTxtBox->AppendText(numSecrets.ToString());
		}

		void GetSaveNum()
		{
			int saveNum = GetValue(0x4B);

			numSavesTxtBox->Clear();
			numSavesTxtBox->AppendText(saveNum.ToString());
		}

		void GetNumFlares()
		{
			int numFlares = GetValue(0x198);

			numFlaresTxtBox->Clear();
			numFlaresTxtBox->AppendText(numFlares.ToString());
		}

		void GetNumSmallMedipacks()
		{
			int numSmallMedipacks = GetValue(0x194);

			smallMedipacksTxtBox->Clear();
			smallMedipacksTxtBox->AppendText(numSmallMedipacks.ToString());
		}

		void GetNumLrgMedipacks()
		{
			int numLrgMedipacks = GetValue(0x196);

			lrgMedipacksTxtBox->Clear();
			lrgMedipacksTxtBox->AppendText(numLrgMedipacks.ToString());
		}

		void GetShotgunNormalAmmo()
		{
			int shotgunNormalAmmo = GetValue(0x1A0);

			shotgunNormalAmmoTxtBox->Clear();
			shotgunNormalAmmoTxtBox->AppendText((shotgunNormalAmmo / 6).ToString());
		}

		void GetShotgunWideshotAmmo()
		{
			int shotgunWideshotAmmo = GetValue(0x1A2);

			shotgunWideshotAmmoTxtBox->Clear();
			shotgunWideshotAmmoTxtBox->AppendText((shotgunWideshotAmmo / 6).ToString());
		}

		void GetUziAmmo()
		{
			int uziAmmo = GetValue(0x19C);

			uziAmmoTxtBox->Clear();
			uziAmmoTxtBox->AppendText(uziAmmo.ToString());
		}

		void GetHKAmmo()
		{
			int hkAmmo = GetValue(0x1A4);

			hkAmmoTxtBox->Clear();
			hkAmmoTxtBox->AppendText(hkAmmo.ToString());
		}

		void GetGrapplingGunAmmo()
		{
			int grapplingGunAmmo = GetValue(0x1A6);

			grapplingGunAmmoTxtBox->Clear();
			grapplingGunAmmoTxtBox->AppendText(grapplingGunAmmo.ToString());
		}

		void GetRevolverAmmo()
		{
			int revolverAmmo = GetValue(0x19E);

			revolverAmmoTxtBox->Clear();
			revolverAmmoTxtBox->AppendText(revolverAmmo.ToString());
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
			}
		}

		void GetWeaponsInfo()
		{
			int uziVal = GetSaveFileData(0x170);
			int shotgunVal = GetSaveFileData(0x171);
			int grapplingGunVal = GetSaveFileData(0x172);
			int hkVal = GetSaveFileData(0x173);
			int revolverVal = GetSaveFileData(0x174);
			int crowbarVal = GetSaveFileData(0x178);
			int pistolsVal = GetSaveFileData(0x16F);

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
	private: System::Windows::Forms::Button^ saveBtn;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::CheckBox^ revolverCheckBox;
	private: System::Windows::Forms::CheckBox^ shotgunCheckBox;
	private: System::Windows::Forms::CheckBox^ hkCheckBox;
	private: System::Windows::Forms::CheckBox^ uziCheckBox;
	private: System::Windows::Forms::CheckBox^ grapplingGunCheckBox;
	private: System::Windows::Forms::TextBox^ consoleTxtBox;
	private: System::Windows::Forms::CheckBox^ crowbarCheckBox;
	private: System::Windows::Forms::TextBox^ grapplingGunAmmoTxtBox;
		   String^ saveFileName;
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



	private: System::Windows::Forms::Button^ browseBtn;

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
			this->browseBtn = (gcnew System::Windows::Forms::Button());
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
			this->saveBtn = (gcnew System::Windows::Forms::Button());
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
			this->groupBox2->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(22, 25);
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
			this->fileTxtBox->Location = System::Drawing::Point(54, 22);
			this->fileTxtBox->Name = L"fileTxtBox";
			this->fileTxtBox->ReadOnly = true;
			this->fileTxtBox->Size = System::Drawing::Size(294, 20);
			this->fileTxtBox->TabIndex = 2;
			// 
			// lvlNameTxtBox
			// 
			this->lvlNameTxtBox->Location = System::Drawing::Point(57, 19);
			this->lvlNameTxtBox->Name = L"lvlNameTxtBox";
			this->lvlNameTxtBox->ReadOnly = true;
			this->lvlNameTxtBox->Size = System::Drawing::Size(109, 20);
			this->lvlNameTxtBox->TabIndex = 3;
			this->lvlNameTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->lvlNameTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::lvlNameTxtBox_TextChanged);
			// 
			// browseBtn
			// 
			this->browseBtn->Location = System::Drawing::Point(355, 20);
			this->browseBtn->Name = L"browseBtn";
			this->browseBtn->Size = System::Drawing::Size(75, 23);
			this->browseBtn->TabIndex = 4;
			this->browseBtn->Text = L"Browse";
			this->browseBtn->UseVisualStyleBackColor = true;
			this->browseBtn->Click += gcnew System::EventHandler(this, &SaveEditUI::browseBtn_Click);
			// 
			// smallMedipacksTxtBox
			// 
			this->smallMedipacksTxtBox->Location = System::Drawing::Point(122, 31);
			this->smallMedipacksTxtBox->Name = L"smallMedipacksTxtBox";
			this->smallMedipacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->smallMedipacksTxtBox->TabIndex = 5;
			this->smallMedipacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->smallMedipacksTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::smallMedipacksTxtBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(26, 34);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Small Medipacks:";
			// 
			// lrgMedipacksTxtBox
			// 
			this->lrgMedipacksTxtBox->Location = System::Drawing::Point(122, 91);
			this->lrgMedipacksTxtBox->Name = L"lrgMedipacksTxtBox";
			this->lrgMedipacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->lrgMedipacksTxtBox->TabIndex = 7;
			this->lrgMedipacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->lrgMedipacksTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::lrgMedpacksTxtBox_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(24, 93);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(92, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Large Medipacks:";
			// 
			// numSecretsTxtBox
			// 
			this->numSecretsTxtBox->Location = System::Drawing::Point(435, 19);
			this->numSecretsTxtBox->Name = L"numSecretsTxtBox";
			this->numSecretsTxtBox->Size = System::Drawing::Size(42, 20);
			this->numSecretsTxtBox->TabIndex = 9;
			this->numSecretsTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(383, 22);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(46, 13);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Secrets:";
			// 
			// revolverAmmoTxtBox
			// 
			this->revolverAmmoTxtBox->Location = System::Drawing::Point(121, 72);
			this->revolverAmmoTxtBox->Name = L"revolverAmmoTxtBox";
			this->revolverAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->revolverAmmoTxtBox->TabIndex = 11;
			this->revolverAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->revolverAmmoTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::revolverAmmoTxtBox_TextChanged);
			// 
			// numSavesTxtBox
			// 
			this->numSavesTxtBox->Location = System::Drawing::Point(289, 19);
			this->numSavesTxtBox->Name = L"numSavesTxtBox";
			this->numSavesTxtBox->Size = System::Drawing::Size(42, 20);
			this->numSavesTxtBox->TabIndex = 13;
			this->numSavesTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->numSavesTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::numSavesTxtBox_TextChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(210, 22);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(75, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Save Number:";
			// 
			// uziAmmoTxtBox
			// 
			this->uziAmmoTxtBox->Location = System::Drawing::Point(121, 94);
			this->uziAmmoTxtBox->Name = L"uziAmmoTxtBox";
			this->uziAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->uziAmmoTxtBox->TabIndex = 15;
			this->uziAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// hkAmmoTxtBox
			// 
			this->hkAmmoTxtBox->Location = System::Drawing::Point(121, 116);
			this->hkAmmoTxtBox->Name = L"hkAmmoTxtBox";
			this->hkAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->hkAmmoTxtBox->TabIndex = 17;
			this->hkAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunWideshotAmmoTxtBox
			// 
			this->shotgunWideshotAmmoTxtBox->Location = System::Drawing::Point(121, 160);
			this->shotgunWideshotAmmoTxtBox->Name = L"shotgunWideshotAmmoTxtBox";
			this->shotgunWideshotAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunWideshotAmmoTxtBox->TabIndex = 19;
			this->shotgunWideshotAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunNormalAmmoTxtBox
			// 
			this->shotgunNormalAmmoTxtBox->Location = System::Drawing::Point(190, 160);
			this->shotgunNormalAmmoTxtBox->Name = L"shotgunNormalAmmoTxtBox";
			this->shotgunNormalAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunNormalAmmoTxtBox->TabIndex = 20;
			this->shotgunNormalAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// numFlaresTxtBox
			// 
			this->numFlaresTxtBox->Location = System::Drawing::Point(122, 144);
			this->numFlaresTxtBox->Name = L"numFlaresTxtBox";
			this->numFlaresTxtBox->Size = System::Drawing::Size(42, 20);
			this->numFlaresTxtBox->TabIndex = 23;
			this->numFlaresTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(77, 146);
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
			this->groupBox2->Location = System::Drawing::Point(17, 59);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(490, 51);
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
			this->groupBox3->Location = System::Drawing::Point(14, 122);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(224, 187);
			this->groupBox3->TabIndex = 27;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Items";
			// 
			// saveBtn
			// 
			this->saveBtn->Enabled = false;
			this->saveBtn->Location = System::Drawing::Point(433, 20);
			this->saveBtn->Name = L"saveBtn";
			this->saveBtn->Size = System::Drawing::Size(75, 23);
			this->saveBtn->TabIndex = 28;
			this->saveBtn->Text = L"Save";
			this->saveBtn->UseVisualStyleBackColor = true;
			this->saveBtn->Click += gcnew System::EventHandler(this, &SaveEditUI::saveBtn_Click);
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
			this->groupBox4->Location = System::Drawing::Point(244, 122);
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
			this->grapplingGunAmmoTxtBox->Location = System::Drawing::Point(121, 138);
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
			this->grapplingGunCheckBox->Size = System::Drawing::Size(94, 17);
			this->grapplingGunCheckBox->TabIndex = 4;
			this->grapplingGunCheckBox->Text = L"Grappling Gun";
			this->grapplingGunCheckBox->UseVisualStyleBackColor = true;
			// 
			// shotgunCheckBox
			// 
			this->shotgunCheckBox->AutoSize = true;
			this->shotgunCheckBox->Location = System::Drawing::Point(10, 163);
			this->shotgunCheckBox->Name = L"shotgunCheckBox";
			this->shotgunCheckBox->Size = System::Drawing::Size(66, 17);
			this->shotgunCheckBox->TabIndex = 3;
			this->shotgunCheckBox->Text = L"Shotgun";
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
			this->hkCheckBox->Size = System::Drawing::Size(41, 17);
			this->hkCheckBox->TabIndex = 2;
			this->hkCheckBox->Text = L"HK";
			this->hkCheckBox->UseVisualStyleBackColor = true;
			// 
			// uziCheckBox
			// 
			this->uziCheckBox->AutoSize = true;
			this->uziCheckBox->Location = System::Drawing::Point(10, 94);
			this->uziCheckBox->Name = L"uziCheckBox";
			this->uziCheckBox->Size = System::Drawing::Size(41, 17);
			this->uziCheckBox->TabIndex = 1;
			this->uziCheckBox->Text = L"Uzi";
			this->uziCheckBox->UseVisualStyleBackColor = true;
			// 
			// revolverCheckBox
			// 
			this->revolverCheckBox->AutoSize = true;
			this->revolverCheckBox->Location = System::Drawing::Point(10, 71);
			this->revolverCheckBox->Name = L"revolverCheckBox";
			this->revolverCheckBox->Size = System::Drawing::Size(108, 17);
			this->revolverCheckBox->TabIndex = 0;
			this->revolverCheckBox->Text = L"Revolver/Deagle";
			this->revolverCheckBox->UseVisualStyleBackColor = true;
			// 
			// consoleTxtBox
			// 
			this->consoleTxtBox->Location = System::Drawing::Point(14, 317);
			this->consoleTxtBox->Name = L"consoleTxtBox";
			this->consoleTxtBox->ReadOnly = true;
			this->consoleTxtBox->Size = System::Drawing::Size(494, 20);
			this->consoleTxtBox->TabIndex = 30;
			// 
			// SaveEditUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(518, 344);
			this->Controls->Add(this->consoleTxtBox);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->saveBtn);
			this->Controls->Add(this->browseBtn);
			this->Controls->Add(this->fileTxtBox);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox3);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"SaveEditUI";
			this->Text = L"Tomb Raider: Chronicles - Savegame Editor";
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void browseBtn_Click(System::Object^ sender, System::EventArgs^ e) {
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
				saveBtn->Enabled = true;
				GetLvlName();
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
				GetLvlInfo();
				consoleTxtBox->Clear();
				consoleTxtBox->AppendText("Loaded save file: " + openFileDialog1->SafeFileName);
			}
		}
	}
	private: System::Void lrgMedpacksTxtBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void saveBtn_Click(System::Object^ sender, System::EventArgs^ e) {

		int newSmallMedipackVal = int::Parse(smallMedipacksTxtBox->Text);
		int newLrgMedipackVal = int::Parse(lrgMedipacksTxtBox->Text);
		int newFlaresVal = int::Parse(numFlaresTxtBox->Text);
		int newSaveNumVal = int::Parse(numSavesTxtBox->Text);
		int newSecretsVal = int::Parse(numSecretsTxtBox->Text);

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

		newShotgunNormalAmmoVal = newShotgunNormalAmmoVal * 6;
		newShotgunWideshotAmmoVal = newShotgunWideshotAmmoVal * 6;

		WriteValue(0x1A4, newHkAmmoVal);
		WriteValue(0x194, newSmallMedipackVal);
		WriteValue(0x196, newLrgMedipackVal);
		WriteValue(0x04B, newSaveNumVal);
		WriteValue(0x198, newFlaresVal);
		WriteValue(0x19E, newRevolverAmmoVal);
		WriteValue(0x19C, newUziAmmoVal);
		WriteValue(0x1A0, newShotgunNormalAmmoVal);
		WriteValue(0x1A2, newShotgunWideshotAmmoVal);
		WriteValue(0x1A6, newGrapplingGunVal);

		if (uziCheckBox->Enabled && uziCheckBox->Checked) WriteToSaveFile(0x170, 0x9);
		else WriteToSaveFile(0x170, 0);

		if (revolverCheckBox->Enabled && revolverCheckBox->Checked) WriteToSaveFile(0x174, 0x9);
		else WriteToSaveFile(0x174, 0);

		if (shotgunCheckBox->Enabled && shotgunCheckBox->Checked) WriteToSaveFile(0x171, 0x9);
		else WriteToSaveFile(0x171, 0);

		if (grapplingGunCheckBox->Enabled && grapplingGunCheckBox->Checked) WriteToSaveFile(0x172, 0xD);
		else WriteToSaveFile(0x172, 0);

		if (hkCheckBox->Enabled && hkCheckBox->Checked) WriteToSaveFile(0x173, 0x9);
		else WriteToSaveFile(0x173, 0);

		if (pistolsCheckBox->Enabled && pistolsCheckBox->Checked) WriteToSaveFile(0x16F, 0x9);
		else WriteToSaveFile(0x16F, 0);

		if (crowbarCheckBox->Enabled && crowbarCheckBox->Checked) WriteToSaveFile(0x178, 0x9);
		else WriteToSaveFile(0x178, 0);

		WriteToSaveFile(0x1C3, newSecretsVal);

		MessageBox::Show("Save file patched!", "SUCCESS");
		consoleTxtBox->Clear();
		consoleTxtBox->AppendText("Patched save file!");
	}
	private: System::Void revolverAmmoTxtBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void smallMedipacksTxtBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void numSavesTxtBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void lvlNameTxtBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
