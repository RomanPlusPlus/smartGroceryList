import os
import sys
import ycm_core

def DirectoryOfThisScript():
    return os.path.dirname(os.path.abspath(__file__))

preferred_build_type = 'debug'

flags = [
    '-std=c++11'
    ,'-Wall'
    ,'-Wextra'
    ,'-Wconversion'
    ,'-Wno-deprecated'
    ,'-I%s' % os.path.join(DirectoryOfThisScript(), 'build', preferred_build_type, 'src')
    ,'-I%s' % os.path.join(DirectoryOfThisScript(), 'src')
]

compilation_database_folder = os.path.join(DirectoryOfThisScript(), 'build')

configurations = ['debug', 'release']
databases = []
for conf in configurations:
    path = os.path.join(compilation_database_folder, conf)
    if os.path.exists(path):      
        databases.append(ycm_core.CompilationDatabase(path))

SOURCE_EXTENSIONS = ['.cpp', '.cxx', '.cc', '.c', '.m', '.mm']

def MakeRelativePathsInFlagsAbsolute(flags, working_directory):
    if not working_directory:
        return list(flags)

    new_flags = []
    make_next_absolute = False
    path_flags = [ '-isystem', '-I', '-iquote', '--sysroot=' ]
    for flag in flags:
        new_flag = flag

        if make_next_absolute:
            make_next_absolute = False
            if not flag.startswith( '/' ):
                new_flag = os.path.join(working_directory, flag)

        for path_flag in path_flags:
            if flag == path_flag:
                make_next_absolute = True
                break

            if flag.startswith( path_flag ):
                path = flag[ len( path_flag ): ]
                new_flag = path_flag + os.path.join(working_directory, path)
                break

        if new_flag:
            new_flags.append( new_flag )
    return new_flags


def IsHeaderFile(filename):
   extension = os.path.splitext(filename)[1]
   return extension in ['.h', '.hxx', '.hpp', '.hh']


def GetCompilationInfoForFileInDb(database, filename):
   # The compilation_commands.json file generated by CMake does not have entries
   # for header files. So we do our best by asking the db for flags for a
   # corresponding source file, if any. If one exists, the flags for that file
   # should be good enough.
   if IsHeaderFile(filename):
      basename = os.path.splitext(filename)[0]
      for extension in SOURCE_EXTENSIONS:
         replacement_file = basename + extension
         if os.path.exists(replacement_file):
            compilation_info = database.GetCompilationInfoForFile(replacement_file)
            if compilation_info.compiler_flags_:
               return compilation_info
      return None
   return database.GetCompilationInfoForFile(filename)

def GetCompilationInfoForFile(filename):
   for db in databases:
      info = GetCompilationInfoForFileInDb(db, filename)
      if info is None:
         continue
      else:
         return info
   return None

def FlagsForFile(filename, **kwargs):
    if len(databases) != 0:
        # Bear in mind that compilation_info.compiler_flags_ does NOT return a
        # python list, but a "list-like" StringVec object
        compilation_info = GetCompilationInfoForFile(filename)
        if not compilation_info:
            relative_to = DirectoryOfThisScript()
            final_flags = MakeRelativePathsInFlagsAbsolute(flags, relative_to)
        else:
            final_flags = MakeRelativePathsInFlagsAbsolute(compilation_info.compiler_flags_, compilation_info.compiler_working_dir_)
    else:
        relative_to = DirectoryOfThisScript()
        final_flags = MakeRelativePathsInFlagsAbsolute(flags, relative_to)

    return {
        'flags': final_flags,
        'do_cache': True
    }
