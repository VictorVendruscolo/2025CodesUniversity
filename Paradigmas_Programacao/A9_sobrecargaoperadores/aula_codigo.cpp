#include<iostream>
#include<string>
using namespace std;

class DFrac{  //manteremos sempre a fração reduzida
    int num;
    unsigned den;
unsigned mmc(DFrac other) const{
            unsigned n1,n2,div,mmc;

            n1  = den;
            n2  = other.den;
            mmc = 1;
            div = 2;

            //enquanto n1>1 ou n2>1, faça            
            //  se n1 ou n2 é divisivel por div, então
            //      se n1 é divisivel por div, então
            //          n1 = n1/div
            //      se n2 é divisivel por div, então
            //          n2 = n2/div 
            //      mmc = mmc * div 
            //  senão
            //      div = div + 1 
            //retorne mmc

            //enquanto n1>1 ou n2>1, faça
            while(n1>1 || n2>1){
            //  se n1 ou n2 é divisivel por div, então
                if(!(n1 % div) || !(n2 % div)){
            //      se n1 é divisivel por div, então
                    if(!(n1 % div))
            //          n1 = n1/div
                        n1 = n1/div;
            //      se n2 é divisivel por div, então
                    if(!(n2 % div))
            //          n2 = n2/div 
                        n2 = n2/div;
                                        
            //      mmc = mmc * div 
                    mmc = mmc * div;
                }
            //  senão
                else
            //      div = div + 1 
                    div++;
            }
            //retorne mmc
            return mmc;
        }
    public:
        DFrac(int num=0,unsigned den=1):
            num(num),
            den(den)
        {}

        int getNum(){
            return num;
        }
        unsigned getDen(){
            return den;
        }
        DFrac operator +(const DFrac &other) {
            unsigned mmc = this->mmc(other);

            return DFrac(mmc/den*num + mmc/other.den*other.num ,mmc);
        }
        DFrac operator -(const DFrac &other) {
            unsigned mmc = this->mmc(other);
            return DFrac(mmc/den*num - mmc/other.den*other.num, mmc);
        }
        DFrac operator *(const DFrac &other) {
            return DFrac(num * other.num, den * other.den);
        }
        DFrac operator /(const DFrac &other) {
            return DFrac(num * other.den, den * other.num);
        }
        bool operator < (const DFrac &other){            
            unsigned mmc = this->mmc(other);

            return (mmc/den*num - mmc/other.den*other.num) < 0;
        
        }
        bool operator > (const DFrac &other){
            unsigned mmc = this->mmc(other);
            return (mmc/den*num - mmc/other.den*other.num) > 0;
        }
        bool operator <= (const DFrac &other){
            unsigned mmc = this->mmc(other);
            return (mmc/den*num - mmc/other.den*other.num) <= 0;
        }
        bool operator >= (const DFrac &other){
            unsigned mmc = this->mmc(other);
            return (mmc/den*num - mmc/other.den*other.num) >= 0;
        }

};
int main(){
    //tarefa: implementar os operadores binários -, *, /, >, <= e >=

    DFrac f1,f2(1,2),f3(1,3);
    bool b;

    f1 = f2 + f3;
    b  = f2 < f3;

    cout<<f1.getNum()<<'/'<<f1.getDen();

    return 0;
}