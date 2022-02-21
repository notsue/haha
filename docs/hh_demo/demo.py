import sys

sys.path.append('../../')
import hh

config = {'sourcefile':'demo.hh', 'outputfile':None, 'toc':2, 'h1':0, 'numbers': 1, 'includes': 3 , 'x3d': 1, 
          'css':'default', 'katex':1, 'highlight': 1, 'dir':'ltr', 'lang':'en', 'class': 'hh', 'view': 1}
    
doc = hh.Document(config)
print(doc.dublin_core['dc.title'])
print('DONE')
