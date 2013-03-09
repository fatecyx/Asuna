""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
" File:
"   omnitags.vim
"
" Author:
"   fwlei <fwlei@live.com>
"
" Version:
"   0.2
"
" Description:
"   This plugin can help you to maintenance tags file.
"
"   There are 3 commands:
"
"     1. :OmniTagsLoad /path/to/tags-file
"
"     Load the tags-file and generate a list of source files indexed by
"     tags-file.
"
"     If tags-file doesn't exist, it can create a null file automaticlly.
"
"     Once tags-file are loaded, every buffer-write event will trigger a
"     re-index operation on current file if current file exists in tags-file.
"
"     The operation will do:
"       a) delete tags of current file from tags-file.
"       b) call "ctags -a" command add the tags of current file to tags-file.
"
"     Therefor, your tags-file will always updated.
"
"     Don't mind the speed of re-index operation, it is indetectable while
"     the tags-file size small than 20MiB.
"
"     2. :OmniTagsUpdate {file1} {file2} ...
"
"     Update the tags-file loaded before, you can specify many files and use
"     wildcards(see ":h wildcards"), "wildignore" option(see "h: wildignore")
"     also influences the result of wildcards parsing.
"
"     If files are not in tags yet, the plugin will add those files to tags,
"     if files already exists, the plugin will update them.
"
"     You can specify no files, for re-index all files that already indexed.
"
"     3. :OmniTagsUnload
"
"     Just an oppsite of :OmniTagsLoad, usually needs not be called by human.
"
" Installation:
"   Just drop the script to ~/.vim/plugin.
"
"   The plugin depends on unix commands below:
"     ctags, grep, tail, cut, sort
"
"   Common linux distribution installed them normally, you can find windows
"   version of them at http://ctags.sf.net/ and http://gnuwin32.sf.net/.
"
""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""

if exists("loaded_OmniTags")
	finish
endif
let loaded_OmniTags = 1

let s:savedCpo = &cpo
set cpo&vim

"""""""""""""""""""""""""
" the utility functions "
"""""""""""""""""""""""""

" for error message
function! s:error(msg)
    echohl Error
    redraw
    echon a:msg
    redraw
    echohl None
endfunction

" generate file list from tags file
function! s:genFileList(tagsFile)
    return split(system('tail -n +7 "'.a:tagsFile.'" | cut -s -f 2 | sort -u'), "\n")
endfunction

" generate a empty tags file
function! s:genTagsFile(tagsFile)
	call system('ctags -f "'.a:tagsFile.'" -L -', 'No\ file\ in\ this\ path\!')
endfunction

" add tags of files in fileList
function! s:addTags(tagsFile, fileList)
    let ctagsArg = '--c++-kinds=+p --fields=+iaS --extra=+q'
	echo("addTags".tagsFile)
	call system('ctags -a '.ctagsArg.' -f "'.a:tagsFile.'" -L -', join(a:fileList, "\n"))
endfunction

" delete tags of files in fileList
function! s:deleteTags(tagsFile, fileList)
    let tmpFile = fnamemodify(a:tagsFile, ':p:h').'/.'.fnamemodify(a:tagsFile, ":t").'.tmp'
    call system('grep -Fv -f - "'.a:tagsFile.'" > "'.tmpFile.'"', join(a:fileList,"\n"))
    return tmpFile
endfunction

""""""""""""""""""""""""""""""""
" the user-interface functions "
""""""""""""""""""""""""""""""""

function! s:updateCurrentFile()
	echo('updateCurrentFile\n')
	if !exists('s:tagsFile') || !exists('s:fileList')
        call s:error('Please load tags file first!')
		return
	endif

	let filename = expand("%:p")
	if has('win32')
		let filename = tr(filename, "\\", "/")
	endif

    if index(s:fileList, filename) < 0
	"echo("no found in\n".system('tail -n +7 tags | cut -s -f 2 | sort -u')."?????".filename)
        return
    endif

	let tmpFile = s:deleteTags(s:tagsFile, [filename])
	call s:addTags(tmpFile, [filename])
    call rename(tmpFile, s:tagsFile)
endfunction

function! s:updateFiles(...)
	if !exists("s:tagsFile") || !exists("s:fileList")
        call s:error("Please load tags file first!")
		return
	endif

    echon "Updating tags..."
    redraw

    if a:0 <= 0
        let choice = confirm("Update all files?", "&Yes\n&No")
        if choice == 1
            call s:genTagsFile(s:tagsFile)
            call s:addTags(s:tagsFile, s:fileList)
        endif

        return 
    endif

    let newFiles = []
    let oldFiles = []
    for filePat in a:000
        for filename in split(glob(filePat), "\n")
            if !isdirectory(filename)
                let filename = fnamemodify(filename, ":p")
                if has("win32")
                    let filename = tr(filename, "\\", "/")
                endif

                if index(s:fileList, filename) >= 0
                    call add(oldFiles, filename)
                else
                    call add(newFiles, filename)
                endif
            endif
        endfor
    endfor

    let fileList = []

    if len(oldFiles) > 0
        let fileList += oldFiles
        let tmpFile = s:deleteTags(s:tagsFile, oldFiles)
    endif

    if len(newFiles) > 0
        call extend(s:fileList, newFiles)
        call sort(s:fileList)
        let fileList += newFiles
    endif

    if len(fileList) > 0
        if exists("tmpFile")
            call s:addTags(tmpFile, fileList)
            call rename(tmpFile, s:tagsFile)
        else
            call s:addTags(s:tagsFile, fileList)
        endif
    endif

    echon "Updating tags... Done!"
    redraw
endfunction

function! s:loadTagsFile(path)
	if !filewritable(a:path)
        let choice = confirm("The tags file not exists, create it?", "&Yes\n&No")
        if choice == 1
            call s:genTagsFile(a:path)
        else
		    return
        endif
	endif

	if exists("s:fileList") || exists("s:tagsFile")
		call s:unloadTagsFile()
	endif

    echon "Parsing tags file..."
    redraw

    let s:tagsFile = fnamemodify(a:path, ":p")
    if has("win32")
        let s:tagsFile = tr(s:tagsFile, "\\", "/")
    endif

    let s:fileList = s:genFileList(s:tagsFile)

   	let s:savedTags = &tags
    let &tags = s:tagsFile . "," . &tags

    aug OmniTags
        au BufWritePost * call s:updateCurrentFile()
        au VimLeavePre * call s:unloadTagsFile()
    aug END

    echon "Parsing tags file... Totally ".string(len(s:fileList))." file(s)."
    redraw
endfunction

function! s:unloadTagsFile()
	if !exists("s:tagsFile") && !exists("s:fileList")
		return
	endif

	let &tags = s:savedTags
    au! OmniTags
    aug! OmniTags

	unlet s:savedTags
	unlet s:tagsFile
	unlet s:fileList
endfunction

" register commands

if !exists(":OmniTagsLoad")
	command -nargs=1 -complete=file OmniTagsLoad :call s:loadTagsFile(<f-args>)
endif

if !exists(":OmniTagsUnload")
	command -nargs=0 OmniTagsUnload :call s:unloadTagsFile()
endif
 
if !exists(":OmniTagsUpdate")
	command -nargs=* -complete=file OmniTagsUpdate :call s:updateFiles(<f-args>)
endif

let &cpo = s:savedCpo
unlet s:savedCpo

