<h1,dc.title HaHa demo and playground >

<TOC >

<h2 Basics >

<p,class=usual,id=me A paragraph with attributes class and id, <b inline bold > and <i inline italics >. Punctuation was glued to 
closing tag of italics, necessary for clean outpu. >

< Multiple end tags are glued here: <b <i try this >>>

< Bold, italic and code should stick together in the html: <b bold ><i italic ><code code >>

<ul
< Nested list >
< we have a choice:
<ol < item one > 
    < item two >
ol> >
< back to unordered list >
ul>

<,value\_a_value\_b Anonymus p with anonymous class="value_a value_b" >

<div,image <img,spam.jpg,i=\_spam,a=the_parrot_is_dead > >

<h2 Comments >

  <!-- only visible in source 
not in html -->

< Using !----------- >

!---------
<!-- 
comment is visible in html
-->
!-----------

<h2 Predefined tags >

<RED:=span,style=color:red;text-decoration:underline >

< Testing new <RED RED > tag >

< Using predefined tags \<G and \<E, to create td's with lang-values 'he' (Greek) and 'en' (English) >

<G:=td,lang=el >
<E:=td,lang=en >

<table
<tr <th Greek > <th English >>
<tr <G  Ἐπίκουρος > <E Epicurus > >
<tr <G Ἕρμαρχος > <E Hermarchus or Hermarch > >
table>

< Some python code, using tag \<PY: >

<PY:=code,language-python >

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

<h2 Footnotes >

< A footnote example <GETF:about >  and a second footnote <GETF:second >  . >

<SETF:about Content of first footnote >

<SETF:second Content of second footnote with <b bold text > and a <a,http://test.org link  > > 

<h2 References >

< We set 4 references: >

<SETR:Parrot_2012 Parrot D. (2012) <i Collected Works > , PSF > 
<SETR:Parrot_1999 Parrot D. (1999) <i Spam, Eggs and Spam > , in <GETR:Parrot_2012 > >
<SETR:Parrot_2009 Parrot D. (2009) <i More Spam and Eggs (and Spam) > , PSF >
<SETR:Parrot_2013 Parrot D. (2012) <i Spam and Eggs in a Nutshell > , PSF > 

< But use only 2. So, only 3 should pop up in reference (one ref referes to a third one ) >

< A paragraph with a reference <GETR:Parrot_1999 > >
< Another paragraph with the second second reference  <GETR:Parrot_2009 > >

<h3 Math and 3D >

< $f(x) = \int_{-\infty}^\infty \widehat{f}(\xi)\,e^{2 \pi i \xi x}\,d\xi$ >

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

< Finaly: <a,https://validator.nu/ w3c's nu validator > > 

<div,header Notes >

<NOTES >

<div,header References >

<REFS >
