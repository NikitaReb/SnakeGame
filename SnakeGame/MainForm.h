#pragma once

#include <time.h>
#include <stdlib.h>


namespace SnakeGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// ќсвободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

		virtual void on_paint(System::Object^ paint_object, PaintEventArgs^ paint_arguments) override {

			Graphics^ argument_graph = paint_arguments->Graphics;

			Brush^ new_food_brush = gcnew SolidBrush(Color::Firebrick);
			Brush^ new_snake_brush = gcnew SolidBrush(Color::Green);

			argument_graph->FillRectangle(new_food_brush, food_position.X, food_position.Y, block_size, block_size);
			argument_graph->FillRectangle(new_snake_brush, snake_position.X, snake_position.Y, block_size + 10, block_size);

		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
		Point snake_position;
		Point food_position;
		const int block_size = 20;
		Timer^ move_timer;
		int move_X = 0;
		int move_Y = 0;

#pragma region Windows Form Designer generated code

		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(1000, 1000);
			this->Text = L"Feed snake";
			this->BackColor = Color::Gray;
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			new_food_position();
			new_snake_position();
			initialize_move_timer();

			this->Paint += gcnew PaintEventHandler(this, &MainForm::on_paint);
			this->KeyDown += gcnew KeyEventHandler(this, &MainForm::button_click);


		}


#pragma endregion

		void new_snake_position() {

			int start_position_x = this->ClientSize.Width / 2;
			int start_position_y = this->ClientSize.Height / 2;

			snake_position = Point(start_position_x, start_position_y);

		}
		
		void new_food_position() {

			srand(time(NULL));

			int max_x = this->ClientSize.Width / block_size;
			int max_y = this->ClientSize.Height / block_size;

			food_position = Point(rand() % max_x * block_size, rand() % max_y * block_size);

		}

		void move_snake(Object^ object, EventArgs^ arguments) {

			snake_position.X += move_X * block_size;
			snake_position.Y += move_Y * block_size;

			Invalidate();
		}

		void initialize_move_timer() {

			move_timer = gcnew Timer();
			move_timer->Interval = 200;
			move_timer->Tick += gcnew EventHandler(this, &MainForm::move_snake);
			move_timer->Start();

		}

		void button_click(Object^ object, KeyEventArgs^ arguments) {

			switch (arguments->KeyCode)
			{
			case Keys::Up: 
				
				move_X = 0;
				move_Y = -1;
				break;

			case Keys::Down:

				move_X = 0;
				move_Y = 1;
				break;

			case Keys::Right:

				move_X = 1;
				move_Y = 0;
				break;

			case Keys::Left:

				move_X = -1;
				move_Y = 0;
				break;

			default:
				break;
			}

		}
	};
}
