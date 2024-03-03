//
// Created by ASUS on 02.06.2023.
//

#include "Szyfrowanie.h"
/**
 * \brief Szyfruje podany tekst.
 *
 * Funkcja szyfruje podany tekst przy użyciu prostego szyfru. Wykorzystuje różnicę wartości
 * kodów ASCII pierwszego i ostatniego znaku w tekście, pomniejszoną o 1, jako klucz szyfrujący.
 * Każdy znak w tekście jest przesuwany o ten klucz.
 *
 * \param t Tekst do zaszyfrowania.
 * \return Zaszyfrowany tekst.
 *
 */
std::string szyfrujTekst(std::string& t) {
    if (t.empty()) {
        return "";
    }
    int key = (static_cast<int>(t.front()) - static_cast<int>(t.back()))-1;
    std::string encryptedText = t;
    for (char& c : encryptedText) {
        c += key;
    }

    return encryptedText;
}
/**
 * \brief Deszyfruje podany zaszyfrowany tekst.
 *
 * Funkcja deszyfruje podany zaszyfrowany tekst przy użyciu prostego szyfru.
 * Wykorzystuje różnicę wartości kodów ASCII pierwszego i ostatniego znaku w tekście,
 * pomniejszoną o 1, jako klucz deszyfrujący. Każdy znak w tekście jest przesuwany
 * o ten klucz w przeciwnym kierunku.
 *
 * \param t Zaszyfrowany tekst do odszyfrowania.
 * \return Odszyfrowany tekst.
 *
 */
std::string deszyfrujTekst(std::string& t) {
    if (t.empty()) {
        return "";
    }

    int key = (static_cast<int>(t.front()) - static_cast<int>(t.back()))-1;

    std::string decryptedText = t;
    for (char& c : decryptedText) {
        c -= key;
    }

    return decryptedText;
}