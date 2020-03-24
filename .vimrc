nnoremap <F4> :! make && make run<cr>
" open debugger with breakpoint on the current line
nnoremap <F5> <C-W>o :Termdebug bin/game<CR><C-W><C-W>:Break<CR><C-W><C-W><C-W><C-W>
