package test_lib;
use strict;
use warnings;
use File::Path qw(make_path);
use Exporter 'import';

our @EXPORT_OK = qw(gen_cmake gen_base_dir run_test tool_check);

sub write_cmake {
    my ($cmakeFile, $test_name, $cmake_source) = @_;

    print $cmakeFile "$cmake_source";
}

sub gen_cmake {
    my ($test_name, $cmake_source) = @_;
    my $fileName = "CMakeLists.txt";

    if(! -e $fileName) {
        print("[WARN] Could not find $fileName. Generate new now.\n");
        open(my $cmakeFile, ">", "$fileName") or die "[ERR] Could not generate CMake with error: $!\n";
        
        write_cmake($cmakeFile, $test_name, $cmake_source);
        close($cmakeFile);

        print("\n[INFO] Generate $fileName successfully.\n");
    }
}

sub gen_cpp_test {
    my ($cpp_file_path, $cpp_source) = @_;
    print $cpp_file_path "$cpp_source";
}

sub gen_base_dir {
    my $base_dir = "src";
    my $build_dir = "$base_dir/build";
    my ($cpp_source, $source_type) = @_;
    my $source_main = "$base_dir/main.$source_type";

    if(! -d $base_dir) {
        print "Could not find $base_dir. Generate now...";
        make_path($build_dir) or die "Could not generate $base_dir & $build_dir $!\n";

        open(my $cpp_file, ">", $source_main) or die "[ERR] Could not generate C++ source with error: $!\n";
        gen_cpp_test($cpp_file, $cpp_source);

        print "Generate C++ Test base successfully.\n";
        close($cpp_file);
        
        return $build_dir;
    }

    return $build_dir;
}

sub run_test {
    my ($build_dir, $test_name) = @_;
    chdir $build_dir or die "Could not change directory to: $build_dir with error: $!\n";

    my $cmake_rc = system("cmake", "../..");
    die "[ERR] CMake error" if $cmake_rc != 0;

    my $make_rc = system("make");
    die "[ERR] Makefile error" if $make_rc != 0;

    my $program = system("./$test_name");
    die "[ERR] Test FAILED" if $program != 0;
}

sub tool_check {
    my ($cmd) = @_;
    my $found = system("which $cmd > /dev/null 2>&1") == 0;

    return $found;
}

1;