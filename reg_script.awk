#!/usr/bin/awk -f
# 説明：cat のような AWK スクリプト
# 使い方：cat.awk ファイル名 ...

{
	if (NF < 10) print $(NF-2),$(NF-1),$(NF)
	else print $(NF-7),$(NF-6),$(NF-5),$(NF-4),$(NF-3),$(NF-2),$(NF-1),$(NF-0)
}
