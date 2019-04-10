#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Light {
public:
	Light(string name) {
		this->name = name;
	}
	void on() {
		cout << name << " on" << endl;
	}
	void off() {
		cout << name << " off" << endl;
	}
private:
	string name;
};


class Command {
public:
	virtual void execute() = 0;
};

class NoCommand :public Command {
public:
	void execute() {
		cout << "nothing happen" << endl;
	}
};

class LightOnCommand :public Command {
private:
	Light& light;
public:
	LightOnCommand(Light& l): light(l){}
	void execute() {
		light.on();
	}
};

class LightOffCommand :public Command {
private:
	Light& light;
public:
	LightOffCommand(Light& l):light(l){}
	void execute() {
		light.off();
	}
};

class RemoteControl {
public:
	RemoteControl(Command* defaultCommand) {
		onCommands.resize(2);
		offCommands.resize(2);
		for (int i = 0; i < 2; i++){
			onCommands[i] = defaultCommand;
			offCommands[i] = defaultCommand;
		}
	}
	void setCommand(int slot, Command* onCommand, Command* offCommand) {
		onCommands[slot] = onCommand;
		offCommands[slot] = offCommand;
	}
	void onButtonWasPushed(int slot) {
		onCommands[slot]->execute();
	}
	void offButtonWasPushed(int slot) {
		offCommands[slot]->execute();
	}
private:
	vector<Command*> onCommands;
	vector<Command*> offCommands;
};


int main() {
	Light light1("l1");
	Light light2("l2");
	LightOnCommand light1On(light1);
	LightOffCommand light1Off(light1);
	LightOnCommand light2On(light2);
	LightOffCommand light2Off(light2);
	NoCommand noCommand;
	RemoteControl control(&noCommand);

	control.setCommand(0, &light1On,&light1Off);
	control.setCommand(1, &light2On, &light2Off);

	control.onButtonWasPushed(0);
	control.offButtonWasPushed(0);
	control.onButtonWasPushed(1);
	control.offButtonWasPushed(1);

	system("pause");
	return 0;
}