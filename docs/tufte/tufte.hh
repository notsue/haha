<NT:=span,class=newthought >
<INPUT:=input,type=checkbox,class=margin-toggle >
<SLABEL:=label,class=margin-toggle_sidenote-number >
<SN:=span,class=sidenote >
<MLABEL:=label,c=margin-toggle >
<MN:=span,marginnote >
<PY:=code,language-python >

<article

<h1,dc.title,i=Tufte-CSS HaHa's Tufte CSS >
<p,dc.creator,c=subtitle NotSue >

<section

    <,dc.description <a,https://github.com/edwardtufte/tufte-css Tufte CSS > provides tools to style 
    web articles using the ideas demonstrated by Edward Tufte’s 
    books and handouts. Tufte’s style is known for its simplicity, extensive use of sidenotes, 
    tight integration of graphics with text, and carefully chosen typography. > 
    
    < Tufte CSS was created by <a,http://www.daveliepmann.com Dave Liepmann >. 
    The original idea was cribbed from <a,https://tufte-latex.github.io/tufte-latex/ <span Tufte- ><span,latex <span L ><span,latex-sup a ><span T><span,latex-sub e ><span X > > > 
    and <a,http://rmarkdown.rstudio.com/tufte\_handout\_format.html R Markdown’s Tufte Handout format >. >
    
    < The <a,https://github.com/notsue/HaHa HaHa project > used <em Tufte CSS > and it's corresponding HTML as a test. 
    With this more demanding HTML-structure, it was shown that HaHa-reader version 0.4 could use some improvements. >

section>


<p,subtitle Contents >

<TOC >


<section
    <h2,i=Tufte-CSS-howto Tufte CSS Howto >
    
   
    
    < Use <code tufte.css > and the <code et-book > directory of font files. With the HaHa-reader this is
      done with the <code --css tufte > option. >
    < HaHa has added some style for numbering of headers (if option <code -n > in on) and for the table
      of contents if <code \<TOC \> > is inserted. >
    < Tufte CSS uses <code h1 > for the document title, <code p > with class <code subtitle > for the document subtitle, <code h2 > for 
      section headings, and <code h3 > for low-level headings. More specific headings are not supported. >
    < Links in Tufte CSS match the body text in color and do not change on mouseover or when clicked. The underline effect is 
      achieved using CSS trickery involving background gradients instead of standard <code text-decoration >. 
      Credit goes to <a,https://adamschwartz.co/ Adam Schwartz > for that technique. > 
    < <NT In his later books >, Tufte starts each section with a bit of vertical space, a non-indented paragraph, and 
    the first few words of the sentence set in small caps. For this <i Tufte CSS > uses a span with the class <code newthought >, as demonstrated 
    at the beginning of this paragraph. In HaHa we use predefined tag-name NT: <code \<NT:=span,class=newthought \> >. >
    
    <,sans If you prefer sans-serifs, use the <code sans > class. It relies on Gill Sans, Tufte’s sans-serif font of choice. > 


    <h3,i=code Code >
 
    < Technical jargon, programming language terms, and code samples are denoted with the <code code > element. 
    <em Tufte CSS > follows GitHub’s  font selection, which shifts gracefully along the monospace spectrum from the 
    elegant but rare Consolas all the way to good old reliable Courier. > 
    < Extended code examples should live in a <code code > element within a <code pre > element. This adds control 
    over indentation and overflow as well: > 
    
<pre <PY,title=tufte.py
!------------

import sys
sys.path.append('../../')
import hh

config = {'sourcefile':'demo.hh', 'outputfile':None, 'toc':2, 'h1':0, 'numbers': 1, 'includes': 3 , 'x3d': 1, 
          'css':'tufte', 'katex':1, 'highlight': 1, 'dir':'ltr', 'lang':'en', 'class': 'hh', 'view': 1}
    
doc = hh.Document(config)
print(doc.dublin_core['dc.title'])
print('DONE... with Tufte CSS')
!------------
>>
    
    < When <em Highlight.js > is activated with option <code -H > , the HaHa-reader uses by default <code github.min.css >, with the same font. >



    <h3,i=epigraphs Epigraphs >
    
    <div,epigraph 
      <blockquote
        < The English language . . . becomes ugly and inaccurate because our thoughts are foolish, 
        but the slovenliness of our language makes it easier for us to have foolish thoughts. > 
        <footer George Orwell, “Politics and the English Language” footer>
      blockquote>
      
      <blockquote
        < For a successful technology, reality must take precedence over public relations, for Nature cannot be fooled. > 
        <footer Richard P. Feynman, <cite "What Do You Care What Other People Think?" > >
      blockquote>
      
      <blockquote I do not paint things, I paint only the differences between things. 
      <footer Henri Matisse, <cite Henri Matisse Dessins: thèmes et variations > (Paris, 1943), 37 > 
      blockquote>
    div>
    
    < If you’d like to introduce your page or a section of your page with some quotes, use epigraphs. Modeled 
    after chapter epigraphs in Tufte’s books (particularly <em Beautiful Evidence >), these are <code blockquote > elements, 
    children of a block <code \<div class='epigraph' \> >. The source goes in a <code footer > element inside the <code blockquote >. 
    We have reused three examples of <em Tufte CSS > in the epigraph of this section, demonstrating shorter and longer quotes, with and 
    without a paragraph tag, and showing how multiple quotes within an epigraph fit together with the use of wrapper class <code epigraph >. > 
section>

<section
<h2,i=sidenotes Sidenotes  >

    <h3 With numbers >

    < One of the most distinctive features of Tufte’s style is his extensive use of sidenotes 
    <SLABEL,for=sn-example-sidenote >
    <INPUT,id=sn-example-sidenote > <SN This is a sidenote. Sidenotes are like footnotes, except they 
    don’t force the reader to jump their eye to the bottom of the page. >.
    On sufficiently large viewports, Tufte CSS uses the margin for sidenotes, margin notes, and small figures. 
    On smaller viewports, elements that would go in the margin are hidden until the user toggles them into view. >
    
    < Sidenotes consist of two elements: a superscript reference number that goes inline with the text, and a sidenote 
    with content. To add the former, just put a label and dummy checkbox into the text where you want the reference to go, like so: > 
    <pre <code,language-html
!-------------
    
    &lt;label for="sn-sidenote-example" class="margin-toggle sidenote-number"&gt;&lt;/label&gt;
    &lt;input type="checkbox" id="sn-sidenote-example" class="margin-toggle"/&gt;
    &lt;span class="sidenote"&gt; ... sidenote text ... &lt;/span&gt;
!-------------
    >>
    
    < In HaHa we can define some tags, with <code \<SLABEL:=label,class=margin-toggle_sidenote-number \> > and
      <code \<INPUT:=input,type=checkbox,class=margin-toggle \> > and <code \<SN:=span,class=sidenote \> >. 
      As demostrated in the hh-markup of this article, this reduces the markup to: >

    <pre <code,nohighlight
!-------------
    
    &lt;SLABEL,for=sn-sidenote-example &gt;
    &lt;INPUT,i=sn-sidenote-example &gt;
    &lt;SN ... sidenote text ... &gt;
!-------------
    >>
    
    <h3 Without numbers >

    < If you want a sidenote without footnote-style numberings, then you want a margin note.
      <MLABEL,for=mn-demo &#8314; >
      <INPUT,id=mn-demo >
      <MN This is a margin note. Notice there isn’t a number preceding the note. > On large screens, a margin 
      note omits the reference number. On small screens, a margin note is like a sidenote except its viewability-toggle is a symbol rather than 
      a reference number. This document currently uses the symbol &#8314; ( <code &amp;#8314; > ). Liepmann uses &#8853;. 
      We've tried creating some similarity between numbered and anonymous notes. > 
      
    < Again, in HaHa we can define the specific tags with <code \<MLABEL:=label,margin-toggle \> > and 
      <code \<MN:=span,marginnote \> >, while <code \<INPUT > remains the same: >
     
    <pre <code,nohighlight
!-------------
    
    &lt;MLABEL,for=mn-demo &#8314; &gt;
    &lt;INPUT,i=mn-demo  &gt;
    &lt;MN ... marginnote text ... &gt;
!-------------
    >>     
    
section>

<section
<h2,id=figures Figures >

    < We are still using content from Liepmann's <a,https://github.com/edwardtufte/tufte-css Tufte CSS > to demonstate 
    figures. > 
    < Figures should try to use the <code figure > element, which by default are constrained to 
    the main column. Don’t wrap figures in a paragraph tag. Any label or margin note goes in a 
    regular margin note inside the figure. For example, most of the time one should introduce a 
    figure directly into the main flow of discussion, like so: > 
    <figure
      <MLABEL,for=mn-exports-imports &#8314; >
      <INPUT,id=mn-exports-imports >
      <MN From Edward Tufte, <em Visual Display of Quantitative Information >, page 92. >
      <img,exports-imports.png,alt=Exports_and_Imports_to_and_from_Denmark_&_Norway_from_1700_to_1780 >
    figure>
    
    
    < <MLABEL,for=mn-figure-1 &#8314; >
    <INPUT,id=mn-figure-1 > 
    <MN <img,rhino.png,alt=Image_of_a_Rhinoceros > F.J. Cole, 
    “The History of Albrecht Dürer’s Rhinoceros in Zooological Literature,” <em Science, Medicine, and 
    History: Essays on the Evolution of Scientific Thought and Medical Practice > (London, 1953), ed. E. 
    Ashworth Underwood, 337-356. From page 71 of Edward Tufte’s <em Visual Explanations >. > 
    But tight integration of graphics with text is central to Tufte’s work even when those graphics are ancillary 
    to the main body of a text. In many of those cases, a margin figure may be most appropriate. To place 
    figures in the margin, just wrap an image (or whatever) in a margin note inside a <code p > tag, as seen 
    to the right of this paragraph. > 
    
    < If you need a full-width figure, give it the <code fullwidth > class. Make sure that’s inside an <code article >, and it
    will take up (almost) the full width of the screen. This approach is demonstrated below using Edward Tufte’s 
    English translation of the Napoleon’s March data visualization. From <em Beautiful Evidence >, page 122-124. > 
    <figure,fullwidth
      <img,napoleons-march.png,alt=Figurative_map_of_the_successive_losses_of_the_French_Army_in_the_Russian_campaign_1812-1813 >
    figure>
    
    < One obstacle to creating elegant figures on the web is the difficulty of handling different screen sizes, 
    especially on the fly. Embedded <code iframe > elements are particularly troublesome. For these instances we 
    wrap the element <code \<iframe > in a <code \<figure,iframe-wrapper >.  >
    < You can use <code div > instead of <code figure >, with slightly different results but the same general effect. > 
    
    <figure,iframe-wrapper
      <iframe,width=853,height=480,src=https://www.youtube.com/embed/YslQ2625TR4,frameborder\=0,allowfullscreen\= >
    figure>
    
    < We could not wait with this expriment with a sphere, a cube and a cone:
      <MLABEL,for=mn-x3d &#8314; >
      <INPUT,id=mn-x3d > 
      <MN
!-------------------
    <x3d> 
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
  Use left mouse-button to rotate and right mouse button to zoom in and out. >  x3d in the margin. We've removed the usual width- and height-attributes from x3d-element.
  In tufte.css we gave the x3d-element has same style as img-element. >
  
  < If that is not your cup of tea, Tufte CSS also provides support for Edward Tufte and Adam Schwartz’s <a,http://imagequilts.com/ ImageQuilts >. >
        
section>
<section
<h2,epilogue Epilogue >
    
    < As usual we have extracted some metadata from the content (see meta-elements in <code HTML-head >). Try printing: the url's are added to the bottem of the article.  >
    < One final margin note.
    <MLABEL,for=sn-euler &#8314; >
    <INPUT,i=sn-euler >
    <MN $ e^{i\pi} + 1 = 0 $ > Here we use <a,https://katex.org/ <span,latex <span K ><span,latex-sup a ><span T><span,latex-sub e ><span X > > a> with 
    the <a,https://katex.org/docs/autorender.html <em auto-render extension > >. >

section>
article>