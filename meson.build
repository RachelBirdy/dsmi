project('DSMIDIWiFi', 'cpp')

system_dir = build_machine.system()
incdirs = include_directories(system_dir)
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

qt5 = import('qt5')
qt5_dep = dependency('qt5', modules: ['Core', 'Gui', 'Network', 'Widgets'])
deps = [qt5_dep]

if system_dir == 'windows'
  sources += [system_dir + '/midiports.cpp']

  windows = import('windows')
  sources += windows.compile_resources(system_dir + '/icon.rc',
                                       include_directories: incdirs)
endif

if system_dir == 'linux'
  deps += dependency('alsa')
endif

moc_files = qt5.compile_moc(headers: moc_headers,
                            include_directories: incdirs,
                            dependencies: qt5_dep)
res_files = qt5.compile_resources(sources: [system_dir + '/images.qrc'])

executable('DSMIDIWiFi',
           sources, moc_files, res_files,
           include_directories: incdirs,
           dependencies: deps)
