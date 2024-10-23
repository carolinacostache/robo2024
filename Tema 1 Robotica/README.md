# Tema 1: EV Charger

## Descrierea temei
Pentru această temă, am simulat o stație de încărcare pentru un vehicul electric, folosind un sistem compus din multe LED-uri și două butoane.

## Scopul temei
Scopul temei era reproducerea comportamentul unei stații reale, unde:
* Stația poate fi liberă sau ocupată, starea fiind indicată cu ajutorul unui LED RGB: roșu - ocupată, verde - liberă;
* Încărcarea este reprezentată prin 4 LED-uri, fiecare dintre acestea arătând un nivel diferit de încărcare (led1 - 25%, led2 - 50%, led3 - 75%, led4 - 100%);
* Apăsarea scurtă a butonului de start declanșează procesul de încărcare, iar starea stației de încărcare este "ocupată" (LED-ul RGB devine roșu). Apăsarea butonului în timpul procesului de încărcare nu va influența stația de încărcare;
* Apăsarea lungă a butonului de stop (>= 1 secundă) întrerupe încărcarea și resetează stația la starea liberă (LED-ul RGB devine verde);
* La finalizarea sau la întreruprea fortață, prin apăsarea butonului de stop, a procesului de încărcare toate cele 4 LED-urile vor clipi de 3 ori;
* Implementarea ia în considerare debouncing-ul, pentru a asigura o citire corectă a apăsărilor butoanelor;

## Componentele utilizate
* 4x LED-uri albastre - afișează nivelul de încărcare, fiecare reprezentând 25%;
* 1x LED RGB - afișează starea stației;
* 2x Butoane - pentru pornirea sau oprirea forțată a stației de încărcare;
* 7x Rezistoare 330Ω - pentru cele 4 LED-uri albastre și pentru LED-ul RBG;
* 2x Rezistoare 1KΩ - pentru cele 2 butoane;
* 1x Breadboard;
* 14x Linii de legătură;

## Montajul fizic
![Montaj](<photos/IMG_7746.PNG>)
![Montaj_closeup](<photos/IMG_7747.PNG>)
![Montaj_lateral1](<photos/IMG_7748.PNG>)
![Montaj_lateral2](<photos/IMG_7749.PNG>)

## Schema electrică
![Schema electrică - Tema 1](<photos/tema 1 poza.png>)

## Video cu funcționalitatea montajului fizic
[Video](https://youtu.be/7g0XaMN5Gg0)