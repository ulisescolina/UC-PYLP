DOCNAME=tutorial_hadoop_integrador_ulises
articulo=$(DOCNAME)

all: art-glosario

.PHONY: clean

art:
	pdflatex $(articulo).tex
	biber $(articulo)
	pdflatex $(articulo).tex
	pdflatex $(articulo).tex

art-glosario: art
	makeglossaries $(articulo)
	pdflatex $(articulo).tex

clean:
	rm *.acn *.acr *.alg *.aux *.blg *.bbl *.bcf *.glg *.glo *.gls *.glsdefs *.ist *.log *.out *.run.xml

