#ifndef NO_H
#define NO_H
class No { //class No
    friend class TabelaHash; //class No amiga da  class TabelaHash
    friend class Bloco;
    friend class Dado;
    friend class Lista;
public:
    //Construtor
    No() {
        mId = -1;
        mMatricula = -1;
    }
private:
    //Atributos
    int mId;
    int mMatricula;

};
#endif 
