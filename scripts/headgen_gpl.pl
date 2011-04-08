#! /usr/bin/perl -w
use strict;
use POSIX qw(strftime);

my $delfile = "rm";
my $scriptName = "HeadGenerator";

# cmtb表示注释开始，cmte表示注释结束，cmtl将添加到每行行首
# 现在为C语言设置的，想要使之适用于其它语言，如vb,只需要修改这三项就可以了
# 数组pts是头部信息的种类，想要添加信息，如emal,直接在相应的行上创建这一项就行了
# 要处理的文件可以用headgen.pl filename来指写，也可以运行脚本后输入
my $cmtb = '/* ';
my $cmte = ' */';
my $cmtd = ''; 
my $cmtl = ' * ';
my $liscence = '
    This file is part of qastro.

    qastro is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    qastro is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with qastro.  If not, see <http://www.gnu.org/licenses/>.

';
my $titl = 'Copyright(C): Leaf Johnson <leafjohn@gmail.com> 2011';
my @pts = (
    );

my $fn;
my $tfn;
my $iscr = 0;
my $smod = '';
($fn, $smod) = @ARGV;
if(!defined($fn)){
    $fn = <STDIN>;
    chomp $fn;
}
print "$scriptName Openning...... $fn\n";
if(-e $fn){
    print "File Exists\n";
    $tfn = $fn.'.tmp';
    $iscr = 1;
    rename $fn, $tfn;
    open FH, '>'.$fn || die "I can not open target file";
}
else{
    $iscr = 0;
    open FH, '>'.$fn || die "I can not open target file";
}
print "$scriptName Opened!        $fn\n";

print FH $cmtb.$titl."\n";
print FH $liscence."\n";
print FH $cmtl.$cmtd."\n";
for my $pt(@pts){
    my $input='';
    print $pt;
    if( $smod =~ m/s/  ){
	    $input = '';
    }else{
	    $input = <STDIN>;
	    chomp $input;
    }
    if($input =~ m/^\s*$/ ){
	if($pt =~ m/FileName/){
	    $input = $fn;
	    $input =~ s(\\)(/)g;
	    $input =~ s(^.*/)()g;
	}
	elsif($pt =~ m/Date/){
	    $input = localtime;
	}
	elsif($pt =~ m/Ver/){
	    $input = "1.0";
	}
	elsif($pt =~ m/Code/){
	    $input = "Leaf";
	}
	else{
	    $input = "  ";
	}
	print $pt.$input." (Default)\n";
	print FH $cmtl.$pt.$input."\n";
    }
    else{
	print FH $cmtl.$pt.$input."\n";
    }
}
print FH $cmtl.$cmtd."\n";
print FH $cmte."\n";


if($iscr){
    print FH "\n\n";
    open  FTH, $tfn || die "I cant open tmp file";
    while(<FTH>){
        print FH;
    }
    close FTH;
    system($delfile, $tfn);
}
close FH;

print "$scriptName - $fn ...................OK!\n";
