#include <iostream>
//#include <

using namespace std;

class IntfColor
{
    public:
        virtual void fillcolor() = 0; 
};

class RedColor: public IntfColor
{
    public:
        void fillcolor()
        { cout << "I am red" <<endl ; }
};

class BlueColor: public IntfColor
{
    public:
        void fillcolor()
        { cout << "I am blue" <<endl; }
};

class Shap
{
    public:
        virtual void drawShap() = 0;
        virtual void colorShap() = 0;
};

class bridge: public Shap
{
    protected:
        IntfColor *objColor;
    public:
        bridge ( IntfColor *obj )
        { objColor = obj; }
};

class RectAngle: public bridge
{
    public:
        RectAngle(IntfColor * obj):bridge(obj) { }

        void drawShap()
        { cout << "I am RectAngle" <<endl; }

        void colorShap()
        { objColor->fillcolor(); }
};

class Squar: public bridge
{
    public:
        Squar(IntfColor * obj):bridge(obj) { }

        void drawShap()
        { cout << "I am Squar" <<endl; }

        void colorShap()
        { objColor->fillcolor(); }
};


int main()
{
    RedColor *rd = new RedColor;
    RectAngle * rect = new RectAngle(rd);
    rect->drawShap();
    rect->colorShap();

    BlueColor *bl = new BlueColor;
    Squar * sqr = new Squar(bl);
    sqr->drawShap();
    sqr->colorShap();


    return 0;
}
