<h1,dc.title HH guide (version 0.4  beta) >

<,dc.description HH ('HaHa') is a markup language that may be not so useful. It is
  based on the assumption that the user knows how HTML works (elements, attributes, ...) and
  does not want to spend much effort in learning other markup languages. That's <b <i 0.074 % > > of the
  world population. <i Less is more > . <br > The HH-reader <a,https://github.com/notsue/HaHa hh.py > reads 
  HH-source and produces valid HTML5. Batteries included: automatic numbering of headers and footnotes,
  metadata extraction from content, printer-friendly url-list, math, highlighting, x3d, ... >
  

<table,c=metadata  
<tr 
<,dc.creator (wdj) > 
<,dc.date 2-22-2022 > 
<,dc.rights <a,https://creativecommons.org/licenses/by/4.0/ Creative Commons Licence CC BY 4.0 > > 
tr>
table>

<div,header Contents >
  
<TOC >
  
<h2 Basic rules >

<TOC >

< Opening tag: <b \<p\> > is reduced to <b \<p > >
< The closing tag can be a nameless <b \> > >          
< Attributes in <b \<p class="red" id="example"\> > are reduced to <b \<p,class=red,id=example > >
< Some attribute-names have a short alternative: >

<ul
        < <b c= > equals class= >
        < <b i= > equals id= >
        < <b h= > equals href= >
        < <b s= > equals src= >
        < <b a= > equals alt= >
        < <b t= > equals title= >
        < <b l= > equals lang= >
ul> 

< Our example becomes: <b \<p,c=red,i=example > >

<,test\_test_test If the value of an attribute contains multiple words, the whitespaces are replaced by underscore <b _ >.  
For example: <b \<p,c=warning_not_important > creates <b \<p class="warning not important"\>. > If an underscore
is part of the attribute-value, use escape <code \_ >. An equal-sign needs te be escaped as well: <code \= >. >

< Tag-names and attribute-names should be written in <b smallcase > characters. >
< Boolean attributes are inserted as for example <b ...,async=,... > (equal sign, but no value). >

< Empty elements? <b \<br  \> > Simple. >
< To write \< or \> as regular content use the <b escape > sign: \\< , \\> . >  
< To summarize: the opening of an element (opening tag with attributes) is <b one 'word' without whitespace. > >

<h3 Anonymous tags and attributes >

< In some cases the opening tag needs no name: >

< The anonymous opening tag \< is interpreted as: >

<ul
< a \<li if the element is a child of \<ul or \<ol >
< a \<td if the element is a child of \<tr >
< a \<p in all other contexts >
ul>

< There are also some anonymous attributes: >

<ul
< <code ,http://demo.org > becomes <code href="http://demo.org > when used in element <code a > , as in <code \<a,http://demo.org > > 
< <code ,demo-picture.png > becomes <code src="demo-picuture.png" > when used in element <code img > , as in <code \<img,demo-picture.png > > 
< <code ,red > becomes <code class="red" > in all other cases >
ul>   

< Anonymous attributes can be combined with other (short) attributes as in \<img,demo.png,a=nice_picture >
< Anonymous attributes can be used in anonymous tags. >

<h3 More on the closing tag >

< It is allowed to use the name of the element in the closing tag, for example <b div\> > . It is not a bad habit
 to use this option when there is a lot of (complex) content between the opening and closing tag. Some 
 favorites: <b table\>, ol\> > and <b ul\>, section\>, ... >  In fact, it facilitates the setting 
 of 'folding'-delimeters in editors like Notepad++. >

< Although a closing \> or (for example) div\> should in principle be a separate word (preceded
and followed by whitespace), following habits are tolerated:  >
<ol
  < a string with multiple closing tags, like: <b \>\>\> > A good hh-reader should split them up 
    in seperate \> >
  < a punctuation which sticks to and follows \> or (for example) div\> , like in <b \>? > or <b \>. > >
  < closing and opening tag sticking together, like in <b  \<b bold \>\<i italic \>\<b bold \> >. This
    produces: <b bold ><i italic ><b bold >. >
ol> 

< There's a limit: do not combine option 1 with others. Do not apply 2 in de middle of a sticking 3. >

<h3 HTML, SVG, script- and pre-elements >

< Users can insert HTML, SVG, script-elements and pre-elements, using delimeters which instruct
the parser to <b copy as-is > all the lines between them. The delimeters start with an exclamation mark,
followed  by at least five hyphens: !----- <br > These tokens should be inserted at the beginning of a new line. >

< Example: >
<pre
!-----------
   
    &lt;pre &lt;code,language-python
    !------------------
        class Element():
            def __init__(self, tag="", parent=None):
                self.parent = parent
    !------------------
    &gt; &gt;

!-----------
pre>

< That's it for the basics.  >

<h2 At your service >

<h3 User-defined tags >

<G:=td,lang=el >
<E:=td,lang=en >
<PY:=code,language-python >

< It happens that an author has to use the same tag with certain attributes and values regularly. >
< If for example we often use <code \<code,c=language-python... > we can reduce this 
  to <code \<PY ... > if we have defined the PY-element as a replacement for <code \<code,c=language-python >. >
< The definition is made with: <code \<PY:=code,c=language-python \> > , of course before it's first use in the text. > 
< This 'element' instructs the parser to replace <i 'PY' > with <i 'code,c=language-python' >. >
< The use of such a 'PY' is demonstrated in following pre-element (python-code is colored with <a,https://highlightjs.org/ highlight.js > ): > 

<pre <PY 
!-----------
    # demo.hh 2 demo.html
    
    import sys

    sys.path.append('../../')
    import hh

    config = {'sourcefile':'demo.hh', 'outputfile':None, 'toc':2, 'h1':0, 'numbers': 1, 'includes': 3 , 
              'css':'default', 'katex':1, 'highlight': 1, 'dir':'ltr', 'lang':'en', 'class': 'hh', 'view': False}
    
    doc = hh.Document(config)
    print(doc.dublin_core['dc.title'])
    print('DONE')
!------------
> >

< Another example. When a table uses td-elements where an attribute needs to be set to certain values. For example, in a table
 with Greek text and English translations,  we have <code \<td,lang=el > and <code \<td,lang=en > >

< These can be replaced with <code \<G > and <code \<E > respectively, using following definitions: >

< <code \<G:=td,lang=el \> > >
< <code \<E:=td,lang=en \> > > 

< Following table uses these user-defined elements: >

<table
<tr <th Greek > <th English >>
<tr <G  Ἐπίκουρος > <E Epicurus > >
<tr <G Ἕρμαρχος > <E Hermarchus or Hermarch > >
table>

< We use capital characters for the user-defined tags, in order not to intervene with the regular tags (always smallcase).
Do not use names starting with 'SET' or 'GET'. These are used for footnote e.a. >  

<h3 Comments >

< It is possible to include comments, that is text which should be ignored by the reader-script and  leaves
no traces in the html-source >

< As in html you place a comment between <code \<!-- > and <code --\> >. However, the opening 'tag' should appear at the
beginning of a new line, while the closing 'tag' should be the last 'word' in a line. >

< This can be used to <i 'comment out' > part of the text. > 

< If one wishes to insert comment in the html-source, use <code !--------------- > >

<h3 Includes >

< We can build one HTML-document from multiple source-files, using the <code \<INCLUDE > element. In your main
source-file write <code \<INCLUDE:chapter1.hh \> > and the content of <code chapter1.hh > will be parsed
and inserted on that spot. Obviously, the hh-reader-scripts should be launched with a source-file that serves as the
main hh-source. One <i include > (say a chapter) can call another include (say a section).   >

< There is a protection against circular includes (A.txt including B.txt and B.txt including A.txt). The hh-reader
produces a warning at a certain level (include-depth), which is by default 4. You can choose: continue 
or not. See below: usage. >  
  
 
<h3 Automatic Numbering of elements (h1), h2, ... >

< There are two options: >

<ol
    < h1-elements are included in numbering <code (config['h1'] == True) > >
    < h1-elements are not included <code (config['h1'] == False) > >
ol>

< When option 2 is set in configuration (see below): all h2, h3, h4, h5 and h6 elements 
  get an id, for example: id='section_2_1' if it is the first h3 under the second h2. >
< When option 1 is selected, the same h3 might have id="section_1_2_1", if found under the first h1. > 

< Another couple of options >

<ol
    < Numbers are visible for the reader of your webpage <code (config['numbers'] == True) > >
    < Numbers are not visible for the reader of your webpage <code (config['numbers'] == False) > >
ol>

< True or False: the id's are always there as a href-target. >

<h3 Table of contents >

< Use the empty element <code \<TOC \> > to mark the position of the table of contents in the document. >

< Obviously, the contentlist will follow the options concerning visual numbering and inclusion of h1. >

< If <code config['toc'] == 2 > the table will contain headers upto level h2. >
< <code config['toc'] > has value 1 upto 6 or  ... 0 (zero) which results in no table at all (with or without \<TOC \>). >

<h3 Footnotes: automatic numbering >

< A footnote example <GETF:about >  and a second footnote <GETF:second >  . >

<SETF:about Content of first footnote >

<SETF:second Content of second footnote with <b bold text > and a <a,http://test.org link  > > 

< The content of a footnote is wrapped in an element with tagname <code \<SETF > . >
< Each footnote has a label, for example <code \<SETF:labelx > . >
< In the text we create a link to this footnote  with <code \<GETF:labelx \> > >
< The hh-reader inserts a number at GETF, and the content of a SETF with the same
  label and number appears at the bottom of the html-page. The labels are used to create the
  links and backlinks. >
< The SETF-elements can be inserted anywhere in the hh-source, after or before the GETF-element
  with the same label. > 
< We can refer multiple times to the same footnote, repeatedly using the same label, like in (see footnote
<GETF:second > ) The backlink however refers to the first use of the footnote.
 We can use an id only once. So far we have valid HTML5 at WC3's <a,https://html5.validator.nu/ nu validator >. >
 
< You should indicate if and where the footnotes should appear in the html-file. Simply insert the empty
element <code \<NOTES \> > somewhere near the end of your main sourcefile. >

< If there are multiple <code \<NOTES \> > in a hh-file (perhaps inserted by one or more  <code \<INCLUDE's >, 
then only the last <code \<NOTES \> > in the complete source will be used as location for the footnotes.  >

<h3 Labeled References >

< For references one can create a seperate list where the items are labeled >

<SETR:Parrot_2012 Parrot D. (2012) <i Collected Works > , PSF > 
<SETR:Parrot_1999 Parrot D. (1999) <i Spam, Eggs and Spam > , in <GETR:Parrot_2012 > >
<SETR:Parrot_2009 Parrot D. (2009) <i More Spam and Eggs (and Spam) > , PSF >
<SETR:Parrot_2013 Parrot D. (2012) <i Spam and Eggs in a Nutshell > , PSF > 

< A paragraph with a reference <GETR:Parrot_1999 > >
< Another paragraph with the second second reference  <GETR:Parrot_2009 > >

< You should indicate if and where the footnotes should appear in the html-file. Simply insert the
element <code \<REFS \> > somewhere near the end of your main sourcefile. >

< You can use \<INCLUDE to load a database with all your favorite references as \<SETR's, even if 
you use only a few of them. Only the used references will pop at the bottom of the html-file.  >  

< If there are multiple <code \<REFS \> > in a hh-file (perhaps inserted by one or more  <code \<INCLUDE's >, 
then only the last <code \<REFS \> > in the complete source will be used as location for the footnotes.  >


<h3 Metadata >

< Search engines look for metadata in de head-element. With HaHa, it is easy to provide
  metadata in an international and widely used standard format: the <b Dublin Core Metadata Element Set > (DCMS)  >
< <a,https://en.wikipedia.org/wiki/Dublin_Core WikiPedia's 'Dublin Core' page > is a good/sufficient guide. >
 
<ol 
    < dc.title – "A name given to the resource". >
    < dc.creator – "An entity primarily responsible for making the resource" (author). >
    < dc.contributor – "An entity responsible for making contributions to the resource". >
    < dc.publisher – "An entity responsible for making the resource available". >
    < dc.date – "A point or period of time associated with an event in the lifecycle of the resource". >
    < dc.description – "An account of the resource" (abstract). >
    < dc.subject – "The topic of the resource (keywords)". >
    < dc.coverage – "The spatial or temporal topic of the resource, the spatial applicability of the resource, or the jurisdiction under which the resource is relevant". >
    < dc.format – "The file format, physical medium, or dimensions of the resource". >
    < dc.identifier – "An unambiguous reference to the resource within a given context" (URL, ISBN). >
    < dc.language – "A language of the resource" (ISO code). >
    < dc.relation – "A related resource". >
    < dc.rights – "Information about rights held in and over the resource". >
    < dc.source – "A related resource from which the described resource is derived". >
    < dc.type – "The nature or genre of the resource". >
ol>

< In HaHa, you do not have te create seperate elements with metadata. You can reuse the content. >

< This page starts with: <code \<h1,dc.title HH guide (version 0.4  beta) \> > >

< The title is saved in a metadata-dictionary and used in meta-elements (and in this case
the title-element as well). >

< Other example. The small, table on top of this page, has hh-markup: >

<pre <code
!------------
&lt;,dc.creator (wdj) &gt;
&lt;,dc.date 2-22-2022 &gt;
&lt;,dc.rights &lt;a,https://creativecommons.org/licenses/by/4.0/ Creative Commons Licence CC BY 4.0 &gt; &gt; 
!-------------
>>

< You may wonder: what about the inline markup of our content? It is removed. The stuff in the metadata-dict is plain text. > 

< HTML validators have problems with metadata, although we follow <a,https://html.spec.whatwg.org/dev/semantics.html HTML5 standards > (follow
link to MetadataExtensions page). Our
main motivation, when using Dublin Core: <a,https://en.wikipedia.org/wiki/Open_Archives_Initiative Open Archives Initiative > 
and <a,https://doaj.org/docs/oai-pmh/ DOAJ (Directory of Open Access Journals)  >  >


<h3 Printing: URL's >

< HaHa provides facilities to print the url's of used links at the end of a webpage. This list
does not show up on screen, but when printing of page is requested, the list shows up (unless the css
is altered). >

< The links in the list are numbered and a reference number, like (url 5), appears after the link in the text. >

< While printing, backlinks are made invisible with css. >

<h3 Math and 3D >

< Things like: >

< $f(x) = \int_{-\infty}^\infty \widehat{f}(\xi)\,e^{2 \pi i \xi x}\,d\xi$ >

< We use <a,https://katex.org/ KaTeX > with the <a,https://katex.org/docs/autorender.html auto-render extension >. >

< An x3d demo. You can interact with mouse (left: rotate, right: zoom). HTML-Validators have problems with x3d. 
Nevver mind: browsers (the real validators) have no problems with x3d. >

!-------------------
<x3d width='500px' height='400px'> 
	   <scene> 
        
		<shape> 
		   <appearance> 
			 <Material ambientIntensity='0.4' diffuseColor='0.8,0,0' emissiveColor='0,0,0' metadata='X3DMetadataObject' shininess='0.2' specularColor='0,0,0' transparency='0.5' ></Material> 
		   </appearance> 
		   <box></box> 
		</shape> 
		<transform translation='-3 0 0'> 
		  <shape> 
			 <appearance> 
			   <material diffuseColor='0 1 0'></material> 
			 </appearance> 
			 <cone></cone> 
		  </shape> 
		</transform> 
		<transform translation='3 0 0'> 
		  <shape> 
			 <appearance> 
			   <material diffuseColor='0 0 1'></material> 
			 </appearance> 
			 <sphere></sphere> 
		  </shape> 
		</transform> 
	   </scene> 
	</x3d> 
!--------------------

<h2 Python script hh.py >

<h3 Usage >

< Download zip-file at <a,https://github.com/notsue/HaHa github.com/notsue/HaHa > (press red code-button, and select
'download zip') >

< For practical learning and experimenting the file <code docs/hh_demo/hh_demo.hh > can serve as a good start.  >

< In a terminal window move to the directory <code docs/hh_demo/ > >

< Try the script: <code \>python ../../hh.py --version >>

< Then: <code \>python ../../hh.py -h >>

< If this produces normal answers, you can try to convert <code demo.hh > into <code demo.html > yourself: >

< <code \>python ../../hh.py demo.hh -K -H >>

< Javascripts: The option -K activates Katex, the option -H activates Highlight (you should be online) >

< The html-output <code demo.html > is stored in the same directory >

< If you add option -v to the command: the script will ask if you want to view the html in your favorite browser. >

< The option -n activates the numbering of titles. >

< Check the metadata in the html-output. Observe the effect of the default css on printing. >

< Observe that your command-options are stored in a comment at the beginning of the html-file. >

< <code docs/hh_demo/demo.py > demonstrates how to call hh.py from another script. It allows us to reduce command to: >

< <code \>python demo.py >>

< Send comments, tips, wishes and questions to notsue at protonmail dot com . Do not compare with markdown, ReST, etc. 
HaHa is not another lightweight markup. It's 'dirty' HTML. As dirty as possible. >


<h3 What's next >

< With version 0.4 the markup became stable. This will not change in future versions. Perhaps more bells and
whistles are added, but that will not harm the compatibility of older HaHa-source. >

< The handling of errors in the hh-source could be better. A clever user should however exploit the INCLUDE-mechanism
which provides a means to test a hh-source piece by piece. When all parts are ok, you can cut and past them in one file. >

<h3 Adaptations >

< You can change the script in order to include more or other css and javascript. >

< Whatever: do not touch the <code class Element >. >

< In the class Document you should not touch the function <code read_include()> >

< We have inserted the marker #OPTION: in places where changes might contribute to your local needs. >


<div,header Notes >

<NOTES >

<div,header References >

<REFS >
  
