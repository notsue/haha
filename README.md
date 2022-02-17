# HaHa

HH ('HaHa') is a markup language that may be not so usefull. It is
based on the assumption that the user knows how HTML works (elements, 
attributes, ...) and does not want to spend much effort in learning 
other markup languages. 

## Basic rules 

- Opening tag: '\<p>' is reduced to '<p'
- The closing tag can be a nameless '>'         
- Attributes in '\<p class="red" id="example">' are reduced to '<p,class=red,id=example' 

Some attribute-names have a short alternative: 

- 'c=' equals 'class='
- i= equals id= 
- h= equals href= 
- s= equals src= 
- a= equals alt= 
- t= equals title= 
- l= equals lang= 

Our example becomes: <p,c=red,i=example 

If the value of an attribute contains multiple words, the whitespaces are 
replaced by underscores.
 
For example: <p,c=warning_important means <p class="waring important"> 

Tag-names and attribute-names should be written in smallcase characters.

Boolean attributes are inserted as for example ...,async=,... (equal sign, but no value)

Empty elements? <br  > Simple.

To write < or > as regular content use the escape sign: \< , \>   

    
To summerize: the opening of an element (opening tag with attributes) is one 'word' without whitespace.
  
### Anonymous tags and attributes

In some cases the opening tag needs no name:

The anonymous opening tag < is interpreted as: 

- a <li if the element is a child of <ul or <ol 
- a <td if the element is a child of <tr 
- a <p in all other contexts 

There are also some anonymous attributes: 


- ,http://demo.org becomes href="http://demo.org when used in element a, as in <a,http://demo.or  
- ,demo-picture.png becomes src="demo-picuture.png" when used in element img, as in <img,demo-picture.png  
- ,red becomes class="red" in all other cases


Anomymous attributes can be combined with other (short) attributes as in <img,demo.png,a=nice_picture 

Anonymous attributes can be used in anonymous tags.