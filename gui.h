#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <iostream>
#include "RegFile.h"
#include "buffer_1.h"
#include "buffer_2.h"
#include "buffer_3.h"
#include "buffer_4.h"
#include "buffer_5.h"
#include "buffer_6.h"
#include "buffer_7.h"
#include "assembly.h"
#include "dmem.h"
#include "code.h"
#ifndef GUI_H
#define GUI_H
using namespace sf;
int const rows=200;

struct TableD {
		Text index[16];
		Text data[16];
		RectangleShape table[16][2];
	};

class GUI {
	
	private:

		void initializeStages(Text stages[][50], Font& f) {
		for (int i = 0; i < 30;i++) {
			for (int j = 0; j < 50; j++) {
				stages[i][j].setString(" ");
				stages[i][j].setPosition(250 + 150 * j, i * 50 + 115);
				stages[i][j].setFillColor(Color::Black);
				stages[i][j].setFont(f);
				stages[i][j].setCharacterSize(16);
			}

		}
	}
		void displayStages(RenderWindow &window, Text stages[][50], vector <Code> p, int clicks) {
		for (int i = 0; i < p.size(); i++){
			for (int j = 0; j < clicks; j++) {
				window.draw(stages[i][j]);
			}
		}
	}

		
		void InitializeGrid(RectangleShape **r, Color& gray) {

		for (int i = 0; i<50; i++)
			for (int j = 0; j < 100; j++) {
				r[i][j].setOutlineColor(Color::Black);
				r[i][j].setOutlineThickness(1);
				if (i % 2 == 0)
					r[i][j].setFillColor(Color::White);
				else
					r[i][j].setFillColor(gray);
				r[i][j].setPosition(150 * j + 200, i * 50 + 100);
				r[i][j].setSize(Vector2f(150, 50));
			}

	}

		
		void initializeTable( TableD& rf, Font &f, int pos) {
		//Text reg[16];
		for (int i = 0; i < 16; i++) {
			rf.data[i].setFont(f);
			rf.data[i].setCharacterSize(16);
			rf.data[i].setFillColor(Color::Black);
			rf.data[i].setPosition(pos + 55, 105 + i * 30);

			rf.index[i].setString(std::to_string(i));
			rf.index[i].setFont(f);
			rf.index[i].setCharacterSize(16);
			rf.index[i].setFillColor(Color::Black);
			rf.index[i].setPosition(pos + 5, 105 + i * 30);

			rf.table[i][0].setOutlineColor(Color::Black);
			rf.table[i][0].setOutlineThickness(3);

			rf.table[i][0].setFillColor(Color::White);

			rf.table[i][0].setPosition(pos, i * 30 + 100);
			rf.table[i][0].setSize(Vector2f(60, 30));

			rf.table[i][1].setOutlineColor(Color::Black);
			rf.table[i][1].setOutlineThickness(3);

			rf.table[i][1].setFillColor(Color::White);

			rf.table[i][1].setPosition(pos + 50, i * 30 + 100);
			rf.table[i][1].setSize(Vector2f(100, 30));

		}
	}
		void displayTableD(RenderWindow &window, TableD& rf) {

		window.setView(window.getDefaultView());
		for (int i = 0; i < 16; i++) {
			window.draw(rf.table[i][1]);
			window.draw(rf.data[i]);
			window.draw(rf.index[i]);
		}

	}


		void InitializeInstruc(RectangleShape instruct [30][2], Text code [30][2], Font &f) {

		for (int i = 0; i < 30; i++) {
		//	code[i][0].setString(" ");
			code[i][0].setFillColor(Color::Black);
			code[i][0].setFont(f);
			code[i][0].setCharacterSize(14);
			code[i][0].setPosition(650 + 110, 120 + i * 50);
			code[i][1].setString(" ");
			code[i][1].setFillColor(Color::Black);
			code[i][1].setFont(f);
			code[i][1].setCharacterSize(14);
			code[i][1].setPosition(710 + 110, 120 + i * 50);
		}
		for (int i = 0; i<30; i++) {
			instruct[i][0].setOutlineColor(Color::Black);
			instruct[i][0].setOutlineThickness(1);

			instruct[i][0].setFillColor(Color::White);

			instruct[i][0].setPosition(640 + 98, i * 50 + 100);
			instruct[i][0].setSize(Vector2f(60, 50));

			instruct[i][1].setOutlineColor(Color::Black);
			instruct[i][1].setOutlineThickness(1);

			instruct[i][1].setFillColor(Color::White);

			instruct[i][1].setPosition(700 + 98, i * 50 + 100);
			instruct[i][1].setSize(Vector2f(200, 50));
		}
	}
		void displayInstruc(RenderWindow &window, RectangleShape instruct[30][2], Text code[30][2], vector <Code> p) {
		
		window.setView(window.getDefaultView());
		for (int i = 0; i<20; i++) {
			window.draw(instruct[i][0]);
			window.draw(instruct[i][1]);
		}
		for (int i = 0; i < p.size(); i++) {

			window.draw(code[i][0]);
			window.draw(code[i][1]);
		}
	}

	public:
		//regfile display
		TableD reg;
		//memory display
		TableD mem;
		//instructions display
		RectangleShape instruc[30][2];
		Text code[30][2];

		//stages display
		Text stages[30][50];

		//window
		RenderWindow window;

		//misc
		Font f;
		Color bg; 
		Color gray; 
		int clicks;
		int noinst;
		bool keypressed;

		//cycles display
		Text *clk = new Text[100];

		//grid
		RectangleShape **r = NULL;
		View DefaultView;

		//button
		Sprite button;
		Texture t;
		

	GUI() {

			 clicks = 0;
			 noinst = 0;
			 window.create(VideoMode(1800, 900), "R4000 SIMULATOR");
			 DefaultView = window.getDefaultView();
			 DefaultView.setViewport(sf::FloatRect(0.5, 0, 0.5, 1));
			 window.setView(DefaultView);
			 
			 //misc
			 f.loadFromFile("pixy.ttf");	
			 Color bl(0x87ceeb);
			 Color gr(229, 229, 229);
			 bg = bl;
			 gray = gr;
			 keypressed = false;
			 t.loadFromFile("next.png");
			 button.setTexture(t);
			 button.setPosition(100, 700);
			 button.setScale(0.8, 0.5);

			 //initialize cycle counter text
			 for (int i = 0; i < 100; i++) {
				 clk[i].setString("Cycle " + std::to_string(i + 1));
				 clk[i].setFillColor(Color::Black);
				 clk[i].setPosition(240 + 150 * i, 70);
				 clk[i].setFont(f);
				 clk[i].setCharacterSize(16);
			 }

			 //initialize regfile 
			 initializeTable(reg, f, 15);
			 //initialize memory
			 initializeTable(mem, f, 230);

			 //initialize instructions display
			 InitializeInstruc(instruc, code, f);

			 //initialize grid
			 r = new RectangleShape*[50];
			 for (int i = 0; i < 50; i++)
				 r[i] = new RectangleShape[100];
			 InitializeGrid(r, gray);

			 //initialize stages
			 initializeStages(stages, f);

		}

	 void display(vector<Code> p) {

			 window.clear(bg);

			 //setting view
			 window.setView(DefaultView);

			 //drawing cycles
			 for (int i = 0; i < clicks; i++)
				 window.draw(clk[i]);

			

			 //drawing grid
			 for (int i = 0; i < 20; i++) {
				 for (int j = 0; j < clicks; j++)
					 window.draw(r[i][j]);
			 }

 //drawing stages
			 displayStages(window, stages, p, clicks);
			 //drawing assembly
			 displayInstruc(window, instruc, code, p);

			 //drawing regfile
			 displayTableD(window, reg);

			 //drawing dmem
			 displayTableD(window, mem);
			 window.draw(button);

			 window.display();
		}
	
	 void updateStages(int clk,vector <Code> p, 
			buffer_1& b1, buffer_2& b2, buffer_3& b3, buffer_4& b4, 
			buffer_5& b5, buffer_6& b6, buffer_7& b7) {
		
		for (int i = 0; i < p.size(); i++) {
		
			if( b1.inst_num==i+1 &&p[i].numinst!=0)
				stages[i][clk - 1].setString( "IF");
				
			else if( b2.inst_num==i+1 && p[i].numinst != 0)
				stages[i][clk - 1].setString("IS");
				
			else if (b3.inst_num==i+1 && p[i].numinst != 0)
				stages[i][clk - 1].setString( "RF");
			
			else if (b4.inst_num == i + 1 && p[i].numinst != 0)
				stages[i][clk - 1].setString( "EX");
			
			else if (b5.inst_num == i + 1 && p[i].numinst != 0)
				stages[i][clk - 1].setString("DF");
		
			else if (b6.inst_num == i + 1 && p[i].numinst != 0)
				stages[i][clk - 1].setString( "DS");
			
			else if (b7.inst_num == i + 1 && p[i].numinst != 0)
				stages[i][clk - 1].setString( "TC");
			else if(stages[i][clk-2].getString()=="TC")
				stages[i][clk - 1].setString("WB");
			else
				stages[i][clk - 1].setString("");
		}

	}

	 void updateRegFile(RegFile rf) {
		 for (int i = 0; i < 16; i++)
			 reg.data[i].setString(std::to_string(rf.file[i]));
	 }

	 //ask osama
	 void updateDmem(dmem m) {
		 for (int i = 0; i < 16; i++)
			 mem.data[i].setString(std::to_string(0));
	 }

	 void updateInstructions(vector<Code> inst) {
		 for (int i = 0; i < inst.size(); i++) {
			 if (inst[i].numinst != 0) {
				 code[i][0].setString(std::to_string(inst[i].pc));

				 code[i][1].setString(inst[i].wordinst);
			 }
		
		 }
	 }

	 void handleEvents() {
		 keypressed = false;
		 Event event;
		 while (window.pollEvent(event))
		 {
			 if (event.type == Event::Closed)
				 window.close();

			 if (Mouse::isButtonPressed(Mouse::Left)) {

				 //Vector2f v=(window.mapPixelToCoords(Vector2i(Mouse::getPosition(window))));

				 if (button.getGlobalBounds().contains(Vector2f(Mouse::getPosition(window))))
				 {
					 clicks++;
					 keypressed = true;
				 }
			 }

			 if (event.type == Event::KeyPressed)
				 if (Keyboard::isKeyPressed(Keyboard::Right)) {

					 DefaultView.move(100, 0);
					 window.setView(DefaultView);
				 }

			 if (event.type == Event::KeyPressed)
				 if (Keyboard::isKeyPressed(Keyboard::Left)) {
					 DefaultView.move(-100, 0);
					 window.setView(DefaultView);
				 }

			 if (event.type == Event::KeyPressed)
				 if (Keyboard::isKeyPressed(Keyboard::Down)) {
					 DefaultView.move(0, 50);
					 window.setView(DefaultView);
				 }
			 if (event.type == Event::KeyPressed)
				 if (Keyboard::isKeyPressed(Keyboard::Up)) {
					 DefaultView.move(0, -50);
					 window.setView(DefaultView);
				 }
		 }
	 }
};

#endif