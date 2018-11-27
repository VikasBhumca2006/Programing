/*
 * C++ Program to Implement Complex Numbers using Classes
 */
class Complex
{
    private:
        int real;
        int imag;

    public:

        Complex(int r = 0, int i = 0): real(r), imag(i) {};

        void setComplex(void);
        Complex add(const Complex& c);
        Complex subtract(const Complex& c);
        void printComplex(void);
};
