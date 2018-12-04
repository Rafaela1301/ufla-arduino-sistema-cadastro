#ifndef DADO_H
#define DADO_H
class Dado {
    friend class Lista;
     friend class No;
    private:
        No dDado;
        Dado* dProximo;
    public:
        Dado(No d){
          dDado = d;
          dProximo = NULL;
        }
};

#endif   
