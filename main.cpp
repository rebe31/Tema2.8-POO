#include <iostream>

using namespace std;

class Complex{
    double re, im;
public:
    Complex(double re = 0, double im = 0){
        this->re = re;
        this->im = im;
    }
    ~Complex(){

    }
    Complex(const Complex& z){
        this->im = z.im;
        this->re = z.re;
    }

    double getre();
    double getim();
    void setre(double re);
    void setim(double im);

    Complex&operator =(Complex t);
    friend istream&operator >>(istream& in, Complex& z);
    friend ostream&operator <<(ostream& out, Complex& z);

    friend class Matrice;
    friend class Nod;
};

double Complex::getre(){
    return this->re;
}

double Complex::getim(){
    return this->im;
}

void Complex::setre(double re){
    this->re = re;
}

void Complex::setim(double im){
    this->im = im;
}

Complex& Complex::operator =(Complex t){
    this->im = t.im;
    this->re = t.re;

    return (*this);
}

istream&operator >>(istream& in, Complex& z){
    double r, i;
    cout<<"Introduceti numarul dorit ( de forma a+bi) :";
    in>>r>>i;
    z.setim(i);
    z.setre(r);

    return in;
}

ostream&operator <<(ostream&out, Complex& z){
    out<<"Numarul este: "<<z.getre()<<" + "<<z.getim()<<"i ";

    return out;
}

class Nod{
    Complex v;
    int lin, col;
    Nod *urm;
public:
    Nod(int lin = 0, int col = 0, Complex v = 0){
        this->lin = lin;
        this->col = col;
        this->v = v;
        this->urm = NULL;
    }

    ~Nod(){

    }

    Nod(const Nod*& p){
        this->lin = p->lin;
        this->col = p->col;
        this->v = p->v;
        this->urm = p->urm;
    }

    int getl();
    int getc();
    Complex& getv();
    Nod*& geturm();
    void seturm(Nod* urm);
    void setv(Complex z);

    Nod&operator =(Nod*& p);

    friend class Matrice;

};

int Nod::getl(){
    return this->lin;
}

int Nod::getc(){
    return this->col;
}

Complex& Nod::getv(){
    return this->v;
}

Nod*& Nod::geturm() {
    return this->urm;
}

void Nod::setv(Complex z) {
    this->v = z;
}

void Nod::seturm(Nod *urm) {
    this->urm = urm;
}


Nod& Nod::operator=(Nod*& p) {
    this->lin = p->lin;
    this->col = p->col;
    this->v = p->v;
    this->urm = p->urm;

    return (*this);
}

class Matrice{
protected:
    int dim1, dim2, nrElem;
    Nod *start, *ultim;
public:

    Matrice(int d1 = 0, int d2 = 0, int nr = 0){
        dim1 = d1;
        dim2 = d2;
        nrElem = nr;
        this->ultim = this->start = NULL;
    }

    ~Matrice(){

    }

    Matrice(const Matrice& mat){
        dim1 = mat.dim1;

    }

    virtual void citire(istream& i) = 0;
    virtual void afisare(ostream& o) = 0;
    virtual int verif_diag() = 0;
};

istream&operator >>(istream& in, Matrice& mat){
    mat.citire(in);
    return in;
}

ostream&operator <<(ostream& o, Matrice& mat){
    mat.afisare(o);
    return o;
}

class MatriceO: public Matrice{
    int dim1, dim2, nr;
    Nod *start, *ultim;
public:
    MatriceO(int dim1, int dim2, int nr):Matrice(dim1, dim2, nr){
        this->dim1 = dim1;
        this->dim2 = dim2;
        this->nr = nr;
        this->start = NULL;
        this->ultim = NULL;
    }

    void adaugare(int lin, int col, Complex &z){
        Nod *p = new Nod(lin, col);
        p->setv(z);
        p->seturm(NULL);

        if(start == NULL){
            start = p;
            ultim = start;
        }
        else{
            ultim->seturm(p);
            ultim = p;
        }
    }

    void citire(istream& in){
        int i;
        int lin, col;
        Complex z;

        for(i=0; i<nr; i++)
        {
            cout<<"Introduceti elementul (valoarea, linia si coloana).";
            in>>z>>lin>>col;
            adaugare(lin, col, z);
        }

    }

    void afisare(ostream& o){
        Nod* p;
        p = start;
        o<<"Afisarea elementelor in ordinea introducerii lor in matrice: "<<endl;
        while(p != NULL)
        {
            o<<p->getv()<<" se afla pe linia "<<p->getl()<<" si coloana "<<p->getc()<<endl;
            p = p->geturm();
        }

        o<<endl;
    }

    int verif_diag(){
        Nod *p;
        int l, c, ok = 1;
        p = start;
        while(p != NULL)
        {
            l = p->getl();
            c = p->getc();
            if(l != c && (p->getv().getre()!= 0 || p->getv().getim() != 0)) ok = 0;
            p = p->geturm();
        }

        return ok;
    }

    MatriceO(const MatriceO& mat):Matrice(mat){
        dim1 = mat.dim1;
        dim2 = mat.dim2;
        nr = mat.nr;
        start = mat.start;
        ultim = mat.ultim;
    }

    ~MatriceO(){
        delete this;
    }
};

class MatriceP: public Matrice{
    int dim1, nrelem;
    Nod *start, *ultim;
public:
    MatriceP(int dim1, int nrelem) :Matrice(dim1, dim1, nrelem) {
        this->dim1 = dim1;
        this->dim1 = dim1;
        this->nrelem = nrelem;
        this->start = NULL;
        this->ultim = NULL;
    }

    void adaugare(int lin, int col, Complex& z){
        Nod *p = new Nod(lin, col);
        p->setv(z);
        p->seturm(NULL);

        if(start == NULL){
            start = p;
            ultim = start;
        }
        else{
            ultim->seturm(p);
            ultim = p;
        }
    }

    int getd1(){
        return this->dim1;
    }


     Nod*& getstart()
    {
        return this->start;
    }

    int getnr()
    {
        return this->nrelem;
    }

    void citire(istream& in){
        int i;
        int lin, col;
        Complex z;

        for(i=0; i<nrelem; i++)
        {
            cout<<"Introduceti elementul (valoarea, linia si coloana).";
            in>>z>>lin>>col;
            adaugare(lin, col, z);
        }

    }

    void afisare(ostream& o){
        Nod* p;
        p = start;
        o<<"Afisarea elementelor in ordinea introducerii lor in matrice: "<<endl;
        while(p != NULL)
        {
            o<<p->getv()<<" se afla pe linia "<<p->getl()<<" si coloana "<<p->getc()<<endl;
            p = p->geturm();
        }

        o<<endl;
    }

    int verif_diag(){
        Nod *p;
        int l, c, ok = 1;
        p = start;
        while(p != NULL)
        {
            l = p->getl();
            c = p->getc();
            if(l != c && p->getv().getim()!= 0 && p->getv().getre() != 0) ok = 0;
            p = p->geturm();
        }

        return ok;
    }

   Complex& determinant(Nod* start, int nrelem, int dim1){
        if(dim1 == 1 && nrelem == 1) return start->getv();
        if(dim1 == 2){
            int i, j;
            double val;
            Complex **v, sum, x1, x2;
            v = new Complex*[2];
            for(i=0; i<2; i++)
                v[i] = new Complex[2];

            for(i=0; i<2; i++)
                for(j=0; j<2; j++)
                    v[i][j] = 0;
            Nod *p = start;
            while(p->geturm() != NULL)
            {
                v[p->getl()][p->getc()] = p->getv();
            }


            val = v[1][1].getre()*v[2][2].getre() - (v[1][1].getim()*v[2][2].getim());
            x1.setre(val);

            val = v[1][1].getre()*v[2][2].getim() + v[1][1].getim()*v[2][2].getre();
            x1.setim(val);

            val = v[1][2].getre()*v[2][1].getre() - (v[1][2].getim()*v[2][1].getim());
            x2.setre(val);

            val = v[1][2].getre()*v[2][1].getim() + v[1][2].getim()*v[2][1].getre();
            x2.setim(val);

            sum.setre(x1.getre() - x1.getre());
            sum.setim(x1.getim() - x2.getim());

            return sum;
        }
   }
};

int main(){

    int t;
    int nr1, nr2, l, c, n;
    cout<<"Matricea patratica va avea dimensiunile: (n x n)\nn=";
    cin>>n;
    cout<<"Numarul de elemente nenule: ";
    cin>>nr1;
    cout<<endl;
    cout<<"Matricea oarecare va avea dimensiunile: (n x m)\nn= ";
    cin>>l;
    cout<<endl;
    cout<<"m= ";cin>>c;
    cout<<"Numarul de elemente nenule: ";
    cin>>nr2;
    cout<<endl;

    MatriceO A(l, c, nr2);
    MatriceP B(n, nr1);

    cout<<"Meniu: "<<endl;
    cout<<"1. Citire matrice oarecare. \n2.Citire matrice patratica. \n 3.Verif. daca matricea patratica este diagonala. \n4.Verif. daca matricea oarecare este diagonala. \n5.Afisare matrice oarecare. \n6.Afisare matrice patratica. \n7.Calculare determinant matrice patratica pentru orice n>=2. \n";
    cout<<"Alegeti un numar. "; cin>>t;

    while(t>=1 && t<=7){
        switch(t){
            case 1:
            {
                cin>>A;
            }break;
            case 2:
            {
                cin>>B;
            }break;
            case 3:
            {
                int ok = B.verif_diag();
                if(ok == 1) cout<<"Matricea este diagonala. \n";
                else cout<<"Matricea nu este diagonala. \n";
            }break;
            case 4:
            {
                int ok = A.verif_diag();
                if(ok == 1) cout<<"Matricea este diagonala. \n";
                else cout<<"Matricea nu este diagonala. \n";
            }break;
            case 5:
            {
               cout<<A;
            }break;
            case 6:
            {
                cout<<B;
            }break;
            case 7:{
                if(n<=2) cout<<B.determinant(B.getstart(),B.getnr(), B.getd1());
                else cout<<"Nu putem calcula determinantul.\n";
            }break;
        }
        cout<<"Alegeti un numar. "; cin>>t;
    }

    return 0;
}


