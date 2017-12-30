#include "Settings.h"

void Organizer::Settings::InitializeComponent(void)
{
	this->button1 = (gcnew System::Windows::Forms::Button());
	this->button2 = (gcnew System::Windows::Forms::Button());
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->warnTime = (gcnew System::Windows::Forms::ComboBox());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->ChangeColor = (gcnew System::Windows::Forms::ComboBox());
	this->SuspendLayout();
	// 
	// button1
	// 
	this->button1->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	this->button1->Location = System::Drawing::Point(236, 243);
	this->button1->Name = L"button1";
	this->button1->Size = System::Drawing::Size(75, 23);
	this->button1->TabIndex = 0;
	this->button1->Text = L"Отмена";
	this->button1->UseVisualStyleBackColor = true;
	// 
	// button2
	// 
	this->button2->DialogResult = System::Windows::Forms::DialogResult::OK;
	this->button2->Location = System::Drawing::Point(155, 243);
	this->button2->Name = L"button2";
	this->button2->Size = System::Drawing::Size(75, 23);
	this->button2->TabIndex = 1;
	this->button2->Text = L"ОК";
	this->button2->UseVisualStyleBackColor = true;
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Location = System::Drawing::Point(12, 20);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(104, 13);
	this->label1->TabIndex = 2;
	this->label1->Text = L"Выбор цвета фона:";
	// 
	// warnTime
	// 
	this->warnTime->FormattingEnabled = true;
	this->warnTime->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"10", L"30", L"60" });
	this->warnTime->Location = System::Drawing::Point(24, 147);
	this->warnTime->Name = L"warnTime";
	this->warnTime->Size = System::Drawing::Size(121, 21);
	this->warnTime->TabIndex = 4;
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Location = System::Drawing::Point(12, 121);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(109, 13);
	this->label2->TabIndex = 5;
	this->label2->Text = L"Время оповещения:";
	// 
	// ChangeColor
	// 
	this->ChangeColor->FormattingEnabled = true;
	this->ChangeColor->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"White", L"Black", L"LightBlue"});
	this->ChangeColor->Location = System::Drawing::Point(24, 46);
	this->ChangeColor->Name = L"ChangeColor";
	this->ChangeColor->Size = System::Drawing::Size(121, 21);
	this->ChangeColor->TabIndex = 6;
	// 
	// Settings
	// 
	this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
	this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
	this->ClientSize = System::Drawing::Size(311, 267);
	this->Controls->Add(this->ChangeColor);
	this->Controls->Add(this->label2);
	this->Controls->Add(this->warnTime);
	this->Controls->Add(this->label1);
	this->Controls->Add(this->button2);
	this->Controls->Add(this->button1);
	this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
	this->Name = L"Settings";
	this->Text = L"Настройки";
	this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Settings::Settings_FormClosing);
	this->ResumeLayout(false);
	this->PerformLayout();
}

void Organizer::Settings::Settings_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (DialogResult != System::Windows::Forms::DialogResult::OK)
		if (MessageBox::Show("Отменить изменения?",
			"Настройки", MessageBoxButtons::OK | MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::Cancel)
			e->Cancel = true;
}