DOKUMENTACJA PROJEKTOWA DRZEWA BST

Dokument zawiera pięć rozdziałów. Rozdziały 1 i 2 przedstawiają wymagania
i analizę, rozdziały 3 i 4 opisują projekt oraz implementację wraz z próbami,
a rozdział 5 zawiera wnioski.

Otwórz Dokumentacja/dokument.tex po rozpakowaniu archiwum.
Kompiluj z katalogu zawierającego ten plik.

  latexmk -pdf dokument.tex

Możesz również wykonać polecenia ręcznie.

  pdflatex dokument.tex
  bibtex dokument
  pdflatex dokument.tex
  pdflatex dokument.tex

Dokument jest zapisany w UTF-8. Do kompilacji użyj pdfLaTeX i BibTeX.
W Overleaf wgraj zawartość katalogu Dokumentacja i ustaw dokument.tex
jako plik główny. Rysunek drzewa powstaje w TikZ. Listingi pobierają
fragmenty z kopii aktualnego kodu C++ w katalogu kod/.
Dane na stronie tytułowej można edytować w dokument.tex.
