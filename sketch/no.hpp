#ifndef NO_H
#define NO_H
class No { //class No
    friend class Hash; //class No amiga da  class TabelaHasg
    friend class Bloco;
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
