/*
	Julian O. Rose
	TRC-SaveEdit.h
	1-29-2023
*/

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <msclr\marshal_cppstd.h>
#include <sstream>

namespace TRCSaveEdit {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;
	using namespace msclr::interop;

	/// <summary>
	/// Summary for SaveEditUI
	/// </summary>
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
		void SetSaveFile(String^ fileName)
		{
			ssSavefileName = fileName;
		}
		int GetSaveFileData(int offset)
		{
			String^ saveFileName = GetSaveFileName();
			std::string sSaveFileName = marshal_as<std::string>(saveFileName);
			std::fstream saveFile(sSaveFileName, std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekp(offset);
			int iData = saveFile.get();
			saveFile.close();
			return iData;
		}
		void WriteToSaveFile(int offset, int num) {
			String^ saveFileName = GetSaveFileName();
			std::string sSaveFileName = marshal_as<std::string>(saveFileName);
			std::fstream saveFile(sSaveFileName, std::ios::in | std::ios::out | std::ios::binary);
			saveFile.seekg(offset, std::ios::beg);
			char data[1] = { num };
			saveFile.write(data, sizeof(data));
			saveFile.close();
		}
		String^ GetSaveFileName()
		{
			return saveFileName;
		}
		void GetNumSmallMedipacks()
		{
			String^ ssNumSmallMedipacks = GetSaveFileData(0x194).ToString();

			smallMedipacksTxtBox->Clear();
			smallMedipacksTxtBox->AppendText(ssNumSmallMedipacks);
		}
		void GetNumLrgMedipacks()
		{
			String^ ssNumLrgMedipacks = GetSaveFileData(0x196).ToString();

			lrgMedpacksTxtBox->Clear();
			lrgMedpacksTxtBox->AppendText(ssNumLrgMedipacks);
		}
		void GetLvlName()
		{
			std::string sSaveFileName = marshal_as<std::string>(GetSaveFileName());
			std::string sLine = "NULL";

			std::ifstream infile(sSaveFileName);

			if (infile.good())
			{
				getline(infile, sLine);
			}

			infile.close();

			ssLvlName = gcnew String(sLine.c_str());

			lvlNameTxtBox->Clear();
			lvlNameTxtBox->AppendText(ssLvlName);
		}
		void GetLvlInfo()
		{
			if (ssLvlName == "Streets of Rome")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
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
				pistolsCheckBox->Enabled = true;
			}
			if (ssLvlName == "Trajan`s markets")
			{
				revolverCheckBox->Enabled = true;
				revolverAmmoTxtBox->Enabled = true;
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
			}

			if (ssLvlName == "The Colosseum")
			{
				revolverCheckBox->Enabled = false;
				revolverAmmoTxtBox->Enabled = false;
				uziCheckBox->Enabled = true;
				uziAmmoTxtBox->Enabled = true;
				shotgunCheckBox->Enabled = false;
				shotgunNormalAmmoTxtBox->Enabled = false;
				shotgunWideshotAmmoTxtBox->Enabled = false;
				grapplingGunCheckBox->Enabled = false;
				grapplingGunAmmoTxtBox->Enabled = false;
				hkCheckBox->Enabled = false;
				hkAmmoTxtBox->Enabled = false;
				crowbarCheckBox->Enabled = true;
				pistolsCheckBox->Enabled = true;
			}

			if (ssLvlName == "The submarine")
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
			}

			if (ssLvlName == "Deepsea dive")
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
			}

			if (ssLvlName == "Sinking submarine")
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
			}

			if (ssLvlName == "Gallows tree")
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
			}

			if (ssLvlName == "Labyrinth")
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
			}

			if (ssLvlName == "Old mill")
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
			}

			if (ssLvlName == "The 13th floor")
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
			}

			if (ssLvlName == "Escape with the iris")
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
			}

			if (ssLvlName == "Red alert!")
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
			}
		}
		void GetNumSecrets()
		{
			String^ ssNumSecrets = GetSaveFileData(0x1C3).ToString();

			numSecretsTxtBox->Clear();
			numSecretsTxtBox->AppendText(ssNumSecrets);
		}
		void GetSaveNum()
		{
			String^ ssNumSaves = GetSaveFileData(0x4B).ToString();

			numSavesTxtBox->Clear();
			numSavesTxtBox->AppendText(ssNumSaves);
		}
		void GetNumFlares()
		{
			String^ ssNumFlares = GetSaveFileData(0x198).ToString();

			numFlaresTxtBox->Clear();
			numFlaresTxtBox->AppendText(ssNumFlares);
		}
		void GetShotgunNormalAmmo()
		{
			String^ ssShotgunNormalAmmo = GetSaveFileData(0x1A0).ToString();

			shotgunNormalAmmoTxtBox->Clear();
			shotgunNormalAmmoTxtBox->AppendText(ssShotgunNormalAmmo);
		}
		void GetShotgunWideshotAmmo()
		{
			String^ ssShotgunWideshotAmmo = GetSaveFileData(0x1A2).ToString();

			shotgunWideshotAmmoTxtBox->Clear();
			shotgunWideshotAmmoTxtBox->AppendText(ssShotgunWideshotAmmo);
		}
		void GetUziAmmo()
		{
			String^ ssUziAmmo = GetSaveFileData(0x19C).ToString();

			uziAmmoTxtBox->Clear();
			uziAmmoTxtBox->AppendText(ssUziAmmo);
		}
		void GetHKAmmo()
		{
			String^ ssHkAmmo = GetSaveFileData(0x1A4).ToString();

			hkAmmoTxtBox->Clear();
			hkAmmoTxtBox->AppendText(ssHkAmmo);
		}
		void GetWeaponsInfo()
		{
			int uziVal = GetSaveFileData(0x170);
			if (uziVal == 0x9)
			{
				uziCheckBox->Checked = true;
			}

			int shotgunVal = GetSaveFileData(0x171);
			if (shotgunVal == 0x9)
			{
				shotgunCheckBox->Checked = true;
			}

			int grapplingGunVal = GetSaveFileData(0x172);
			if (grapplingGunVal == 0xD)
			{
				grapplingGunCheckBox->Checked = true;
			}

			int hkVal = GetSaveFileData(0x173);
			if (hkVal == 0x9 || hkVal == 0xD)
			{
				hkCheckBox->Checked = true;
			}

			int revolverVal = GetSaveFileData(0x174);
			if (revolverVal == 0x9 || revolverVal == 0xD)
			{
				revolverCheckBox->Checked = true;
			}

			int crowbarVal = GetSaveFileData(0x178);
			if (crowbarVal == 0x1)
			{
				crowbarCheckBox->Checked = true;
			}

			int pistolsVal = GetSaveFileData(0x16F);
			if (pistolsVal == 0x9)
			{
				pistolsCheckBox->Checked = true;
			}
		}
		void GetGrapplingGunAmmo()
		{
			String^ ssGrapplingGunAmmo = GetSaveFileData(0x1A6).ToString();

			grapplingGunAmmoTxtBox->Clear();
			grapplingGunAmmoTxtBox->AppendText(ssGrapplingGunAmmo);
		}
		void GetRevolverAmmo()
		{
			String^ ssRevolverAmmo = GetSaveFileData(0x19E).ToString();

			revolverAmmoTxtBox->Clear();
			revolverAmmoTxtBox->AppendText(ssRevolverAmmo);
		}
	private: System::Windows::Forms::TextBox^ smallMedipacksTxtBox;
	public:

	public:
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ lrgMedpacksTxtBox;
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
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
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
		/// <summary>
		/// Required designer variable.
		/// </summary>
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
			this->lrgMedpacksTxtBox = (gcnew System::Windows::Forms::TextBox());
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
			this->label1->Location = System::Drawing::Point(22, 15);
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
			this->fileTxtBox->Location = System::Drawing::Point(54, 12);
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
			this->browseBtn->Location = System::Drawing::Point(355, 10);
			this->browseBtn->Name = L"browseBtn";
			this->browseBtn->Size = System::Drawing::Size(75, 23);
			this->browseBtn->TabIndex = 4;
			this->browseBtn->Text = L"Browse";
			this->browseBtn->UseVisualStyleBackColor = true;
			this->browseBtn->Click += gcnew System::EventHandler(this, &SaveEditUI::browseBtn_Click);
			// 
			// smallMedipacksTxtBox
			// 
			this->smallMedipacksTxtBox->Location = System::Drawing::Point(122, 23);
			this->smallMedipacksTxtBox->Name = L"smallMedipacksTxtBox";
			this->smallMedipacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->smallMedipacksTxtBox->TabIndex = 5;
			this->smallMedipacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->smallMedipacksTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::smallMedipacksTxtBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(26, 23);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(90, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Small Medipacks:";
			// 
			// lrgMedpacksTxtBox
			// 
			this->lrgMedpacksTxtBox->Location = System::Drawing::Point(122, 83);
			this->lrgMedpacksTxtBox->Name = L"lrgMedpacksTxtBox";
			this->lrgMedpacksTxtBox->Size = System::Drawing::Size(42, 20);
			this->lrgMedpacksTxtBox->TabIndex = 7;
			this->lrgMedpacksTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->lrgMedpacksTxtBox->TextChanged += gcnew System::EventHandler(this, &SaveEditUI::lrgMedpacksTxtBox_TextChanged);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(24, 83);
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
			this->revolverAmmoTxtBox->Location = System::Drawing::Point(117, 60);
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
			this->label7->Size = System::Drawing::Size(73, 13);
			this->label7->TabIndex = 14;
			this->label7->Text = L"Save number:";
			// 
			// uziAmmoTxtBox
			// 
			this->uziAmmoTxtBox->Location = System::Drawing::Point(117, 86);
			this->uziAmmoTxtBox->Name = L"uziAmmoTxtBox";
			this->uziAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->uziAmmoTxtBox->TabIndex = 15;
			this->uziAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// hkAmmoTxtBox
			// 
			this->hkAmmoTxtBox->Location = System::Drawing::Point(117, 110);
			this->hkAmmoTxtBox->Name = L"hkAmmoTxtBox";
			this->hkAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->hkAmmoTxtBox->TabIndex = 17;
			this->hkAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunWideshotAmmoTxtBox
			// 
			this->shotgunWideshotAmmoTxtBox->Location = System::Drawing::Point(117, 159);
			this->shotgunWideshotAmmoTxtBox->Name = L"shotgunWideshotAmmoTxtBox";
			this->shotgunWideshotAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunWideshotAmmoTxtBox->TabIndex = 19;
			this->shotgunWideshotAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// shotgunNormalAmmoTxtBox
			// 
			this->shotgunNormalAmmoTxtBox->Location = System::Drawing::Point(189, 159);
			this->shotgunNormalAmmoTxtBox->Name = L"shotgunNormalAmmoTxtBox";
			this->shotgunNormalAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->shotgunNormalAmmoTxtBox->TabIndex = 20;
			this->shotgunNormalAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// numFlaresTxtBox
			// 
			this->numFlaresTxtBox->Location = System::Drawing::Point(122, 136);
			this->numFlaresTxtBox->Name = L"numFlaresTxtBox";
			this->numFlaresTxtBox->Size = System::Drawing::Size(42, 20);
			this->numFlaresTxtBox->TabIndex = 23;
			this->numFlaresTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(75, 139);
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
			this->groupBox2->Location = System::Drawing::Point(17, 50);
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
			this->groupBox3->Controls->Add(this->lrgMedpacksTxtBox);
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
			this->saveBtn->Location = System::Drawing::Point(433, 10);
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
			this->pistolsCheckBox->Location = System::Drawing::Point(10, 42);
			this->pistolsCheckBox->Name = L"pistolsCheckBox";
			this->pistolsCheckBox->Size = System::Drawing::Size(56, 17);
			this->pistolsCheckBox->TabIndex = 23;
			this->pistolsCheckBox->Text = L"Pistols";
			this->pistolsCheckBox->UseVisualStyleBackColor = true;
			// 
			// grapplingGunAmmoTxtBox
			// 
			this->grapplingGunAmmoTxtBox->Location = System::Drawing::Point(117, 136);
			this->grapplingGunAmmoTxtBox->Name = L"grapplingGunAmmoTxtBox";
			this->grapplingGunAmmoTxtBox->Size = System::Drawing::Size(66, 20);
			this->grapplingGunAmmoTxtBox->TabIndex = 22;
			this->grapplingGunAmmoTxtBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// grapplingGunCheckBox
			// 
			this->grapplingGunCheckBox->AutoSize = true;
			this->grapplingGunCheckBox->Location = System::Drawing::Point(10, 136);
			this->grapplingGunCheckBox->Name = L"grapplingGunCheckBox";
			this->grapplingGunCheckBox->Size = System::Drawing::Size(94, 17);
			this->grapplingGunCheckBox->TabIndex = 4;
			this->grapplingGunCheckBox->Text = L"Grappling Gun";
			this->grapplingGunCheckBox->UseVisualStyleBackColor = true;
			// 
			// shotgunCheckBox
			// 
			this->shotgunCheckBox->AutoSize = true;
			this->shotgunCheckBox->Location = System::Drawing::Point(10, 159);
			this->shotgunCheckBox->Name = L"shotgunCheckBox";
			this->shotgunCheckBox->Size = System::Drawing::Size(66, 17);
			this->shotgunCheckBox->TabIndex = 3;
			this->shotgunCheckBox->Text = L"Shotgun";
			this->shotgunCheckBox->UseVisualStyleBackColor = true;
			// 
			// crowbarCheckBox
			// 
			this->crowbarCheckBox->AutoSize = true;
			this->crowbarCheckBox->Location = System::Drawing::Point(11, 19);
			this->crowbarCheckBox->Name = L"crowbarCheckBox";
			this->crowbarCheckBox->Size = System::Drawing::Size(65, 17);
			this->crowbarCheckBox->TabIndex = 21;
			this->crowbarCheckBox->Text = L"Crowbar";
			this->crowbarCheckBox->UseVisualStyleBackColor = true;
			// 
			// hkCheckBox
			// 
			this->hkCheckBox->AutoSize = true;
			this->hkCheckBox->Location = System::Drawing::Point(10, 111);
			this->hkCheckBox->Name = L"hkCheckBox";
			this->hkCheckBox->Size = System::Drawing::Size(41, 17);
			this->hkCheckBox->TabIndex = 2;
			this->hkCheckBox->Text = L"HK";
			this->hkCheckBox->UseVisualStyleBackColor = true;
			// 
			// uziCheckBox
			// 
			this->uziCheckBox->AutoSize = true;
			this->uziCheckBox->Location = System::Drawing::Point(10, 86);
			this->uziCheckBox->Name = L"uziCheckBox";
			this->uziCheckBox->Size = System::Drawing::Size(41, 17);
			this->uziCheckBox->TabIndex = 1;
			this->uziCheckBox->Text = L"Uzi";
			this->uziCheckBox->UseVisualStyleBackColor = true;
			// 
			// revolverCheckBox
			// 
			this->revolverCheckBox->AutoSize = true;
			this->revolverCheckBox->Location = System::Drawing::Point(10, 63);
			this->revolverCheckBox->Name = L"revolverCheckBox";
			this->revolverCheckBox->Size = System::Drawing::Size(69, 17);
			this->revolverCheckBox->TabIndex = 0;
			this->revolverCheckBox->Text = L"Revolver";
			this->revolverCheckBox->UseVisualStyleBackColor = true;
			// 
			// consoleTxtBox
			// 
			this->consoleTxtBox->Location = System::Drawing::Point(14, 317);
			this->consoleTxtBox->Name = L"consoleTxtBox";
			this->consoleTxtBox->ReadOnly = true;
			this->consoleTxtBox->Size = System::Drawing::Size(490, 20);
			this->consoleTxtBox->TabIndex = 30;
			// 
			// SaveEditUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(520, 341);
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
			this->Text = L"Tomb Raider: Chronicles - SaveGame Editor";
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
				SetSaveFile(openFileDialog1->FileName);
				fileTxtBox->Clear();
				fileTxtBox->AppendText(GetSaveFileName());
				myStream->Close();
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
		WriteToSaveFile(0x194, int::Parse(smallMedipacksTxtBox->Text));
		WriteToSaveFile(0x196, int::Parse(lrgMedpacksTxtBox->Text));
		WriteToSaveFile(0x198, int::Parse(numFlaresTxtBox->Text));
		WriteToSaveFile(0x04B, int::Parse(numSavesTxtBox->Text));
		WriteToSaveFile(0x1C3,  int::Parse(numSecretsTxtBox->Text));
		WriteToSaveFile(0x19C, int::Parse(uziAmmoTxtBox->Text));
		WriteToSaveFile(0x19E, int::Parse(revolverAmmoTxtBox->Text));
		WriteToSaveFile(0x1A0, int::Parse(shotgunNormalAmmoTxtBox->Text));
		WriteToSaveFile(0x1A2, int::Parse(shotgunWideshotAmmoTxtBox->Text));
		WriteToSaveFile(0x1A4, int::Parse(hkAmmoTxtBox->Text));
		WriteToSaveFile(0x1A6, int::Parse(grapplingGunAmmoTxtBox->Text));

		if (uziCheckBox->Enabled && uziCheckBox->Checked) { WriteToSaveFile(0x170, 0x9); }
		else { WriteToSaveFile(0x170, 0); }

		if (revolverCheckBox->Enabled && revolverCheckBox->Checked) { WriteToSaveFile(0x174, 0x9); }
		else { WriteToSaveFile(0x174, 0); }

		if (shotgunCheckBox->Enabled && shotgunCheckBox->Checked) { WriteToSaveFile(0x171, 0x9); }
		else { WriteToSaveFile(0x171, 0); }
		
		if (grapplingGunCheckBox->Enabled && grapplingGunCheckBox->Checked) { WriteToSaveFile(0x172, 0xD); }
		else { WriteToSaveFile(0x172, 0); }

		if (hkCheckBox->Enabled && hkCheckBox->Checked) { WriteToSaveFile(0x1A4, 0x9); }
		else { WriteToSaveFile(0x1A4, 0); }
		
		if (pistolsCheckBox->Enabled && pistolsCheckBox->Checked) { WriteToSaveFile(0x16F, 0x9); }
		else { WriteToSaveFile(0x16F, 0); }

		if (crowbarCheckBox->Enabled && crowbarCheckBox->Checked) { WriteToSaveFile(0x178, 0x9); }
		else { WriteToSaveFile(0x178, 0); }

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
