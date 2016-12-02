" Vim Syntax File
" Language: uu
" Maintainer: Thomas Willingham
" Latest Revision: 01 Dec 2016

if exists("b:current_syntax")
    finish
endif

syn keyword basicLanguageKeywords func if else while for nil break
syn keyword builtins print println array
syn keyword stdlib stack push pop peek cons car cdr setCar setCdr min max node getParent getGrandparent setParent setLeft setRight getLeft getRight
syn match uuComment "//.*$"

hi def link basicLanguageKeywords Statement
hi def link builtins Type
hi def link stdlib PreProc
hi def link uuComment Comment
