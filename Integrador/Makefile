DOCNAME=integrador_pylp_ulises
articulo=$(DOCNAME)
IEEE=$(DOCNAME)-IEEE

all: compilarart

ctodo: compilarart compilari3e

compilarart: art glosarioart
	echo -e "Finalizó la compilación del documento."

compilari3e: i3e glosarioi3e
	echo -e "Finalizó la compilación del documento."

compilarl: art glosarioart limpiar
	echo -e "Finalizó la compilación del documento."

art:
	pdflatex -shell-escape $(articulo).tex
	biber $(articulo)
	pdflatex -shell-escape $(articulo).tex

glosarioart:
	makeglossaries $(articulo)
	pdflatex -shell-escape $(articulo).tex

i3e:
	pdflatex $(IEEE).tex
	biber $(IEEE)
	pdflatex $(IEEE).tex

glosarioi3e:
	makeglossaries $(IEEE)
	pdflatex $(IEEE).tex
	biber $(IEEE)
	pdflatex $(IEEE).tex

limpiar:
	rm *.acn *.acr *.alg *.aux *.blg *.bbl *.bcf *.glg *.glo *.gls *.glsdefs *.ist *.log *.out *.run.xml
	rm -rf _minted-integrador_pylp_ulises

ver: art glosarioart limpiar
	# xdg-open abre el documento con la aplicación preferida
	# se puede cambiar por una llamada más específica si se
	# prefiere.
	# Ej:
	#		zathura $(DOCNAME).pdf
	#		evince $(DOCNAME).pdf
	xdg-open $(articulo).pdf
