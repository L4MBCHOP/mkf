#ifndef __HELP_TEXT_H__
#define __HELP_TEXT_H__


const char help[] = "\n\
MKF\n\
    A cli utility for generating sets of files\n\
\n\
Usage\n\
    mkf.exe [-h] [-v] [-d] [-RtX | -RbX] [filename(s)] ... [filenameSet(s)] ...\n\
\n\
    -h\n\
        Help. Display this help.\n\
    -v\n\
        Verbose. Print Info To Console.\n\
    -d\n\
        Dryrun. don't actualy create the files just print to console what would \n\
        have been done.\n\
    -RbX / -RtX\n\
        Random Binary/Text. Generate random data in the file. Replace X with the\n\
        size of the file in bytes, the postfixes of K, M, and G can be used and\n\
        refer to KibiBytes, MibiBytes and GigiBytes respectively. If more than \n\
        one of these options exist in the command only the first is accepted the\n\
        others are ignored.\n\
        e.g.\n\
            '-Rb1024' make file(s) with random binary data 1024 bytes long\n\
            '-Rt1K'   make file(s) with random text data 1024 bytes long \n\
\n\
    filenames / filename Sets\n\
        filenames:\n\
        Single filenames can be anything that does not match a Filename Set or\n\
        one of the previous options.\n\
        e.g.\n\
            'myfile.txt' or 'FileWithNoExtension'\n\
\n\
        filename Sets:\n\
        use the format <filename>.[<exention1>;<extention2>;...;<extentionN>]\n\
        e.g.\n\
            'myfile.[c;h]' will result in 2 files; 'myfile.c' and 'myfile.h'\n\
\n\
"; 

#endif //__HELP_TEXT_H__