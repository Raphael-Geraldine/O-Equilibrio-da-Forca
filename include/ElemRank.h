#pragma once

#include <string>
using namespace std;

namespace OEquilibrioDaForca
{
    class ElemRank
    {
        private:
            string nome;
            int pontos;

        public:
            ElemRank();
            ElemRank(string n, int p);
            ~ElemRank();
            void setNome(string n);
            void setPontos(int p);
            string getNome();
            int getPontos();   
    };
}