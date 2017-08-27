# $1 is {fileDirname}
# $2 is {fileBasename}
# $3 is {fileBasenameNoExtension}

fileDirname=$1
fileBasename=$2
fileBasenameNoExtension=$3
extension=.out

export fileDirname
export fileBasename
export fileBasenameNoExtension

clang++ -std=c++11 -Wall $fileDirname/$fileBasename -o $fileDirname/$fileBasenameNoExtension$extension