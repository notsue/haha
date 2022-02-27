import sys
sys.path.append('../../')
import hh
import xml.etree.ElementTree as ET


config = {'sourcefile':'tufte.hh', 'outputfile':None, 'toc':3, 'h1':0, 'numbers': 1, 'includes': 3 , 'x3d': 1, 
          'css':'tufte', 'katex':1, 'highlight': 1, 'highlight-css': 'github.min.css' , 'dir':'ltr', 'lang':'en', 'class': 'hh', 'view': 0}
    
doc = hh.Document(config)
print(doc.dublin_core['dc.title'])
print('DONE... with Tufte CSS')

print('\nTesting xml.etree. Structure of element body:\n')

tree = ET.fromstring(doc.body)
print(tree.tag)
for child in tree:
    print('  ', child.tag, child.attrib)
    for ch in child:
        print('    ', ch.tag, ch.attrib)
