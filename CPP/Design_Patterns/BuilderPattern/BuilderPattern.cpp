#include<iostream>
#include<memory>
#include<string>
//#include "unique.h"

using namespace std;

class Pizza
{
    public:
        void ShowPizza()
        {
            cout << "Topping = " << m_topping << endl; 
            cout << "Sauce = " << m_sauce << endl; 
            cout << "Base = " << m_base << endl; 
        }

        void setTopping( const string & str )   
        {   m_topping = str;  }

        void setSauce( const string & str )     
        {   m_sauce = str;    }

        void setBase( const string & str )      
        {   m_base = str;     }

    private:
        string m_topping;
        string m_sauce;
        string m_base;
};

class PizzaBuilder
{
    public:
        virtual ~PizzaBuilder () {} ;

        Pizza * getPizza()
        { return m_pizza;   }//.release(); }

        void createPizza()
        {
            m_pizza = new Pizza;//make_unique<Pizza>();
        }

        virtual void buildTopping() = 0;
        virtual void buildSauce() = 0;
        virtual void buildBase() = 0;

    protected:
        //unique_ptr <Pizza> m_pizza;
        Pizza *m_pizza;
};

class SpicyPizza : public PizzaBuilder
{
    public:
        ~SpicyPizza() {}
        void buildTopping()
        {
            m_pizza->setTopping( "SpicyTopping" );
        }
        void buildSauce( )
        {
            m_pizza->setSauce( "SpicySauce" );
        }
        void buildBase( )
        {
            m_pizza->setBase( "SpicyBase" );
        }
};

class Non_SpicyPizza : public PizzaBuilder
{
    public:
        ~Non_SpicyPizza() {}
        void buildTopping()
        {
            m_pizza->setTopping( "Non_SpicyTopping" );
        }
        void buildSauce( )
        {
            m_pizza->setSauce( "Non_SpicySauce" );
        }
        void buildBase( )
        {
            m_pizza->setBase( "Non_SpicyBase" );
        }
};

class Cook
{
    public:
        void ShowPizza()
        {
            m_pizzaBuilder->getPizza()->ShowPizza();
        }
        void PreparePizza ( PizzaBuilder *pizza)
        {
            m_pizzaBuilder = pizza;
            m_pizzaBuilder->createPizza();
            m_pizzaBuilder->buildTopping();
            m_pizzaBuilder->buildSauce();
            m_pizzaBuilder->buildBase();
        }

    private:
        PizzaBuilder * m_pizzaBuilder;
};

int main()
{
    Cook cook;
    Non_SpicyPizza nsp;
    SpicyPizza sp;

    cook.PreparePizza ( &nsp );
    cook.ShowPizza();

    cook.PreparePizza ( &sp );
    cook.ShowPizza();

    return 0;
}
