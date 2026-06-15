#include "../include/ElemRank.h"
using namespace TrabalhoJogo;

ElemRank::ElemRank(): pontos(0)
{
    nome.clear();
}
ElemRank::ElemRank(string n, int p): nome(n), pontos(p)
{}
ElemRank::~ElemRank()
{
    nome.clear();
}
void ElemRank::setNome(string n)
{
    nome=n;
}
void ElemRank::setPontos(int p)
{
    pontos=p;
}
string ElemRank::getNome()
{
    return nome;
}
int ElemRank::getPontos()
{
    return pontos;
}