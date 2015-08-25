{
  'target_defaults': {
    'variables': {
      'win_debug_RuntimeChecks': '0',
    },
  },
  'targets': [
    {
      'target_name': 'xwalk_cplusplus',
      'type': 'static_library',
      'dependencies': [
        '../../../base/base.gyp:base',
        '../../extensions/extensions.gyp:xwalk_extensions',
        '../../xwalk.gyp:xwalk_resources',
        'xwalk_mixeddll',
      ],
      'sources': [
        'dotnet_extension.h',
        'dotnet_extension.cc',
      ],
      'link_settings': {
        'libraries': [
          #'-lxwalk_mixeddll',
          #'-lxwalk_csharp.dll',
       ],
      },
    },
    {
      'target_name': 'xwalk_csharp',
      'type': 'none',
      'actions': [{
        'action_name': 'compile',
        'inputs': [ 'csharp/hello.cs'],
        'outputs': [ 'xwalk_csharp.dll' ],
        'message': 'msbuild xwalk_csharp.csproj',
        'action': ['msbuild', 'csharp/xwalk_csharp.csproj', '/p:Configuration=Release,Platform=AnyCPU']
      }]
    },
    #{
    #  'target_name': 'xwalk_mixeddll',
    #  'type': 'none',
    #  'actions': [{
    #    'action_name': 'compile',
    #    'inputs': [ 'glue/hello.cc', 'glue/hello.h'],
    #    'outputs': [ 'xwalk_mixeddll.dll' ],
    #    'message': 'msbuild xwalk_mixeddll.vcxproj',
    #    'action': ['msbuild', 'glue/xwalk_mixeddll.vcxproj', '/p:Configuration=Debug,Platform=AnyCPU,OutputPath=<(PRODUCT_DIR)']
    #  }]
    #},
    {
      'target_name': 'xwalk_mixeddll',
      'type': 'shared_library',
      'sources': [
        'glue/hello.cc',
        'glue/hello.h',
        'glue/AssemblyInfo.cc'
      ],
      'msvs_settings': {
        'VCCLCompilerTool': {
          'RuntimeTypeInfo': 'true',
          #'BasicRuntimeChecks': '<(win_debug_RuntimeChecks)',
          'CompileAsManaged':'true',
        }
      },
      'msbuild_settings': {
        'ClCompile': {
          'RuntimeTypeInfo': 'true',
          #'BasicRuntimeChecks': '<(win_debug_RuntimeChecks)',
          'CompileAsManaged':'true',
         }
      }
     },
  ],
}
