#pragma once

#include <stdlib.h>
#include <math.h>
#include <stdio.h>
int X, Y;

void turn(int x0, int y0, int alfa, float x, float y,float* x1, float* y1)
{
float t;
t=alfa*3.14/180;
*x1=x0+(x-x0)*cos(t)+(y-y0)*sin(t);
*y1=y0-(x-x0)*sin(t)+(y-y0)*cos(t);
return;
}

namespace graphika {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// ������ ��� Form1
	///
	/// ��������! ��� ��������� ����� ����� ������ ���������� ����� ��������
	///          �������� ����� ����� �������� ("Resource File Name") ��� �������� ���������� ������������ �������,
	///          ���������� �� ����� ������� � ����������� .resx, �� ������� ������� ������ �����. � ��������� ������,
	///          ������������ �� ������ ��������� �������� � ���������������
	///          ���������, ��������������� ������ �����.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: �������� ��� ������������
			//
		}

	protected:
		/// <summary>
		/// ���������� ��� ������������ �������.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected: 
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown1;
	private: System::Windows::Forms::NumericUpDown^  numericUpDown2;
	private: System::Windows::Forms::ColorDialog^  colorDialog1;
	private: System::Windows::Forms::Button^  button2;
	

	private:
		/// <summary>
		/// ��������� ���������� ������������.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// ������������ ����� ��� ��������� ������������ - �� ���������
		/// ���������� ������� ������ ��� ������ ��������� ����.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->numericUpDown2 = (gcnew System::Windows::Forms::NumericUpDown());
			this->colorDialog1 = (gcnew System::Windows::Forms::ColorDialog());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->pictureBox1->Location = System::Drawing::Point(42, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(457, 400);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(168, 419);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(150, 30);
			this->button1->TabIndex = 2;
			this->button1->Text = L"��������";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::button1_Click_1);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(99, 428);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"��������";
			this->label1->Click += gcnew System::EventHandler(this, &Form1::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(331, 428);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"��������";
			this->label2->Click += gcnew System::EventHandler(this, &Form1::label2_Click);
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(399, 424);
			this->numericUpDown1->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, 0});
			this->numericUpDown1->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {5, 0, 0, System::Int32::MinValue});
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(40, 20);
			this->numericUpDown1->TabIndex = 5;
			this->numericUpDown1->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown1_ValueChanged);
			// 
			// numericUpDown2
			// 
			this->numericUpDown2->Location = System::Drawing::Point(46, 424);
			this->numericUpDown2->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) {10, 0, 0, 0});
			this->numericUpDown2->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown2->Name = L"numericUpDown2";
			this->numericUpDown2->Size = System::Drawing::Size(40, 20);
			this->numericUpDown2->TabIndex = 6;
			this->numericUpDown2->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {1, 0, 0, 0});
			this->numericUpDown2->ValueChanged += gcnew System::EventHandler(this, &Form1::numericUpDown2_ValueChanged);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(452, 426);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 7;
			this->button2->Text = L"����";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::button2_Click);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(539, 460);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->numericUpDown2);
			this->Controls->Add(this->numericUpDown1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->pictureBox1);
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"������������ ������������ ������";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->numericUpDown2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

#pragma endregion

	private: Color myColor1;
	private: Color myColor;
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				Bitmap ^myBitmap = gcnew Bitmap(pictureBox1->Width,pictureBox1->Height);
				 Graphics ^g2=Graphics::FromImage(myBitmap);
				 g2->Clear(System::Drawing::Color::White);
				 
				 PointF point1=Point(150,100);
				 PointF point2=Point(150,200);
				 PointF point3=Point(300,200);
				 array <PointF> ^PointsXY={point1,point2,point3};
				 Pen ^myPen= gcnew Pen(System::Drawing::Color::Red,3);
				 g2->DrawPolygon(myPen,PointsXY);
				 pictureBox1->BackgroundImage::set(myBitmap);
			 }
	private: System::Void pictureBox1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void button1_Click_1(System::Object^  sender, System::EventArgs^  e) 
			 {
				
				int N=3; // N=3 ������ �����������
				PointF point1=PointF(200,100); // ������ ����������
				PointF point2=PointF(200,200); // ������
				PointF point3=PointF(350,200); // ������������
				int xC=200,yC=200; //�������
				int i,Angle,k,Tempo; // ���������
				float x,y,X,Y; // ����������
				// ������� ������ �� ����������� �������
				Graphics ^g=pictureBox1->CreateGraphics();
				g->Clear(System::Drawing::Color::White);
				Pen ^myPen= gcnew Pen(myColor,3);
				Pen ^myPen1=gcnew Pen(myColor1,3);
				// ��� �������� ���� ������ ����(BLACK) � ������� ����� (3)
				array <PointF> ^PointsXY={point1,point2,point3};
				// ������ ����������� ��� ������� DrawPolygon()
				g->DrawPolygon(myPen,PointsXY);
			
				// ����� ��������
				k=(int)this->numericUpDown2->Value;
				// �������� ��������, ������������� �������� Tempo
				// �������� �������� ������ ������� �������
				Tempo=(int)this->numericUpDown1->Value;
				if(!Tempo)
					{
						MessageBox::Show("�������� �� ������ ��������� ����!",
						"��������!");
						return;
					}
				do{
					for(Angle=0;Angle<360;Angle+=Math::Abs(Tempo))
						{
						//����� ���� ������� ����������� ������������
						myPen->Color::set(Color::White);
						g->DrawPolygon(myPen,PointsXY);
						for(i=0;i<N;i++)
							{
							x=PointsXY[i].X; y=PointsXY[i].Y;
							// ������� turn ������������ ������ ������� (x,y) �� ���� Tempo
							// ������ ������� (xC,Yc)
							turn(xC,yC,-Tempo,x,y,&X,&Y);
							PointsXY[i].X=X; PointsXY[i].Y=Y;
							}
						//������ ���� ������ ����������� � ����� (����� ��������) ���������
						myPen->Color::set(Color::Red);
						g->DrawPolygon(myPen1,PointsXY);
						// ����� �������� ������� �����:
						// myPen->Width::set(3);
						myPen->Color::set(Color::Aqua);
						g->DrawEllipse(myPen,xC-3,yC-3,7,7);
						_sleep(100); //�������� �� 50 ��, �������� � <stdlib.h>
						}
				} while (--k);
				this->numericUpDown1->Value=1;
			 }
private: System::Void numericUpDown1_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label2_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void label1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void numericUpDown2_ValueChanged(System::Object^  sender, System::EventArgs^  e) {
			 }
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			if (this->colorDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
				 myColor1 = this->colorDialog1->Color;
				Bitmap ^myBitmap = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
			 Graphics ^g = Graphics::FromImage(myBitmap);
			 Pen ^myPen1= gcnew Pen(myColor1, 3);
			 g->Clear(Color::White);
			 PointF point1=Point(200,100);
			 PointF point2=Point(200,200);
			 PointF point3=Point(350,200);
			
			 array <PointF> ^PointsXY={point1,point2,point3};
			 g->DrawPolygon(myPen1,PointsXY);
			 pictureBox1->BackgroundImage::set(myBitmap);
		 }

private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e) 
		 {
			myColor=Color::Black;
			Bitmap ^myBitmap = gcnew Bitmap(pictureBox1->Width,pictureBox1->Height);
			Graphics ^g2=Graphics::FromImage(myBitmap);
			g2->Clear(System::Drawing::Color::White);
			Pen ^myPen= gcnew Pen(System::Drawing::Color::Black,3);

			int xC=200,yC=200; /* �������� ���������� */
			PointF point1=Point(200,100);
			PointF point2=Point(200,200);
			PointF point3=Point(350,200);
			array <PointF> ^PointsXY={point1,point2,point3};

			g2->DrawPolygon(myPen,PointsXY);
			myPen->Color=myColor;
			//myPen= gcnew Pen(System::Drawing::Color::Aqua,3);
			g2->DrawEllipse(myPen,xC-3,yC-3,7,7);
			pictureBox1->BackgroundImage::set(myBitmap);
		 }

};
}

