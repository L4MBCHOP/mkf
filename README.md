# mkf
A cli utility for generating files

Are you tired of having to pipe to a file to create it?

do you need a couple files of the same name all with different file extentions?

do you need a random or arbitrary data file of an arbitrary size?

if you answered yes to any of the above then mkf is for you. 

## Current State of features

- [x] Ability to create Files
- [x] Creation w/ List of file extentions
- [x] Ability to generate random files w/ Arbitrary size

## Usage Examples

To make a file: 
    `mkf filename.txt`

To make multiple files:
    `mkf fileOne.txt fileTwo.bin fileThree.c fileN.whatever`

To make multiple files Having the same name but different extentions:
    `mkf fileName.[a;b;c;d;potato;tar.gz]`

    results in the following empty files being created:
        filename.a
        filename.b
        filename.c
        filename.d
        filename.potato
        filename.tar.gz

To Make a file with 1KB (1024 bytes) of random binary data:
    `mkf -Rb 1024 randomJunk.bin`

To Make a file with 1KB (1024 bytes) of random text data (Giberish):
    `mkf -Rt 1K randomJunk.txt`

To fill up your hard drive with garbage (generally don't do this):
    `mkf -Rb 10G  lotsofFiles.[a;b;c;d;e;f;g;h;i;j;k;l;m;n;o;p;q;r;s;t;u;v;w;x;y;z]`