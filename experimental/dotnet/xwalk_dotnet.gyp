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
    },
    # We compile here the csharp with msbuild but that's not needed, we expect people to do so themselves
    # OutDir here doesn't work because PRODUCT_DIR is relative and msbuild doesn't work with that,
    # thus the copy below. For the auto-tests where we're going to compile the csharp, we need to
    # convert the relative to absolute, probably with a tiny python script.
    {
      'target_name': 'compile_csharp',
      'type': 'none',
      'variables': {
        'parameters':
            '/p:Configuration=Release,Platform=AnyCPU,OutDir=<(PRODUCT_DIR)',
      },
      'actions': [{
        'action_name': 'compile',
        'inputs': [ 'csharp/hello.cs' ],
        'outputs': [ 'xwalk_csharp.dll' ],
        'message': 'msbuild xwalk_csharp.csproj',
        'action': ['msbuild', 'csharp/xwalk_csharp.csproj', '/p:Configuration=Release,Platform=AnyCPU,OutDir=<(PRODUCT_DIR)']
      }]
    },
    {
      'target_name': 'xwalk_csharp',
      'type': 'none',
      'dependencies': [
        'compile_csharp',
      ],
      'copies': [
        {
          'destination': '<(PRODUCT_DIR)',
          'files': [
            'csharp/obj/Release/xwalk_csharp.dll',
            'csharp/obj/Release/xwalk_csharp.pdb',
          ],
        },
      ],
    },
    {
      'target_name': 'xwalk_mixeddll',
      'type': 'shared_library',
      'sources': [
        'glue/hello.cc',
        'glue/hello.h',
        'glue/AssemblyInfo.cc'
      ],
      'defines': [
        'NATIVEDLL_EXPORTS',
      ],
      'dependencies': [
        'xwalk_csharp',
      ],
      'msvs_settings': {
        'VCCLCompilerTool': {
          'RuntimeTypeInfo': 'true',
          'CompileAsManaged':'true',
        }
      },
     },
  ],
}
