#include "MyForm.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void Main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Organizer::MyForm form;
	Application::Run(%form);
}

Organizer::MyForm::MyForm(void)
{
	opt = new Option;
	calendar = new Сalendar();
	opt->LoadOpt(SETTINGS);
	InitializeComponent();
	CheckingDate();
	timer1->Interval = 60000;
	timer1->Start();
	this->DoubleBuffered = true;
	showEvent();
}

Void Organizer::MyForm::MyForm_Load_1(System::Object^  sender, System::EventArgs^  e)
{
	time_t second = time(NULL);
	tm* timeinfo = localtime(&second);
	for (int i = 0; i <= 23; i++)
		this->comboBox1->Items->Add(i);
	for (int i = 1; i<60; i++)
		this->comboBox2->Items->Add(i);
}

void Organizer::MyForm::CheckingDate()
{
	int month = calendar->GetMonth();
	int dayT = nMonth[month];
	String^ stringM = gcnew System::String(sMonth[month].c_str());
	this->Month->Text = stringM;
	int year = calendar->GetYear();
	if (year % 4 == 0 && month == 1)
		++dayT;
	String^string = String::Format("{0}", year);
	this->year->Text = string;
	ReplaceСalendar(dayT, month, year);
}

void Organizer::MyForm::showEvent()
{
	std::vector<std::string> stringLine = calendar->getString();
	if (stringLine.size() == 0)
		return;
	this->SuspendLayout();
	this->ShowLayout->Controls->Clear();
	array<Control^>^temp = gcnew array<Control^>(stringLine.size());
	for (int i = 0; i < stringLine.size(); ++i)
	{
		Label^ itsDay = gcnew Label();
		itsDay->ForeColor = System::Drawing::Color::Blue;
		String^ string = gcnew System::String(stringLine.at(i).c_str());
		itsDay->MaximumSize =System::Drawing::Size(400, 23);
		itsDay->AutoSize = true;
		itsDay->TextAlign = System::Drawing::ContentAlignment::TopLeft;
		itsDay->Text = string;
		itsDay->Tag = string;
		itsDay->Click += gcnew System::EventHandler(this, &MyForm::DeleteButton_Click);
		temp[i] = itsDay;
		this->ShowLayout->RowCount++;
	}
	this->ShowLayout->Controls->AddRange(temp);
	this->ResumeLayout();
}

Void Organizer::MyForm::button2_Click(System::Object^  sender, System::EventArgs^  e)
{
	calendar->plusMonth();
	CheckingDate();
}

System::Void Organizer::MyForm::DeleteButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (MessageBox::Show("Вы действительно хотите удалить событие?", "Удаление", MessageBoxButtons::OKCancel) == System::Windows::Forms::DialogResult::Cancel)
		return;
	Label^ itsLabel = (Label^)sender;
	String^ string = itsLabel->Text;
	this->ShowLayout->Controls->RemoveByKey(string);
	const char *cString = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string)).ToPointer();
	calendar->DeleteEvent(cString);
	showEvent();
}

Void Organizer::MyForm::button1_Click(System::Object^  sender, System::EventArgs^  e)
{
	calendar->minusMonth();
	CheckingDate();
}

Void Organizer::MyForm::MyForm_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e)
{
	String^ newCol = gcnew String(itsColor[opt->backcolor].c_str());
	this->BackColor = System::Drawing::Color::FromName(newCol);
	switch (opt->backcolor)
	{
	case 0:
	{
		this->Month->ForeColor = System::Drawing::Color::Black;
		this->year->ForeColor = System::Drawing::Color::Black;
		break;
	}
	case 1:
	{
		this->Month->ForeColor = System::Drawing::Color::AliceBlue;
		this->year->ForeColor = System::Drawing::Color::AliceBlue;
		break;
	}
	case 2:
	{
		this->Month->ForeColor = System::Drawing::Color::White;
		this->year->ForeColor = System::Drawing::Color::White;
		break;
	}
	default:
		break;
	}
}

Void Organizer::MyForm::button1_Click_1(System::Object^  sender, System::EventArgs^  e)
{
	Settings setting;
	setting.ChangeColor->SelectedIndex = opt->backcolor;
	setting.warnTime->Text = System::Convert::ToString(opt->time);
	if (setting.ShowDialog() == System::Windows::Forms::DialogResult::OK)
	{
		if (opt->backcolor != setting.ChangeColor->SelectedIndex)
			opt->backcolor = setting.ChangeColor->SelectedIndex;
		if (opt->time != System::Convert::ToInt32(setting.warnTime->Text))
			opt->time = System::Convert::ToInt32(setting.warnTime->Text);
	}
	this->Invalidate();
}


Void Organizer::MyForm::timer1_Tick(System::Object^  sender, System::EventArgs^  e)
{
	std::string message = calendar->MesEvent(30);
	if (message != "null")
	{
		String^ mes = gcnew System::String(message.c_str());
		String^ caption = "Оповещение";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		System::Windows::Forms::DialogResult result;
		result = MessageBox::Show(this, mes, caption, buttons);
	}
}

Void Organizer::MyForm::addEvent_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (this->comboBox1->Text->Length == 0 || this->comboBox2->Text->Length == 0)
	{
		String^ message = "Вы не указали время события";
		String^ caption = "Ошибка ввода";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		System::Windows::Forms::DialogResult result;
		result = MessageBox::Show(this, message, caption, buttons);
		return;
	}
	int hour = System::Convert::ToInt32(this->comboBox1->Text);
	int min = System::Convert::ToInt32(this->comboBox2->Text);
	String^ string = this->textBox1->Text;
	const char *cString = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(string)).ToPointer();
	if (calendar->NewEvent(cString, hour, min))
	{
		String^ message = "Вы не указали дату события";
		String^ caption = "Ошибка ввода";
		MessageBoxButtons buttons = MessageBoxButtons::OK;
		System::Windows::Forms::DialogResult result;
		result = MessageBox::Show(this, message, caption, buttons);
		return;
	}
	String^ message = "Дата успешно добавлена";
	String^ caption = "Дата добавлена";
	MessageBoxButtons buttons = MessageBoxButtons::OK;
	this->textBox1->Clear();
	System::Windows::Forms::DialogResult result;
	result = MessageBox::Show(this, message, caption, buttons);
	showEvent();
}

void Organizer::MyForm::ReplaceСalendar(int num, int month, int year)
{
	this->SuspendLayout();
	this->FCalendar->Controls->Clear();
	month++;
	int a = double(14 - month) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	int week = (1 + y + y / 4 - y / 100 + y / 400 + (31 * m) / 12) % 7;
	if (week == 0)
		week += 7;
	array<Control^>^temp = gcnew array<Control^>(num + week);
	if (week != 1)
	{
		int k = 1;
		while (k != week)
		{
			Button^ itsDay = gcnew Button();
			itsDay->Size = System::Drawing::Size(40, 30);
			itsDay->Enabled = false;
			itsDay->FlatAppearance->BorderSize = 0;
			itsDay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			temp[k] = itsDay;
			k++;
		}
	}
	for (int i = 1; i <= num; ++i)
	{
		Button^ itsDay = gcnew Button();
		itsDay->BackColor = System::Drawing::Color::White;
		itsDay->ForeColor = System::Drawing::Color::Blue;
		String^ string = String::Format("{0}", i);
		itsDay->Text = string;
		itsDay->Tag = i;
		itsDay->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		itsDay->Size = System::Drawing::Size(40, 30);
		itsDay->Click += gcnew System::EventHandler(this, &MyForm::CalendarButton_Click);
		temp[i + week - 1] = itsDay;
	}
	this->FCalendar->Controls->AddRange(temp);
	this->ResumeLayout();
}

System::Void Organizer::MyForm::CalendarButton_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	Button^ itsButton = (Button^)sender;
	int month = calendar->GetMonth();
	String^ stringM = gcnew System::String(sMonth[month].c_str());
	int year = calendar->GetYear();
	String^ string = String::Format("{0} {1} {2} года", itsButton->Tag, stringM, year);
	this->Data->Text = string;
	calendar->newDate((int)itsButton->Tag, month, year);
	return System::Void();
}

Option::Option()
{
}

void Option::LoadOpt(std::string file_name)
{
	std::ifstream input(file_name);
	if (!input.is_open())
	{
		input.close();
		return;
	}
	std::string str;
	do
	{
		input >> str;
	} while (str != "[BACKCOLOR]" && input.good());
	getline(input, str, '=');
	input >> this->backcolor;
	input.seekg(0);
	do
	{
		input >> str;
	} while (str != "[TIME]" && input.good());
	getline(input, str, '=');
	int tim;
	input >> tim;
	this->time = tim;
	input.close();
}

void Option::SaveOpt(std::string file_name)
{
	std::ofstream output(file_name, std::ios_base::out | std::ios_base::trunc);
	if (output.is_open())
	{
		output << "[BACKCOLOR] = " << this->backcolor << std::endl;
		output << "[TIME] = " << this->time << std::endl;
	}
	output.close();
}

Void Organizer::MyForm::MyForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	opt->SaveOpt(SETTINGS);
}

Organizer::MyForm::~MyForm()
{
	if (calendar != NULL)
	{
		delete calendar;
		calendar = NULL;
	}
	if (components)
	{
		delete components;
	}
}

void Organizer::MyForm::InitializeComponent(void)
{
	this->components = (gcnew System::ComponentModel::Container());
	this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
	this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
	this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
	this->Data = (gcnew System::Windows::Forms::Label());
	this->addEvent = (gcnew System::Windows::Forms::Button());
	this->textBox1 = (gcnew System::Windows::Forms::TextBox());
	this->Month = (gcnew System::Windows::Forms::Label());
	this->ButtonLeft = (gcnew System::Windows::Forms::Button());
	this->ButtonRight = (gcnew System::Windows::Forms::Button());
	this->interactionEvent = (gcnew System::Windows::Forms::TabPage());
	this->ShowLayout = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->ChoiceAction = (gcnew System::Windows::Forms::TabControl());
	this->newEvent = (gcnew System::Windows::Forms::TabPage());
	this->year = (gcnew System::Windows::Forms::Label());
	this->FCalendar = (gcnew System::Windows::Forms::TableLayoutPanel());
	this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
	this->button1 = (gcnew System::Windows::Forms::Button());
	this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
	this->label1 = (gcnew System::Windows::Forms::Label());
	this->label2 = (gcnew System::Windows::Forms::Label());
	this->label3 = (gcnew System::Windows::Forms::Label());
	this->label4 = (gcnew System::Windows::Forms::Label());
	this->label5 = (gcnew System::Windows::Forms::Label());
	this->label6 = (gcnew System::Windows::Forms::Label());
	this->label7 = (gcnew System::Windows::Forms::Label());
	this->groupBox1->SuspendLayout();
	this->interactionEvent->SuspendLayout();
	this->ChoiceAction->SuspendLayout();
	this->newEvent->SuspendLayout();
	this->SuspendLayout();
	// 
	// comboBox1
	// 
	this->comboBox1->FormattingEnabled = true;
	this->comboBox1->Location = System::Drawing::Point(6, 192);
	this->comboBox1->Name = L"comboBox1";
	this->comboBox1->Size = System::Drawing::Size(45, 25);
	this->comboBox1->TabIndex = 0;
	// 
	// comboBox2
	// 
	this->comboBox2->FormattingEnabled = true;
	this->comboBox2->Location = System::Drawing::Point(57, 192);
	this->comboBox2->Name = L"comboBox2";
	this->comboBox2->Size = System::Drawing::Size(45, 25);
	this->comboBox2->TabIndex = 1;
	// 
	// groupBox1
	// 
	this->groupBox1->Controls->Add(this->Data);
	this->groupBox1->Controls->Add(this->addEvent);
	this->groupBox1->Controls->Add(this->textBox1);
	this->groupBox1->Controls->Add(this->comboBox1);
	this->groupBox1->Controls->Add(this->comboBox2);
	this->groupBox1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->groupBox1->Location = System::Drawing::Point(10, 20);
	this->groupBox1->Name = L"groupBox1";
	this->groupBox1->Size = System::Drawing::Size(249, 254);
	this->groupBox1->TabIndex = 2;
	this->groupBox1->TabStop = false;
	this->groupBox1->Text = L"Введите событие";
	// 
	// Data
	// 
	this->Data->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(0)));
	this->Data->Location = System::Drawing::Point(108, 191);
	this->Data->Name = L"Data";
	this->Data->Size = System::Drawing::Size(135, 27);
	this->Data->TabIndex = 13;
	this->Data->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	// 
	// addEvent
	// 
	this->addEvent->Location = System::Drawing::Point(145, 225);
	this->addEvent->Name = L"addEvent";
	this->addEvent->Size = System::Drawing::Size(98, 23);
	this->addEvent->TabIndex = 3;
	this->addEvent->Text = L"Добавить";
	this->addEvent->UseVisualStyleBackColor = true;
	this->addEvent->Click += gcnew System::EventHandler(this, &MyForm::addEvent_Click);
	// 
	// textBox1
	// 
	this->textBox1->Location = System::Drawing::Point(6, 30);
	this->textBox1->MaxLength = 128;
	this->textBox1->Multiline = true;
	this->textBox1->Name = L"textBox1";
	this->textBox1->Size = System::Drawing::Size(226, 153);
	this->textBox1->TabIndex = 2;
	// 
	// Month
	// 
	this->Month->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 15.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->Month->Location = System::Drawing::Point(143, 59);
	this->Month->Name = L"Month";
	this->Month->Size = System::Drawing::Size(151, 33);
	this->Month->TabIndex = 4;
	this->Month->Text = L"Месяц";
	this->Month->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
	// 
	// ButtonLeft
	// 
	this->ButtonLeft->BackColor = System::Drawing::SystemColors::ButtonFace;
	this->ButtonLeft->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->ButtonLeft->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->ButtonLeft->ForeColor = System::Drawing::SystemColors::Highlight;
	this->ButtonLeft->Location = System::Drawing::Point(53, 69);
	this->ButtonLeft->Name = L"ButtonLeft";
	this->ButtonLeft->Size = System::Drawing::Size(75, 23);
	this->ButtonLeft->TabIndex = 5;
	this->ButtonLeft->Text = L"<<";
	this->ButtonLeft->UseVisualStyleBackColor = false;
	this->ButtonLeft->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
	// 
	// ButtonRight
	// 
	this->ButtonRight->BackColor = System::Drawing::SystemColors::ButtonFace;
	this->ButtonRight->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
	this->ButtonRight->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 12, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->ButtonRight->ForeColor = System::Drawing::SystemColors::Highlight;
	this->ButtonRight->Location = System::Drawing::Point(315, 69);
	this->ButtonRight->Name = L"ButtonRight";
	this->ButtonRight->Size = System::Drawing::Size(75, 23);
	this->ButtonRight->TabIndex = 6;
	this->ButtonRight->Text = L">>";
	this->ButtonRight->UseVisualStyleBackColor = false;
	this->ButtonRight->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
	// 
	// interactionEvent
	// 
	this->interactionEvent->BackColor = System::Drawing::Color::Transparent;
	this->interactionEvent->Controls->Add(this->ShowLayout);
	this->interactionEvent->Location = System::Drawing::Point(4, 22);
	this->interactionEvent->Name = L"interactionEvent";
	this->interactionEvent->Padding = System::Windows::Forms::Padding(3);
	this->interactionEvent->Size = System::Drawing::Size(265, 293);
	this->interactionEvent->TabIndex = 1;
	this->interactionEvent->Text = L"События";
	// 
	// ShowLayout
	// 
	this->ShowLayout->AutoScroll = true;
	this->ShowLayout->ColumnCount = 1;
	this->ShowLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent, 100)));
	this->ShowLayout->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 20)));
	this->ShowLayout->Location = System::Drawing::Point(7, 6);
	this->ShowLayout->Name = L"ShowLayout";
	this->ShowLayout->RowCount = 1;
	this->ShowLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->ShowLayout->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 20)));
	this->ShowLayout->Size = System::Drawing::Size(252, 281);
	this->ShowLayout->TabIndex = 0;
	// 
	// ChoiceAction
	// 
	this->ChoiceAction->Controls->Add(this->interactionEvent);
	this->ChoiceAction->Controls->Add(this->newEvent);
	this->ChoiceAction->ImeMode = System::Windows::Forms::ImeMode::Disable;
	this->ChoiceAction->Location = System::Drawing::Point(470, 69);
	this->ChoiceAction->Name = L"ChoiceAction";
	this->ChoiceAction->SelectedIndex = 0;
	this->ChoiceAction->Size = System::Drawing::Size(273, 319);
	this->ChoiceAction->TabIndex = 10;
	// 
	// newEvent
	// 
	this->newEvent->BackColor = System::Drawing::Color::Transparent;
	this->newEvent->Controls->Add(this->groupBox1);
	this->newEvent->ForeColor = System::Drawing::SystemColors::ControlText;
	this->newEvent->Location = System::Drawing::Point(4, 22);
	this->newEvent->Name = L"newEvent";
	this->newEvent->Padding = System::Windows::Forms::Padding(3);
	this->newEvent->Size = System::Drawing::Size(265, 293);
	this->newEvent->TabIndex = 2;
	this->newEvent->Text = L"Добавить событие";
	// 
	// year
	// 
	this->year->AutoSize = true;
	this->year->Location = System::Drawing::Point(205, 91);
	this->year->Name = L"year";
	this->year->Size = System::Drawing::Size(25, 13);
	this->year->TabIndex = 11;
	this->year->Text = L"Год";
	// 
	// FCalendar
	// 
	this->FCalendar->ColumnCount = 7;
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle()));
	this->FCalendar->Location = System::Drawing::Point(53, 130);
	this->FCalendar->Name = L"FCalendar";
	this->FCalendar->RowCount = 5;
	this->FCalendar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->FCalendar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->FCalendar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->FCalendar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->FCalendar->RowStyles->Add((gcnew System::Windows::Forms::RowStyle()));
	this->FCalendar->Size = System::Drawing::Size(337, 235);
	this->FCalendar->TabIndex = 12;
	// 
	// button1
	// 
	this->button1->Location = System::Drawing::Point(669, 398);
	this->button1->Name = L"button1";
	this->button1->Size = System::Drawing::Size(92, 23);
	this->button1->TabIndex = 13;
	this->button1->Text = L"Настройки";
	this->button1->UseVisualStyleBackColor = true;
	this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click_1);
	// 
	// timer1
	// 
	this->timer1->Enabled = true;
	this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
	// 
	// label1
	// 
	this->label1->AutoSize = true;
	this->label1->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label1->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label1->Location = System::Drawing::Point(62, 111);
	this->label1->Name = L"label1";
	this->label1->Size = System::Drawing::Size(25, 17);
	this->label1->TabIndex = 14;
	this->label1->Text = L"Пн";
	// 
	// label2
	// 
	this->label2->AutoSize = true;
	this->label2->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label2->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label2->Location = System::Drawing::Point(109, 111);
	this->label2->Name = L"label2";
	this->label2->Size = System::Drawing::Size(26, 17);
	this->label2->TabIndex = 15;
	this->label2->Text = L"Вт";
	// 
	// label3
	// 
	this->label3->AutoSize = true;
	this->label3->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label3->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label3->Location = System::Drawing::Point(159, 111);
	this->label3->Name = L"label3";
	this->label3->Size = System::Drawing::Size(23, 17);
	this->label3->TabIndex = 16;
	this->label3->Text = L"Ср";
	// 
	// label4
	// 
	this->label4->AutoSize = true;
	this->label4->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label4->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label4->Location = System::Drawing::Point(202, 111);
	this->label4->Name = L"label4";
	this->label4->Size = System::Drawing::Size(28, 17);
	this->label4->TabIndex = 17;
	this->label4->Text = L"Чт";
	// 
	// label5
	// 
	this->label5->AutoSize = true;
	this->label5->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label5->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label5->Location = System::Drawing::Point(246, 111);
	this->label5->Name = L"label5";
	this->label5->Size = System::Drawing::Size(27, 17);
	this->label5->TabIndex = 18;
	this->label5->Text = L"Пт";
	// 
	// label6
	// 
	this->label6->AutoSize = true;
	this->label6->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label6->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label6->Location = System::Drawing::Point(294, 111);
	this->label6->Name = L"label6";
	this->label6->Size = System::Drawing::Size(22, 17);
	this->label6->TabIndex = 19;
	this->label6->Text = L"Сб";
	// 
	// label7
	// 
	this->label7->AutoSize = true;
	this->label7->Font = (gcnew System::Drawing::Font(L"Monotype Corsiva", 11.25F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
		static_cast<System::Byte>(204)));
	this->label7->ForeColor = System::Drawing::SystemColors::Highlight;
	this->label7->Location = System::Drawing::Point(341, 111);
	this->label7->Name = L"label7";
	this->label7->Size = System::Drawing::Size(22, 17);
	this->label7->TabIndex = 20;
	this->label7->Text = L"Вс";
	// 
	// MyForm
	// 
	this->ClientSize = System::Drawing::Size(773, 433);
	this->Controls->Add(this->label7);
	this->Controls->Add(this->label6);
	this->Controls->Add(this->label5);
	this->Controls->Add(this->label4);
	this->Controls->Add(this->label3);
	this->Controls->Add(this->label2);
	this->Controls->Add(this->label1);
	this->Controls->Add(this->button1);
	this->Controls->Add(this->FCalendar);
	this->Controls->Add(this->year);
	this->Controls->Add(this->ChoiceAction);
	this->Controls->Add(this->ButtonRight);
	this->Controls->Add(this->ButtonLeft);
	this->Controls->Add(this->Month);
	this->MaximizeBox = false;
	this->Name = L"MyForm";
	this->Text = L"Органайзер";
	this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MyForm::MyForm_FormClosing);
	this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load_1);
	this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MyForm::MyForm_Paint);
	this->groupBox1->ResumeLayout(false);
	this->groupBox1->PerformLayout();
	this->interactionEvent->ResumeLayout(false);
	this->ChoiceAction->ResumeLayout(false);
	this->newEvent->ResumeLayout(false);
	this->ResumeLayout(false);
	this->PerformLayout();
}