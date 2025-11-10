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
	using namespace System::Collections::Generic;

	/// <summary>
	/// —водка дл€ MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
	
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

			for each(Point peace_snake in snake_collection) {
				
				argument_graph->FillRectangle(new_snake_brush, peace_snake.X, peace_snake.Y, block_size, block_size);
			
			}

		}

	private:
		/// <summary>
		/// ќб€зательна€ переменна€ конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
		List<Point>^ snake_collection = gcnew List<Point>();
		Point food_position;
		Timer^ move_timer = gcnew Timer();
		Label^ score_label = gcnew Label();
		
		const int block_size = 20;
		int move_X = 0;
		int move_Y = 0;
		int score = 0;
		

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

			snake_collection->Add(Point(100, 100));

			initialize_score_label();
			new_food_position();
			initialize_move_timer();

			this->Paint += gcnew PaintEventHandler(this, &MainForm::on_paint);
			this->KeyDown += gcnew KeyEventHandler(this, &MainForm::button_click);

		}


#pragma endregion

		void new_food_position() {

			srand(time(NULL));

			int max_x = this->ClientSize.Width / block_size;
			int max_y = this->ClientSize.Height / block_size;

			do {
				food_position = Point(rand() % max_x * block_size, rand() % max_y * block_size);
			} while (snake_collection->Contains(food_position));
		}

		void move_snake_position(Object^ object, EventArgs^ arguments) {

			increase_snake();
			snake_collection->RemoveAt(snake_collection->Count - 1);

			if (game_over()) {

				move_timer->Stop();
				MessageBox::Show("GAME OVER! Score: " + score);
				return;
			}

			if (snake_collection[0] == food_position) {
				
				increase_snake();
				new_food_position();
				
				score++;
				score_label->Text = "Score: " + score;
			}

			//move_timer->Interval = 200 / snake_collection->Count;

			this->Invalidate();
		}

		void initialize_score_label() {

			score_label->BackColor = Color::Transparent;
			score_label->ForeColor = Color::Red;
			score_label->Location = Point(10, 10);
			score_label->Text = "Score: " + score;
			this->Controls->Add(score_label);
			
		}

		void initialize_move_timer() {

			move_timer->Interval = 100;
			move_timer->Tick += gcnew EventHandler(this, &MainForm::move_snake_position);
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
	
		void increase_snake() {

			Point new_head = snake_collection[0];
			new_head.X += move_X * block_size;
			new_head.Y += move_Y * block_size;

			snake_collection->Insert(0, new_head);

		}

		bool game_over() {

			Point head_snake = snake_collection[0];

			bool hit_wall = head_snake.X < 0
				|| head_snake.Y < 0
				|| head_snake.X >= ClientSize.Width
				|| head_snake.Y >= ClientSize.Height;

			bool eat_youself = false;

			for (int i = 1; i < snake_collection->Count; i++) {
				
				if (head_snake == snake_collection[i]) {
					
					eat_youself = true;
					break;
				}

			}

			return hit_wall || eat_youself;
		}

};

}
