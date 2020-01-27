#include <iostream>

using namespace std;

class Component
{
    public:
        virtual void operation() = 0;
};


class ConcreteComponent : public Component
{
    public:
        virtual void operation()
        {
            cout << " In ConcreteComponent " << endl;
        }
};

class Decorator : public Component
{
    Component *mComponent;

    public:
        Decorator ( Component *comp ): mComponent(comp) 
        { 
            cout << "In Decorator" << comp <<endl;
        }

        virtual void operation()
        {
            cout << "operation : In Decorator " << endl;
        }
        
};

class ConcreteDecoratorA : public Decorator
{
    public:
        ConcreteDecoratorA ( Component *comp ): Decorator(comp) 
        { 
            cout << "In ConcreteDecoratorA " << comp << endl;
        }

        virtual void operation()
        {
            cout << "operation : In ConcreteDecoratorA " << endl;
        }
};

class ConcreteDecoratorB : public Decorator
{
    public:
        ConcreteDecoratorB ( Component *comp ): Decorator(comp) 
        { 
            cout << "In ConcreteDecoratorB " << comp << endl;
        }

        virtual void operation()
        {
            cout << "operation : In ConcreteDecoratorB " << endl;
        }
};


int main()
{
    ConcreteComponent * ccObj = new ConcreteComponent ;

    ConcreteDecoratorB * ccbObj = new ConcreteDecoratorB (ccObj);

    Component *obj = new ConcreteDecoratorA ( ccbObj );
    
}
