//Utilitare.h (Functia template)
#pragma once
#include <vector>
#include "DispozitivSmart.h"

//functia primeste vectorul de dispozitive (pointeri catre clasa de baza DispozitivSmart)
//si foloseste dynamic_cast<TipCautat*>
template <typename TipCautat>
int numaraDispozitiveDupaTip(const std::vector<DispozitivSmart*>& dispozitive)
{
    int contor = 0;
    for (const auto& disp : dispozitive)
    {
        if (dynamic_cast<TipCautat*>(disp) != nullptr) //dispozitivul e de tipul cautat
        {
            contor++;
        }
    }
    return contor;
}