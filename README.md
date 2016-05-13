# Logika

CZEŚĆ 1:
  Kompilacja: czesc1.cpp: g++ czesc1.cpp -o ciag
              czesc1_neg.cpp: g++ czesc1_neg.cpp -o ciag
              
  Przykładowe wywołanie:
              ./ciag 2 4 8 16 32 64
  Skrypt "test" posiada zdefiniowaną nazwę programu wykonywalnego "ciag".
    
    
CZEŚĆ 2:
  Kompilacja:
              g++ czesc2.cpp -std=c++11 -o game
  Przykładowe wywołanie:
              ./game --impl impl.txt --not not.txt --and and.txt --or or.txt
