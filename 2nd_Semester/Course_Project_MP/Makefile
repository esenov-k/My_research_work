# At the beginning of the main .tex file type:
#
# \providecommand\classopts{}
# \expandafter\documentclass\expandafter[\classopts]{bmstu}
#
# instead of:
#
# \documentclass{bmstu}
#
# Also use file titlepage.tex for generate title page. It can
# be included to main .tex file via:
#
# \includepdf{titlepage.pdf}


# Default shell
SHELL=/bin/bash

# Name of main tex file
TEX_SOURCE := main
# Name of title page tex file
TITLE_SOURCE := titlepage
# Name of bibliography data base
BIB_SOURCE := BibDB
# Name of produced pdf file in draft mode
DRAFT_FILE_NAME := draft

# pdflatex params for final file
FINALPARAM := -interaction=nonstopmode -file-line-error -halt-on-error
# pdflatex params for draft file
DRAFTPARAM := -halt-on-error -file-line-error -interaction=nonstopmode \
-jobname=$(DRAFT_FILE_NAME)
# grep params for parse pdflatex errors
GREPPARAM_TEX := -m 1 -A 1 -E "*[.]tex:[0-9]+:|^!"
# grep params for parse biber errors
GREPPARAM_BIBER_WARN := -E " WARN "
# grep params for parse biber warnings
GREPPARAM_BIBER_ERR := -E " ERROR "
# texlogsieve params
TEXLOGSIEVEPARAM = --only-summary --color --summary-detail --repetitions \
	--no-heartbeat --no-box-detail
# extentions of temp files
TEMP_FILES = *.aux *.bbl *.bcf *.blg *.log *.out *.run.xml *.toc

TRASH := /dev/null

# Major targets
.PHONY: help title final draft clean cleanall
.SILENT: help title final draft clean cleanall

help:
	printf "\e[1;97mSYNOPSIS\n\
	\tmake\e[0m [command]\n\
	\n\
	\e[1;97mCOMMANDS\e[0m\n\
	\tThis version of Makefile understands the following commands.\n\
	\n\
	\t\e[1;97mclean\e[0m\tDelete all pdflatex temporary files (including \e[4m.aux\e[0m\n\
	\t\tand \e[4mlog\e[0m files).\n\
	\n\
	\t\e[1;97mcleanall\e[0m\n\
	\t\tmake \e[1;97mclean\e[0m plus delete all produced \e[4m.pdf\e[0m files.\n\
	\n\
	\t\e[1;97mdraft\e[0m\tSets document class options \e[1;97mdraft\e[0m so pdflatex doesn't\n\
	\t\tinclude images and \e[4m.pdf\e[0m files marking it with empty\n\
	\t\trectangles. Also lists of bibliography and contents are \n\
	\t\tnot printed (fast mode).\n\
	\n\
	\t\e[1;97mfinal\e[0m\tFull compilation of \e[4m.tex\e[0m files. It may take a long time.\n\
	\n\
	\t\e[1;97mhelp\e[0m\tPrint this help message. Also can be printed with\n\
	\t\tsingle command \e[1;97mmake\e[0m without any arguments.\n\
	\n\
	\t\e[1;97mtitle\e[0m\tCompilation of \e[4mtitlepage.tex\e[0m file.\n\
	\n\
	\e[1;97mFILES\e[0m\n\
	\tBy default given commands produce the following files:\n\
	\n\
	\t\t\e[1;97mtitle\e[0m  -->  \e[4mtitlepage.pdf\e[0m\n\
	\t\t\e[1;97mdraft\e[0m  -->  \e[4mdraft.pdf\e[0m\n\
	\t\t\e[1;97mfinal\e[0m  -->  \e[4mmain.pdf\e[0m\n\
	\n\
	\tYou can change it in \e[4mMakefile\e[0m if necessary.\n\
	\n\
	\e[1;97mREQUIREMENTS\e[0m\n\
	\tCorrect operation is guaranteed if installed:\n\
	\n\
	\t\ttexlogseive\n\
	\t\tpdfpages\n\
	\t\tbmstu\n"

title: $(TITLE_SOURCE).pdf
	make -s $(TITLE_SOURCE).log
	printf "\e[1;31m"
	grep $(GREPPARAM_TEX) $(TITLE_SOURCE).log || \
	printf "\e[1;32m Title done! \e[0m"
	printf "\e[0m"

draft: $(TITLE_SOURCE).pdf $(DRAFT_FILE_NAME).pdf
	make -s $(DRAFT_FILE_NAME).log
	printf "\e[1;31m"
	grep $(GREPPARAM_TEX) $(DRAFT_FILE_NAME).log || \
	(printf "\e[0m" && texlogsieve $(TEXLOGSIEVEPARAM) $(DRAFT_FILE_NAME).log \
	&& printf "\e[1;32m Draft done! \e[0m")
	printf "\e[0m"
 
final: $(TITLE_SOURCE).pdf $(TEX_SOURCE).pdf
	make -s $(TEX_SOURCE).log
	make -s $(TEX_SOURCE).blg
	printf "\e[1;31m"
	grep $(GREPPARAM_TEX) $(TEX_SOURCE).log || \
	(grep $(GREPPARAM_BIBER_ERR) $(TEX_SOURCE).blg || \
	(printf "\e[1;33m" && grep $(GREPPARAM_BIBER_WARN) $(TEX_SOURCE).blg | \
	cut -d ">" -f2; printf "\e[0m \n" | \
	grep $(GREPPARAM_TEX) $(TEX_SOURCE).log || \
	(printf "\e[0m" && texlogsieve $(TEXLOGSIEVEPARAM) $(TEX_SOURCE).log \
	&& printf "\e[1;32m Final file done! \e[0m\n")))
	printf "\e[0m"

clean:
	for tmpfile in $(TEMP_FILES) ; do \
			find . -name $${tmpfile} -type f -delete ; \
			find ./sourcefiles -name $${tmpfile} -type f -delete ; \
	done
	find . -name "auto" -type d -exec rm -r {} +
	printf "\e[1;32m Clean done! \e[0m\n"

cleanall:
	make -s clean >$(TRASH)
	rm -f $(TEX_SOURCE).pdf
	rm -f $(TITLE_SOURCE).pdf
	rm -f $(DRAFT_FILE_NAME).pdf
	make -s clean >$(TRASH)
	printf "\e[1;32m Cleanall done! \e[0m\n"


# Service targets
.SILENT: $(TITLE_SOURCE).pdf $(TEX_SOURCE).pdf $(DRAFT_FILE_NAME).pdf \
$(TITLE_SOURCE).log $(TEX_SOURCE).log $(TEX_SOURCE).blg $(DRAFT_FILE_NAME).log

# Title page compilation
$(TITLE_SOURCE).pdf: $(TITLE_SOURCE).tex
	pdflatex $(FINALPARAM) $(TITLE_SOURCE).tex >$(TRASH) || true

# Draft file compilation
$(DRAFT_FILE_NAME).pdf: $(TEX_SOURCE).tex sourcefiles/*.tex
	pdflatex $(DRAFTPARAM) "\def\classopts{draft}\input{$(TEX_SOURCE).tex}" \
	>$(TRASH) || true

# Final file compilation
$(TEX_SOURCE).pdf: $(TEX_SOURCE).tex sourcefiles/*.tex $(BIB_SOURCE).bib
	pdflatex $(FINALPARAM) $(TEX_SOURCE).tex >$(TRASH) && \
	biber $(TEX_SOURCE) >$(TRASH) && \
	pdflatex $(FINALPARAM) $(TEX_SOURCE).tex >$(TRASH) && \
	pdflatex $(FINALPARAM) $(TEX_SOURCE).tex >$(TRASH) || true

# Creation of title log if it does no exist
$(TITLE_SOURCE).log:
	test -s $(TITLE_SOURCE).log || touch $(TITLE_SOURCE).log

# Creation of draft log if it does no exist
$(DRAFT_FILE_NAME).log:
	test -s $(DRAFT_FILE_NAME).log || touch $(DRAFT_FILE_NAME).log

# Creation of final log if it does no exist
$(TEX_SOURCE).log:
	test -s $(TEX_SOURCE).log || touch $(TEX_SOURCE).log

# Creation of bib log if it does no exist
$(TEX_SOURCE).blg:
	test -s $(TEX_SOURCE).blg || touch $(TEX_SOURCE).blg