AUTOMAKE_OPTIONS = foreign


AM_LDFLAGS = -L$(libdir)

INCLUDES = -I$(includedir) 


include_HEADERS = 

lib_LTLIBRARIES =  librcdaqplugin_mvtx_file.la



librcdaqplugin_dam_la_SOURCES = \
	daq_device_mvtx_file.cc \
	mvtx_fileTriggerHandler.cc \
	mvtx_file_plugin.cc



clean-local:
	rm -f $(BUILT_SOURCES)
