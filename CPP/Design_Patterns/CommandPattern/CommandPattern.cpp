#include<iostream>
using namespace std;

class Command
{
    public:
        virtual void execute () = 0;
};

class Light
{
    public:
        void Off ()
        { cout << " Light is OFF " << endl; }

        void ON ()
        { cout << " Light is ON " << endl;  }
};

class LightOffCommand : public Command
{
    private:
        Light *mLight;
    public :
        LightOffCommand ( Light *lightObj ):mLight(lightObj) {}
        void execute () { mLight->Off(); }
};

class LightOnCommand : public Command
{
    private:
        Light *mLight;
    public :
        LightOnCommand ( Light *lightObj ):mLight(lightObj) {}
        void execute () { mLight->ON(); }
};

class Remote
{
    private:
        Command *mCmd;
    public:
        void setCommand ( Command *cmd)
        { mCmd = cmd; }

        void buttonPress ()
        { mCmd->execute(); }
};

int main()
{
    Light *light = new Light;
    LightOffCommand * offPtr = new LightOffCommand ( light );
    LightOnCommand * onPtr = new LightOnCommand ( light );

    Remote *rem = new Remote;

    rem->setCommand ( onPtr );
    rem->buttonPress();

    rem->setCommand ( offPtr );
    rem->buttonPress();

    return 0;
}
