# haha

haha is a markup-language, which is mixed with HTML. haha facilitates writing of HTML-documents. 
The haha -markup for elements and attributes reduces typing of HTML-markup by at least 50 % ( haha = 'Half HTML'). 
A client-side JavaScript ( **haha.js** ) converts haha into HTML5. The browser shows a normal webpage, but if 
the reader opens the page-source in the same browser, he/she gets the original haha . The source of this 
document is 95 % haha . Contrary to many other lightweight markup, there is no seperate haha-document.

## Basic rules 

This is only a resumé. Consult the complete [HaHa Guide](https://notsue.github.io/haha.html)

- Opening tag: `<p>` is reduced to `[p`
- The closing tag can be a nameless `]`     
- Attributes in `<p class="red" id="example">` are reduced to `[p,class=red,id=example` 
(comma is separator, value is not quoted)

Some attribute-names have a short alternative: 

- `c=` equals `class=`
- `i=` equals `id=` 
- `h=` equals `href=` 
- `s=` equals `src=` 
- `a=` equals `alt=` 
- `t=` equals `title=` 
- `l=` equals `lang=` 
- `p=` equals `property=`

Our example becomes: `[p,c=red,i=example`

If the value of an attribute contains multiple words, the whitespaces are 
replaced by underscores.
 
For example: `[p,c=warning_important` means `<p class="warning important">` 

Tag-names and attribute-names should be written in **smallcase** characters.

Boolean attributes are inserted as for example `B=async` 

To write `[` or `]` as regular content use the escape sign: `\[` , `\]`   

    
To summerize: the opening of an element (opening tag with attributes) is **one word** without whitespace.
  
### Anonymous tags and attributes

In some cases the opening tag needs no name:

The anonymous opening tag `[` is interpreted as: 

- a `[li` if the element is a child of `<ul` or `<ol` 
- a `[td` if the element is a child of `<tr` 
- a `[p` in all other contexts 

There are also some anonymous attributes: 


- `,http://demo.org` becomes `href="http://demo.org` when used in element `a`, as in `[a,http://demo.or`  
- `,demo-picture.png` becomes `src="demo-picuture.png"` when used in element `img`, as in `[img,demo-picture.png`  
- `,red` becomes `class="red"` in all other cases


Anomymous attributes can be combined with other (short) attributes as in `[img,demo.png,a=nice_picture` 

Anonymous attributes can be used in anonymous tags.

### Footnotes and references

Footnotes are managed with elements `[FN`. These are numbered 
automaticcaly, while links and backlinks are created.

### Tufte CSS

You may also be interested in  [haha and Tufte CSS](https://notsue.github.io/haha-tufte.html). This is haha/html with sidenotes and margin notes. 

## Usage

Download zip-file at our [Demo site] (https://github.com/notsue/notsue.github.io) (press green code-button, and select 'download zip')

Read haha.html and haha-tufte.html.

Send comments, tips, wishes and questions to notsue at protonmail dot com . Do not compare with markdown, ReST, etc. HaHa is not another lightweight markup. It's 'dirty' HTML. As dirty as possible.
