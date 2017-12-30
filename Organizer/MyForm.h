#pragma once
#include "Ñalendar.h"
#include "Settings.h"
#define SETTINGS "settings.ini"

int nMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
std::string sMonth[] = { "ßíâàðü","Ôåâðàëü","Ìàðò","Àïðåëü","Ìàé","Èþíü","Èþëü","Àâãóñò", "Ñåíòÿáðü", "Îêòÿáðü", "Íîÿáðü", "Äåêàáðü" };
std::string itsColor[] = { "White", "Black", "LightBlue"};

struct Option
{
	int backcolor;
	int time;
	Option ();
	void LoadOpt(std::string file_name);
	void SaveOpt(std::string file_name);
};
namespace Organizer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private: Ñalendar* calendar;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  label7;
	private: void InitializeComponent(void);
	public:
		Option* opt;
		MyForm(void);
	protected:
		~MyForm();
	private: System::Void MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);

	private: void CheckingDate();
	private: void showEvent();
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::ComboBox^  comboBox2;
	private: System::Windows::Forms::GroupBox^  groupBox1;

	private: System::Windows::Forms::Label^  Month;
	private: System::Windows::Forms::Button^  ButtonLeft;

	private: System::Windows::Forms::Button^  ButtonRight;
	private: System::Windows::Forms::Button^  addEvent;

	private: System::Windows::Forms::TextBox^  textBox1;

	private: System::Windows::Forms::TabPage^  interactionEvent;
	private: System::Windows::Forms::TabControl^  ChoiceAction;
	private: System::Windows::Forms::TabPage^  newEvent;

	private: System::Windows::Forms::Label^  year;
	private: System::Windows::Forms::TableLayoutPanel^  FCalendar;
	private: System::Windows::Forms::Label^  Data;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	private: System::Windows::Forms::TableLayoutPanel^  ShowLayout;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Timer^  timer1;

	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
#pragma endregion
private: void ReplaceÑalendar(int, int, int);

private: System::Void MyForm_Load_1(System::Object^  sender, System::EventArgs^  e);

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void CalendarButton_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void Organizer::MyForm::DeleteButton_Click(System::Object ^ sender, System::EventArgs ^ e);

private: System::Void addEvent_Click(System::Object^  sender, System::EventArgs^  e);

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e);

private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e);

private: System::Void MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e);
};
}
