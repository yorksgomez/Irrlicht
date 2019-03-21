#ifndef EVENTS_INCLUDED
#define EVENTS_INCLUDED

#include <cwchar>
#include <string>
#include <ctype.h>
#include <vector>
#include <iomanip>

namespace base {

class Events : public IEventReceiver {
private:
	Context* context;
	bool eqPressed;

public:
	Events(Context* c) : context(c), eqPressed(true) {}

	virtual bool OnEvent(const SEvent& event) {
		EEVENT_TYPE type = event.EventType;

		if(type == EET_GUI_EVENT) {
			gui::IGUIEditBox* calc = context->mainwindow->getCalc();
				core::stringw str = calc->getText();
			SEvent::SGUIEvent guiev = event.GUIEvent;
			EGUI_EVENT_TYPE guitype = guiev.EventType;

			if(guitype == EGET_EDITBOX_ENTER) {
				int num = 0;
					std::vector<int> nums;
					std::vector<char> ops;
					enum states { NUM, OP } c = NUM;

					for(int i = 0; i < str.size(); i++) {
						char ch = str[i];

						if(std::isdigit(ch)) {

							if(c != NUM) {
								nums.push_back(num);
								num = 0;
							}

							int n = ch - '0';

							if(n >= 0 && n <= 9)
								num = num * 10 + n;
							else
								std::cout << "There has been a login error!" << std::endl;

							c = NUM;
						} else {
							ops.push_back(ch);
							c = OP;
						}

					}

					nums.push_back(num);

					float r = nums.at(0);

					for (int i = 1; i < nums.size(); i++) {
						char op = ops.at(i - 1);

						switch(op) {
							case '+':
								r = r + nums.at(i);
								break;
							case '-':
								r = r - nums.at(i);
								break;
							case '*':
								r = r * nums.at(i);
								break;
							case '/':
								r = r / nums.at(i);
								break;
							case '.':
								r = r + nums.at(i) / 10.f;
								break;
						}

						str = core::stringw(r, 1);
						eqPressed = true;
					}

				std::setprecision(1);
				calc->setText(str.c_str());
			}

			if(guitype == EGET_BUTTON_CLICKED) {
				s32 id = guiev.Caller->getID();
				int num;
				bool isNum, isOp, isEq;
				isNum = isOp = isEq = false;
				enum operation {
					PLUS,
					MINUS,
					MULT,
					DIV,
					EQUAL,
					DOT
				} op;

				switch(id) {
					case BUTTON_0: isNum = true; num = 0; break;
					case BUTTON_1: isNum = num = 1; break;
					case BUTTON_2: isNum = num = 2; break;
					case BUTTON_3: isNum = num = 3; break;
					case BUTTON_4: isNum = num = 4; break;
					case BUTTON_5: isNum = num = 5; break;
					case BUTTON_6: isNum = num = 6; break;
					case BUTTON_7: isNum = num = 7; break;
					case BUTTON_8: isNum = num = 8; break;
					case BUTTON_9: isNum = num = 9; break;
					case BUTTON_PLUS: isOp = true; op = PLUS; break;
					case BUTTON_MINUS: isOp = true; op = MINUS; break;
					case BUTTON_MUL: isOp = true; op = MULT; break;
					case BUTTON_DIV: isOp = true; op = DIV; break;
					case BUTTON_DOT: isOp = true; op = DOT; break;
					case BUTTON_EQUAL: isEq = true; break;
				}

				gui::IGUIEditBox* calc = context->mainwindow->getCalc();
				core::stringw str = calc->getText();

				if(isNum) {

					if(str == "0" || eqPressed) {
						str = L"";
						eqPressed = true;
					}

					str += num;
				} else if(isOp) {
					eqPressed = false;
				
					switch(op) {
						case PLUS: str += L"+"; break;
						case MINUS: str += L"-"; break;
						case MULT: str += L"*"; break;
						case DIV: str += L"/"; break;
						case DOT: str += L"."; break;
					}

				} else if(isEq) {

					int num = 0;
					std::vector<int> nums;
					std::vector<char> ops;
					enum states { NUM, OP } c = NUM;

					for(int i = 0; i < str.size(); i++) {
						char ch = str[i];

						if(std::isdigit(ch)) {

							if(c != NUM) {
								nums.push_back(num);
								num = 0;
							}

							int n = ch - '0';

							if(n >= 0 && n <= 9)
								num = num * 10 + n;
							else
								std::cout << "There has been a login error!" << std::endl;

							c = NUM;
						} else {
							ops.push_back(ch);
							c = OP;
						}

					}

					nums.push_back(num);

					float r = nums.at(0);

					for (int i = 1; i < nums.size(); i++) {
						char op = ops.at(i - 1);

						switch(op) {
							case '+':
								r = r + nums.at(i);
								break;
							case '-':
								r = r - nums.at(i);
								break;
							case '*':
								r = r * nums.at(i);
								break;
							case '/':
								r = r / nums.at(i);
								break;
							case '.':
								r = r + nums.at(i) / 10.f;
								break;
						}

						str = core::stringw(r, 1);
						eqPressed = true;
					}

				}
				std::setprecision(1);
				calc->setText(str.c_str());
			}

		}

		return false;
	}

};

}


#endif