#include <iostream>

using namespace std;

class Node{
    int valore;
    Node *next;

public:
    Node(){
        valore = 0;
        next = nullptr;
    }
    ~Node(){
        if(next != nullptr)
            delete next;
    }


    //geteri
    int getValore() const {
        return valore;
    }
    Node *getNext() const {
        return next;
    }
    //setteri
    void setValore(int valore) {
        Node::valore = valore;
    }


    void setNext(Node *next) {
        Node::next = next;
    }

};

class IntList{
    Node *start;

public:
    IntList(){
        this->start = nullptr;
    }

    IntList(const int size,const int vect[]){
       this ->start = nullptr; //trbuie sa il declar null pentru ca el initial o sa aiba o valoare random pe care o pune la inceput
        for(int i=0;i<size;i++)
            add_after_element(vect[i]);
    }

    ~IntList(){
        if(start != nullptr){
          delete start;
        }
    }

    int find_poz(int element){

        if(start == nullptr){
            return -1;
        }
        else if (start ->getNext() == nullptr){
            if(start ->getValore() == element)
                return 1;
        }
        else{
            Node *actual = start;
            int nr=0;
            while(actual -> getNext() != nullptr){
                if(actual -> getValore() == element){
                    nr++;
                    return nr;
                }
                nr++;
                actual = actual -> getNext();
            }
            if(actual ->getValore() == element)
                return nr+1;
            return -1;

        }
    return -1;
    }

    int find_element(int pozitie){
        Node *actual = start;
        for(int i=1; i<pozitie;i++){
            if(actual -> getNext() == nullptr)
                return -1;
            actual = actual -> getNext();
        }
        return actual->getValore();
    }

    void add_element(int element){

        if(this -> start == nullptr){
            this -> start = new Node();
            this -> start ->setValore(element);
            this -> start ->setNext(nullptr);

        }
            else{
            Node *viitor_prim,*aux;
            /// viitor_prim o sa il fac primul element
            viitor_prim = new Node();
            viitor_prim -> setValore( element);
            viitor_prim -> setNext(start);
            start = viitor_prim; ///start o sa devina noul pointer care arata catre elementele care arata viitor prim.
        }
    }

    void add_after_element(int element){
        Node *viitor_next;
        if(start == nullptr){
            start = new Node();
            start ->setValore(element);
            start ->setNext(nullptr);
        }
        else{
            Node *actual = start;
            while(actual->getNext() != nullptr){
                actual = actual -> getNext();
            }
            viitor_next = new Node();
            viitor_next->setValore(element);
            actual->setNext(viitor_next);
        }

    }

    void set_element(int element, int poz){

        Node *actual = start;
        int ok=0;
        for(int i=1; i<poz;i++){
            if(actual -> getNext() == nullptr){
                cout<<"Element inexisent";
                break;
                ok = 1;
            }
            actual = actual -> getNext();
        }
        if(ok == 0){
            actual->setValore(element);
        }

    }

    IntList concat(const IntList &b){

        IntList noua_lista; // imi creez o lista noua
        Node *actual =this->start; /// iau ca prim element this->start

        while(actual->getNext()!= nullptr) //cat timp exista un next
        {
            noua_lista.add_after_element(actual->getValore()); //il adaug la final in noua lista
            actual = actual->getNext();
        }
        noua_lista.add_after_element(actual->getValore());

        actual = b.start;
        while(actual->getNext()!= nullptr)
        {
            noua_lista.add_after_element(actual->getValore());
            actual = actual->getNext();
        }
        noua_lista.add_after_element(actual->getValore());


        return noua_lista;


    }
    IntList & operator= (IntList const &lista){
        if(this->start != nullptr){
            delete this->start;
            this ->start = nullptr; /// nu ii dau new Node pentru ca imi face un nod care are 0 initial
            /// si eu o sa adaug dupa el
        }

           Node *actual = lista.start;
        
            while(actual ->getNext() != nullptr){
                add_after_element(actual ->getValore());
               actual = actual ->getNext();
           }

        add_after_element(actual ->getValore());
    return *this;
    }

    friend ostream & operator << (ostream &out , const IntList &v);

private:
    Node *final(const IntList &lista ){
        Node *actual = lista.start;
        while(actual-> getNext() != nullptr){
            actual = actual -> getNext();
        }
        return actual;
    }
};
ostream & operator << (ostream &out , const IntList &v){

    if(v.start == nullptr){
        out<<"Lista vida";
    }
    else{
        Node *actual = v.start;
        out << actual -> getValore()<< ' ';
        while(actual->getNext() != nullptr){
            actual = actual -> getNext();
            out << actual->getValore() << ' ';

        }
    }
    cout<<"\n";
    return out;
}
int main(){
    const int vect[] ={2,3,4};

    IntList v,c,d,e(3,vect);
    cout<<v;
    v.add_element(4);
    v.add_element(5);
    cout<<v;
    v.add_after_element(6);
    cout<<v;
    cout<<v.find_poz(6)<<endl;

    cout<<v.find_element(1)<<endl;
    v.set_element(7,3);
    cout<<"v:"<<v;
    c.add_element(8);
    d = v;
    d.add_element(1);
    cout<<"d: "<<d;
    e= d.concat(v);
    cout<<"v:"<<v;
    cout<<"e:"<<e;

    return 0;

}
