set tabstop=4
set softtabstop=4
set shiftwidth=4
set expandtab
set smartindent

set number
set relativenumber
set guicursor=n-v-c-sm:block,i-ci-ve:ver25,r-cr-o:hor20

"set nohlsearch
set noerrorbells
set nowrap
set incsearch

set termguicolors
set signcolumn=yes
set mouse=a
set foldmethod=syntax
set foldlevel=0

inoremap {<CR> {<CR>}<Esc>O


" Specify a directory for plugins
" - For Neovim: stdpath('data') . '/plugged'
" - Avoid using standard Vim directory names like 'plugin'

call plug#begin('~/.config/nvim/plugged')

    Plug 'gruvbox-community/gruvbox'
    
    Plug 'ErichDonGubler/vim-sublime-monokai'
    
    Plug 'joshdick/onedark.vim'
    Plug 'altercation/vim-colors-solarized'

    Plug 'ycm-core/YouCompleteMe'
    Plug 'junegunn/fzf', { 'do': { -> fzf#install() } }
    Plug 'junegunn/fzf.vim'

    "Plug 'sickill/vim-monokai'
    "Plug 'patstockwell/vim-monokai-tasty'
    "Plug 'tomasr/molokai'
    "Plug 'crusoexia/vim-monokai'
    "Plug 'Tiriel/sublimemonokai'
    "Plug 'ctrlpvim/ctrlp.vim'
    "Plug 'vim-scripts/gruvbox'
    "Plug 'octol/vim-cpp-enhanced-highlight'
    "Plug 'bfrg/vim-cpp-modern'

call plug#end()

syntax on
colorscheme sublimemonokai

nnoremap <C-f> :Files ~/Programming/Library/<CR>
noremap! <C-BS> <C-w>
noremap! <C-h> <C-w>
inoremap <C-w> <C-\><C-o>dB
inoremap <C-BS> <C-\><C-o>db

augroup folds
  au!
  au InsertEnter * let w:oldfdm = &l:foldmethod | setlocal foldmethod=manual
  au InsertLeave *
        \ if exists('w:oldfdm') |
        \   let &l:foldmethod = w:oldfdm |
        \   unlet w:oldfdm |
        \ endif |
        \ normal! zv
augroup END


autocmd filetype cpp nnoremap <C-c> :w <bar> !Compile.sh %:r <CR> 
