project('DSMIDIWiFi', 'cpp')

compiler = meson.get_compiler('cpp')
system_dir = build_machine.system()

incdirs = include_directories(system_dir)

if system_dir == 'linux'
  moc_headers = [
    system_dir + '/midi2udpthread.h',
    system_dir + '/udp2midithread.h',
    system_dir + '/wifimidiwindow.h'  
  ]
  sources = [
    system_dir + '/dswifimidi.cpp',
    system_dir + '/midi2udpthread.cpp',
    system_dir + '/udp2midithread.cpp',
    system_dir + '/wifimidiwindow.cpp'
  ]
else
  moc_headers = [
    system_dir + '/midi2udp.h',
    system_dir + '/udp2midi.h',
    system_dir + '/wifimidiwindow.h'  
  ]
  sources = [
    system_dir + '/dswifimidi.cpp',
    system_dir + '/midi2udp.cpp',
    system_dir + '/udp2midi.cpp',
    system_dir + '/wifimidiwindow.cpp'
  ]
endif

qt6 = import('qt6')
qt6_dep = dependency('qt6', modules: ['Core', 'Gui', 'Network', 'Widgets'])
deps = [qt6_dep]

if system_dir == 'windows'
  sources += [system_dir + '/midiports.cpp']

  windows = import('windows')
  sources += windows.compile_resources(system_dir + '/icon.rc',
                                       include_directories: incdirs)

  deps += compiler.find_library('ws2_32', required: true)
  deps += compiler.find_library('winmm', required: true)
endif

if system_dir == 'linux'
  deps += dependency('alsa')
endif

moc_files = qt6.compile_moc(headers: moc_headers,
                            include_directories: incdirs,
                            dependencies: qt6_dep)
res_files = qt6.compile_resources(sources: [system_dir + '/images.qrc'])

executable('DSMIDIWiFi',
           sources, moc_files, res_files,
           include_directories: incdirs,
           dependencies: deps)
