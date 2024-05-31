# Описание
Целью создания данного репозитория является желание автора упростить процесс
написания курсовых и дипломных работ с помощью LaTeX. Ввиду того, что автор
обучается в МГТУ им. Н.Э. Баумана, то за основу взят шаблон
[bmstu-latex-class](https://github.com/Orianti/bmstu-latex-class), но не
составляет трудностей использовать другой класс документа (необходимо изменить
несколько строк). Основной упор сделан на организацию LaTeX проекта и упрощение
процесса его компиляции.

В шаблоне реализовано:
- удобная сборка через makefile --- сборка одной командой;
- draft mode --- ускоренный режим сборки;
- вывод в командную строку только важных сообщений о процессе сборки;
- автосортируемый список сокращений (работоспособность не зависит от шаблона
  bmstu).

# Структура репозитория

Для организации работы предлагаются следующие решения: 
- вынесение титульной страницы в отдельный tex файл. Такое решение принято из-за
  получения warnings при сборке титульника из шаблона bmstu;
- вынесение пользовательских команд в файл commands.tex;
- вынесение сокращений в файл abbreviations.tex;
- вынесение всех tex файлов в поддиректорию sourcefiles, кроме главного файла и
  файла титульника;
- вынесение всех графических файлов в поддиректорию img.

# Описание режимов сборки
В шаблоне реализованы следующие режимы сборки:
- final --- полная сборка документа, включающая пересборку титульника и всех tex
  файлов. В начале процесса удаляются все временные файлы и созданные pdf файлы,
  после чего происходит компиляция документа, за которой следует удаление все
  временных файлов;
- draft --- быстрая сборка документа в draft моде. Не удаляются временные файлы,
  все картинки вставляются в виде пустых прямоугольников, что значительно
  ускоряет процесс компиляции документов с большим количеством изображений;
- title --- сборка титульника. Происходит сборка титульного листа и удаляются
  временные файлы;
- clean --- удаление временных файлов LaTeX;
- cleanall --- clean + удаление созданных pdf файлов.

Для запуска процесса сборки необходимо написать в командную строку make <одна из
вышеперечисленных команд>. После выполнения процесса в командную строку будет
выведено соответствующее сообщение.
Если в процессе сборки LaTeX выдаст ошибку, то информация об ошибке будет
выведена на экран.

Результаты выполнения команд make build и make draft представлены в файлах
[make_final.pdf](https://github.com/BelloMak/LaTeX_template/blob/main/examples/make_final.pdf) и
[make_draft.pdf](https://github.com/BelloMak/LaTeX_template/blob/main/examples/make_draft.pdf)
соответственно.

# Системные требования
Для корректной работы шаблона на OS Windows необходимо:
- установить [make](https://gnuwin32.sourceforge.net/packages/make.htm) и
  [grep](https://gnuwin32.sourceforge.net/packages/grep.htm) и прописать их в
  PATH;
- установить пакет [texlogsieve](https://www.ctan.org/tex-archive/support/texlogsieve?lang=en);
- скачать программу [nhcolor](https://nhutils.ru/blog/цвет-текста-в-командном-файле/) и прописать
  ее в PATH.

Для корректной работы шаблона на OS Linux необходимо:
- наличие свежей версии дистрибутива TeX Live полной версии.
> Данный шаблон будет корректно работать и на OS Windows в случае запуска make файла из терминала cygwin.