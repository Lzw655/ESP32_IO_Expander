idf_component_register(SRCS "test_ESP_IOExpander.cpp")

target_compile_options(${COMPONENT_LIB} PRIVATE -Wno-missing-field-initializers)
