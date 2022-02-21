# HaHa

HaHa (Half HTML) is a markup language, based on the assumption that the user 
knows how HTML works (elements, attributes, ...) and does not want to spend much 
effort in learning other markup languages. 

**hh.py** is a script that reads hh-sources and produces well formed HTML5.

## Basic rules 

This is only a resumé. Consult the **complete hh_guide in docs/hh_guide/**

- Opening tag: `<p>` is reduced to `<p`
- The closing tag can be a nameless `>`     
- Attributes in `<p class="red" id="example">` are reduced to `<p,class=red,id=example` 
(comma is separator, value is not quoted)

Some attribute-names have a short alternative: 

- `c=` equals `class=`
- `i=` equals `id=` 
- `h=` equals `href=` 
- `s=` equals `src=` 
- `a=` equals `alt=` 
- `t=` equals `title=` 
- `l=` equals `lang=` 

Our example becomes: `<p,c=red,i=example`

If the value of an attribute contains multiple words, the whitespaces are 
replaced by underscores.
 
For example: `<p,c=warning_important` means `<p class="waring important">` 

Tag-names and attribute-names should be written in **smallcase** characters.

Boolean attributes are inserted as for example `...,async=,...` (equal sign, but no value)

Empty elements? `<br  >` Simple.

To write `<` or `>` as regular content use the escape sign: `\<` , `\>`   

    
To summerize: the opening of an element (opening tag with attributes) is **one word** without whitespace.
  
### Anonymous tags and attributes

In some cases the opening tag needs no name:

The anonymous opening tag `<` is interpreted as: 

- a `<li` if the element is a child of `<ul` or `<ol` 
- a `<td` if the element is a child of `<tr` 
- a `<p` in all other contexts 

There are also some anonymous attributes: 


- `,http://demo.org` becomes `href="http://demo.org` when used in element `a`, as in `<a,http://demo.or`  
- `,demo-picture.png` becomes `src="demo-picuture.png"` when used in element `img`, as in `<img,demo-picture.png`  
- `,red` becomes `class="red"` in all other cases


Anomymous attributes can be combined with other (short) attributes as in `<img,demo.png,a=nice_picture` 

Anonymous attributes can be used in anonymous tags.

### Footnotes and references

Footnotes are managed with elements `<SETF` and `<GETF` . These are numbered 
automaticcaly, while links and backlinks are created.

References are managed with elements `<SETR` and `<GETR`

### Customized tags

A tag like `<PY` can be defined as a replacement for `<code,class=python-language`

### Headers

Automatic numbering of headers and creation of a contentlist is part of the
basic services.

### Metadata

Metadata are extracted from the main text with markers like `,dc.title` (we use
Dublin Core scheme). 

### Includes

With `<INCLUDE` a parser can be instructed to insert other files in main
file. Included file may contain further `<INCLUDE`-instructions.

## Usage

Download zip-file (press green code-button, and select 'download zip')

For practical learning and experimenting the file `docs/hh_demo/hh_demo.hh` can serve as a good start.

In a terminal window move to the directory `docs/hh_demo/`

Try the script: `>python ../../hh.py --version`

Then: `>python ../../hh.py -h`

If this produces normal answers, you can try to convert demo.hh into demo.html yourself:

`>python ../../hh.py demo.hh -K -H`

Javascripts: The option -K activates Katex, the option -H activates Highlight.js (you should be online)

The html-output `demo.html` is stored in the same directory

If you add option -v to the command: the script will ask if you want to view the html in your favorite browser.

The option -n activates the numbering of titles.

Check the metadata in the html-output. Observe the effect of the default css on printing.

Observe that your command-options are stored in a comment at the beginning of the html-file.

`docs/hh_demo/demo.py` demonstrates how to call hh.py from another script. It allows us to reduce command to:

`>python demo.py`

Send comments, tips, wishes and questions to notsue at protonmail dot com . Do not compare with markdown, ReST, etc. HaHa is not another lightweight markup. It's 'dirty' HTML. As dirty as possible.
