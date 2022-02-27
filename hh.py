# hh.py version 0.4 bete of HaHa-reader
# second upload 22/02/2022

import os
import argparse
import re 
import webbrowser

__version__ = '0.4 beta'

class Element():

    def __init__(self, document, open_tag="", parent=None):
    
        self.document = document
        self.parent = parent
        self.half_close_tag = "" # example: div>
        self.child = None
        self.metadata = None
        self.footnote = False
        self.footnote_reuse = False
        self.reference = False
        self.definition = False
        self.include = False
        self.include_depth = 0
        self.html = ""
        self.readOpenTag(open_tag)
       
    def readOpenTag(self, open_tag):
        '''Evaluates opening tag: <li,red,i=xxx ...'''
            
        H_num_string = ''
        H_id_num_string = ''
        footnote = False
        reference = False
        
        if ':=' in open_tag:
            define = open_tag.split(':=')
            self.document.defined[define[0][1:]] = define[1]
            self.definition = True
        elif 'INCLUDE' in open_tag:
            file = open_tag.split(':')[1]
            self.include = True
            self.document.read_include(file, self.parent)
        else:
            ot = open_tag.split(',')
            self.tag = ot[0][1:]
            atts = ot[1:]
                    
            if self.tag in self.document.defined.keys():
                ot = self.document.defined[self.tag].split(',')
                ot.extend(atts)
                self.tag = ot[0]
                
            if self.tag.startswith('GETF:'):
                footnote_label = self.tag.split(':')[1]
                self.half_close_tag = "span>"
                footnote = True
                
                if footnote_label in self.document.footnote_order: # we can not us  same id twice
                    self.tag = "span class='footnote'" 
                    self.footnote_reuse = True
                else:
                    self.tag = "span id='footnote_backlink_%s' class='footnote'" % footnote_label
                    self.document.footnote_order.append(footnote_label)
                
            elif self.tag.startswith('GETR:'):
                ref_label = self.tag.split(':')[1]
                self.tag = "span id='backlink_%s' class='reference'" % ref_label
                self.half_close_tag = "span>"
                reference = True
                if ref_label not in self.document.referenced:
                    self.document.referenced.append(ref_label)
            elif self.tag.startswith('SETF:'):
                self.footnote_label = self.tag.split(':')[1]
                self.tag = "span id='footnote_%s' " % self.footnote_label
                self.half_close_tag = "span> <a class='noprint' href='#footnote_backlink_%s'> &#11149; </a> " % self.footnote_label
                self.document.footnote_dict[self.footnote_label] = ""
                self.footnote = True
            elif self.tag.startswith('SETR:'):
                self.ref_label = self.tag.split(':')[1]
                self.tag = "span id='reference_%s' " % self.ref_label
                self.half_close_tag = "span> <a class='noprint' href='#backlink_%s'> &#11149; </a> " % self.ref_label
                self.document.reference_dict[self.ref_label] = ""
                self.reference = True
            else:
                if self.tag == "":
                    if self.parent.tag in self.document.anonymous_tags.keys():
                        self.tag = self.document.anonymous_tags[self.parent.tag]
                    else:
                        self.tag = 'p'
                self.half_close_tag = "%s>" % self.tag
            
            if self.tag not in self.document.H_elements:
                self.html = "<%s" % self.tag
            
            # -------- numbering of (h1), h2, h3 ... ----------------
            if self.tag in self.document.H_elements:
                i = self.document.H_elements.index(self.tag)
                self.document.H_number[i] += 1
                for n in range(i + 1, 7):
                    self.document.H_number[n] = 0
                for j in range(0,6):
                    num = self.document.H_number[j]
                    if num != 0:
                        H_num_string += '%s.' % num
                if self.document.config['h1'] == True:
                    H_num_string = H_num_string[0:-1]
                else:
                    H_num_string = H_num_string[2:-1]
                H_id_num_string = H_num_string.replace('.', '_')
                    
                if self.document.config['h1'] == True:
                    self.html += "<%s title='section_%s' class='H_level_%s' " % (self.tag, H_id_num_string, self.tag[1] )
                else:
                    if self.tag != 'h1':
                        self.html += "<%s title='section_%s' class='H_level_%s' " % (self.tag, H_id_num_string, self.tag[1])
                    else:
                        self.html = "<%s " % (self.tag)
            # ------------- attributes -----------
            for att in ot[1:]:
                att = att.replace('\=', 'TEMP-EQUAL')
                name_value = att.split('=')
                    
                if len(name_value) == 2:
                    
                    if name_value[0] in self.document.boolean_attributes:
                        self.html += " %s " % (name_value[0])
                    else:
                        if name_value[0] in self.document.short_attributes.keys():
                            name_value[0] = self.document.short_attributes[name_value[0]]
                        val = name_value[1].replace('\_', 'TEMP-UNDERSCORE')
                        val = val.replace('_', ' ')
                        val = val.replace('TEMP-UNDERSCORE', '_')
                        val = val.replace('TEMP-EQUAL', '=')
                        self.html += " %s='%s'" % (name_value[0], val )
                        if name_value[0] == 'href':
                            self.document.url_list.append(name_value[1])
                else:
                    if name_value[0] in self.document.dublin_core.keys():
                        self.metadata = name_value[0]
                        
                    elif self.tag in self.document.anonymous_attributes.keys():
                        val = name_value[0].replace('\_', 'TEMP-UNDERSCORE')
                        val = val.replace('_', ' ')
                        val = val.replace('TEMP-UNDERSCORE', '_')
                        val = val.replace('TEMP-EQUAL', '=')
                        self.html += " %s='%s'" % (self.document.anonymous_attributes[self.tag], val)
                        if self.tag == 'a':
                            self.document.url_list.append(val)
                            
                    else:
                        val = name_value[0].replace('\_', 'TEMP-UNDERSCORE')
                        val = val.replace('_', ' ')
                        val = val.replace('TEMP-UNDERSCORE', '_')
                        self.html += " class='%s'" % val
            self.html += ">"
            if H_id_num_string != '':
                self.html += "<span id='section_%s'></span>" % H_id_num_string
            # -------- numbering of (h1), h2, h3 ... ----------------
            if self.document.config['numbers'] and self.tag in self.document.H_elements:
                if self.document.config['h1'] == True:
                    self.html += '<span class="number">%s</span> ' % H_num_string
                else:
                    if self.tag != 'h1':
                        self.html += '<span class="number">%s</span> ' % H_num_string
            # ------------  link to footnotes  ---------
            if footnote:
                
                if self.footnote_reuse == True:
                    self.html += "<a href='#footnote_%s'> [%d]</a> " % (footnote_label, self.document.footnote_label_number[footnote_label])
                else:
                    self.html += "<a href='#footnote_%s'> [%d]</a> " % (footnote_label, self.document.footnote_counter)
                    self.document.footnote_label_number[footnote_label] = self.document.footnote_counter
                    self.document.footnote_counter += 1
                
            if reference:
                self.html += "<a href='#reference_%s'> [%s]</a> " % (ref_label, ref_label.replace('_', ' '))
        
    def add_child(self, html, glue=1):
        
        if glue == 1:
            self.html += "%s" % html
        else:
            self.html += "%s " % html
        for h in range(1,7):
            
            if html.startswith('<h%d' % h):
                self.document.toc_list.append(html)
        self.child = None
        
    def append(self, source_word, mode='word', glue=0, body=0):
        
        if self.child:
            self.child.append(source_word, mode, glue, body)
            if self.metadata != None and not source_word.startswith('<'):
                if source_word.startswith('>') or source_word.startswith(self.half_close_tag):
                    spl = source_word.split('>')
                    self.document.dublin_core[self.metadata] += "%s " % spl[1]
                else:
                    self.document.dublin_core[self.metadata] += "%s " % source_word
        else:
            if mode == 'line':
                self.html += source_word 
            else:
                if source_word.startswith('<'):
                    self.child = Element(document = self.document, open_tag = source_word, parent = self)
                elif source_word.startswith('>') or source_word.startswith(self.half_close_tag):
                    if body == 0 and self.half_close_tag == 'body>': # error detection
                        print('error at line %d in %s (probably: MISSING OPENING TAG)'% (self.document.line_number, self.document.file))
                    if self.definition == True or self.include == True:
                        pass
                    elif self.tag in self.document.empty_elements:
                        pass
                    elif self.tag == 'a':
                        self.html = self.html[0:-1] + "</a> <span class='whenprint'>(url %d)</span>" % len(self.document.url_list)
                    else:
                        if source_word in ['>', self.half_close_tag]: # normal case
                            if self.html[-1] == '>': # element is empty, although no member of empty_elements
                                self.html = self.html + "</%s" % self.half_close_tag
                            else:
                                self.html = self.html[0:-1] + "</%s" % self.half_close_tag 
                        else:
                            source_word = source_word.replace('>', '> ')
                            swords = source_word.split()
                            if self.html[-1] == '>': # element is empty
                                self.html = self.html + "</%s" % self.half_close_tag
                            else:
                                self.html = self.html[0:-1] + "</%s%s" % (self.half_close_tag, swords[1])
                            
                    if self.parent != None:
                        if self.footnote:
                            self.document.footnote_dict[self.footnote_label] = self.html
                            self.parent.child = None
                        elif self.reference:
                            self.document.reference_dict[self.ref_label] = self.html
                            self.parent.child = None
                        else:
                            self.parent.add_child(self.html, glue)
                else:
                    if source_word.endswith('>'): # catch dirty source
                        self.html += "%s " % source_word[0:-1]
                        self.append('>', mode, glue, body)
                    else:
                        self.html += "%s " % source_word
                        if self.metadata != None:
                            self.document.dublin_core[self.metadata] += "%s " % source_word
   
class Document():
    
    def __init__(self, config):
    
        self.config = config
        self.directories = {'css': None} # updated in self.check
        self.mode = 'word'
        self.comment = False
        self.H_number = [0, 0, 0, 0, 0, 0, 0] # used in Element (numebering of headers)
        self.footnote_counter = 1
        self.footnote_label_number = {}
        self.footnote_order = []
        self.footnote_dict = {}
        self.url_list = []
        self.line_number = 0 # error detection
        self.file = None     # error detection
        self.dublin_core = {'dc.title':"", 'dc.description': "", 'dc.subject': "", 'dc.creator': "", 'dc.date': "", 
                             'dc.language': self.config['lang'], 'dc.rights': "", 'dc.format': 'HTML', 'dc.type': "", 'dc.contributor': "", 
                             'dc.coverage': "", 'dc.identifier': self.config['sourcefile'], 'dc.publisher': "", 'dc.relation': "", 'dc.source': ""  }
        self.boolean_attributes = ['allowfullscreen', 'allowpaymentrequest', 'async', 'autofocus', 
                                   'autoplay', 'checked', 'controls', 'default', 'defer', 'disabled', 'formnovalidate', 
                                   'hidden', 'ismap', 'itemscope', 'loop', 'multiple', 'muted', 'nomodule', 
                                   'novalidate', 'open', 'playsinline', 'readonly', 'required', 'reversed', 
                                   'selected', 'truespeed']
        self.empty_elements = ['TOC', 'NOTES', 'REFS', 'URLS', 'area', 'base', 'br', 'col', 'embed', 'hr', 'img', 'input', 'link', 'meta', 'param', 'source', 'track', 'wbr']
        self.H_elements = ['h1', 'h2', 'h3', 'h4', 'h5', 'h6']
        self.anonymous_tags = {'ul': 'li', 'ol': 'li', 'tr': 'td'}
        self.short_attributes = {'c': 'class', 'i': 'id', 'h': 'href', 'l': 'lang', 'a':'alt', 's':'src', 't':'title'}
        self.anonymous_attributes = {'a': 'href', 'img':'src'}
        self.referenced = []
        self.reference_dict = {}
        self.toc_list = []
        self.include_depth = 0
        self.head = None
        self.body = None
        self.defined = {}
        self.multiple_endtags = re.compile(r'^>+$') # matches '>>' or '>>>>'
        self.check()
        self.read_source()
        self.create_head()
        self.write_output()
        
    def check(self):
        
        s = self.config['sourcefile']
        if not os.path.exists(s):
            print('\n\tERROR: Sourcefile "%s" does not exist' % s) 
            exit()
        
        if self.config['outputfile'] == None:
            for ext in ['.txt', '.hh', '.haha']: 
                if self.config['sourcefile'].endswith(ext):
                    self.config['outputfile'] = self.config['sourcefile'].replace(ext, '.html')
                    
        # locating directories css e.a. in dir . or .. or ../..
        dirs = os.listdir('.')
        for dir in self.directories.keys():
            if dir in dirs:
                self.directories[dir] = './%s/' % dir
            else:
                pdirs = os.listdir('..')
                if dir in pdirs:
                    self.directories[dir] = '../%s/' % dir
                else:
                    ppdirs = os.listdir('../..')
                    if dir in ppdirs:
                        self.directories[dir] = '../../%s/' % dir
        
    def create_head(self):
        
        html = '<!DOCTYPE html>\n<html dir="%s" lang="%s">\n<head>\n' % (self.config['dir'], self.config['lang'])
        html += '<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />\n'
        html += '<meta name="viewport" content="width=device-width" />\n'
        html += '<title>%s</title>\n' % self.dublin_core['dc.title']
        html += '<!-- hh.py configuration \n'
        for k in self.config.keys():
            html += '%s : %s\n' % (k, self.config[k]) 
        html += '-->\n' 
       
        html += '''<style>
    div.header {font-size: 1.6rem;
            padding: 20px;}
    .whenprint {display: none;}
    @media print {
        div.whenprint {display: block;}
        span.whenprint {display: inline;}
        .noprint {display: none;}
        a {color: black;}
    }
    div.table_of_contents {margin-left: 25px; border-left: solid 1px black; padding: 5px;}
    div.table_of_contents  > div > a {text-decoration: none; color: black; font-size: 1.3rem;}
    div.table_of_contents  > div > a:hover {background-color: silver; color: white; }
    div.table_of_contents  > div  a.H_level_2 {margin-left: 12px;}
    div.table_of_contents  > div  a.H_level_3 {margin-left: 24px;}
    div.table_of_contents  > div  a.H_level_4 {margin-left: 36px;}
    div.table_of_contents  > div  a.H_level_5 {margin-left: 48px;}
    </style>
    '''
        if self.config['css'] == 'default':
            html += '<link rel="stylesheet" href="%s%s" >\n' % (self.directories['css'], 'hh_basic.css')
        elif self.config['css'] == 'tufte':
            html += '<link rel="stylesheet" href="https://edwardtufte.github.io/tufte-css/tufte.css" >\n'
            html += '<link rel="stylesheet" href="https://edwardtufte.github.io/tufte-css/latex.css" >\n'
            html += '<link rel="stylesheet" href="%s%s" >\n' % (self.directories['css'], 'tufte-haha.css')
        #OPTION: add more css-options (adapt list in argparse (function run() below)
        
        html += '<link rel="schema.dc" href="http://purl.org/dc/elements/1.1/">\n'
        for dc in self.dublin_core.keys():
            if self.dublin_core[dc] != "":
                html += '<meta name="%s" content="%s" />\n' % (dc, self.dublin_core[dc].strip().replace('\n', ''))
        
        if self.config['x3d']:
            html += "<script type='text/javascript' src='https://www.x3dom.org/download/x3dom.js'> </script>\n" 
            html += "<link rel='stylesheet' type='text/css' href='https://www.x3dom.org/download/x3dom.css'>\n"
        
        if self.config['katex']:
            html += '<!-- webfontloader -->'
            html += '''<script>
  window.WebFontConfig = {
    custom: {
      families: ['KaTeX_AMS', 'KaTeX_Caligraphic:n4,n7', 'KaTeX_Fraktur:n4,n7',
        'KaTeX_Main:n4,n7,i4,i7', 'KaTeX_Math:i4,i7', 'KaTeX_Script',
        'KaTeX_SansSerif:n4,n7,i4', 'KaTeX_Size1', 'KaTeX_Size2', 'KaTeX_Size3',
        'KaTeX_Size4', 'KaTeX_Typewriter'],
    },
  };
</script>'''
            html += '<script defer src="https://cdn.jsdelivr.net/npm/webfontloader@1.6.28/webfontloader.js" integrity="sha256-4O4pS1SH31ZqrSO2A/2QJTVjTPqVe+jnYgOWUVr7EEc=" crossorigin="anonymous"></script>'
        
            html += '<link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/katex.min.css" integrity="sha384-MlJdn/WNKDGXveldHDdyRP1R4CTHr3FeuDNfhsLPYrq2t0UBkUdK2jyTnXPEK1NQ" crossorigin="anonymous">\n'
            html += '<!-- The loading of KaTeX is deferred to speed up page rendering -->\n'
            html += '<script defer src="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/katex.min.js" integrity="sha384-VQ8d8WVFw0yHhCk5E8I86oOhv48xLpnDZx5T9GogA/Y84DcCKWXDmSDfn13bzFZY" crossorigin="anonymous"></script>\n'
            html += '<!-- To automatically render math in text elements, include the auto-render extension: -->\n'
            html += '<script defer src="https://cdn.jsdelivr.net/npm/katex@0.15.2/dist/contrib/auto-render.min.js" integrity="sha384-+XBljXPPiv+OzfbB3cVmLHf4hdUFHlWNZN5spNQ7rmHTXpd7WvJum6fIACpNNfIR" crossorigin="anonymous"></script>\n'
        
            html += '''<script>
    document.addEventListener("DOMContentLoaded", function() {
        renderMathInElement(document.body, {
          // customised options
          // https://katex.org/docs/autorender.html
          // • auto-render specific keys, e.g.:
          delimiters: [
              {left: '$$', right: '$$', display: true},
              {left: '$', right: '$', display: false},
              {left: '\\\\(', right: '\\\\)', display: false},
             {left: '\\\\[', right: '\\\\]', display: true}
          ],
          // • rendering keys, e.g.:
          throwOnError : false
       });
    });
</script>\n'''

        if self.config['highlight']:
        
            html += '<link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.4.0/styles/%s">\n' % self.config['highlight-css']
            html += '<script src="https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.4.0/highlight.min.js"></script>'
            html += '<script>hljs.highlightAll();</script>\n'
            
        html += '</head>\n'
        self.head = html
        
    def read_include(self, file, parent_element):
        
        tokens = {'\&': '&amp;' ,'\>':'&gt;', '\<':'&lt;'}
        self.line_number = 0 # error detection
        self.file = file # error detection
        
        self.include_depth += 1
        
        if self.include_depth > self.config['includes']:
            print('WARNING: includes above level %d' % self.config['includes'])
            yesno = input('\nContinue? (y/n) Press [Enter]: ')
            if yesno.lower() == "y":
                pass
            else:
                exit()
            
        with open(file, 'r', encoding="utf-8") as source:
            for line in source.readlines():
                self.line_number += 1  # error detection
                
                if line.startswith('!-----'):
                    if self.mode == 'word':
                        self.mode = 'line'
                    else:
                        self.mode = 'word'
                    continue
                
                if self.mode == 'line':
                    parent_element.append(line, mode='line')
                elif self.mode == 'word':
                    if line.strip().startswith('<!--'):
                        self.comment = True
                        continue
                    if line.strip().endswith('-->'):
                        self.comment = False
                        continue
                    if self.comment == True:
                        continue
                    else:
                        for word in line.split():
                            for t in tokens.keys():
                                word = word.replace(t, tokens[t])
                            if self.multiple_endtags.match(word):
                                word = word.replace('>', '> ')
                                for endtag in word.split():
                                    parent_element.append(endtag.strip())
                            else:
                                if '><' in word: # case ><b
                                    word = word.replace('><', '> <')
                                    words = word.split()
                                    parent_element.append(words[0], glue=1)
                                    parent_element.append(words[1])
                                else:
                                    parent_element.append(word)
                        
                    parent_element.append('\n')
                #print(self.line_number, end= ' ')
        self.include_depth -= 1
        
    def create_header(self, body):
    
        body.html += '<header class="hh noprint"></header>\n<nav class="hh noprint"></nav>\n'
        
    def create_footer(self, body):
    
        body.html += '<footer class="hh noprint"></footer>\n\n'
    
    def read_source(self):
        
        tokens = {'\&': '&amp;' ,'\>':'&gt;', '\<':'&lt;'}
        
        body_tag = "<body,class=%s" % (self.config['class'])
        body = Element(document = self, open_tag = body_tag )
        body.append('\n')
        #OPTION: self.create_header(body)
                
        self.read_include(self.config['sourcefile'], body)
        
        body.html += '\n<URLS>\n' # location for URL, visibe @media print
        #OPTION: self.create_footer(body)
        body.append('>', body=1) # close body-element
        
        # ------------- footnotes ------------
        self.footnote_counter = 1
        
        footnoteblock = '<div class="footnotes">'
        for f in self.footnote_order:
            footnoteblock += '\n<p class="footnote"><span class="footnote_number">[%d]</span> %s</p>' % (self.footnote_counter, self.footnote_dict[f])
            self.footnote_counter += 1  
        footnoteblock += '\n</div>\n'
        f = re.findall('<NOTES>', body.html)
        if len(f) > 1:
            body.html = body.html.replace('<NOTES>', "", len(f) - 1)
        body.html = body.html.replace('<NOTES>', footnoteblock)
        
        # --------- references ---------------
        refblock = '<div class="references">'
        
        for r in sorted(self.referenced):
            refblock += '\n<p class="reference"><span class="reference_label">[%s]</span> %s</p>' % (r.replace('_', ' '), self.reference_dict[r])
        refblock += '\n</div>\n'
        f = re.findall('<REFS>', body.html)
        if len(f) > 1:
            body.html = body.html.replace('<REFS>', "", len(f) - 1)
        body.html = body.html.replace('<REFS>', refblock )
        
        # ---------- URLs -------------------
        url_counter = 1
        urlblock = "<div class='urls whenprint'>\n<div class='header'>URL's</div>"
        
        for u in self.url_list:
            urlblock += '\n<p class="url"><span class="url_number">[%d]</span> %s</p>' % (url_counter, u)
            url_counter += 1
        urlblock += '\n</div>\n'
        body.html = body.html.replace('<URLS>', urlblock )
        
        # ------------- TOC ------------------
        if self.config['toc'] != 0:
            TOC = "<div class='table_of_contents'>\n"
            for h in self.toc_list:
                tag = h[1:3]
                num = h[2]
                if h.startswith('<h1') and self.config['h1'] == False:
                    pass
                else:
                    if int(tag[1]) <= self.config['toc']:
                        hlink = h.replace("<%s title='" % tag, "<div class='H_level_%s'><a href='#" % num )
                        hlink = hlink.replace("</%s>" % tag, "</a></div>\n")
                        hlink = hlink.replace("id=", "alt=")
                        TOC += hlink
            TOC += "</div>\n"
        else:
            TOC = ""
        body.html = body.html.replace('<TOC>', TOC, 1) # only first occurance of <TOC>
        body.html = body.html.replace('<TOC>', '')      # remove others
        
        self.body = body.html
        
    def write_output(self):               
        # write output       
        with open(self.config['outputfile'], 'w', encoding="utf-8") as output:
            output.write(self.head)
            output.write(self.body)
            output.write("\n</html>")
        #OPTION: post processing
        if self.config['view']:    
            view = input('\nView in favorit browser? (y/n) Press [Enter]: ')
            if view.lower() == "y":
                webbrowser.open(self.config['outputfile'], new=2, autoraise=True)
    
def run():

    parser = argparse.ArgumentParser()
    parser.add_argument("sourcefile", help="path to hhtmlfile")
    parser.add_argument("-o", "--outputfile", help="path to output htmlfile (default = 'sourcefilename.html')")
    parser.add_argument("-t", "--toc", help="create table of contents with depth n, or not (if value 0)",  type=int, choices=[0, 1, 2, 3, 4, 5, 6], default=3)
    parser.add_argument("-h1", "--h1", help="include h1-header in table of contents", action="store_true")
    parser.add_argument("-n", "--numbers", help="numbered headers", action="store_true")
    parser.add_argument("-i", "--includes", help="allowed depth of includes",  type=int,  default=4)
    parser.add_argument("-v", "--view", help="view output in browser", action="store_true")
    parser.add_argument("-l", "--lang", help="language code for <html lang=''>", default='en')
    parser.add_argument("-d", "--dir", help="text direction of content for <html dir=''> (ltr, rtl | auto) ", default='ltr')
    parser.add_argument("-c", "--class", help="set class attribute <body class=''> ", default='hh')
    # target <head> css, javascripts 
    parser.add_argument("-C", "--css", help="stylesheet(s) (default | tufte)", default='default')
    parser.add_argument("-K", "--katex", help="include KaTeX scripts (math LaTeX)", action="store_true")
    parser.add_argument("-H", "--highlight", help="include Highlight scripts (coloring code)", action="store_true")
    parser.add_argument("-HC", "--highlight-css", help="KaTeX style sheet", default="github.min.css")
    parser.add_argument("-X", "--x3d", help="include x3d scripts (x3dom)", action="store_true")
    parser.add_argument('--version', action='version', version='%(prog)s ' + __version__)
    args = parser.parse_args()
    
    config = {'sourcefile':None, 'outputfile':None, 'toc':2, 'h1':0, 'numbers': 0, 'includes': 4 ,'css':'default', 'katex':0, 'highlight': 0, 'highlight-css':'github.min.css', 'x3d':0, 'dir':'ltr', 'lang':'en', 'class': 'hh', 'view': False}
    config.update(vars(args))
    d = Document(config)

if __name__ == '__main__':
    run()
    
    
