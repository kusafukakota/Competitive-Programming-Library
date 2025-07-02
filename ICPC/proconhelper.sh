#!/bin/bash

# =============================================================================
# Linux用 競技プログラミング ヘルパースクリプト
#
# このスクリプトは、PowerShellで書かれた競技プログラミング用の
# ユーティリティ群をBashに移植したものです。
#
# 作者: Gemini
# バージョン: 2.1
#
# 使い方:
# 1. このファイルを 'cj.sh' などの名前で保存します。
# 2. 実行権限を与えます: chmod +x cj.sh
# 3. .bashrc や .zshrc に以下の行を追加して、シェル起動時に読み込むようにします:
#    source /path/to/your/cj.sh
# 4. シェルを再起動するか、`source ~/.bashrc` を実行します。
#    `help` と入力すると、利用可能なコマンド一覧が表示されます。
#
# 依存関係:
# - g++       : C++コンパイラ
# - python    : 'v'コマンドのexpander.pyを実行するために必要
# - xclip     : 'q' (クリップボードから実行) と 'v' (クリップボードにコピー) のために必要
# - bc        : 'time'コマンドでのミリ秒計算に必要
# =============================================================================

# --- グローバル設定 ---
contestdir="./"
curfile="0"

# --- ヘルパー関数 ---
box() {
    local condition=$1
    local color_green='\033[0;32m'
    local color_red='\033[0;31m'
    local color_cyan='\033[0;36m'
    local color_yellow='\033[0;33m'
    local color_nc='\033[0m'

    case $condition in
        1) echo -en "[${color_green}+${color_nc}] " ;;
        0) echo -en "[${color_red}x${color_nc}] " ;;
        -1) echo -en "[${color_cyan}i${color_nc}] " ;;
        2) echo -en "[${color_yellow}#${color_nc}] " ;;
        *) echo -en "[?] " ;;
    esac
}

inner_compile() {
    box -1
    echo -en "\033[0;36mCompiling...\r\033[0m"
}

# --- メインコマンド ---
c() {
    local arg1=${1:-def}
    local arg2=${2:-def}
    local lower_arg1=$(echo "$arg1" | tr 'A-Z' 'a-z')
    local cpp_file="${contestdir}${lower_arg1}.cpp"
    local exec_file="./a.out"

    if [[ ! -f "$cpp_file" ]]; then
        box 0; echo -e "\033[0;31mFile Not Found: $cpp_file\033[0m"; return 1
    fi

    local compile_opts="-std=c++20 -I . -Wall -O2"
    if [[ "$arg2" == "def" ]]; then
        compile_opts="$compile_opts -D_GLIBCXX_DEBUG"
    else
        box -1; echo -e "\033[0;36m_GLIBCXX_DEBUG is disabled\033[0m"
    fi

    inner_compile
    g++ $compile_opts "$cpp_file" -o "$exec_file"
    local exit_code=$?

    if [[ $exit_code -eq 0 ]]; then
        box 1; echo -e "\033[0;32mCompiled Successfully!\033[0m"
        curfile=$(realpath "$cpp_file")
        box -1; echo -e "\033[0;36mCompiled File: $(basename "$curfile")\033[0m"
    else
        box 0; echo -e "\033[0;31mCompilation Failed\033[0m"
    fi
    return $exit_code
}

in() {
    echo -e "\033[0;90m[>] Standard Input :\033[0m"
    if [[ "$1" == "def" || -z "$1" ]]; then cat ./in.txt; else echo -e "\033[0;33m-- hidden --\033[0m"; fi
    echo
    echo -e "\033[0;90m[<] Standard Output :\033[0m"
    ./a.out < ./in.txt
    local exit_code=$?
    echo
    if [[ $exit_code -eq 0 ]]; then
        box 1; echo -e "\033[0;32mExecuted Successfully!\033[0m"
    else
        box 0; echo -e "\033[0;31mRuntime Error (Exit Code: $exit_code)\033[0m"
    fi
}

q() {
    if ! command -v xclip &> /dev/null; then
        box 0; echo -e "\033[0;31m'xclip' is not installed.\033[0m"; return 1
    fi
    echo -e "\033[0;90m[>] Standard Input (from Clipboard) :\033[0m"
    xclip -o
    echo
    echo -e "\033[0;90m[<] Standard Output :\033[0m"
    xclip -o | ./a.out
    local exit_code=$?
    echo
    if [[ $exit_code -eq 0 ]]; then
        box 1; echo -e "\033[0;32mExecuted Successfully!\033[0m"
    else
        box 0; echo -e "\033[0;31mRuntime Error (Exit Code: $exit_code)\033[0m"
    fi
}

a() {
    ./a.out
    local exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        echo; box 1; echo -e "\033[0;32mExecuted Successfully!\033[0m"
    else
        echo; box 0; echo -e "\033[0;31mRuntime Error (Exit Code: $exit_code)\033[0m"
    fi
}

out() {
    ./a.out < ./in.txt > ./out.txt
    local exit_code=$?
    if [[ $exit_code -eq 0 ]]; then
        box 1; echo -e "\033[0;32mExecuted Successfully! Output saved to out.txt\033[0m"
    else
        box 0; echo -e "\033[0;31mRuntime Error (Exit Code: $exit_code)\033[0m"
    fi
}

ca() { c "$1" && a; }
cq() { c "$1" && q; }
m() { c memo; }

naive() {
    inner_compile
    g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG naive.cpp -o naive_
    if [[ $? -eq 0 ]]; then
        box 1; echo -e "\033[0;32mCompiled 'naive.cpp' successfully!\033[0m"
    else
        box 0; echo -e "\033[0;31mFailed to compile 'naive.cpp'.\033[0m"
    fi
}

random() {
    inner_compile
    g++ -std=c++20 -I . -Wall -O2 -D_GLIBCXX_DEBUG random.cpp -o random_
    if [[ $? -eq 0 ]]; then
        box 1; echo -e "\033[0;32mCompiled 'random.cpp' successfully!\033[0m"
    else
        box 0; echo -e "\033[0;31mFailed to compile 'random.cpp'.\033[0m"
    fi
}

v() {
    if [[ "$curfile" == "0" || ! -f "$curfile" ]]; then
        box 0; echo -e "\033[0;31mFile is not specified. Compile a file with 'c' first.\033[0m"; return 1
    fi
    if ! command -v xclip &> /dev/null; then
        box 0; echo -e "\033[0;31m'xclip' is not installed.\033[0m"; return 1
    fi

    grep -vE "(^\s*//|^.*(?:cerr|print|_internal/cpp-dump-main/cpp-dump\.hpp).*$)" "$curfile" > ./combined.cpp
    if [[ -f "./expander.py" ]]; then
        python -X utf8 expander.py ./combined.cpp
    fi
    
    box 1; echo -e "\033[0;32mExpanded Successfully!\033[0m"
    cat ./combined.cpp | xclip -selection clipboard
    box -1; echo -e "\033[0;36mCopied to Clipboard (Without Comments and Debugs)\033[0m"
}

debug() {
    local trial_count=${1:-100}
    > ./WA_input.txt
    local ac_count=0
    
    for exe in ./random_ ./naive_ ./a.out; do
        if [ ! -x "$exe" ]; then
            box 0; echo -e "\033[0;31mExecutable not found: $exe\033[0m"; return 1
        fi
    done

    for i in $(seq 1 $trial_count); do
        local input=$(./random_)
        local ans=$(echo "$input" | ./naive_ 2>/dev/null)
        local naive_exit_code=$?
        local myans=$(echo "$input" | ./a.out 2>/dev/null)
        local my_exit_code=$?
        
        if [[ $my_exit_code -ne 0 ]]; then
            echo -en "\033[0;31m x \033[0m"; { echo "# Case $i (RE)"; echo -n "$input"; echo "[+] $ans"; } >> ./WA_input.txt
            continue
        fi
        if [[ $naive_exit_code -ne 0 ]]; then echo -en "\033[0;33m ! \033[0m"; continue; fi

        local normalized_ans=$(echo "$ans" | tr -s '[:space:]' ' ' | sed 's/ *$//;s/^ *//')
        local normalized_myans=$(echo "$myans" | tr -s '[:space:]' ' ' | sed 's/ *$//;s/^ *//')

        if [[ "$normalized_ans" == "$normalized_myans" ]]; then
            echo -en "\033[0;32m + \033[0m"; ((ac_count++))
        else
            echo -en "\033[0;31m x \033[0m"; { echo "# Case $i (WA)"; echo -n "$input"; echo "[+] $ans"; echo "[x] $myans"; } >> ./WA_input.txt
        fi
    done

    echo
    if [[ $ac_count -eq $trial_count ]]; then
        box 1; echo -e "\033[0;32mPassed $trial_count Testcases!\033[0m"
    else
        local failed_count=$((trial_count - ac_count))
        box 0; echo -e "\033[0;31mFailed in $failed_count/$trial_count Testcases!\033[0m"
        box -1; echo -e "\033[0;36mFailing cases are in WA_input.txt\033[0m"
    fi
}

judge() {
    local trial_count=${1:-100}
    > ./WA_input.txt
    local ac_count=0

    for exe in ./random_ ./naive_ ./a.out; do
        if [ ! -x "$exe" ]; then box 0; echo -e "\033[0;31mExecutable not found: $exe\033[0m"; return 1; fi
    done

    for i in $(seq 1 $trial_count); do
        local input=$(./random_)
        local myans=$(echo "$input" | ./a.out 2>/dev/null)
        if [[ $? -ne 0 ]]; then
            echo -en "\033[0;31m x \033[0m"; { echo "# Case $i (RE)"; echo -n "$input"; } >> ./WA_input.txt
            continue
        fi

        local judge_result=$(echo -e "$input\n$myans" | ./naive_ 2>/dev/null)
        if [[ "$judge_result" == "Yes" ]]; then
            echo -en "\033[0;32m + \033[0m"; ((ac_count++))
        else
            echo -en "\033[0;31m x \033[0m"; { echo "# Case $i (WA)"; echo -n "$input"; echo "[x] $myans"; } >> ./WA_input.txt
        fi
    done
    
    echo
    if [[ $ac_count -eq $trial_count ]]; then
        box 1; echo -e "\033[0;32mPassed $trial_count Testcases!\033[0m"
    else
        local failed_count=$((trial_count - ac_count))
        box 0; echo -e "\033[0;31mFailed in $failed_count/$trial_count Testcases!\033[0m"
        box -1; echo -e "\033[0;36mFailing cases are in WA_input.txt\033[0m"
    fi
}

match() {
    if [ ! -f ./out.txt ] || [ ! -f ./in.txt ]; then
        box 0; echo -e "\033[0;31m'in.txt' or 'out.txt' not found.\033[0m"; return 1
    fi

    local ans=$(cat ./out.txt)
    local myans=$(./a.out < ./in.txt)
    local exit_code=$?
    
    echo -e "\033[0;90m[=] Expected Output:\033[0m"; echo "$ans"
    echo; echo -e "\033[0;90m[<] Standard Output:\033[0m"; echo "$myans"; echo

    if [[ $exit_code -ne 0 ]]; then box 0; echo -e "\033[0;31mRE (Runtime Error)\033[0m"; return 1; fi

    local normalized_ans=$(echo "$ans" | tr -s '[:space:]' ' ' | sed 's/ *$//;s/^ *//')
    local normalized_myans=$(echo "$myans" | tr -s '[:space:]' ' ' | sed 's/ *$//;s/^ *//')
    
    if [[ "$normalized_ans" == "$normalized_myans" ]]; then
        box 1; echo -e "\033[0;32mAC (Accepted)\033[0m"
    else
        box 0; echo -e "\033[0;31mWA (Wrong Answer)\033[0m"
    fi
}

time() {
    echo -e "\033[0;90m[>] Standard Input :\033[0m"
    if [[ "$1" == "def" || -z "$1" ]]; then cat ./in.txt; else echo -e "\033[0;33m-- hidden --\033[0m"; fi
    echo; echo -e "\033[0;90m[<] Standard Output :\033[0m"

    local time_output=$( { time (./a.out < ./in.txt); } 2>&1 >/dev/tty)
    local exit_code=$?
    
    local real_time=$(echo "$time_output" | grep real | sed -E 's/.*m([0-9]+\.[0-9]{3})s/\1/')
    local msec=$(echo "$real_time * 1000" | bc)

    echo; echo "---------------------------------"
    box -1; echo -e "\033[0;36mExecution Time : ${msec%.*} ms\033[0m"
    echo "---------------------------------"

    if [[ $exit_code -eq 0 ]]; then
        echo; box 1; echo -e "\033[0;32mExecuted Successfully!\033[0m"
    else
        echo; box 0; echo -e "\033[0;31mRuntime Error (Exit Code: $exit_code)\033[0m"
    fi
}

# --- ヘルプ機能 ---
help() {
    local C_CMD='\033[1;36m'
    local C_ARG='\033[0;35m'
    local C_DESC='\033[0;90m'
    local C_NC='\033[0m'

    echo "競技プログラミング用ヘルパースクリプト コマンド一覧"
    echo
    echo -e "  ${C_CMD}c ${C_ARG}[file] (release)${C_NC}  ${C_DESC}C++ファイルをコンパイル (例: c a)${C_NC}"
    echo -e "  ${C_CMD}in (hide)${C_NC}             ${C_DESC}in.txtを標準入力として実行${C_NC}"
    echo -e "  ${C_CMD}q${C_NC}                      ${C_DESC}クリップボードの内容を標準入力として実行${C_NC}"
    echo -e "  ${C_CMD}a${C_NC}                      ${C_DESC}対話的に実行${C_NC}"
    echo -e "  ${C_CMD}out${C_NC}                     ${C_DESC}in.txtを入力とし、結果をout.txtに出力${C_NC}"
    echo -e "  ${C_CMD}ca ${C_ARG}[file]${C_NC}             ${C_DESC}コンパイルして対話的に実行${C_NC}"
    echo -e "  ${C_CMD}cq ${C_ARG}[file]${C_NC}             ${C_DESC}コンパイルしてクリップボードから実行${C_NC}"
    echo
    echo -e "  ${C_CMD}m${C_NC}                       ${C_DESC}memo.cpp をコンパイル${C_NC}"
    echo -e "  ${C_CMD}naive${C_NC}                   ${C_DESC}naive.cpp (正解コード)をコンパイル${C_NC}"
    echo -e "  ${C_CMD}random${C_NC}                  ${C_DESC}random.cpp (テストケース生成)をコンパイル${C_NC}"
    echo
    echo -e "  ${C_CMD}v${C_NC}                       ${C_DESC}提出用に整形してクリップボードにコピー${C_NC}"
    echo -e "  ${C_CMD}debug (count)${C_NC}           ${C_DESC}自動生成テストケースでストレステストを実行${C_NC}"
    echo -e "  ${C_CMD}judge (count)${C_NC}           ${C_DESC}インタラクティブ問題や複数解用のジャッジテスト${C_NC}"
    echo -e "  ${C_CMD}match${C_NC}                   ${C_DESC}a.outの出力とout.txtの内容を比較${C_NC}"
    echo -e "  ${C_CMD}time${C_NC}                    ${C_DESC}実行時間を計測${C_NC}"
    echo -e "  ${C_CMD}help${C_NC}                    ${C_DESC}このヘルプメッセージを表示${C_NC}"
    echo
}

box -1
echo -e "\033[0;36mCompetitive Programming helper script loaded. Type 'help' for commands.\033[0m"
